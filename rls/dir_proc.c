/*
 * dir_proc.c: remote readdir
 * implementation
 */
#include <dirent.h>
#include "dir.h"                /* Created by rpcgen */

 
readdir_res *
readdir_1_svc(dirname, req)
	nametype *dirname;
	struct svc_req *req;
 
{
	DIR *dirp;
	struct dirent *d;
	namelist nl;
	namelist *nlp;
	static readdir_res res; /* must be static! */
	
	/* Open directory */
	dirp = opendir(*dirname);
	if (dirp == (DIR *)NULL) {
		res.errno = -1;
		return (&res);
	}
	/* Free previous result */
	xdr_free(xdr_readdir_res, &res);
	/*
	 * Collect directory entries.
 * Memory allocated here is free by
	 * xdr_free the next time readdir_1
 * is called
	 */
	nlp = &res.readdir_res_u.list;
	while (d = readdir(dirp)) {
		nl = *nlp = (namenode *) malloc(sizeof(namenode));
		if (nl == (namenode *) NULL) {
			res.errno = -1;
			closedir(dirp);
			return(&res);
		}
		nl->name = strdup(d->d_name);
		nlp = &nl->next;
	}
	*nlp = (namelist)NULL;
	/* Return the result */
	res.errno = 0;
	closedir(dirp);
	return (&res);
}