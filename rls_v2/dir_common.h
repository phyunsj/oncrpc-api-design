#ifndef __REMOTE__
#define __REMOTE__

typedef struct HANDLER {
	CLIENT *clnt;
	char *server;
} HANDLER;

int  INIT_HANDLER( HANDLER *remote, char *server, char *proto );
void DESTROY_HANDLER( HANDLER *remote );

// USER-DEFINED API
namelist  READ_DIR( HANDLER *remote, char *dir);

#endif