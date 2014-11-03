#include "tlocSystemsProcessor.h"

namespace tloc { namespace core { namespace component_system {

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
    m_systemsToProcess.push_back(a_system);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SystemsProcessor::
    Initialize()
  { core::for_each_all(m_systemsToProcess, algos::entity_system::Initialize_Deref()); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SystemsProcessor::
    Process(time_type a_deltaT)
  { core::for_each_all(m_systemsToProcess, algos::entity_system::Process_Deref(a_deltaT)); }

};};};

using namespace tloc::core_cs;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/containers/tlocArray.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(SystemsProcessor);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(SystemsProcessor);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(SystemsProcessor::processing_system_ptr);