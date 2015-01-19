#include "tlocSystemsProcessor.h"

namespace tloc { namespace core { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // SystemInfo

  SystemsProcessor::SystemInfo::
    SystemInfo()
    : m_updateDeltaT(0.0)
    , m_accumulatedTime(0.0)
    , m_updatedSinceLastFrame(false)
  {
  }

  // ///////////////////////////////////////////////////////////////////////
  // SystemsProcessor

  SystemsProcessor::
    SystemsProcessor(BufferArg a_debugName)
    : core_bclass::DebugName(a_debugName)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SystemsProcessor::this_type&
    SystemsProcessor::
    Add(processing_system_ptr a_system, time_type a_updateDeltaT)
  {
    SystemInfo si;
    si.m_system = a_system;
    si.m_updateDeltaT = a_updateDeltaT;

    m_systemsToProcess.push_back(si);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SystemsProcessor::
    Initialize()
  { 
    core::for_each_all(m_systemsToProcess, 
                       algos::system_processor::Initialize_FromSystemInfo()); 
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SystemsProcessor::
    Process(time_type a_deltaT)
  { 
    for (auto itr = m_systemsToProcess.begin(), itrEnd = m_systemsToProcess.end();
         itr != itrEnd; ++itr)
    {
      auto& si = *itr;
      si.m_accumulatedTime += a_deltaT;
      si.m_updatedSinceLastFrame = false;

      while (si.m_updateDeltaT <= si.m_accumulatedTime)
      {
        si.m_system->ProcessActiveEntities(si.m_updateDeltaT);
        si.m_accumulatedTime -= si.m_updateDeltaT;
        si.m_updatedSinceLastFrame = true;
      }
    }
  }

};};};

using namespace tloc::core_cs;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/containers/tlocArray.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(SystemsProcessor);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(SystemsProcessor);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(SystemsProcessor::processing_system_ptr);