CROSS_COMPILE=
CC=$(CROSS_COMPILE)gcc

all:  cpp  codegen  xdr client server 

cpp:
	cpp cl_calc.h -o cl_calc.i

codegen:
	python generator.py  cl_calc.i

xdr: 
	rpcgen --version
	rpcgen CL.x

server: 
	$(CC) --version
	$(CC) CL_xdr.c CL_svc.c  CL_svc_proc.c   cl_calc.c -lnsl -o calc_server

client:
	$(CC) CL_xdr.c CL_clnt.c CL_proc.c  cl_calc.c cl_common.c cl_client.c -lnsl -o calc_client

clean:
	rm -f *.o calc_server calc_client *.pyc
