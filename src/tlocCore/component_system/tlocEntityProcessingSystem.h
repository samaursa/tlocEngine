#ifndef TLOC_ENTITY_PROCESSING_SYSTEM_H
#define TLOC_ENTITY_PROCESSING_SYSTEM_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/tlocAssert.h>
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
                           register_type a_compsToRegister);

  protected: // Initialization
    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(entity_vptr a_ent) = 0;
    virtual error_type Post_Initialize();

  protected: // Re-Initialization
    virtual error_type Pre_ReInitialize();
    virtual error_type ReInitializeEntity(entity_vptr a_ent);
    virtual error_type Post_ReInitialize();

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
    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&);
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&);

  private:
    virtual void DoProcessActiveEntities (const entity_count_cont& a_entities,
                                          f64 a_deltaT);

    virtual error_type DoInitialize(const entity_count_cont& a_entities);

    virtual error_type DoShutdown(const entity_count_cont& a_entities);

  private:
    core_cs::entity_ptr_array     m_entsToReInit;
    core_cs::entity_ptr_array     m_entsToShutdown;
  };

};};};

#endif