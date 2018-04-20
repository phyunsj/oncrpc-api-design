#!/usr/bin/python

from __future__ import print_function
from pprint import pprint
from string import Template
import argparse
import sys, os

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
sys.path.extend(['.', '..'])

from pycparser import c_parser, c_ast, parse_file

scriptpath = "./rpcTemplate.py"
sys.path.append(os.path.abspath(scriptpath))
from rpcTemplate import *


class FuncCallVisitor(c_ast.NodeVisitor):
    def __init__(self):
        # [ { name : xxx, return : xxx, params : [ { name : xxx, ref : 0 }, ...] }, ... ]
        self.functions = []
        self.typedefs = []
        self.typedefs_struct = []
        self.primitive_types = ['void', 'short','int','long','unsigned short','unsigned int', 'unsigned long']

    def search_typedef( self, type_name) :       
        for item in self.typedefs :
            #print(item)
            if item['name'] == type_name :
                return item['type_origin']
        return 'unknown'

    def dump(self):
        return { 'func' : self.functions , 'typedef' : self.typedefs, 'typedef-struct' : self.typedefs_struct }

    def visit_FuncDecl (self, node):
        #if isinstance(node, c_ast.FuncDecl):
        #   pass
        func = {}
        params = []
        # parameter
        if isinstance(node.args, c_ast.ParamList):
            unnamed_counter = 10
            for param in node.args.params :
                ptr = 0
                args_list = { 'ptr' : 0 }  
                if isinstance(param, c_ast.Decl): 
                   # named parameter
                   args_list['direction'] = param.name
                else:
                   args_list['direction'] = 'in'+str(unnamed_counter) # c_ast.Typename
                   unnamed_counter =  unnamed_counter + 1

                if isinstance(param.type, c_ast.PtrDecl):
                      args_list['ptr'] = 1
                      args_list['type'] = ' '.join(param.type.type.type.names)
                if isinstance(param.type, c_ast.TypeDecl):
                      args_list['type'] = ' '.join(param.type.type.names)

                params.append(args_list)

        func['params'] = params
        # function name
        if isinstance(node.type, c_ast.TypeDecl):
            #print("TypeDecl:", node.type.declname )
            func['name'] = node.type.declname
            # return type
            if isinstance(node.type.type, c_ast.IdentifierType):
                #print("IdentifierType:", node.type.type.names[0] )
                func['return'] = ' '.join(node.type.type.names)
        self.functions.append(func)

    def visit_TypeDecl (self, node):
        typedef = {}
        params = []
        if isinstance(node.type, c_ast.IdentifierType):
            typedef['name'] = node.declname
            typedef['type'] = ' '.join(node.type.names)
            if typedef['type'] in self.primitive_types :
               typedef['type_origin'] = typedef['type']
            else:
               # find from self.typedefs
               typedef['type_origin'] = self.search_typedef( typedef['type'] )
            self.typedefs.append(typedef)
        elif isinstance(node.type, c_ast.Struct):
            typedef['name'] = node.type.name
            for param in node.type.decls :
                params.append( { 'name' : param.type.declname ,'type' : ' '.join(param.type.type.names) })
            typedef['type'] = params
            self.typedefs_struct.append(typedef)
            typedef['type_origin'] = 'struct'
            self.typedefs.append(typedef)
        else:
            pass     



class CodeGenerator ( rpcTemplate ):
    def __init__ (self, symtab) :
        self.product = 'CL'
        self.version = '1'
        self.program = '0x20000001'
        self.symtab  = symtab
        self.primitive_types = ['void', 'short','int','long','unsigned short','unsigned int', 'unsigned long']

    def search_type(self, searchType) :
        for typedef in  self.symtab['typedef'] :
            if typedef['name'] == searchType : 
                if typedef['type_origin'] != 'struct' :
                    return typedef['type_origin']
                else:
                    return typedef['name']+'_s'
        # primitive type already. just return it
        return searchType 
    
    def find_type(self, searchType) :
        if searchType in self.primitive_types :
           return 1
        for typedef in  self.symtab['typedef'] :
            if typedef['name'] == searchType : 
                if typedef['type_origin'] in self.primitive_types :
                    return 1
                else:
                    return 0
        return 0

    def print_pointer(self, ptr) :
        if ptr == 1 :
           return '*'
        else:
           return ''

    def print_void(self, ptr) :
        if ptr == 'void' :
           return ' 300; '
        else:
           return ''
    
    def print_ref(self, ptr) :
        if ptr == 1 :
           return ''
        else:
           return '&'

    def print_r_ref(self, ptr) :
        if ptr == 1 :
           return '&'
        else:
           return ''

    def print_comma(self, idx) :
        if idx == 0 :
           return ''
        else:
           return ','

    def print_ret(sefl, type) :
        if type == 'void' :
           return ''
        else:
           return 'ret'

    def gen_xdr(self):
        self.xdr   = open('./'+self.product.upper()+'.x', 'w') 

        # typedef struct 
        for typedef in  self.symtab['typedef'] :
            if typedef['type_origin'] == 'struct' :  
                self.xdr.write('\n\nstruct '+ typedef['name']+'_s {')
                for member in typedef['type'] :
                    self.xdr.write('\n\t'+self.search_type(member['type'])+' '+member['name']+';')
                self.xdr.write('\n};\ntypedef struct '+ typedef['name']+'_s '+ typedef['name']+'_s;')

        # func req/res
        for idx, func in  enumerate(self.symtab['func']) :
            
            counter_in  =0
            counter_out = 0
            list_input = ''
            list_output = ''
            for idx2, params in enumerate(func['params']) :
                if params['direction'].startswith('in') or params['direction'].startswith('inout') :
                    counter_in = counter_in + 1
                    list_input = list_input + '\n\t'+self.search_type(params['type'])+' __'+params['direction']+';'
                if params['direction'].startswith('inout') or params['direction'].startswith('out') :
                    counter_out = counter_out + 1
                    list_output = list_output + '\n\t'+self.search_type(params['type'])+' __'+params['direction']+';'
            # req
            self.xdr.write('\n\nstruct '+func['name'].lower()+'_req {')
            if counter_in > 0 :
                self.xdr.write(list_input)
            else:
                self.xdr.write('\tint errcode; /* void */')
            self.xdr.write('\n};\ntypedef struct '+func['name'].lower()+'_req '+func['name'].lower()+'_req;\n')
            # res
            self.xdr.write('\nstruct '+func['name'].lower()+'_res_t {')
            if counter_out > 0 :
                self.xdr.write(list_output)
            else:
                self.xdr.write('\tint errcode; /* void */')
            self.xdr.write('\n};\ntypedef struct '+func['name'].lower()+'_res_t '+func['name'].lower()+'_res_t;\n')
            # res union
            self.xdr.write('\nunion '+func['name'].lower()+'_res switch(int errcode) {')
            self.xdr.write('\n\tcase 300  : '+func['name'].lower()+'_res_t __res;')
            self.xdr.write('\n\tdefault : void;\n};')

        # func
        self.xdr.write('\n\nprogram '+self.product+'PROG {\n')
        self.xdr.write('\tversion '+self.product+'VERS {\n')

        for idx, func in  enumerate(self.symtab['func']) :
            self.xdr.write('\t\t'+func['name'].lower()+'_res '+func['name'].upper()+'_FUNC ( '+func['name'].lower()+'_req ) = '+str(idx+1)+';\n')
        
        self.xdr.write('\t} = '+self.version+';\n')
        self.xdr.write('} = '+self.program+';\n')
        self.xdr.close()


    def gen_client(self):
        
        self.client  = open(self.product.upper()+'_proc.c', 'w') 
        self.client_h  = open(self.product.upper()+'_proc.h', 'w') 
        self.client.write('#include "'+self.product+'.h"\n')
        self.client.write('#include "'+self.product.lower()+'_calc.h"\n\n')
        self.client.write('#include "'+self.product.lower()+'_common.h"\n\n')
        self.client.write('#define debug_  0\n')
        
        # for simplicity, repeat/separete unpack/pack code-generation
        for idx, struct in  enumerate(self.symtab['typedef-struct']) :
            self.client.write('\n\nvoid '+struct['name'].upper()+'_PACK ( '+struct['name']+'_s *to , /* <- */ '+struct['name']+' *from ) {')
            for member in struct['type'] :
                self.client.write('\n\tto->'+member['name']+' = from->'+member['name']+';')
            self.client.write('\n}')

        for idx, struct in  enumerate(self.symtab['typedef-struct']) :
            self.client.write('\n\nvoid '+struct['name'].upper()+'_UNPACK ( '+struct['name']+'_s *from , /* -> */ '+struct['name']+' *to ) {')
            for member in struct['type'] :
                self.client.write('\n\tto->'+member['name']+' = from->'+member['name']+';')
            self.client.write('\n}')
        # RPC res unpack
        for idx, func in  enumerate(self.symtab['func']) :
            unpack_stmt = ''
            res_counter = 1
            for idx2, param in enumerate(func['params']):
                if param['direction'].startswith('inout') or param['direction'].startswith('out'):
                  if not self.find_type(param['type']) :
                    self.client.write('\n\nvoid '+func['name'].upper()+'_UNPACK_'+str(res_counter)+'( '+func['name']+'_res_t *res, '+param['type']+' *'+param['direction'] +') {') 
                    self.client.write('\n\t\t'+param['type'].upper()+'_UNPACK( &res->__'+param['direction']+' , '+param['direction'] +' );')
                    self.client.write('\n}')  
                    res_counter = res_counter + 1
                       #unpack_stmt = unpack_stmt + '\n\t\tparam['type'].upper()+'_UNPACK_' ();


        for idx, func in  enumerate(self.symtab['func']) :
            arg_list = ''
            param_list = ''
            marshall_list = ''
            unmarshall_list = ''
            req_counter = 1
            res_counter = 1
            for idx2, param in enumerate(func['params']):
                arg_list =  arg_list + ', '+param['type']+' '+self.print_pointer(param['ptr'])+ param['direction']
                param_list = param_list +  self.print_comma(idx2) + param['direction']

                if param['direction'].startswith('in') :
                    if self.find_type(param['type']) :
                        marshall_list = marshall_list +'\n\t\treq.__'+param['direction']+' = '+self.print_pointer(param['ptr'])+param['direction']+';'
                    else:
                        marshall_list = marshall_list +'\n\t\t'+param['type'].upper()+'_PACK( &req.__'+param['direction']+' /* << */ ,'+ self.print_ref(param['ptr'])+param['direction'] +' );'
                        req_counter = req_counter + 1

                if param['direction'].startswith('inout') or param['direction'].startswith('out'):
                    if self.find_type(param['type']) :
                        unmarshall_list = unmarshall_list + '\n\t\t'+self.print_pointer(param['ptr'])+param['direction']+' = res->'+func['name'].lower()+'_res_u.__res.__'+ param['direction']+';'
                    else:
                        unmarshall_list = unmarshall_list + '\n\t\t'+func['name'].upper()+'_UNPACK_'+str(res_counter)+'( &res->'+func['name'].lower()+'_res_u.__res  /* >> */ ,'+ self.print_ref(param['ptr'])+param['direction'] +' );'
                        res_counter = res_counter + 1

            stmt = Template(self.rpc_clnt_c).safe_substitute( dict( \
                        FUNC_NAME=func['name'].upper(), \
                        func_name=func['name'].lower(), \
                        func_arg_list= arg_list, \
                        func_param_list= param_list,\
                        param_marshalling =marshall_list,\
                        param_unmarshalling =unmarshall_list,\
                        func_ret=func['return'], \
                        return_stmt=self.print_ret(func['return'])\
                         ))
            self.client.write( stmt ) 
            stmt = Template(self.rpc_clnt_h).safe_substitute( dict( \
                        FUNC_NAME=func['name'].upper(), \
                        func_name=func['name'].lower(), \
                        func_arg_list= arg_list, \
                        func_ret=func['return'] \
                         ))

            self.client_h.write( stmt ) 
        self.client.close()

    def gen_server(self):
        self.server  = open(self.product.upper()+'_svc_proc.c', 'w') 
        self.server.write('#include "'+self.product+'.h"\n')
        self.server.write('#include "'+self.product.lower()+'_calc.h"\n\n')
        self.server.write('#define debug_  0\n')
        
        # for simplicity, repeat/separete unpack/pack code-generation
        for idx, struct in  enumerate(self.symtab['typedef-struct']) :
            self.server.write('\n\nvoid '+struct['name'].upper()+'_UNPACK ( '+struct['name']+'_s *from , /* -> */ '+struct['name']+' *to ) {')
            for member in struct['type'] :
                self.server.write('\n\tto->'+member['name']+' = from->'+member['name']+';')
            self.server.write('\n}')

        for idx, struct in  enumerate(self.symtab['typedef-struct']) :
            self.server.write('\n\nvoid '+struct['name'].upper()+'_PACK ( '+struct['name']+'_s *to , /* <- */ '+struct['name']+' *from ) {')
            for member in struct['type'] :
                self.server.write('\n\tto->'+member['name']+' = from->'+member['name']+';')
            self.server.write('\n}')

        # RPC res pack
        for idx, func in  enumerate(self.symtab['func']) :
            unpack_stmt = ''
            res_counter = 1
            for idx2, param in enumerate(func['params']):
                if param['direction'].startswith('inout') or param['direction'].startswith('out'):
                  if not self.find_type(param['type']) :
                    self.server.write('\n\nvoid '+func['name'].upper()+'_PACK_'+str(res_counter)+'( '+func['name']+'_res_t *res, /* <- */ '+param['type']+' *'+param['direction'] +') {') 
                    self.server.write('\n\t\t'+param['type'].upper()+'_PACK( &res->__'+param['direction']+' , /* <- */ '+param['direction'] +' );')
                    self.server.write('\n}')  
                    res_counter = res_counter + 1
                       #unpack_stmt = unpack_stmt + '\n\t\tparam['type'].upper()+'_UNPACK_' ();

        
        for idx, func in  enumerate(self.symtab['func']) :
            arg_list = ''
            param_list = ''
            marshall_list = ''
            unmarshall_list = ''
            req_counter = 1
            res_counter = 1
            for idx2, param in enumerate(func['params']):
                param_list =  param_list + '\n\t\t' +param['type']+' '+param['direction']+';'
                arg_list = arg_list +  self.print_comma(idx2) + self.print_r_ref(param['ptr']) + param['direction']

                if param['direction'].startswith('in') :
                    if self.find_type(param['type']) :
                        marshall_list = marshall_list +'\n\t\t'+param['direction']+' = f_req->__'+param['direction']+';'
                    else:
                        marshall_list = marshall_list +'\n\t\t'+param['type'].upper()+'_UNPACK( &f_req->__'+param['direction']+' /* >> */ , &'+param['direction'] +' );'
                        req_counter = req_counter + 1

                if param['direction'].startswith('inout') or param['direction'].startswith('out'):
                    if self.find_type(param['type']) :
                        unmarshall_list = unmarshall_list + '\n\t\tres.'+func['name'].lower()+'_res_u.__res.__'+ param['direction']+' = '+param['direction'] +';'
                    else:
                        unmarshall_list = unmarshall_list + '\n\t\t'+func['name'].upper()+'_PACK_'+str(res_counter)+'( &res.'+func['name'].lower()+'_res_u.__res  /* << */ , &'+param['direction'] +' );'
                        res_counter = res_counter + 1        
            stmt = Template(self.rpc_svc_).safe_substitute( dict( \
                        FUNC_NAME=func['name'].upper(), \
                        func_name=func['name'].lower(), \
                        param_list=param_list, \
                        arg_list=arg_list,\
                        param_marshalling=marshall_list, \
                        param_unmarshalling=unmarshall_list, \
                        return_void=self.print_void(func['return'])\
                         ))

            self.server.write( stmt ) 
        
        self.server.close()

    def gen(self):
        self.gen_xdr()
        self.gen_server()
        self.gen_client()


if __name__ == "__main__":
    argparser = argparse.ArgumentParser('Scan AST & Create Symbol Table')
    argparser.add_argument('filename', help='name of file to parse')
    args = argparser.parse_args()

    ast = parse_file(args.filename, use_cpp=False)
    #ast.show()
    #for (child_name, child) in ast.children():
    #        child.show( sys.stdout ,
    #           offset= 2,
    #            attrnames=True,
    #            nodenames=True,
    #            showcoord=True,
    #            _my_node_name=child_name)

    v = FuncCallVisitor()
    v.visit(ast)
    #pprint(v.dump())

    rpc = CodeGenerator( v.dump() )
    rpc.gen()

    

