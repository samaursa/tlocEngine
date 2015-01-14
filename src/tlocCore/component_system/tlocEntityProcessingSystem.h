#ifndef TLOC_ENTITY_PROCESSING_SYSTEM_H
#define TLOC_ENTITY_PROCESSING_SYSTEM_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/tlocAssert.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocEntitySystemBase.h>

namespace tloc { namespace core { namespace component_system {

  class EntityProcessingSystem
    : public EntitySystemBase
  {
  public:
    typedef EntitySystemBase                    base_type;

  public:
    friend class EntitySystemBase;

    virtual void SortEntities()
    { TLOC_ASSERT_FALSE("No sorting function defined for this system"); }

  protected:
    EntityProcessingSystem(event_manager_ptr a_eventMgr,
                           entity_manager_ptr a_entityMgr,
                           register_type a_compsToRegister, 
                           BufferArg a_debugName);

  protected: // Initialization
    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(entity_vptr a_ent) = 0;
    virtual error_type Post_Initialize();

  protected: // Re-Initialization
    virtual error_type Pre_ReInitialize();
    virtual error_type ReInitializeEntity(entity_vptr a_ent);
    virtual error_type Post_ReInitialize();

  protected: // Re-Activate
    virtual error_type Pre_Reactivate();
    virtual error_type ReactivateEntity(entity_vptr a_ent);
    virtual error_type Post_Reactivate();

  protected: // De-Activate
    virtual error_type Pre_Deactivate();
    virtual error_type DeactivateEntity(entity_vptr a_ent);
    virtual error_type Post_Deactivate();

  protected: // Processing
    virtual bool CheckProcessing();
    virtual void Pre_ProcessActiveEntities(f64 a_deltaT);
    virtual void ProcessEntity(entity_vptr a_ent,
                               f64 a_deltaT) = 0;
    virtual void Post_ProcessActiveEntities(f64 a_deltaT);

  protected: // Shutdown
    virtual error_type Pre_Shutdown();
    virtual error_type ShutdownEntity(entity_vptr a_ent) = 0;
    virtual error_type Post_Shutdown();

  protected: // component insert/remove
    virtual void OnComponentInsert(const entity_comp_event_type&);
    virtual void OnComponentRemove(const entity_comp_event_type&);
    
    virtual void OnComponentDisable(const entity_comp_event_type&);
    virtual void OnComponentEnable(const entity_comp_event_type&);

    virtual void OnEntityActivate(const entity_comp_event_type&);
    virtual void OnEntityDeactivate(const entity_comp_event_type&);

  private:
    virtual void DoProcessActiveEntities (const entity_count_cont& a_entities,
                                          f64 a_deltaT);

    virtual error_type DoInitialize(const entity_count_cont& a_entities);
    virtual error_type DoReInitialize(const entity_count_cont& a_entities);
    virtual error_type DoShutdown(const entity_count_cont& a_entities);

  private:
    core_cs::entity_ptr_array     m_entsToReInit;
    core_cs::entity_ptr_array     m_entsDeactivated;
    core_cs::entity_ptr_array     m_entsActivated;
    core_cs::entity_ptr_array     m_entsToShutdown;

  protected:
    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_entsToReInit, m_entsToReInit);
    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_entsToDeactivate, m_entsDeactivated);
    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_entsToActivate, m_entsActivated);
    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_entsToShutdown, m_entsToShutdown);
  };
  
  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_VIRTUAL_PTR(EntityProcessingSystem, entity_processing_system);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_VIRTUAL_PTR(tloc::core_cs::EntityProcessingSystem);

#endif