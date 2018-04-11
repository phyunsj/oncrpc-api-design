#include "dir.h"
#include "dir_common.h"
#include "dir_local.h"

namelist READ_DIR( HANDLER *remote,  char *dir ) {

    if ( remote->clnt != (CLIENT *)NULL ) {
        
        readdir_res *result;
        namelist head, copy_head, nl;       
        copy_head = head = nl = NULL;
        //////////////////////////////////////////////////
        // 1. LOCAL REQUEST -> RPC


        //////////////////////////////////////////////////
        // 2. RPC CALL

        result = readdir_1(&dir, remote->clnt);
	    if (result == (readdir_res *)NULL) {
		   clnt_perror(remote->clnt, remote->server);
		   return NULL;
	    }

        //////////////////////////////////////////////////
        // 3. RPC RESPONSE -> LOCAL
        
        if ( result->errno != 0 ) return NULL;

        // copy first entry
        nl = result->readdir_res_u.list;
        copy_head = head = (namenode *) malloc(sizeof(namenode)); 
        head->name = strdup(nl->name);
        head->next = NULL;
        nl = nl->next;

        // copy the remaning result
        for (; nl != NULL; nl = nl->next) {
           head->next = (namenode *) malloc(sizeof(namenode));            
           head = head->next;
           head->name = strdup(nl->name);
           head->next = NULL;
	    }
        xdr_free(xdr_readdir_res, result);
        
        return copy_head;

    } else {
       
        return read_dir(dir);

    }

    return NULL;
} 

int INIT_HANDLER( HANDLER *remote, char *server, char *proto )  {
    if ( server != NULL ) {
       remote->clnt = clnt_create(server, DIRPROG, DIRVERS, proto);
       if (remote->clnt == (CLIENT *)NULL) {
		  clnt_pcreateerror(server);
		  return -1;
	   }
    }
}

void DESTROY_HANDLER( HANDLER *remote ) {

	if ( remote->clnt != (CLIENT *)NULL ) clnt_destroy(remote->clnt);
}