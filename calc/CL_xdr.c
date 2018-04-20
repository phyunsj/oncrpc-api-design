/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "CL.h"

bool_t
xdr_cl_msg_t_s (XDR *xdrs, cl_msg_t_s *objp)
{
	register int32_t *buf;

	 if (!xdr_short (xdrs, &objp->addr))
		 return FALSE;
	 if (!xdr_short (xdrs, &objp->flags))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->len))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_bus_t_s (XDR *xdrs, cl_bus_t_s *objp)
{
	register int32_t *buf;


	if (xdrs->x_op == XDR_ENCODE) {
		buf = XDR_INLINE (xdrs, 6 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->info))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->src))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->dst))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->length))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->stride))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->next))
				 return FALSE;
		} else {
			IXDR_PUT_LONG(buf, objp->info);
			IXDR_PUT_LONG(buf, objp->src);
			IXDR_PUT_LONG(buf, objp->dst);
			IXDR_PUT_LONG(buf, objp->length);
			IXDR_PUT_LONG(buf, objp->stride);
			IXDR_PUT_LONG(buf, objp->next);
		}
		return TRUE;
	} else if (xdrs->x_op == XDR_DECODE) {
		buf = XDR_INLINE (xdrs, 6 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->info))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->src))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->dst))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->length))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->stride))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->next))
				 return FALSE;
		} else {
			objp->info = IXDR_GET_LONG(buf);
			objp->src = IXDR_GET_LONG(buf);
			objp->dst = IXDR_GET_LONG(buf);
			objp->length = IXDR_GET_LONG(buf);
			objp->stride = IXDR_GET_LONG(buf);
			objp->next = IXDR_GET_LONG(buf);
		}
	 return TRUE;
	}

	 if (!xdr_int (xdrs, &objp->info))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->src))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->dst))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->length))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->stride))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->next))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_freq_req (XDR *xdrs, cl_calc_freq_req *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->__in10))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->__in))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_freq_res_t (XDR *xdrs, cl_calc_freq_res_t *objp)
{
	register int32_t *buf;

	 if (!xdr_u_int (xdrs, &objp->__out))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_freq_res (XDR *xdrs, cl_calc_freq_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->errcode))
		 return FALSE;
	switch (objp->errcode) {
	case 300:
		 if (!xdr_cl_calc_freq_res_t (xdrs, &objp->cl_calc_freq_res_u.__res))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_cl_calc_alert_req (XDR *xdrs, cl_calc_alert_req *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->__in10))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->__in))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->__inout))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_alert_res_t (XDR *xdrs, cl_calc_alert_res_t *objp)
{
	register int32_t *buf;

	 if (!xdr_u_int (xdrs, &objp->__inout))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_alert_res (XDR *xdrs, cl_calc_alert_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->errcode))
		 return FALSE;
	switch (objp->errcode) {
	case 300:
		 if (!xdr_cl_calc_alert_res_t (xdrs, &objp->cl_calc_alert_res_u.__res))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_cl_calc_read_req (XDR *xdrs, cl_calc_read_req *objp)
{
	register int32_t *buf;

	 if (!xdr_short (xdrs, &objp->__in10))
		 return FALSE;
	 if (!xdr_u_short (xdrs, &objp->__in))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_read_res_t (XDR *xdrs, cl_calc_read_res_t *objp)
{
	register int32_t *buf;

	 if (!xdr_u_int (xdrs, &objp->__out))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_read_res (XDR *xdrs, cl_calc_read_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->errcode))
		 return FALSE;
	switch (objp->errcode) {
	case 300:
		 if (!xdr_cl_calc_read_res_t (xdrs, &objp->cl_calc_read_res_u.__res))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_cl_calc_write_req (XDR *xdrs, cl_calc_write_req *objp)
{
	register int32_t *buf;

	 if (!xdr_cl_msg_t_s (xdrs, &objp->__in))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_write_res_t (XDR *xdrs, cl_calc_write_res_t *objp)
{
	register int32_t *buf;

	 if (!xdr_cl_bus_t_s (xdrs, &objp->__out))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_write_res (XDR *xdrs, cl_calc_write_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->errcode))
		 return FALSE;
	switch (objp->errcode) {
	case 300:
		 if (!xdr_cl_calc_write_res_t (xdrs, &objp->cl_calc_write_res_u.__res))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_cl_calc_timer_req (XDR *xdrs, cl_calc_timer_req *objp)
{
	register int32_t *buf;

	 if (!xdr_cl_msg_t_s (xdrs, &objp->__in))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_timer_res_t (XDR *xdrs, cl_calc_timer_res_t *objp)
{
	register int32_t *buf;

	 if (!xdr_cl_bus_t_s (xdrs, &objp->__out))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_timer_res (XDR *xdrs, cl_calc_timer_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->errcode))
		 return FALSE;
	switch (objp->errcode) {
	case 300:
		 if (!xdr_cl_calc_timer_res_t (xdrs, &objp->cl_calc_timer_res_u.__res))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_cl_calc_filter_req (XDR *xdrs, cl_calc_filter_req *objp)
{
	register int32_t *buf;

	 if (!xdr_cl_msg_t_s (xdrs, &objp->__in))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_filter_res_t (XDR *xdrs, cl_calc_filter_res_t *objp)
{
	register int32_t *buf;

	 if (!xdr_cl_bus_t_s (xdrs, &objp->__out))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_filter_res (XDR *xdrs, cl_calc_filter_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->errcode))
		 return FALSE;
	switch (objp->errcode) {
	case 300:
		 if (!xdr_cl_calc_filter_res_t (xdrs, &objp->cl_calc_filter_res_u.__res))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_cl_calc_serial_req (XDR *xdrs, cl_calc_serial_req *objp)
{
	register int32_t *buf;

	 if (!xdr_cl_msg_t_s (xdrs, &objp->__in1))
		 return FALSE;
	 if (!xdr_cl_msg_t_s (xdrs, &objp->__in2))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_serial_res_t (XDR *xdrs, cl_calc_serial_res_t *objp)
{
	register int32_t *buf;

	 if (!xdr_cl_bus_t_s (xdrs, &objp->__out))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_serial_res (XDR *xdrs, cl_calc_serial_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->errcode))
		 return FALSE;
	switch (objp->errcode) {
	case 300:
		 if (!xdr_cl_calc_serial_res_t (xdrs, &objp->cl_calc_serial_res_u.__res))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_cl_calc_servo_req (XDR *xdrs, cl_calc_servo_req *objp)
{
	register int32_t *buf;

	 if (!xdr_cl_msg_t_s (xdrs, &objp->__inout))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_servo_res_t (XDR *xdrs, cl_calc_servo_res_t *objp)
{
	register int32_t *buf;

	 if (!xdr_cl_msg_t_s (xdrs, &objp->__inout))
		 return FALSE;
	 if (!xdr_cl_bus_t_s (xdrs, &objp->__out))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_servo_res (XDR *xdrs, cl_calc_servo_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->errcode))
		 return FALSE;
	switch (objp->errcode) {
	case 300:
		 if (!xdr_cl_calc_servo_res_t (xdrs, &objp->cl_calc_servo_res_u.__res))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_cl_calc_set_req (XDR *xdrs, cl_calc_set_req *objp)
{
	register int32_t *buf;

	 if (!xdr_short (xdrs, &objp->__in1))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->__in2))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_set_res_t (XDR *xdrs, cl_calc_set_res_t *objp)
{
	register int32_t *buf;

	 if (!xdr_u_short (xdrs, &objp->__out))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_cl_calc_set_res (XDR *xdrs, cl_calc_set_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->errcode))
		 return FALSE;
	switch (objp->errcode) {
	case 300:
		 if (!xdr_cl_calc_set_res_t (xdrs, &objp->cl_calc_set_res_u.__res))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}