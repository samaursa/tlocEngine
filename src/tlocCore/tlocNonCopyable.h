#ifndef TLOC_NON_COPYABLE
#define TLOC_NON_COPYABLE

#include "tlocBase.h"

namespace tloc { namespace core {

  class NonCopyable
  {
  public:
    NonCopyable() {}

    template <typename T>
    NonCopyable(const T& a_Other)
    {
      TLOC_STATIC_ASSERT(false, Copy_constructor_disabled_for_this_class_by_design);
    }

    template <typename T>
    NonCopyable& operator=(const T& a_Other)
    {
      TLOC_STATIC_ASSERT(false, Assignment_operator_disabled_for_this_class_by_design);
    }

  private:

    NonCopyable(const NonCopyable& a_other);
    NonCopyable& operator= (const NonCopyable& a_other);
  };

};};

#endif