#ifndef _TLOC_CORE_DISPATCH_CALLBACK_RETURN_H_
#define _TLOC_CORE_DISPATCH_CALLBACK_RETURN_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace core { namespace dispatch {

  class CallbackReturn
  {
  public:
    typedef CallbackReturn                          this_type;

  public:

    CallbackReturn();

    this_type&  Veto();
    this_type&  Continue();

    TLOC_DECL_AND_DEF_GETTER(bool, IsVeto, m_veto);
    TLOC_DECL_AND_DEF_GETTER(bool, IsContinue, m_veto == false);

  private:
    bool  m_veto;
  };

  TL_I CallbackReturn Veto();
  TL_I CallbackReturn Continue();

};};};

#endif