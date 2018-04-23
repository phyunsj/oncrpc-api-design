#include <stdio.h>
#include "CL.h"
#include "cl_common.h"
#include "cl_calc.h"
//#define NDEBUG

// http://www.jera.com/techinfo/jtns/jtn002.html  MinUnit
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)

int tests_run = 0;
HANDLER remote;
HANDLER remote_null_client;


static char * TEST_CL_CALC_FREQ() {
   
    cl_return_t errcode = 0;
    unsigned int out;

    printf("\ncalling CL_CALC_FREQ(remote)\n");
    errcode = CL_CALC_FREQ ( &remote, 4, 5, &out );

    mu_assert( "remote:CL_CALC_FREQ() errcode != 300", errcode  == 300 );
    mu_assert( "remote:CL_CALC_FREQ() out != 9", out == 9  );

    return 0;
}

static char * TEST_CL_CALC_FREQ_NULL_CLIENT() {
   
    cl_return_t errcode = 0;
    unsigned int out;

    printf("\ncalling CL_CALC_FREQ(local)\n");
    errcode = CL_CALC_FREQ ( &remote_null_client, 8, 4, &out );

    mu_assert( "local:CL_CALC_FREQ() errcode != 300", errcode  == 300 );
    mu_assert( "local:CL_CALC_FREQ() out != 12", out == 12  );

    return 0;
}

static char * TEST_CL_CALC_FREQ_LOCAL() {
   
    cl_return_t errcode = 0;
    unsigned int out;

    printf("\ncalling cl_calc_freq(local)\n");
    errcode = cl_calc_freq ( 5, 6, &out );

    mu_assert( "local:cl_calc_freq() errcode != 300", errcode  == 300 );
    mu_assert( "local:cl_calc_freq() out != 11", out == 11  );
 
    return 0;
}

static char * TEST_CL_CALC_ALERT() {
   
    cl_return_t errcode = 0;
    unsigned int out = 10;

    printf("\ncalling CL_CALC_ALERT(remote)\n");
    errcode = CL_CALC_ALERT ( &remote, 4, 5, &out );

    mu_assert( "remote:CL_CALC_ALERT() errcode != 300", errcode  == 300 );
    mu_assert( "remote:CL_CALC_ALERT() out != 9", out == 19  );

    return 0;
}

static char * TEST_CL_CALC_ALERT_NULL_CLIENT() {
   
    cl_return_t errcode = 0;
    unsigned int out = 11;

    printf("\ncalling CL_CALC_ALERT(local)\n");
    errcode = CL_CALC_ALERT ( &remote_null_client, 8, 4, &out );

    mu_assert( "local:CL_CALC_ALERT() errcode != 300", errcode  == 300 );
    mu_assert( "local:CL_CALC_ALERT() out != 12", out == 23  );

    return 0;
}

static char * TEST_CL_CALC_ALERT_LOCAL() {
   
    cl_return_t errcode = 0;
    unsigned int out = 12;

    printf("\ncalling cl_calc_alert(local)\n");
    errcode = cl_calc_alert ( 5, 7, &out );

    mu_assert( "local:cl_calc_alert() errcode != 300", errcode  == 300 );
    mu_assert( "local:cl_calc_alert() out != 11", out == 24  );
 
    return 0;
}


static char * TEST_CL_CALC_READ() {
   
    cl_return_t errcode = 0;
    cl_int16_t in1 = 5;
    cl_int16_t in2 = 9;
    cl_int32_t out;

    printf("\ncalling CL_CALC_READ(remote)\n");
    errcode = CL_CALC_READ ( &remote, in1, in2, &out );

    mu_assert( "remote:CL_CALC_READ() errcode != 300", errcode  == 300 );
    mu_assert( "remote:CL_CALC_READ() out != 11", out == 14  );

    return 0;
}

static char * TEST_CL_CALC_READ_NULL_CLIENT() {
   
    cl_return_t errcode = 0;
    cl_int16_t in1 = 3;
    cl_int16_t in2 = 9;
    cl_int32_t out;

    printf("\ncalling CL_CALC_READ(local)\n");
    errcode = CL_CALC_READ ( &remote_null_client, in1, in2, &out );

    mu_assert( "local:CL_CALC_READ() errcode != 300", errcode  == 300 );
    mu_assert( "local:CL_CALC_READ() out != 12", out == 12  );

    return 0;
}

static char * TEST_CL_CALC_READ_LOCAL() {
   
    cl_return_t errcode = 0;
    cl_int16_t in1 = 5;
    cl_int16_t in2 = 9;
    cl_int32_t out;

    printf("\ncalling cl_calc_read(local)\n");
    errcode = cl_calc_read ( in1, in2, &out );

    mu_assert( "local:cl_calc_read() errcode != 300", errcode  == 300 );
    mu_assert( "local:cl_calc_read() out != 11", out == 14 );
 
    return 0;
}


static char * TEST_CL_CALC_WRITE() {
   
    cl_return_t errcode = 0;
    cl_msg_t   in;
    cl_bus_t   out;

    in.addr  = 44;
    in.flags = 33;
    in.len   = 22;

    printf("\ncalling CL_CALC_WRITE(remote)\n");
    errcode = CL_CALC_WRITE ( &remote, in,  &out );

    mu_assert( "remote:CL_CALC_WRITE() errcode != 300", errcode  == 300 );
    mu_assert( "remote:CL_CALC_WRITE() out.info   != 44", out.info   == 44 );
    mu_assert( "remote:CL_CALC_WRITE() out.src    != 32", out.src    == 32);
    mu_assert( "remote:CL_CALC_WRITE() out.dst    != 54", out.dst    == 54);
    mu_assert( "remote:CL_CALC_WRITE() out.length != 22", out.length == 22);
    mu_assert( "remote:CL_CALC_WRITE() out.stride != 122", out.stride == 122);
    mu_assert( "remote:CL_CALC_WRITE() out.next   != 64", out.next   == 64 );

    return 0;
}

static char * TEST_CL_CALC_WRITE_NULL_CLIENT() {
   
    cl_return_t errcode = 0;
    cl_msg_t   in;
    cl_bus_t   out;

    in.addr  = 44;
    in.flags = 33;
    in.len   = 22;

    printf("\ncalling CL_CALC_WRITE(local)\n");
    errcode = CL_CALC_WRITE ( &remote_null_client, in,  &out );

    mu_assert( "local:CL_CALC_WRITE() errcode != 300", errcode  == 300 );
    mu_assert( "local:CL_CALC_WRITE() out.info   != 44", out.info   == 44 );
    mu_assert( "local:CL_CALC_WRITE() out.src    != 32", out.src    == 32);
    mu_assert( "local:CL_CALC_WRITE() out.dst    != 54", out.dst    == 54);
    mu_assert( "local:CL_CALC_WRITE() out.length != 22", out.length == 22);
    mu_assert( "local:CL_CALC_WRITE() out.stride != 122", out.stride == 122);
    mu_assert( "local:CL_CALC_WRITE() out.next   != 64", out.next   == 64 );

    return 0;
}

static char * TEST_CL_CALC_WRITE_LOCAL() {
   
    cl_return_t errcode = 0;
    cl_msg_t   in;
    cl_bus_t   out;

    in.addr  = 44;
    in.flags = 33;
    in.len   = 22;

    printf("\ncalling cl_calc_write(local)\n");
    errcode = cl_calc_write ( in,  &out );

    mu_assert( "local:cl_cal_write() errcode != 300", errcode  == 300 );
    mu_assert( "local:cl_cal_write() out.info   != 44", out.info   == 44 );
    mu_assert( "local:cl_cal_write() out.src    != 32", out.src    == 32);
    mu_assert( "local:cl_cal_write() out.dst    != 54", out.dst    == 54);
    mu_assert( "local:cl_cal_write() out.length != 22", out.length == 22);
    mu_assert( "local:cl_cal_write() out.stride != 122", out.stride == 122);
    mu_assert( "local:cl_cal_write() out.next   != 64", out.next   == 64 );

    return 0;
}


static char * TEST_CL_CALC_TIMER() {
   
    cl_return_t errcode = 0;
    cl_msg_t   in;
    cl_bus_t   out;

    in.addr  = 44;
    in.flags = 33;
    in.len   = 22;

    printf("\ncalling CL_CALC_TIMER(remote)\n");
    errcode = CL_CALC_TIMER ( &remote, &in,  &out );

    mu_assert( "remote:CL_CALC_TIMER() errcode != 300", errcode  == 300 );
    mu_assert( "remote:CL_CALC_TIMER() out.info   != 44", out.info   == 44 );
    mu_assert( "remote:CL_CALC_TIMER() out.src    != 32", out.src    == 32);
    mu_assert( "remote:CL_CALC_TIMER() out.dst    != 54", out.dst    == 54);
    mu_assert( "remote:CL_CALC_TIMER() out.length != 22", out.length == 22);
    mu_assert( "remote:CL_CALC_TIMER() out.stride != 122", out.stride == 122);
    mu_assert( "remote:CL_CALC_TIMER() out.next   != 64", out.next   == 64 );

    return 0;
}

static char * TEST_CL_CALC_TIMER_NULL_CLIENT() {
   
    cl_return_t errcode = 0;
    cl_msg_t   in;
    cl_bus_t   out;

    in.addr  = 44;
    in.flags = 33;
    in.len   = 22;
    
    printf("\ncalling CL_CALC_TIMER(local)\n");
    errcode = CL_CALC_TIMER ( &remote_null_client, &in,  &out );

    mu_assert( "local:CL_CALC_TIMER() errcode != 300", errcode  == 300 );
    mu_assert( "local:CL_CALC_TIMER() out.info   != 44", out.info   == 44 );
    mu_assert( "local:CL_CALC_TIMER() out.src    != 32", out.src    == 32);
    mu_assert( "local:CL_CALC_TIMER() out.dst    != 54", out.dst    == 54);
    mu_assert( "local:CL_CALC_TIMER() out.length != 22", out.length == 22);
    mu_assert( "local:CL_CALC_TIMER() out.stride != 122", out.stride == 122);
    mu_assert( "local:CL_CALC_TIMER() out.next   != 64", out.next   == 64 );

    return 0;
}

static char * TEST_CL_CALC_TIMER_LOCAL() {
   
    cl_return_t errcode = 0;
    cl_msg_t   in;
    cl_bus_t   out;

    in.addr  = 44;
    in.flags = 33;
    in.len   = 22;
    
    printf("\ncalling cl_calc_timer(local)\n");
    errcode = cl_calc_timer ( &in,  &out );

    mu_assert( "local:cl_calc_timer() errcode != 300", errcode  == 300 );
    mu_assert( "local:cl_calc_timer() out.info   != 44", out.info   == 44 );
    mu_assert( "local:cl_calc_timer() out.src    != 32", out.src    == 32);
    mu_assert( "local:cl_calc_timer() out.dst    != 54", out.dst    == 54);
    mu_assert( "local:cl_calc_timer() out.length != 22", out.length == 22);
    mu_assert( "local:cl_calc_timer() out.stride != 122", out.stride == 122);
    mu_assert( "local:cl_calc_timer() out.next   != 64", out.next   == 64 );

    return 0;
}

static char * TEST_CL_CALC_FILTER() {
   
    cl_return_t errcode = 0;
    cl_msg_t   in;
    cl_bus_t   out;

    in.addr  = 44;
    in.flags = 33;
    in.len   = 22;

    printf("\ncalling CL_CALC_FILTER(remote)\n");
    errcode = CL_CALC_FILTER ( &remote, &in,  &out );

    mu_assert( "remote:CL_CALC_FILTER() errcode != 300", errcode  == 300 );
    mu_assert( "remote:CL_CALC_FILTER() out.info   != 44", out.info   == 44 );
    mu_assert( "remote:CL_CALC_FILTER() out.src    != 32", out.src    == 32);
    mu_assert( "remote:CL_CALC_FILTER() out.dst    != 54", out.dst    == 54);
    mu_assert( "remote:CL_CALC_FILTER() out.length != 22", out.length == 22);
    mu_assert( "remote:CL_CALC_FILTER() out.stride != 122", out.stride == 122);
    mu_assert( "remote:CL_CALC_FILTER() out.next   != 64", out.next   == 64 );

    return 0;
}

static char * TEST_CL_CALC_FILTER_NULL_CLIENT() {
   
    cl_return_t errcode = 0;
    cl_msg_t   in;
    cl_bus_t   out;

    in.addr  = 44;
    in.flags = 33;
    in.len   = 22;

    printf("\ncalling CL_CALC_FILTER(local)\n");
    errcode = CL_CALC_FILTER ( &remote_null_client, &in,  &out );

    mu_assert( "local:CL_CALC_FILTER() errcode != 300", errcode  == 300 );
    mu_assert( "local:CL_CALC_FILTER() out.info   != 44", out.info   == 44 );
    mu_assert( "local:CL_CALC_FILTER() out.src    != 32", out.src    == 32);
    mu_assert( "local:CL_CALC_FILTER() out.dst    != 54", out.dst    == 54);
    mu_assert( "local:CL_CALC_FILTER() out.length != 22", out.length == 22);
    mu_assert( "local:CL_CALC_FILTER() out.stride != 122", out.stride == 122);
    mu_assert( "local:CL_CALC_FILTER() out.next   != 64", out.next   == 64 );

    return 0;
}

static char * TEST_CL_CALC_FILTER_LOCAL() {
   
    cl_return_t errcode = 0;
    cl_msg_t   in;
    cl_bus_t   out;

    in.addr  = 44;
    in.flags = 33;
    in.len   = 22;

    printf("\ncalling cl_calc_filter(local)\n");
    errcode = cl_calc_filter ( &in,  &out );

    mu_assert( "local:cl_calc_filter() errcode != 300", errcode  == 300 );
    mu_assert( "local:cl_calc_filter() out.info   != 44", out.info   == 44 );
    mu_assert( "local:cl_calc_filter() out.src    != 32", out.src    == 32);
    mu_assert( "local:cl_calc_filter() out.dst    != 54", out.dst    == 54);
    mu_assert( "local:cl_calc_filter() out.length != 22", out.length == 22);
    mu_assert( "local:cl_calc_filter() out.stride != 122", out.stride == 122);
    mu_assert( "local:cl_calc_filter() out.next   != 64", out.next   == 64 );

    return 0;
}

static char * TEST_CL_CALC_SERIAL() {
   
    cl_return_t errcode = 300;
    cl_msg_t   in1;
    cl_msg_t   in2;
    cl_bus_t   out;

    in1.addr  = 44;
    in1.flags = 33;
    in1.len   = 22;

    in2.addr  = 45;
    in2.flags = 34;
    in2.len   = 23;
 
    printf("\ncalling CL_CALC_SERIAL(remote)\n");
    CL_CALC_SERIAL ( &remote, &in1, &in2, &out );

    mu_assert( "remote:CL_CALC_SERIAL() errcode != 300", errcode  == 300 );
    mu_assert( "remote:CL_CALC_SERIAL() out.info   != 44", out.info   == 44 );
    mu_assert( "remote:CL_CALC_SERIAL() out.src    != 32", out.src    == 32);
    mu_assert( "remote:CL_CALC_SERIAL() out.dst    != 54", out.dst    == 54);
    mu_assert( "remote:CL_CALC_SERIAL() out.length != 22", out.length == 22);
    mu_assert( "remote:CL_CALC_SERIAL() out.stride != 122", out.stride == 122);
    mu_assert( "remote:CL_CALC_SERIAL() out.next   != 64", out.next   == 64 );

    return 0;
}

static char * TEST_CL_CALC_SERIAL_NULL_CLIENT() {
   
    cl_return_t errcode = 300;
    cl_msg_t   in1;
    cl_msg_t   in2;
    cl_bus_t   out;

    in1.addr  = 44;
    in1.flags = 33;
    in1.len   = 22;

    in2.addr  = 45;
    in2.flags = 34;
    in2.len   = 23;

    printf("\ncalling CL_CALC_SERIAL(local)\n");
    CL_CALC_SERIAL ( &remote_null_client, &in1, &in2, &out );

    mu_assert( "local:CL_CALC_SERIAL() errcode != 300", errcode  == 300 );
    mu_assert( "local:CL_CALC_SERIAL() out.info   != 44", out.info   == 44 );
    mu_assert( "local:CL_CALC_SERIAL() out.src    != 32", out.src    == 32);
    mu_assert( "local:CL_CALC_SERIAL() out.dst    != 54", out.dst    == 54);
    mu_assert( "local:CL_CALC_SERIAL() out.length != 22", out.length == 22);
    mu_assert( "local:CL_CALC_SERIAL() out.stride != 122", out.stride == 122);
    mu_assert( "local:CL_CALC_SERIAL() out.next   != 64", out.next   == 64 );

    return 0;
}

static char * TEST_CL_CALC_SERIAL_LOCAL() {
   
    cl_return_t errcode = 300;
    cl_msg_t   in1;
    cl_msg_t   in2;
    cl_bus_t   out;

    in1.addr  = 44;
    in1.flags = 33;
    in1.len   = 22;

    in2.addr  = 45;
    in2.flags = 34;
    in2.len   = 23;
    
    printf("\ncalling cl_calc_serial(local)\n");
    cl_calc_serial ( &in1, &in2, &out );

    mu_assert( "local:cl_calc_serial() errcode != 300", errcode  == 300 );
    mu_assert( "local:cl_calc_serial() out.info   != 44", out.info   == 44 );
    mu_assert( "local:cl_calc_serial() out.src    != 32", out.src    == 32);
    mu_assert( "local:cl_calc_serial() out.dst    != 54", out.dst    == 54);
    mu_assert( "local:cl_calc_serial() out.length != 22", out.length == 22);
    mu_assert( "local:cl_calc_serial() out.stride != 122", out.stride == 122);
    mu_assert( "local:cl_calc_serial() out.next   != 64", out.next   == 64 );

    return 0;
}


static char * TEST_CL_CALC_SERVO() {
   
    cl_return_t errcode = 0;
    cl_msg_t   in;
    cl_bus_t   out;

    in.addr  = 44;
    in.flags = 33;
    in.len   = 22;

    printf("\ncalling CL_CALC_SERVO(remote)\n");
    errcode = CL_CALC_SERVO ( &remote, &in,  &out );

    mu_assert( "remote:CL_CALC_SERVO() errcode != 300", errcode  == 300 );
    
    mu_assert( "remote:CL_CALC_SERVO() in.addr   != 49", in.addr   == 49 );
    mu_assert( "remote:CL_CALC_SERVO() in.flags  != 43", in.flags   == 43 );
    mu_assert( "remote:CL_CALC_SERVO() in.len    != 37", in.len   == 37 );
    
    mu_assert( "remote:CL_CALC_SERVO() out.info   != 44", out.info   == 44 );
    mu_assert( "remote:CL_CALC_SERVO() out.src    != 32", out.src    == 32);
    mu_assert( "remote:CL_CALC_SERVO() out.dst    != 54", out.dst    == 54);
    mu_assert( "remote:CL_CALC_SERVO() out.length != 22", out.length == 22);
    mu_assert( "remote:CL_CALC_SERVO() out.stride != 122", out.stride == 122);
    mu_assert( "remote:CL_CALC_SERVO() out.next   != 64", out.next   == 64 );

    return 0;
}

static char * TEST_CL_CALC_SERVO_NULL_CLIENT() {
   
    cl_return_t errcode = 0;
    cl_msg_t   in;
    cl_bus_t   out;

    in.addr  = 44;
    in.flags = 33;
    in.len   = 22;

    printf("\ncalling CL_CALC_SERVO(local)\n");
    errcode = CL_CALC_SERVO ( &remote_null_client, &in,  &out );

    mu_assert( "local:CL_CALC_SERVO() errcode != 300", errcode  == 300 );
    
    mu_assert( "local:CL_CALC_SERVO() in.addr   != 49", in.addr   == 49 );
    mu_assert( "local:CL_CALC_SERVO() in.flags  != 43", in.flags   == 43 );
    mu_assert( "local:CL_CALC_SERVO() in.len    != 37", in.len   == 37 );
    
    mu_assert( "local:CL_CALC_SERVO() out.info   != 44", out.info   == 44 );
    mu_assert( "local:CL_CALC_SERVO() out.src    != 32", out.src    == 32);
    mu_assert( "local:CL_CALC_SERVO() out.dst    != 54", out.dst    == 54);
    mu_assert( "local:CL_CALC_SERVO() out.length != 22", out.length == 22);
    mu_assert( "local:CL_CALC_SERVO() out.stride != 122", out.stride == 122);
    mu_assert( "local:CL_CALC_SERVO() out.next   != 64", out.next   == 64 );

    return 0;
}

static char * TEST_CL_CALC_SERVO_LOCAL() {
   
    cl_return_t errcode = 0;
    cl_msg_t   in;
    cl_bus_t   out;

    in.addr  = 44;
    in.flags = 33;
    in.len   = 22;

    printf("\ncalling cl_calc_servo(local)\n");
    errcode = cl_calc_servo ( &in,  &out );

    mu_assert( "local:cl_calc_servo() errcode != 300", errcode  == 300 );
    
    mu_assert( "local:cl_calc_servo() in.addr   != 49", in.addr   == 49 );
    mu_assert( "local:cl_calc_servo() in.flags  != 43", in.flags   == 43 );
    mu_assert( "local:cl_calc_servo() in.len    != 37", in.len   == 37 );
    
    mu_assert( "local:cl_calc_servo() out.info   != 44", out.info   == 44 );
    mu_assert( "local:cl_calc_servo() out.src    != 32", out.src    == 32);
    mu_assert( "local:cl_calc_servo() out.dst    != 54", out.dst    == 54);
    mu_assert( "local:cl_calc_servo() out.length != 22", out.length == 22);
    mu_assert( "local:cl_calc_servo() out.stride != 122", out.stride == 122);
    mu_assert( "local:cl_calc_servo() out.next   != 64", out.next   == 64 );

    return 0;
}

static char * TEST_CL_CALC_SET() {
   
    cl_return_t errcode = 0;
    cl_int16_t in1 = 5;
    cl_int32_t in2 = 9;
    cl_int16_t out;

    printf("\ncalling CL_CALC_SET(remote)\n");
    errcode = CL_CALC_SET ( &remote, in1, in2, &out );

    mu_assert( "remote:CL_CALC_SET() errcode != 301", errcode  == 301 );

    return 0;
}

static char * TEST_CL_CALC_SET_NULL_CLIENT() {
   
    cl_return_t errcode = 0;
    cl_int16_t in1 = 3;
    cl_int32_t in2 = 9;
    cl_int16_t out;

    printf("\ncalling CL_CALC_SET(local)\n");
    errcode = CL_CALC_SET ( &remote_null_client, in1, in2, &out );

    mu_assert( "local:CL_CALC_SET() errcode != 301", errcode  == 301 );

    return 0;
}

static char * TEST_CL_CALC_SET_LOCAL() {
   
    cl_return_t errcode = 0;
    cl_int16_t in1 = 5;
    cl_int32_t in2 = 9;
    cl_int16_t out;

    printf("\ncalling cl_calc_set(local)\n");
    errcode = cl_calc_set ( in1, in2, &out );

    mu_assert( "local:cl_calc_set() errcode != 301", errcode  == 301 );
 
    return 0;
}


static char * all_tests() {
    mu_run_test(TEST_CL_CALC_FREQ);
    mu_run_test(TEST_CL_CALC_FREQ_NULL_CLIENT);
    mu_run_test(TEST_CL_CALC_FREQ_LOCAL);
    mu_run_test(TEST_CL_CALC_ALERT);
    mu_run_test(TEST_CL_CALC_ALERT_NULL_CLIENT);
    mu_run_test(TEST_CL_CALC_ALERT_LOCAL);
    mu_run_test(TEST_CL_CALC_READ);
    mu_run_test(TEST_CL_CALC_READ_NULL_CLIENT);
    mu_run_test(TEST_CL_CALC_READ_LOCAL);
    mu_run_test(TEST_CL_CALC_WRITE);
    mu_run_test(TEST_CL_CALC_WRITE_NULL_CLIENT);
    mu_run_test(TEST_CL_CALC_WRITE_LOCAL);
    mu_run_test(TEST_CL_CALC_TIMER);
    mu_run_test(TEST_CL_CALC_TIMER_NULL_CLIENT);
    mu_run_test(TEST_CL_CALC_TIMER_LOCAL);
    mu_run_test(TEST_CL_CALC_FILTER);
    mu_run_test(TEST_CL_CALC_FILTER_NULL_CLIENT);
    mu_run_test(TEST_CL_CALC_FILTER_LOCAL);
    mu_run_test(TEST_CL_CALC_SERIAL);
    mu_run_test(TEST_CL_CALC_SERIAL_NULL_CLIENT);
    mu_run_test(TEST_CL_CALC_SERIAL_LOCAL);
    mu_run_test(TEST_CL_CALC_SERVO);
    mu_run_test(TEST_CL_CALC_SERVO_NULL_CLIENT);
    mu_run_test(TEST_CL_CALC_SERVO_LOCAL);
    mu_run_test(TEST_CL_CALC_SET);
    mu_run_test(TEST_CL_CALC_SET_NULL_CLIENT);
    mu_run_test(TEST_CL_CALC_SET_LOCAL);
    return 0;
}
 
int main(int argc, char **argv) {

     INIT_HANDLER ( &remote, argv[1], "tcp");

     char *result = all_tests();
     printf("\nTESTS RUN: %d\n", tests_run);
     if (result != 0) printf("%s\n", result);
     else printf("ALL TESTS PASSED\n\n");
     
     DESTROY_HANDLER( &remote);
     return result != 0;
}
