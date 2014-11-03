#include "tlocECS.h"

namespace tloc { namespace core { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // ECS

  ECS::
    ~ECS()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ECS::
    Initialize()
  { m_sysProcessor->Initialize(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ECS::
    Process(time_type a_deltaT)
  { m_sysProcessor->Process(a_deltaT); }

};};};