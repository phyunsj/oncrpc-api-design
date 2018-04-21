# ONC/RPC API Design


- Example 1 [rls](https://github.com/phyunsj/oncrpc-api-design/tree/master/rls) (remote `ls` - original version)

- Example 2 [rls_v2](https://github.com/phyunsj/oncrpc-api-design/tree/master/rls_v2) (revised)

- Example 3 [calc](https://github.com/phyunsj/oncrpc-api-design/tree/master/calc)

## Example 3 calc

**ONCRPC** restricted us to remote procedures that accept a single parameter and return a single parameter. (Might not be true now but stick to this restriction)

Instead of starting with **IDL** (like Example 1 & 2), start wtih **API.h** and generate ONCRPC middle-layer  automatically. Keep (or share) the same local implementation between RPC server and RPC client.


Similar to non-RPC application, the below files are manaully created. Create RPC middle-layer to integrate the local APIs defined in `cl_calc.h`. Use the same API locally or remotely. 

`cl_calc.c/h` : functions declaration, definition.

`cl_client.c` : client main program

`cl_common.c/h` : RPC Client handler

**CL** is an imaginary product name for example 3. 


1. **cpp** cl_calc.h -o cl_calc.i
2. **pycparser** to generate AST
3. AST visitor extracts ***typdef*** & *** fucntion declaration *** out of AST
4. generate IDL & RPC middle-layer Interface

The following files are generated from `cl_calc.h`

- CL.x (ONCRPC IDL)
- CL_proc.c (Client Middlelayer)
- CL_svc_proc.c (Server Middlelayer)
- CL_proc.h

`CL.x` generates :

- CL.h
- CL_svc.c
- CL_clnt.c
- CL_xdr.c


## FYI

### pycparser

Complete C99 parser in pure Python

**pycparser** installation. ( powered by [PLY](https://github.com/dabeaz/ply) )

> pip install --index-url=https://pypi.python.org/simple/  pycparser 
