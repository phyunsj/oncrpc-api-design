/**
 * @file cl_common.h
 * @author phyunsj@yahoo.com
 * @date April 2018
 * @brief 
 *
**/
#ifndef _CL_COMMON_
#define _CL_COMMON_

/**
 * @brief device handler to store RPC Clinet & server name.
 *
 */

typedef struct HANDLER {
	CLIENT *clnt;
	char *server; /* not used for now */
} HANDLER;

/**
* @brief initialize RPC client handler with IP address.
*
* @param [in] [out]  remote - RPC Client Handle.
* @param [in] server - IP address.
* @param [in] proto - "tcp", "udp" protocol. 
* @return int SUCCESS or error code.
*/

int  INIT_HANDLER( HANDLER *remote, char *server, char *proto );

/**
* @brief disconnect RPC.
*
* @param [in]  remote - disconnect from RPC server.
* @return void.
*/

void DESTROY_HANDLER( HANDLER *remote );

#endif /* _CL_COMMON_ */