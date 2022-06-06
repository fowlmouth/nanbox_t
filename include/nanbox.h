#ifndef NANBOX_HEADER_INCLUDED
#define NANBOX_HEADER_INCLUDED


#include <stdint.h>


#define NANBOX_MASK_NAN     0xFFF8000000000000LL
#define NANBOX_MASK_TYPE    0x0007000000000000LL
#define NANBOX_MASK_PAYLOAD 0x0000FFFFFFFFFFFFLL
#define NANBOX_MASK_SIGN    0x0000800000000000LL

#define NANBOX_BITS_PAYLOAD 48
#define NANBOX_BITS_TYPE    3

#ifndef NANBOX_FLOAT_TYPE
#define NANBOX_FLOAT_TYPE double
#endif

#ifndef NANBOX_INT_TYPE
#define NANBOX_INT_TYPE long long
#endif

#ifndef NANBOX_PTR_TYPE
#define NANBOX_PTR_TYPE void*
#endif

typedef NANBOX_FLOAT_TYPE nanbox_t;
typedef NANBOX_INT_TYPE nanbox_int_t;
typedef NANBOX_PTR_TYPE nanbox_ptr_t;

#ifdef __cplusplus
extern "C" {
#endif

nanbox_t mk_nan();

int nan_get_type(nanbox_t nan);
nanbox_t nan_set_type(nanbox_t nan, int type);

uint64_t nan_get_payload(nanbox_t nan);
nanbox_t nan_set_payload(nanbox_t nan, uint64_t payload);

nanbox_int_t nan_get_int(nanbox_t nan);
nanbox_t nan_set_int(nanbox_t nan, nanbox_int_t number);

nanbox_ptr_t nan_get_ptr(nanbox_t nan);
nanbox_t nan_set_ptr(nanbox_t nan, nanbox_ptr_t value);

void nan_run_tests();

#ifdef __cplusplus
}
#endif

#endif
