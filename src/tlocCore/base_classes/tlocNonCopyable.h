#ifndef TLOC_NON_COPYABLE
#define TLOC_NON_COPYABLE

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>

namespace tloc { namespace core { namespace base_classes {

  class non_copyable_i
  {
  public:
    non_copyable_i() {}

    non_copyable_i(const non_copyable_i& a_other) = delete;
    non_copyable_i& operator= (const non_copyable_i& a_other) = delete;
  };

};};};

#endif