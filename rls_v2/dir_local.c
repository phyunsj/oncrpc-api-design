#include "dir.h"
#include <dirent.h>

namelist  read_dir(char *dir) {

    DIR *dirp;
	struct dirent *d;
    namelist nl, head;
    nl = head = NULL;
    dirp = opendir(dir);
      
    printf("read_dir(): %s directory\n", dir);
	if (dirp == (DIR *)NULL)  return NULL;
    
    /* copy first entry */
    if( (d = readdir(dirp)) != NULL ) {
      head = nl = (namenode *) malloc(sizeof(namenode));  
	  if (nl == (namenode *) NULL) {
		    closedir(dirp);
		    return NULL;
	  }
	  nl->name = strdup(d->d_name);
	  nl->next = NULL;
    }

    // copy the remaining entry
	while (d = readdir(dirp)) {
		nl->next = (namenode *) malloc(sizeof(namenode));  
		nl = nl->next; nl->next = NULL;
		if (nl == (namenode *) NULL) {
		    closedir(dirp);
		    return NULL;
		}
		nl->name = strdup(d->d_name);
	}
    
	return head;
}