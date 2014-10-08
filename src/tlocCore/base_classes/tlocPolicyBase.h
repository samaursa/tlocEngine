#ifndef TLOC_POLICY_BASE
#define TLOC_POLICY_BASE

#include <tlocCore/tlocCoreBase.h>

namespace tloc { namespace core { namespace base_classes {

  template <typename T_Derived>
  class PolicyBase_TI
  {
  protected:
    typedef T_Derived                     derived_type;
    typedef PolicyBase_TI<derived_type>   this_type;

    T_Derived* This()
    {
      return static_cast<derived_type*>(this);
    }

    const T_Derived* This() const
    {
      return static_cast<const derived_type*>(this);
    }
  };

};};};

#endif