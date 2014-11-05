#ifndef _TLOC_CORE_COMPONENT_SYSTEM_SYSTEMS_PROCESSOR_H_
#define _TLOC_CORE_COMPONENT_SYSTEM_SYSTEMS_PROCESSOR_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

namespace tloc { namespace core { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // SystemsProcessor

  class SystemsProcessor
    : public core_bclass::DebugName
  {
  public:
    typedef SystemsProcessor                          this_type;
    typedef entity_processing_system_vptr             processing_system_ptr;
    typedef core_conts::Array<processing_system_ptr>  processing_system_cont;
    typedef processing_system_cont::iterator          processing_system_iterator;
    typedef processing_system_cont::const_iterator    const_processing_system_iterator;
    typedef EntityProcessingSystem::error_type        error_type;
    typedef EntitySystemBase::time_type               time_type;

  private:
    processing_system_cont  m_systemsToProcess;

  public:
    SystemsProcessor(BufferArg a_debugName = "SystemsProcessor");

    this_type&  Add(processing_system_ptr a_system);

    void        Initialize();
    void        Process(time_type a_deltaT);

  public:

    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(systems, m_systemsToProcess);
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(SystemsProcessor, systems_processor);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(SystemsProcessor, systems_processor);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::core_cs::SystemsProcessor);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::core_cs::SystemsProcessor);
TLOC_EXTERN_TEMPLATE_ARRAY(tloc::core_cs::SystemsProcessor::processing_system_ptr);

#endif