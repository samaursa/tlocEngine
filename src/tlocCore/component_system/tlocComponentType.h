#ifndef TLOC_COMPONENT_TYPE_H
#define TLOC_COMPONENT_TYPE_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>

namespace tloc { namespace core {

  namespace components
  {
    enum type
    {
      transform = 0,
      mesh,

      count
    };
  }; typedef tl_uint component_type;

};};

#endif