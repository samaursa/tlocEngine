#ifndef _TLOC_CORE_EXCEPTION_H_
#define _TLOC_CORE_EXCEPTION_H_

#include <tlocCore/tlocBase.h>
#include <exception>

namespace tloc { namespace core {

  class core_exception
    : std::exception
  { };

};};

#endif