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
      friend class SystemsProcessor;

    public:
      SystemInfo();

      TLOC_DECL_AND_DEF_GETTER(processing_system_ptr, GetSystem, m_system);
      TLOC_DECL_AND_DEF_GETTER(time_type, GetUpdateDeltaT, m_updateDeltaT);
      TLOC_DECL_AND_DEF_GETTER(time_type, GetIsUpdatedSinceLastFrame, 
                               m_updatedSinceLastFrame);

      TLOC_DECL_AND_DEF_SETTER(time_type, SetUpdateDeltaT, m_updateDeltaT);

    private:
      processing_system_ptr             m_system;
      time_type                         m_updateDeltaT;
      time_type                         m_accumulatedTime;
      bool                              m_updatedSinceLastFrame;
    };

  public:
    typedef core_conts::Array<SystemInfo>             sys_info_cont;
    typedef sys_info_cont::iterator                   sys_info_iterator;
    typedef sys_info_cont::const_iterator             const_sys_info_iterator;

  public:
    SystemsProcessor(BufferArg a_debugName = "SystemsProcessor");

    this_type&  Add(processing_system_ptr a_system, 
                    time_type a_updateDeltaT = 1.0/60.0);

    void        Initialize();
    void        Process(time_type a_deltaT = 1.0/60.0);

  private:
    sys_info_cont  m_systemsToProcess;

  public:
    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_systems, m_systemsToProcess);
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(SystemsProcessor, systems_processor);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(SystemsProcessor, systems_processor);

  // -----------------------------------------------------------------------

  namespace algos { namespace systems_processor {

    struct use_system_info
    {
      typedef SystemsProcessor::processing_system_ptr     processing_system_ptr;
      typedef processing_system_ptr::value_type           value_type;

      value_type&
        operator()(SystemsProcessor::SystemInfo& a) const 
      { return *a.GetSystem(); }
    };

    typedef entity_system::Initialize_T<use_system_info>     Initialize_FromSystemInfo;
    typedef entity_system::Process_T<use_system_info>        Process_FromSystemInfo;

    namespace compare {

      TLOC_DECL_ALGO_WITH_CTOR_UNARY(System_T, const_entity_processing_system_vptr, const);
      TLOC_DEFINE_ALGO_WITH_CTOR_UNARY(System_T, const)
      { return extract()(a).GetSystem() == m_value; }

      typedef System_T<use_reference>             System;
      typedef System_T<use_pointee>               System_Deref;
    }

  };};

  // -----------------------------------------------------------------------

  namespace f_systems_processor {

    // -----------------------------------------------------------------------

    typedef SystemsProcessor::sys_info_iterator         requested_itr;
    typedef SystemsProcessor::sys_info_iterator         end_itr;
    typedef SystemsProcessor::const_sys_info_iterator   const_requested_itr;
    typedef SystemsProcessor::const_sys_info_iterator   const_end_itr;

    // -----------------------------------------------------------------------

    core::Pair<requested_itr, end_itr>
      GetSystemInfo(SystemsProcessor& a_sysProcessor,
                    entity_processing_system_vptr a_system);

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    core::Pair<const_requested_itr, const_end_itr>
      GetSystemInfo(const SystemsProcessor& a_sysProcessor,
                    const_entity_processing_system_vptr a_system);

  }

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::core_cs::SystemsProcessor);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::core_cs::SystemsProcessor);
TLOC_EXTERN_TEMPLATE_ARRAY(tloc::core_cs::SystemsProcessor::processing_system_ptr);

#endif