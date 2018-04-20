#include "CL.h"
#include "cl_common.h"

int INIT_HANDLER( HANDLER *remote, char *server, char *proto )  {
   
    /* clear the previosu CLIENT handler */
	if ( remote->clnt != (CLIENT *)NULL ) clnt_destroy(remote->clnt);

    if ( server != NULL ) {
       remote->clnt = clnt_create(server, CLPROG, CLVERS, proto);
       if (remote->clnt == (CLIENT *)NULL) {
		  clnt_pcreateerror(server);
		  return -1;
	   }
    }
    return 0;
}

void DESTROY_HANDLER( HANDLER *remote ) {

	if ( remote->clnt != (CLIENT *)NULL ) clnt_destroy(remote->clnt);
}