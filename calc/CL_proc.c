#include "CL.h"
#include "cl_calc.h"

#include "cl_common.h"

#define debug_  0


void CL_MSG_T_PACK ( cl_msg_t_s *to , /* <- */ cl_msg_t *from ) {
	to->addr = from->addr;
	to->flags = from->flags;
	to->len = from->len;
}

void CL_BUS_T_PACK ( cl_bus_t_s *to , /* <- */ cl_bus_t *from ) {
	to->info = from->info;
	to->src = from->src;
	to->dst = from->dst;
	to->length = from->length;
	to->stride = from->stride;
	to->next = from->next;
}

void CL_MSG_T_UNPACK ( cl_msg_t_s *from , /* -> */ cl_msg_t *to ) {
	to->addr = from->addr;
	to->flags = from->flags;
	to->len = from->len;
}

void CL_BUS_T_UNPACK ( cl_bus_t_s *from , /* -> */ cl_bus_t *to ) {
	to->info = from->info;
	to->src = from->src;
	to->dst = from->dst;
	to->length = from->length;
	to->stride = from->stride;
	to->next = from->next;
}

void CL_CALC_WRITE_UNPACK_1( cl_calc_write_res_t *res, cl_bus_t *out) {
		CL_BUS_T_UNPACK( &res->__out , out );
}

void CL_CALC_TIMER_UNPACK_1( cl_calc_timer_res_t *res, cl_bus_t *out) {
		CL_BUS_T_UNPACK( &res->__out , out );
}

void CL_CALC_FILTER_UNPACK_1( cl_calc_filter_res_t *res, cl_bus_t *out) {
		CL_BUS_T_UNPACK( &res->__out , out );
}

void CL_CALC_SERIAL_UNPACK_1( cl_calc_serial_res_t *res, cl_bus_t *out) {
		CL_BUS_T_UNPACK( &res->__out , out );
}

void CL_CALC_SERVO_UNPACK_1( cl_calc_servo_res_t *res, cl_msg_t *inout) {
		CL_MSG_T_UNPACK( &res->__inout , inout );
}

void CL_CALC_SERVO_UNPACK_2( cl_calc_servo_res_t *res, cl_bus_t *out) {
		CL_BUS_T_UNPACK( &res->__out , out );
}


cl_return_t CL_CALC_FREQ ( HANDLER *remote , int in10, int in, unsigned int *out )  
{
  
  int ret = 0;

  if ( remote->clnt != (CLIENT *)NULL ) {

    cl_calc_freq_req req;
    cl_calc_freq_res *res;

    memset(&req, 0, sizeof(cl_calc_freq_req));

    /* request */
    
		req.__in10 = in10;
		req.__in = in;

    if ( debug_ ) fprintf(stdout, "->Sent cl_calc_freq req\n"); 
    
    res = cl_calc_freq_func_1( &req, remote->clnt );
    if (res == (cl_calc_freq_res *) NULL) { 
      clnt_perror (remote->clnt, "[RPC] cl_calc_freq failed\n");
      return -1;
    }

    ret = res->errcode;
    if ( ret == 300 /* SUCCESS */ ) {
    /* response */
    
		*out = res->cl_calc_freq_res_u.__res.__out;
    
    }
    
    return ret;
  } else {

    return cl_calc_freq( in10,in,out );

  }

}




cl_return_t CL_CALC_ALERT ( HANDLER *remote , int in10, int in, unsigned int *inout )  
{
  
  int ret = 0;

  if ( remote->clnt != (CLIENT *)NULL ) {

    cl_calc_alert_req req;
    cl_calc_alert_res *res;

    memset(&req, 0, sizeof(cl_calc_alert_req));

    /* request */
    
		req.__in10 = in10;
		req.__in = in;
		req.__inout = *inout;

    if ( debug_ ) fprintf(stdout, "->Sent cl_calc_alert req\n"); 
    
    res = cl_calc_alert_func_1( &req, remote->clnt );
    if (res == (cl_calc_alert_res *) NULL) { 
      clnt_perror (remote->clnt, "[RPC] cl_calc_alert failed\n");
      return -1;
    }

    ret = res->errcode;
    if ( ret == 300 /* SUCCESS */ ) {
    /* response */
    
		*inout = res->cl_calc_alert_res_u.__res.__inout;
    
    }
    
    return ret;
  } else {

    return cl_calc_alert( in10,in,inout );

  }

}




cl_return_t CL_CALC_READ ( HANDLER *remote , cl_int16_t in10, cl_uint16_t in, cl_uint32_t *out )  
{
  
  int ret = 0;

  if ( remote->clnt != (CLIENT *)NULL ) {

    cl_calc_read_req req;
    cl_calc_read_res *res;

    memset(&req, 0, sizeof(cl_calc_read_req));

    /* request */
    
		req.__in10 = in10;
		req.__in = in;

    if ( debug_ ) fprintf(stdout, "->Sent cl_calc_read req\n"); 
    
    res = cl_calc_read_func_1( &req, remote->clnt );
    if (res == (cl_calc_read_res *) NULL) { 
      clnt_perror (remote->clnt, "[RPC] cl_calc_read failed\n");
      return -1;
    }

    ret = res->errcode;
    if ( ret == 300 /* SUCCESS */ ) {
    /* response */
    
		*out = res->cl_calc_read_res_u.__res.__out;
    
    }
    
    return ret;
  } else {

    return cl_calc_read( in10,in,out );

  }

}




cl_return_t CL_CALC_WRITE ( HANDLER *remote , cl_msg_t in, cl_bus_t *out )  
{
  
  int ret = 0;

  if ( remote->clnt != (CLIENT *)NULL ) {

    cl_calc_write_req req;
    cl_calc_write_res *res;

    memset(&req, 0, sizeof(cl_calc_write_req));

    /* request */
    
		CL_MSG_T_PACK( &req.__in /* << */ ,&in );

    if ( debug_ ) fprintf(stdout, "->Sent cl_calc_write req\n"); 
    
    res = cl_calc_write_func_1( &req, remote->clnt );
    if (res == (cl_calc_write_res *) NULL) { 
      clnt_perror (remote->clnt, "[RPC] cl_calc_write failed\n");
      return -1;
    }

    ret = res->errcode;
    if ( ret == 300 /* SUCCESS */ ) {
    /* response */
    
		CL_CALC_WRITE_UNPACK_1( &res->cl_calc_write_res_u.__res  /* >> */ ,out );
    
    }
    
    return ret;
  } else {

    return cl_calc_write( in,out );

  }

}




cl_return_t CL_CALC_TIMER ( HANDLER *remote , cl_msg_t *in, cl_bus_t *out )  
{
  
  int ret = 0;

  if ( remote->clnt != (CLIENT *)NULL ) {

    cl_calc_timer_req req;
    cl_calc_timer_res *res;

    memset(&req, 0, sizeof(cl_calc_timer_req));

    /* request */
    
		CL_MSG_T_PACK( &req.__in /* << */ ,in );

    if ( debug_ ) fprintf(stdout, "->Sent cl_calc_timer req\n"); 
    
    res = cl_calc_timer_func_1( &req, remote->clnt );
    if (res == (cl_calc_timer_res *) NULL) { 
      clnt_perror (remote->clnt, "[RPC] cl_calc_timer failed\n");
      return -1;
    }

    ret = res->errcode;
    if ( ret == 300 /* SUCCESS */ ) {
    /* response */
    
		CL_CALC_TIMER_UNPACK_1( &res->cl_calc_timer_res_u.__res  /* >> */ ,out );
    
    }
    
    return ret;
  } else {

    return cl_calc_timer( in,out );

  }

}




int CL_CALC_FILTER ( HANDLER *remote , cl_msg_t *in, cl_bus_t *out )  
{
  
  int ret = 0;

  if ( remote->clnt != (CLIENT *)NULL ) {

    cl_calc_filter_req req;
    cl_calc_filter_res *res;

    memset(&req, 0, sizeof(cl_calc_filter_req));

    /* request */
    
		CL_MSG_T_PACK( &req.__in /* << */ ,in );

    if ( debug_ ) fprintf(stdout, "->Sent cl_calc_filter req\n"); 
    
    res = cl_calc_filter_func_1( &req, remote->clnt );
    if (res == (cl_calc_filter_res *) NULL) { 
      clnt_perror (remote->clnt, "[RPC] cl_calc_filter failed\n");
      return -1;
    }

    ret = res->errcode;
    if ( ret == 300 /* SUCCESS */ ) {
    /* response */
    
		CL_CALC_FILTER_UNPACK_1( &res->cl_calc_filter_res_u.__res  /* >> */ ,out );
    
    }
    
    return ret;
  } else {

    return cl_calc_filter( in,out );

  }

}




void CL_CALC_SERIAL ( HANDLER *remote , cl_msg_t *in1, cl_msg_t *in2, cl_bus_t *out )  
{
  
  int ret = 0;

  if ( remote->clnt != (CLIENT *)NULL ) {

    cl_calc_serial_req req;
    cl_calc_serial_res *res;

    memset(&req, 0, sizeof(cl_calc_serial_req));

    /* request */
    
		CL_MSG_T_PACK( &req.__in1 /* << */ ,in1 );
		CL_MSG_T_PACK( &req.__in2 /* << */ ,in2 );

    if ( debug_ ) fprintf(stdout, "->Sent cl_calc_serial req\n"); 
    
    res = cl_calc_serial_func_1( &req, remote->clnt );
    if (res == (cl_calc_serial_res *) NULL) { 
      clnt_perror (remote->clnt, "[RPC] cl_calc_serial failed\n");
      return -1;
    }

    ret = res->errcode;
    if ( ret == 300 /* SUCCESS */ ) {
    /* response */
    
		CL_CALC_SERIAL_UNPACK_1( &res->cl_calc_serial_res_u.__res  /* >> */ ,out );
    
    }
    
    return ;
  } else {

    return cl_calc_serial( in1,in2,out );

  }

}




int CL_CALC_SERVO ( HANDLER *remote , cl_msg_t *inout, cl_bus_t *out )  
{
  
  int ret = 0;

  if ( remote->clnt != (CLIENT *)NULL ) {

    cl_calc_servo_req req;
    cl_calc_servo_res *res;

    memset(&req, 0, sizeof(cl_calc_servo_req));

    /* request */
    
		CL_MSG_T_PACK( &req.__inout /* << */ ,inout );

    if ( debug_ ) fprintf(stdout, "->Sent cl_calc_servo req\n"); 
    
    res = cl_calc_servo_func_1( &req, remote->clnt );
    if (res == (cl_calc_servo_res *) NULL) { 
      clnt_perror (remote->clnt, "[RPC] cl_calc_servo failed\n");
      return -1;
    }

    ret = res->errcode;
    if ( ret == 300 /* SUCCESS */ ) {
    /* response */
    
		CL_CALC_SERVO_UNPACK_1( &res->cl_calc_servo_res_u.__res  /* >> */ ,inout );
		CL_CALC_SERVO_UNPACK_2( &res->cl_calc_servo_res_u.__res  /* >> */ ,out );
    
    }
    
    return ret;
  } else {

    return cl_calc_servo( inout,out );

  }

}




cl_return_t CL_CALC_SET ( HANDLER *remote , cl_int16_t in1, cl_uint32_t in2, cl_uint16_t *out )  
{
  
  int ret = 0;

  if ( remote->clnt != (CLIENT *)NULL ) {

    cl_calc_set_req req;
    cl_calc_set_res *res;

    memset(&req, 0, sizeof(cl_calc_set_req));

    /* request */
    
		req.__in1 = in1;
		req.__in2 = in2;

    if ( debug_ ) fprintf(stdout, "->Sent cl_calc_set req\n"); 
    
    res = cl_calc_set_func_1( &req, remote->clnt );
    if (res == (cl_calc_set_res *) NULL) { 
      clnt_perror (remote->clnt, "[RPC] cl_calc_set failed\n");
      return -1;
    }

    ret = res->errcode;
    if ( ret == 300 /* SUCCESS */ ) {
    /* response */
    
		*out = res->cl_calc_set_res_u.__res.__out;
    
    }
    
    return ret;
  } else {

    return cl_calc_set( in1,in2,out );

  }

}

