#ifndef _TLOC_CORE_ASSERT_CUSTOM_BREAK_H_
#define _TLOC_CORE_ASSERT_CUSTOM_BREAK_H_

namespace tloc { namespace core { namespace assert {
  
  // ///////////////////////////////////////////////////////////////////////
  // destructor decoration to allow 'throw' from destructor in C++11
  // this is used ONLY for testing
  //
  // Note that in C++11 destructors are noexcept() by default which is
  // problematic when we want to test our assertions. For this reason the
  // following macro is provided (which is not used in C++03 as it does not
  // have a noexcept() decoration)
  
#if !defined TLOC_RELEASE && !defined TLOC_CXX03 && !defined TLOC_COMPILER_VISUAL_CPP
#define TLOC_DTOR_ASSERT noexcept(false)
#else
#define TLOC_DTOR_ASSERT
#endif

  // ///////////////////////////////////////////////////////////////////////
  // CustomBreak
  //
  // BAse class for all custom breaks

  class CustomBreak
  {
  public:
    virtual void Break() const = 0;
  };

  // -----------------------------------------------------------------------
  // methods for controlling assertions

  void                SetAssertCustomBreak(const CustomBreak* a_break);
  void                SetAssertDefaultBreak();
  const CustomBreak*  GetCustomBreak();

  bool                IsDefaultBreak();
  
};};};

#endif