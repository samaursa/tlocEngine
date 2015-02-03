#include "tlocECS.h"

namespace tloc { namespace core { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // ECS

  ECS::
   ECS(BufferArg a_debugName)
   : core_bclass::DebugName(a_debugName)
   , m_entMgr(MakeArgs(m_eventMgr.get()))
   , m_autoRecycleUnusedComponents(true)
   , m_autoRecycleDeltaT(0.5)
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
  { 
    m_entMgr->Update();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ECS::
    Process(time_type a_deltaT)
  { 
    m_sysProcessor->Process(a_deltaT); 

    m_autoRecycleTimer += a_deltaT;
    if (m_autoRecycleTimer > m_autoRecycleDeltaT && m_autoRecycleUnusedComponents)
    {
      RecycleAllUnusedComponents();
      m_autoRecycleTimer = 0.0;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ECS::
    RecycleAllUnusedComponents()
  { m_compPoolMgr->RecycleAllUnused(); }

};};};

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::core_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(ECS);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(ECS);