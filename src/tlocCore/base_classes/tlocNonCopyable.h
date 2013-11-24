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

    template <typename T>
    NonCopyable_I(const T& a_Other)
    {
      TLOC_STATIC_ASSERT((Loki::IsSameType<T, DummyStruct>::value),
                         Copy_constructor_disabled_for_this_class_by_design);
    }

    template <typename T>
    NonCopyable_I& operator=(const T& a_Other)
    {
      TLOC_STATIC_ASSERT((Loki::IsSameType<T, DummyStruct>::value),
                         Assignment_operator_disabled_for_this_class_by_design);
    }

  private:

    NonCopyable_I(const NonCopyable_I& a_other);
    NonCopyable_I& operator= (const NonCopyable_I& a_other);
  };

};};};

#endif