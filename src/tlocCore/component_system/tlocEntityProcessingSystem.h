#ifndef TLOC_ENTITY_PROCESSING_SYSTEM_H
#define TLOC_ENTITY_PROCESSING_SYSTEM_H

#include <tlocCore/tlocCoreBase.h>

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
    { TLOC_ASSERT(false, "No sorting function defined for this system"); }

  protected:
    template <size_type T_VarSize>
    EntityProcessingSystem(event_manager_ptr a_eventMgr,
                           entity_manager_ptr a_entityMgr,
                           const data_structs::Variadic
                              <component_type, T_VarSize>& a_typeFlags);

  protected: // Initialization
    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(entity_vptr a_ent) = 0;
    virtual error_type Post_Initialize();

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

  private:
    virtual void DoProcessActiveEntities (const entity_ptr_array& a_entities,
                                          f64 a_deltaT);

    virtual error_type DoInitialize(const entity_ptr_array& a_entities);

    virtual error_type DoShutdown(const entity_ptr_array& a_entities);
  };

  //------------------------------------------------------------------------
  // Template definitions

    template <tl_size T_VarSize>
    EntityProcessingSystem::
      EntityProcessingSystem (event_manager_ptr a_eventMgr,
                              entity_manager_ptr a_entityMgr,
                              const data_structs::
                              Variadic<component_type, T_VarSize>& a_typeFlags)
      : EntitySystemBase(a_eventMgr, a_entityMgr, a_typeFlags)
    { }

};};};

#endif