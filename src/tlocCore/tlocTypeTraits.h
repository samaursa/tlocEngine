#ifndef TLOC_TYPE_TRAITS_H
#define TLOC_TYPE_TRAITS_H

#include "3rdParty/loki/TypeTraits.h"

namespace tloc
{
  typedef Loki::Int2Type<1> type_true;
  typedef Loki::Int2Type<0> type_false;
};

#endif