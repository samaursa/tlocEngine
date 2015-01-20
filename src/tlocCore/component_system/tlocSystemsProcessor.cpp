#include "tlocSystemsProcessor.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocMath/tlocMath.h>

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
                       algos::systems_processor::Initialize_FromSystemInfo()); 
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

      if (math::IsEqualToZero(si.m_updateDeltaT))
      { continue; }
      else
      {
        while (si.m_updateDeltaT <= si.m_accumulatedTime)
        {
          si.m_system->ProcessActiveEntities(si.m_updateDeltaT);
          si.m_accumulatedTime -= si.m_updateDeltaT;
          si.m_updatedSinceLastFrame = true;
        }
      }
    }
  }

  // -----------------------------------------------------------------------

  namespace f_systems_processor {

    core::Pair<requested_itr, end_itr>
      GetSystemInfo(SystemsProcessor& a_sysProcessor,
                    entity_processing_system_vptr a_system)
    {
      auto itr =  core::find_if(a_sysProcessor.begin_systems(), 
                                a_sysProcessor.end_systems(), 
                                algos::systems_processor::compare::System(a_system));
      return core::MakePair(itr, a_sysProcessor.end_systems());
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    core::Pair<const_requested_itr, const_end_itr>
      GetSystemInfo(const SystemsProcessor& a_sysProcessor, 
                    const_entity_processing_system_vptr a_system)
    {
      auto itr =  core::find_if(a_sysProcessor.begin_systems(), 
                                a_sysProcessor.end_systems(), 
                                algos::systems_processor::compare::System(a_system));
      return core::MakePair(itr, a_sysProcessor.end_systems());
    }

  };

};};};

using namespace tloc::core_cs;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/containers/tlocArray.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(SystemsProcessor);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(SystemsProcessor);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(SystemsProcessor::processing_system_ptr);