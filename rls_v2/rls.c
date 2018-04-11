/*
 * rls.c: Remote directory listing client
 */
 
#include <stdio.h>
#include "dir.h"                       /* generated by rpcgen */
#include "dir_common.h"


main(argc, argv)
	int argc;
	char *argv[];
{

	HANDLER handler[2];
 
	char *server;
    int retCode = 0;

	char *dir;
	namelist local_head = NULL;
	namelist remote_head = NULL;
	
 	if (argc != 3) {
		fprintf(stderr, "usage: %s host directory\n",argv[0]);
		exit(1);
	}
	server = argv[1];
	dir = argv[2];

	memset(&handler, 0, sizeof(HANDLER) * 2);

	/*
	 * Create client "handle" used for
     * calling MESSAGEPROG on the server
     * designated on the command line.
	 */
	INIT_HANDLER ( &handler[0] , NULL, NULL);
    INIT_HANDLER ( &handler[1] , server, "tcp");
    
	
	/* remote or local calls */
	local_head = READ_DIR( &handler[0], dir );
    for (  ; local_head != NULL; local_head = local_head->next) {
	    printf("ls:%s\n", local_head->name);
	}
    remote_head = READ_DIR( &handler[1], dir);
    for (  ; remote_head != NULL; remote_head = remote_head->next) {
	    printf("rls:%s\n", remote_head->name);
	}

    /*
	 * Close client "handle" used for
     * calling MESSAGEPROG on the server
     * designated on the command line.
	 */
	DESTROY_HANDLER ( &handler[0] );
	DESTROY_HANDLER ( &handler[1] );

	exit(0);
}