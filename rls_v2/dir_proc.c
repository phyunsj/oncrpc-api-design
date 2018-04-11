/*
 * dir_proc.c: remote readdir
 * implementation
 */
#include <dirent.h>
#include "dir.h"                /* Created by rpcgen */
#include "dir_local.h"
 
readdir_res *
readdir_1_svc(dirname, req)
	nametype *dirname;
	struct svc_req *req;
 
{
	static readdir_res res; /* must be static! */

	DIR *dirp;
	struct dirent *d;
	
	namelist head;
	namelist nl;
	namelist *nlp;
	
	/* Free previous result */
    xdr_free(xdr_readdir_res, &res);

	//////////////////////////////////////////////////
    // 1. RPC REQUEST -> LOCAL


    //////////////////////////////////////////////////
    // 2. LOCAL CALL

	head = read_dir(*dirname);  //shared API between server and client. DRY.
    if ( head == NULL ) {
    	res.errno = -1;
		return (&res);
    }

    //////////////////////////////////////////////////
    // 3. LOCAL RESPONSE -> RPC

    /*
	 * Collect directory entries.
     * Memory allocated here is free by
	 * xdr_free the next time readdir_1
     * is called
	 */
	nlp = &res.readdir_res_u.list;
    while ( head ) {
        nl = *nlp = (namenode *) malloc(sizeof(namenode));
        nl->name = strdup(head->name);
        nlp = &nl->next;
    	head = head->next;
    }
    *nlp = (namelist)NULL;

	/* Return the result */
	res.errno = 0;
	return (&res);
}