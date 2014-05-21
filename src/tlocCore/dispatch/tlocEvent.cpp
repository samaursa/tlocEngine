#include "tlocEvent.h"

namespace tloc { namespace core { namespace dispatch {

  // ///////////////////////////////////////////////////////////////////////
  // CallbackReturn

  Event::
    Event(veto a_veto)
    : m_veto(a_veto)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Event::this_type&
    Event::
    Veto()
  { m_veto = true; return *this; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Event::this_type&
    Event::
    Continue()
  { m_veto = false; return *this; }

  // -----------------------------------------------------------------------
  // helper functions

  namespace f_event {

    Event
      Veto()
    { return Event(Event::veto(true)); }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    Event
      Continue()
    { return Event(Event::veto(false)); }

  };

};};};