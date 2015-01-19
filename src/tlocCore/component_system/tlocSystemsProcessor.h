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
    typedef EntityProcessingSystem::error_type        error_type;
    typedef EntitySystemBase::time_type               time_type;

  public:
    struct SystemInfo
    {
      SystemInfo();

      processing_system_ptr             m_system;
      time_type                         m_updateDeltaT;
      time_type                         m_accumulatedTime;
      bool                              m_updatedSinceLastFrame;
    };

  public:
    typedef core_conts::Array<SystemInfo>             processing_system_cont;
    typedef processing_system_cont::iterator          processing_system_iterator;
    typedef processing_system_cont::const_iterator    const_processing_system_iterator;

  public:
    SystemsProcessor(BufferArg a_debugName = "SystemsProcessor");

    this_type&  Add(processing_system_ptr a_system, 
                    time_type a_updateDeltaT = 1.0/60.0);

    void        Initialize();
    void        Process(time_type a_deltaT);

  private:
    processing_system_cont  m_systemsToProcess;

  public:
    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_systems, m_systemsToProcess);
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(SystemsProcessor, systems_processor);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(SystemsProcessor, systems_processor);

  // -----------------------------------------------------------------------

  namespace algos { namespace system_processor {

    struct use_system_info
    {
      typedef SystemsProcessor::processing_system_ptr     processing_system_ptr;
      typedef processing_system_ptr::value_type           value_type;

      value_type&
        operator()(SystemsProcessor::SystemInfo& a) const 
      { return *a.m_system; }
    };

    typedef entity_system::Initialize_T<use_system_info>     Initialize_FromSystemInfo;
    typedef entity_system::Process_T<use_system_info>        Process_FromSystemInfo;

    namespace compare {

      TLOC_DECL_ALGO_WITH_CTOR_UNARY(System_T, entity_processing_system_vptr, const);
      TLOC_DEFINE_ALGO_WITH_CTOR_UNARY(System_T, const)
      { return extract()(a).m_system == m_value; }

      typedef System_T<use_reference>             System;
      typedef System_T<use_pointee>               System_Deref;

      //struct System
      //{
      //  System(entity_processing_system_vptr a_sys)
      //    : m_value(a_sys)
      //  { }

      //  bool operator()(SystemsProcessor::SystemInfo& a_info) const
      //  {
      //    return m_value == a_info.m_system;
      //  }

      //  entity_processing_system_vptr m_value;
      //};
    }

  };};

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::core_cs::SystemsProcessor);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::core_cs::SystemsProcessor);
TLOC_EXTERN_TEMPLATE_ARRAY(tloc::core_cs::SystemsProcessor::processing_system_ptr);

#endif