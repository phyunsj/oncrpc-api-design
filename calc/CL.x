

struct cl_msg_t_s {
	short addr;
	short flags;
	int len;
};
typedef struct cl_msg_t_s cl_msg_t_s;

struct cl_bus_t_s {
	int info;
	int src;
	int dst;
	int length;
	int stride;
	int next;
};
typedef struct cl_bus_t_s cl_bus_t_s;

struct cl_calc_freq_req {
	int __in10;
	int __in;
};
typedef struct cl_calc_freq_req cl_calc_freq_req;

struct cl_calc_freq_res_t {
	unsigned int __out;
};
typedef struct cl_calc_freq_res_t cl_calc_freq_res_t;

union cl_calc_freq_res switch(int errcode) {
	case 300  : cl_calc_freq_res_t __res;
	default : void;
};

struct cl_calc_alert_req {
	int __in10;
	int __in;
	unsigned int __inout;
};
typedef struct cl_calc_alert_req cl_calc_alert_req;

struct cl_calc_alert_res_t {
	unsigned int __inout;
};
typedef struct cl_calc_alert_res_t cl_calc_alert_res_t;

union cl_calc_alert_res switch(int errcode) {
	case 300  : cl_calc_alert_res_t __res;
	default : void;
};

struct cl_calc_read_req {
	short __in10;
	unsigned short __in;
};
typedef struct cl_calc_read_req cl_calc_read_req;

struct cl_calc_read_res_t {
	unsigned int __out;
};
typedef struct cl_calc_read_res_t cl_calc_read_res_t;

union cl_calc_read_res switch(int errcode) {
	case 300  : cl_calc_read_res_t __res;
	default : void;
};

struct cl_calc_write_req {
	cl_msg_t_s __in;
};
typedef struct cl_calc_write_req cl_calc_write_req;

struct cl_calc_write_res_t {
	cl_bus_t_s __out;
};
typedef struct cl_calc_write_res_t cl_calc_write_res_t;

union cl_calc_write_res switch(int errcode) {
	case 300  : cl_calc_write_res_t __res;
	default : void;
};

struct cl_calc_timer_req {
	cl_msg_t_s __in;
};
typedef struct cl_calc_timer_req cl_calc_timer_req;

struct cl_calc_timer_res_t {
	cl_bus_t_s __out;
};
typedef struct cl_calc_timer_res_t cl_calc_timer_res_t;

union cl_calc_timer_res switch(int errcode) {
	case 300  : cl_calc_timer_res_t __res;
	default : void;
};

struct cl_calc_filter_req {
	cl_msg_t_s __in;
};
typedef struct cl_calc_filter_req cl_calc_filter_req;

struct cl_calc_filter_res_t {
	cl_bus_t_s __out;
};
typedef struct cl_calc_filter_res_t cl_calc_filter_res_t;

union cl_calc_filter_res switch(int errcode) {
	case 300  : cl_calc_filter_res_t __res;
	default : void;
};

struct cl_calc_serial_req {
	cl_msg_t_s __in1;
	cl_msg_t_s __in2;
};
typedef struct cl_calc_serial_req cl_calc_serial_req;

struct cl_calc_serial_res_t {
	cl_bus_t_s __out;
};
typedef struct cl_calc_serial_res_t cl_calc_serial_res_t;

union cl_calc_serial_res switch(int errcode) {
	case 300  : cl_calc_serial_res_t __res;
	default : void;
};

struct cl_calc_servo_req {
	cl_msg_t_s __inout;
};
typedef struct cl_calc_servo_req cl_calc_servo_req;

struct cl_calc_servo_res_t {
	cl_msg_t_s __inout;
	cl_bus_t_s __out;
};
typedef struct cl_calc_servo_res_t cl_calc_servo_res_t;

union cl_calc_servo_res switch(int errcode) {
	case 300  : cl_calc_servo_res_t __res;
	default : void;
};

struct cl_calc_set_req {
	short __in1;
	unsigned int __in2;
};
typedef struct cl_calc_set_req cl_calc_set_req;

struct cl_calc_set_res_t {
	unsigned short __out;
};
typedef struct cl_calc_set_res_t cl_calc_set_res_t;

union cl_calc_set_res switch(int errcode) {
	case 300  : cl_calc_set_res_t __res;
	default : void;
};

program CLPROG {
	version CLVERS {
		cl_calc_freq_res CL_CALC_FREQ_FUNC ( cl_calc_freq_req ) = 1;
		cl_calc_alert_res CL_CALC_ALERT_FUNC ( cl_calc_alert_req ) = 2;
		cl_calc_read_res CL_CALC_READ_FUNC ( cl_calc_read_req ) = 3;
		cl_calc_write_res CL_CALC_WRITE_FUNC ( cl_calc_write_req ) = 4;
		cl_calc_timer_res CL_CALC_TIMER_FUNC ( cl_calc_timer_req ) = 5;
		cl_calc_filter_res CL_CALC_FILTER_FUNC ( cl_calc_filter_req ) = 6;
		cl_calc_serial_res CL_CALC_SERIAL_FUNC ( cl_calc_serial_req ) = 7;
		cl_calc_servo_res CL_CALC_SERVO_FUNC ( cl_calc_servo_req ) = 8;
		cl_calc_set_res CL_CALC_SET_FUNC ( cl_calc_set_req ) = 9;
	} = 1;
} = 0x20000001;
