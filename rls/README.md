

## Example : Passing Complex Data Structures
from  https://docs.oracle.com/cd/E19683-01/816-1435/rpcgenpguide-21470/index.html

Revised Version : https://github.com/phyunsj/oncrpc-api-design/blob/master/rls_v2/README.md

#### dir.x

```
const MAXNAMELEN = 255;						/* max length of directory
entry */
typedef string nametype<MAXNAMELEN>;		/* director entry */
typedef struct namenode *namelist;			/* link in the listing */
 
/* A node in the directory listing */
struct namenode {
	nametype name;						/* name of directory entry */
	namelist next;						/* next entry */
};
 
union readdir_res switch (int errno) {
	case 0:
		namelist list;	/* no error: return directory listing */
	default:
		void;			/* error occurred: nothing else to return */
};

program DIRPROG {
	version DIRVERS {
		readdir_res READDIR(nametype) = 1;
	} = 1;
} = 0x20000076; 
```

#### Server
```
$ rpcgen dir.x
$ gcc dir_svc.c dir_proc.c dir_xdr.c -o dir_svc -lnsl
$ dir_svc &
```
#### Client
```
$ rpcgen dir.x
$ gcc rls.c dir_clnt.c dir_xdr.c -o rls -lnsl
```
#### 
```
$ rls "127.0.0.1" /usr/share/lib
 ascii
 eqnchar
 ...
 tabs4
 local
$
```

