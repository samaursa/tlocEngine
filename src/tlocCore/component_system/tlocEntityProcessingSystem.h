#ifndef TLOC_ENTITY_PROCESSING_SYSTEM_H
#define TLOC_ENTITY_PROCESSING_SYSTEM_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocEntitySystemBase.h>

namespace tloc { namespace core { namespace component_system {

  class EntityProcessingSystem : public EntitySystemBase
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

  public:
    friend class EntitySystemBase;

  protected:
    template <size_type T_VarSize>
    EntityProcessingSystem(event_manager* a_eventMgr,
                           entity_manager* a_entityMgr,
                           const data_structs::Variadic
                              <component_type, T_VarSize>& a_typeFlags);

    virtual ~EntityProcessingSystem();

  protected: // Initialization
    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(entity_manager* a_mgr,
                                        entity_type* a_ent) = 0;
    virtual error_type Post_Initialize();

  protected: // Processing
    virtual bool CheckProcessing();
    virtual void Pre_ProcessActiveEntities();
    virtual void ProcessEntity(entity_manager* a_mgr,
                               entity_type* a_ent) = 0;
    virtual void Post_ProcessActiveEntities();

  protected: // Shutdown
    virtual error_type Pre_Shutdown();
    virtual error_type ShutdownEntity(entity_manager* a_mgr,
                                      entity_type* a_ent) = 0;
    virtual error_type Post_Shutdown();

  private:
    virtual void DoProcessActiveEntities (entity_manager* a_mgr,
                                          const entity_ptr_array& a_entities);

    virtual error_type DoInitialize(entity_manager* a_mgr,
                                    const entity_ptr_array& a_entities);

    virtual error_type DoShutdown(entity_manager* a_mgr,
                                  const entity_ptr_array& a_entities);
  };

  //------------------------------------------------------------------------
  // Template definitions

    template <tl_size T_VarSize>
    EntityProcessingSystem::EntityProcessingSystem
      (event_manager* a_eventMgr, entity_manager* a_entityMgr,
       const data_structs::Variadic<component_type, T_VarSize>& a_typeFlags)
       : EntitySystemBase(a_eventMgr, a_entityMgr, a_typeFlags)
    {
    }

};};};

#endif