#ifndef _TLOC_CORE_DISPATCH_EVENT_H_
#define _TLOC_CORE_DISPATCH_EVENT_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocStrongType.h>

namespace tloc { namespace core { namespace dispatch {

  class Event
  {
  public:
    typedef Event                          this_type;
    typedef core_t::StrongType_T<bool, 0>  veto;

  public:

    explicit Event(veto a_veto);

    this_type&  Veto();
    this_type&  Continue();

    TLOC_DECL_AND_DEF_GETTER(bool, IsVeto, m_veto);
    TLOC_DECL_AND_DEF_GETTER(bool, IsContinue, m_veto == false);

  private:
    bool  m_veto;
  };

  // -----------------------------------------------------------------------
  // helper functions

  namespace f_event {

    Event Veto();
    Event Continue();

  };

};};};

#endif