#include "tlocNullptr.h"

#ifdef TLOC_CXX03
namespace std {
  nullptr_t nullptr = { };
};
#endif

