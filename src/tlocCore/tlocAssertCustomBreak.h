#ifndef _TLOC_CORE_ASSERT_CUSTOM_BREAK_H_
#define _TLOC_CORE_ASSERT_CUSTOM_BREAK_H_

namespace tloc { namespace core { namespace assert {

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