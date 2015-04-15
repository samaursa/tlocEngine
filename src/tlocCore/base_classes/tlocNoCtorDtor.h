#ifndef _TLOC_CORE_BASE_CLASSES_NO_CTOR_NO_DTOR_
#define _TLOC_CORE_BASE_CLASSES_NO_CTOR_NO_DTOR_

#include <tlocCore/tlocCoreBase.h>

namespace tloc { namespace core { namespace base_classes {

  class NoCtorNoDtor
  {
  protected:
    NoCtorNoDtor();
    NoCtorNoDtor(const NoCtorNoDtor& a_other);
    ~NoCtorNoDtor();

  };

};};};

#endif