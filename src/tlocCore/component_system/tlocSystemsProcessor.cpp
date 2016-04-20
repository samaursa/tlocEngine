#include "tlocSystemsProcessor.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/time/tlocTime.h>
#include <tlocMath/tlocMath.h>

namespace tloc { namespace core { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // SystemInfo

  SystemsProcessor::SystemInfo::
    SystemInfo()
    : m_timeToInitialize(0.0)
    , m_timeToProcessLastFrame(0.0)
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
    Add(processing_system_ptr a_system)
  {
    SystemInfo si;
    si.m_system = a_system;

    m_systemsToProcess.push_back(si);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    SystemsProcessor::
    Initialize() -> time_type
  { 
    core_time::Timer t;
    auto totalTime = t.ElapsedSeconds();

    for (auto itr = m_systemsToProcess.begin(), itrEnd = m_systemsToProcess.end();
         itr != itrEnd; ++itr)
    {
      t.Reset();
      itr->GetSystem()->Initialize();
      const auto elapsed = t.ElapsedSeconds();

      itr->m_timeToInitialize = elapsed;
      totalTime += elapsed;
    }

    return totalTime;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    SystemsProcessor::
    Process(time_type a_deltaT) -> time_type
  { 
    core_time::Timer t;
    auto totalTime = time_type();

    for (auto itr = m_systemsToProcess.begin(), itrEnd = m_systemsToProcess.end();
         itr != itrEnd; ++itr)
    {
      auto& si = *itr;

      t.Reset();

      si.m_system->ProcessActiveEntities(a_deltaT);
      si.m_updatedSinceLastFrame = true;

      const auto elapsed = t.ElapsedSeconds();
      si.m_timeToProcessLastFrame = elapsed;
      totalTime += elapsed;
    }

    return totalTime;
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