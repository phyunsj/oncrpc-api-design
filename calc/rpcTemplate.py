#!/usr/bin/env python

class rpcTemplate(object):

    def __init__ (self):
        pass
    
    rpc_clnt_h = '''
${func_ret} ${FUNC_NAME} ( HANDLER *remote ${func_arg_list} );
'''
    rpc_clnt_c = '''


${func_ret} ${FUNC_NAME} ( HANDLER *remote ${func_arg_list} )  
{
  
  int ret = 0;

  if ( remote != NULL &&  remote->clnt != (CLIENT *)NULL ) {

    ${func_name}_req req;
    ${func_name}_res *res;

    memset(&req, 0, sizeof(${func_name}_req));

    /* request */
    ${param_marshalling}

    if ( debug_ ) fprintf(stdout, "->Sent ${func_name} req\\n"); 
    
    res = ${func_name}_func_1( &req, remote->clnt );
    if (res == (${func_name}_res *) NULL) { 
      clnt_perror (remote->clnt, "[RPC] ${func_name} failed\\n");
      return -1;
    }

    ret = res->errcode;
    if ( ret == 300 /* SUCCESS */ ) {
    /* response */
    ${param_unmarshalling}
    
    }
    
    return ${return_stmt};
  } else {

    return ${func_name}( ${func_param_list} );

  }

}

'''


    rpc_svc_ = '''

${func_name}_res * 
${func_name}_func_1_svc ( f_req  , req ) 
      ${func_name}_req  *f_req;
      struct svc_req    *req;
{
    static ${func_name}_res res;
    ${param_list}

    /* request */
    ${param_marshalling}

    res.errcode = ${return_void} ${func_name} ( ${arg_list} );

    if( res.errcode == 300 ) {
    
    /* response */
    ${param_unmarshalling}
    
    }

    return (&res);
} 

'''

