#define NANBOX_IMPLEMENTATION
#include "nanbox.h"

#include <stdio.h>
#include <math.h>

#include <assert.h>
 

typedef union
{
  double as_real;
  uint64_t as_bits;
} nanbox_value_t;






nanbox_t mk_nan()
{
  nanbox_value_t value = {.as_bits = NANBOX_MASK_NAN};
  return value.as_real;
}

// returns the type mask or -1 for floating point values
int nan_get_type(nanbox_t nan)
{
  nanbox_value_t value = {.as_real = nan};
  if((value.as_bits & NANBOX_MASK_NAN) != NANBOX_MASK_NAN)
  {
    // this is a normal double
    return -1;
  }
  return (value.as_bits & NANBOX_MASK_TYPE) >> NANBOX_BITS_PAYLOAD;
}

nanbox_t nan_set_type(nanbox_t nan, int type)
{
  type = type & ((1 << NANBOX_BITS_TYPE) - 1);
  nanbox_value_t value = {.as_real = nan};
  value.as_bits = (value.as_bits & ~NANBOX_MASK_TYPE) | ((uint64_t)type << NANBOX_BITS_PAYLOAD);
  return value.as_real;
}


uint64_t nan_get_payload(nanbox_t nan)
{
  nanbox_value_t value = {.as_real = nan};
  return value.as_bits & NANBOX_MASK_PAYLOAD;
}

nanbox_t nan_set_payload(nanbox_t nan, uint64_t payload)
{
  nanbox_value_t value = {.as_real = nan};
  value.as_bits = (value.as_bits & (NANBOX_MASK_NAN | NANBOX_MASK_TYPE)) | (payload & NANBOX_MASK_PAYLOAD);
  return value.as_real;
}

nanbox_int_t nan_get_int(nanbox_t nan)
{
  uint64_t payload = nan_get_payload(nan);
  if(payload & NANBOX_MASK_SIGN)
  {
    // sign extension
    payload |= NANBOX_MASK_NAN | NANBOX_MASK_TYPE;
  }
  return (nanbox_int_t)payload;
}

nanbox_t nan_set_int(nanbox_t nan, nanbox_int_t number)
{
  return nan_set_payload(nan, (uint64_t)number);
}

nanbox_ptr_t nan_get_ptr(nanbox_t nan)
{
  return (nanbox_ptr_t)nan_get_payload(nan);
}

nanbox_t nan_set_ptr(nanbox_t nan, nanbox_ptr_t value)
{
  return nan_set_payload(nan, (uint64_t)value);
}



void nan_dump(nanbox_t nan)
{
  nanbox_value_t value = {.as_real = nan};
  printf(
    "number: %f\n"
    "  isnan= %d  bits= 0x%016llx\n"
    "  type= %d  int= %lld  ptr= %p\n\n",
    nan,
    isnan(nan), value.as_bits,
    nan_get_type(nan), nan_get_int(nan), nan_get_ptr(nan));
}

void nan_run_tests()
{

#define TEST(expr) \
  printf("testing `%s`\n", #expr); \
  nan_dump(expr);

  nanbox_t n = mk_nan();
  nan_dump(n);
  for(int i = 0; i < (1 << NANBOX_BITS_TYPE); ++i)
  {
    n = nan_set_type(n, i);
    printf("iteration %d\n", i);
    nan_dump(n);
  }

  printf("-------\n"
    "integers\n");
  n = nan_set_int(nan_set_type(mk_nan(), 3), -42);
  nan_dump(n);
  assert(nan_get_int(n) == -42);

  n = nan_set_int(n, 99);
  nan_dump(n);
  assert(nan_get_int(n) == 99);

  printf("-------\n"
    "floats\n");
  TEST(3.14);
  TEST(nan("0"));
  TEST(nan("1"));
  TEST(INFINITY);
  TEST(nan_set_int(mk_nan(), NANBOX_MASK_PAYLOAD));
  // TEST(nan_set_int(mk_nan(), (1 << 48) - 1));



}
