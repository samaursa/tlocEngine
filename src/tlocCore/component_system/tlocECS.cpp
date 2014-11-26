#include "tlocECS.h"

namespace tloc { namespace core { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // ECS

  ECS::
   ECS(BufferArg a_debugName)
   : core_bclass::DebugName(a_debugName)
   , m_entMgr(MakeArgs(m_eventMgr.get()))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

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
    Update()
  { m_entMgr->Update(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ECS::
    Process(time_type a_deltaT)
  { 
    m_sysProcessor->Process(a_deltaT); 
  }

};};};