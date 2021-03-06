#include "fd_operators.h"

// Operators aliases to make code more readable
// Inclusion is totally optional

// Mask

#define UNIFORM_SECOND_SPATIAL_DERIVATIVE_CENTERED_MASK(jam,i) \
  FDOPERATORJAM_SDSUC_SET_MASK(jam,i)

#define MIXED_SECOND_SPATIAL_DERIVATIVE_CENTERED_MASK(jam,i1,i2) \
  FDOPERATORJAM_SDSMC_SET_MASK(jam,i1,i2)

#define MIXED_SECOND_SPATIAL_DERIVATIVE_CENTERED_BOUCHUT_MASK(jam,i1,i2) \
  FDOPERATORJAM_SDSMCB_SET_MASK(jam,i1,i2)

#define FIRST_SPATIAL_DERIVATIVE_UPWIND_MASK(jam,i) \
  FDOPERATORJAM_SDFU_SET_MASK(jam,i)

#define FIRST_SPATIAL_DERIVATIVE_CENTERED_MASK(jam,i) \
  FDOPERATORJAM_SDFC_SET_MASK(jam,i)

#define FIRST_SPATIAL_DERIVATIVE_FORWARD_MASK(jam,i) \
  FIRST_SPATIAL_DERIVATIVE_UPWIND_MASK(jam,i)

#define FIRST_TIME_DERIVATIVE_FORWARD_MASK(jam) \
  FDOPERATORJAM_TDFF_SET_MASK(jam)

#define ZERO_ORDER_MASK(jam) FDOPERATORJAM_ZO_SET_MASK(jam)

// Value
#define UNIFORM_SECOND_SPATIAL_DERIVATIVE_CENTERED_SET(jam,i,v) \
  FDOPERATORJAM_SDSUC_SET_VALUE(jam,i,v)

#define MIXED_SECOND_SPATIAL_DERIVATIVE_CENTERED_SET(jam,i1,i2,v) \
  FDOPERATORJAM_SDSMC_SET_VALUE(jam,i1,i2,v)

#define MIXED_SECOND_SPATIAL_DERIVATIVE_CENTERED_BOUCHUT_SET(jam,i1,i2,v) \
  FDOPERATORJAM_SDSMCB_SET_VALUE(jam,i1,i2,v)

#define FIRST_SPATIAL_DERIVATIVE_UPWIND_SET(jam,i,v) \
  FDOPERATORJAM_SDFU_SET_VALUE(jam,i,v)

#define FIRST_SPATIAL_DERIVATIVE_CENTERED_SET(jam,i,v) \
  FDOPERATORJAM_SDFC_SET_VALUE(jam,i,v)

#define FIRST_SPATIAL_DERIVATIVE_FORWARD_SET(jam,i,v) \
  FIRST_SPATIAL_DERIVATIVE_UPWIND_SET(jam,i,v)

#define FIRST_TIME_DERIVATIVE_FORWARD_SET(jam,v) \
  FDOPERATORJAM_TDFF_SET_VALUE(jam,v)

#define ZERO_ORDER_SET(jam,v) FDOPERATORJAM_ZO_SET_VALUE(jam,v)

