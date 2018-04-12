

## Example : Passing Complex Data Structures (Version 2)
from  https://docs.oracle.com/cd/E19683-01/816-1435/rpcgenpguide-21470/index.html

## Change Log

#### 1. API 

- `namelist read_dir(char *);` for local only
- `namelist READ_DIR( HANDLER *,  char * )` for local & remote

#### 2. Files

Hide ONCRPC specific system calls (clnt_xxx(), readdir_1()) from `rls.c`. 

- `dir_local.c/h` : `read_dir()` local function to read the directory
- **Server** : `dir_proc.c` executes a local funtion `read_dir()` defined in `dir_local.h`
- **Client** : `READ_DIR():dir_common.c` executes a local function `read_dir():dir_local.c` or communicate with RPC server `readdir_1()` depending on Handler's `CLINET`.
```
namelist READ_DIR( HANDLER *remote,  char *dir ) {
    if ( remote->clnt != (CLIENT *)NULL ) {       
       ...
        result = readdir_1(&dir, remote->clnt);
	    if (result == (readdir_res *)NULL) {
		   clnt_perror(remote->clnt, remote->server);
		   return NULL;
	    }
        ...
    } else {       
        return read_dir(dir);
    }
    return NULL;
} 
```

#### 3. Client `rls.c`

```
main(...)
{
    HANDLER handler[2];
    ...
    INIT_HANDLER ( &handler[0] , NULL, NULL);     // handler[0] for local
    INIT_HANDLER ( &handler[1] , server, "tcp");  // handler[1] for remote
     ...
    /* local call */
    local_head = READ_DIR( &handler[0], dir );
    for (  ; local_head != NULL; local_head = local_head->next) {
	    printf("ls:%s\n", local_head->name);
    }
    /* remote call */
    remote_head = READ_DIR( &handler[1], dir);
    for (  ; remote_head != NULL; remote_head = remote_head->next) {
	    printf("rls:%s\n", remote_head->name);
    }
    ...
    DESTROY_HANDLER ( &handler[0] );
    DESTROY_HANDLER ( &handler[1] );
    exit(0);
}
```
## Build & Run 

#### Server

```
$ rpcgen dir.x
$ gcc dir_xdr.c dir_svc.c dir_proc.c  dir_local.c -lnsl -o dir_svc
$ dir_svc &
```
#### Client

```
$ rpcgen dir.x
$ gcc dir_xdr.c dir_clnt.c dir_common.c dir_local.c rls.c -lnsl -o rls 
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
