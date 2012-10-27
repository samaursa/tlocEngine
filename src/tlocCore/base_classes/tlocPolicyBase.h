#ifndef TLOC_POLICY_BASE
#define TLOC_POLICY_BASE

namespace tloc { namespace core { namespace policies {

  template <typename T_Derived>
  class Base
  {
  public:
    typedef T_Derived             derived_type;
    typedef Base<derived_type>    this_type;

    T_Derived* This()
    {
      return static_cast<derived_type*>(this);
    }
  };

};};};

#endif