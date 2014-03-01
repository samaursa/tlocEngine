#ifndef TLOC_NON_COPYABLE
#define TLOC_NON_COPYABLE

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>

namespace tloc { namespace core { namespace base_classes {

  class NonCopyable_I
  {
  public:
    NonCopyable_I() {}

  private:

    NonCopyable_I(const NonCopyable_I& a_other);
    NonCopyable_I& operator= (const NonCopyable_I& a_other);
  };

};};};

#endif