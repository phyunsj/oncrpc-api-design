#include "CL.h"
#include "cl_calc.h"

#define debug_  0


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

void CL_CALC_WRITE_PACK_1( cl_calc_write_res_t *res, /* <- */ cl_bus_t *out) {
		CL_BUS_T_PACK( &res->__out , /* <- */ out );
}

void CL_CALC_TIMER_PACK_1( cl_calc_timer_res_t *res, /* <- */ cl_bus_t *out) {
		CL_BUS_T_PACK( &res->__out , /* <- */ out );
}

void CL_CALC_FILTER_PACK_1( cl_calc_filter_res_t *res, /* <- */ cl_bus_t *out) {
		CL_BUS_T_PACK( &res->__out , /* <- */ out );
}

void CL_CALC_SERIAL_PACK_1( cl_calc_serial_res_t *res, /* <- */ cl_bus_t *out) {
		CL_BUS_T_PACK( &res->__out , /* <- */ out );
}

void CL_CALC_SERVO_PACK_1( cl_calc_servo_res_t *res, /* <- */ cl_msg_t *inout) {
		CL_MSG_T_PACK( &res->__inout , /* <- */ inout );
}

void CL_CALC_SERVO_PACK_2( cl_calc_servo_res_t *res, /* <- */ cl_bus_t *out) {
		CL_BUS_T_PACK( &res->__out , /* <- */ out );
}

cl_calc_freq_res * 
cl_calc_freq_func_1_svc ( f_req  , req ) 
      cl_calc_freq_req  *f_req;
      struct svc_req    *req;
{
    static cl_calc_freq_res res;
    
		int in10;
		int in;
		unsigned int out;

    /* request */
    
		in10 = f_req->__in10;
		in = f_req->__in;

    res.errcode =  cl_calc_freq ( in10,in,&out );

    if( res.errcode == 300 ) {
    
    /* response */
    
		res.cl_calc_freq_res_u.__res.__out = out;
    
    }

    return (&res);
} 



cl_calc_alert_res * 
cl_calc_alert_func_1_svc ( f_req  , req ) 
      cl_calc_alert_req  *f_req;
      struct svc_req    *req;
{
    static cl_calc_alert_res res;
    
		int in10;
		int in;
		unsigned int inout;

    /* request */
    
		in10 = f_req->__in10;
		in = f_req->__in;
		inout = f_req->__inout;

    res.errcode =  cl_calc_alert ( in10,in,&inout );

    if( res.errcode == 300 ) {
    
    /* response */
    
		res.cl_calc_alert_res_u.__res.__inout = inout;
    
    }

    return (&res);
} 



cl_calc_read_res * 
cl_calc_read_func_1_svc ( f_req  , req ) 
      cl_calc_read_req  *f_req;
      struct svc_req    *req;
{
    static cl_calc_read_res res;
    
		cl_int16_t in10;
		cl_uint16_t in;
		cl_uint32_t out;

    /* request */
    
		in10 = f_req->__in10;
		in = f_req->__in;

    res.errcode =  cl_calc_read ( in10,in,&out );

    if( res.errcode == 300 ) {
    
    /* response */
    
		res.cl_calc_read_res_u.__res.__out = out;
    
    }

    return (&res);
} 



cl_calc_write_res * 
cl_calc_write_func_1_svc ( f_req  , req ) 
      cl_calc_write_req  *f_req;
      struct svc_req    *req;
{
    static cl_calc_write_res res;
    
		cl_msg_t in;
		cl_bus_t out;

    /* request */
    
		CL_MSG_T_UNPACK( &f_req->__in /* >> */ , &in );

    res.errcode =  cl_calc_write ( in,&out );

    if( res.errcode == 300 ) {
    
    /* response */
    
		CL_CALC_WRITE_PACK_1( &res.cl_calc_write_res_u.__res  /* << */ , &out );
    
    }

    return (&res);
} 



cl_calc_timer_res * 
cl_calc_timer_func_1_svc ( f_req  , req ) 
      cl_calc_timer_req  *f_req;
      struct svc_req    *req;
{
    static cl_calc_timer_res res;
    
		cl_msg_t in;
		cl_bus_t out;

    /* request */
    
		CL_MSG_T_UNPACK( &f_req->__in /* >> */ , &in );

    res.errcode =  cl_calc_timer ( &in,&out );

    if( res.errcode == 300 ) {
    
    /* response */
    
		CL_CALC_TIMER_PACK_1( &res.cl_calc_timer_res_u.__res  /* << */ , &out );
    
    }

    return (&res);
} 



cl_calc_filter_res * 
cl_calc_filter_func_1_svc ( f_req  , req ) 
      cl_calc_filter_req  *f_req;
      struct svc_req    *req;
{
    static cl_calc_filter_res res;
    
		cl_msg_t in;
		cl_bus_t out;

    /* request */
    
		CL_MSG_T_UNPACK( &f_req->__in /* >> */ , &in );

    res.errcode =  cl_calc_filter ( &in,&out );

    if( res.errcode == 300 ) {
    
    /* response */
    
		CL_CALC_FILTER_PACK_1( &res.cl_calc_filter_res_u.__res  /* << */ , &out );
    
    }

    return (&res);
} 



cl_calc_serial_res * 
cl_calc_serial_func_1_svc ( f_req  , req ) 
      cl_calc_serial_req  *f_req;
      struct svc_req    *req;
{
    static cl_calc_serial_res res;
    
		cl_msg_t in1;
		cl_msg_t in2;
		cl_bus_t out;

    /* request */
    
		CL_MSG_T_UNPACK( &f_req->__in1 /* >> */ , &in1 );
		CL_MSG_T_UNPACK( &f_req->__in2 /* >> */ , &in2 );

    res.errcode =  300;  cl_calc_serial ( &in1,&in2,&out );

    if( res.errcode == 300 ) {
    
    /* response */
    
		CL_CALC_SERIAL_PACK_1( &res.cl_calc_serial_res_u.__res  /* << */ , &out );
    
    }

    return (&res);
} 



cl_calc_servo_res * 
cl_calc_servo_func_1_svc ( f_req  , req ) 
      cl_calc_servo_req  *f_req;
      struct svc_req    *req;
{
    static cl_calc_servo_res res;
    
		cl_msg_t inout;
		cl_bus_t out;

    /* request */
    
		CL_MSG_T_UNPACK( &f_req->__inout /* >> */ , &inout );

    res.errcode =  cl_calc_servo ( &inout,&out );

    if( res.errcode == 300 ) {
    
    /* response */
    
		CL_CALC_SERVO_PACK_1( &res.cl_calc_servo_res_u.__res  /* << */ , &inout );
		CL_CALC_SERVO_PACK_2( &res.cl_calc_servo_res_u.__res  /* << */ , &out );
    
    }

    return (&res);
} 



cl_calc_set_res * 
cl_calc_set_func_1_svc ( f_req  , req ) 
      cl_calc_set_req  *f_req;
      struct svc_req    *req;
{
    static cl_calc_set_res res;
    
		cl_int16_t in1;
		cl_uint32_t in2;
		cl_uint16_t out;

    /* request */
    
		in1 = f_req->__in1;
		in2 = f_req->__in2;

    res.errcode =  cl_calc_set ( in1,in2,&out );

    if( res.errcode == 300 ) {
    
    /* response */
    
		res.cl_calc_set_res_u.__res.__out = out;
    
    }

    return (&res);
} 

