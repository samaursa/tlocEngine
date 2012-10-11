#ifndef TLOC_ENTITY_PROCESSING_SYSTEM_H
#define TLOC_ENTITY_PROCESSING_SYSTEM_H

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocEntitySystemBase.h>

namespace tloc { namespace core { namespace component_system {

  class EntityProcessingSystem : EntitySystemBase
  {
  public:

    typedef EntitySystemBase                    base_type;
    using base_type::component_type;
    using base_type::component_type_array;
    using base_type::size_type;
    using base_type::error_type;

    using base_type::event_manager;
    using base_type::entity_manager;
    using base_type::entity_type;
    using base_type::event_type;
    using base_type::event_value_type;

    template <size_type T_VarSize>
    EntityProcessingSystem(event_manager* a_eventMgr,
                           entity_manager* a_entityMgr,
                           const Variadic<component_type, T_VarSize>& a_typeFlags);

    virtual ~EntityProcessingSystem();

    virtual bool CheckProcessing();
    virtual void Pre_ProcessActiveEntities();
    virtual void ProcessEntity(entity_manager* a_mgr, entity_type* a_ent) = 0;
    virtual void ProcessActiveEntities (entity_manager* a_mgr,
                                        const entity_array& a_entities);
    virtual void Post_ProcessingActiveEntities();
  };

  //------------------------------------------------------------------------
  // Template definitions

    template <tl_size T_VarSize>
    EntityProcessingSystem::EntityProcessingSystem
      (event_manager* a_eventMgr, entity_manager* a_entityMgr,
       const Variadic<component_type, T_VarSize>& a_typeFlags)
       : EntitySystemBase(a_eventMgr, a_entityMgr, a_typeFlags)
    {
    }

};};};

#endif