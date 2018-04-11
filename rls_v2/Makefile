CROSS_COMPILE=
CC=$(CROSS_COMPILE)gcc

all: xdr server client

xdr: 
	rpcgen dir.x
server: 
	$(CC) dir_xdr.c dir_svc.c dir_proc.c dir_local.c -lnsl -o dir_svc
client: 
	$(CC) dir_xdr.c dir_clnt.c dir_common.c dir_local.c rls.c -lnsl -o rls
clean:
	rm -f *.o dir_svc rls
