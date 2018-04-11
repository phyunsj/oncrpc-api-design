/*
 * rls.c: Remote directory listing client
 */
 
#include <stdio.h>
#include "dir.h"                       /* generated by rpcgen */
 
 
main(argc, argv)
	int argc;
	char *argv[];
{
	CLIENT *clnt;
	char *server;
	char *dir;
	readdir_res *result;
	namelist nl;
 	if (argc != 3) {
		fprintf(stderr, "usage: %s host directory\n",argv[0]);
		exit(1);
	}
	server = argv[1];
	dir = argv[2];
	/*
	 * Create client "handle" used for
 * calling MESSAGEPROG on the server
 * designated on the command line.
	 */
	clnt = clnt_create(server, DIRPROG,
								DIRVERS, "tcp");
	if (clnt == (CLIENT *)NULL) {
		clnt_pcreateerror(server);
		exit(1);
	}
	result = readdir_1(&dir, clnt);
	if (result == (readdir_res *)NULL) {
		clnt_perror(clnt, server);
		exit(1);
	}
	/* Okay, we successfully called
 * the remote procedure.
 */
	if (result->errno != 0) {
		/* Remote system error. Print error message and die. */
		//errno = result->errno;
		perror(dir);
		exit(1);
	}
	/* Successfully got a directory listing.
 * Print it.
 */
	for (nl = result->readdir_res_u.list;
								nl != NULL;
		nl = nl->next) {
		printf("%s\n", nl->name);
	}
	xdr_free(xdr_readdir_res, result);
	clnt_destroy(clnt);
	exit(0);
}