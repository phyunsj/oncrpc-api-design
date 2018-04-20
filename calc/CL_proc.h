
cl_return_t CL_CALC_FREQ ( HANDLER *remote , int in10, int in, unsigned int *out );

cl_return_t CL_CALC_ALERT ( HANDLER *remote , int in10, int in, unsigned int *inout );

cl_return_t CL_CALC_READ ( HANDLER *remote , cl_int16_t in10, cl_uint16_t in, cl_uint32_t *out );

cl_return_t CL_CALC_WRITE ( HANDLER *remote , cl_msg_t in, cl_bus_t *out );

cl_return_t CL_CALC_TIMER ( HANDLER *remote , cl_msg_t *in, cl_bus_t *out );

int CL_CALC_FILTER ( HANDLER *remote , cl_msg_t *in, cl_bus_t *out );

void CL_CALC_SERIAL ( HANDLER *remote , cl_msg_t *in1, cl_msg_t *in2, cl_bus_t *out );

int CL_CALC_SERVO ( HANDLER *remote , cl_msg_t *inout, cl_bus_t *out );

cl_return_t CL_CALC_SET ( HANDLER *remote , cl_int16_t in1, cl_uint32_t in2, cl_uint16_t *out );
