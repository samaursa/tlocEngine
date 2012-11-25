#ifndef TLOC_ENTITY_SYSTEM_BASE_H
#define TLOC_ENTITY_SYSTEM_BASE_H

#include <tlocCore/component_system/tlocEvent.h>
#include <tlocCore/component_system/tlocEntityEvent.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/error/tlocError.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/data_structures/tlocVariadic.h>

namespace tloc { namespace core { namespace component_system {

  class EntitySystemBase : public EventListener
  {
  public:

    // The maximum number of components a system is allowed to register for
    // events listening
    enum { max_component_types = 4 };

    typedef components::value_type                component_type;
    typedef tl_size                               size_type;
    typedef core::error::Error                    error_type;

    typedef core::component_system::EventManager        event_manager;
    typedef core::component_system::EventBase           event_type;
    typedef EventBase::event_type                       event_value_type;
    typedef core::component_system::EntityManager       entity_manager;
    typedef core::component_system::Entity              entity_type;

    typedef tl_array_fixed
      <component_type, max_component_types>::type component_type_array;

  public:

    ///-------------------------------------------------------------------------
    /// @brief Gives derived classes opportunity to perform initialization.
    ///-------------------------------------------------------------------------
    error_type Initialize();

    ///-------------------------------------------------------------------------
    /// @brief Cleans up anything done in Initialize()
    ///-------------------------------------------------------------------------
    error_type Shutdown();

    ///-------------------------------------------------------------------------
    /// @brief
    /// Process the active entities. The entities are not processed if
    /// CheckProcessing returns 0.
    ///-------------------------------------------------------------------------
    void ProcessActiveEntities();

  protected:

    template <tl_size T_VarSize>
    EntitySystemBase(event_manager* a_eventMgr, entity_manager* a_entityMgr,
                     const Variadic<component_type, T_VarSize>& a_typeFlags);

    ~EntitySystemBase();

    ///-------------------------------------------------------------------------
    /// @brief Called before DoInitializeEntity is called
    ///-------------------------------------------------------------------------
    virtual error_type Pre_Initialize() = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called by Initialize()
    ///-------------------------------------------------------------------------
    virtual error_type DoInitialize(entity_manager* a_mgr,
                                    const entity_array& a_entities) = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called after DoInitializeEntity is called
    ///-------------------------------------------------------------------------
    virtual error_type Post_Initialize() = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called before DoInitializeEntity is called
    ///-------------------------------------------------------------------------
    virtual error_type Pre_Shutdown() = 0;


    ///-------------------------------------------------------------------------
    /// @brief Called by Initialize()
    ///-------------------------------------------------------------------------
    virtual error_type DoShutdown(entity_manager* a_mgr,
                                  const entity_array& a_entities) = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called after DoInitializeEntity is called
    ///-------------------------------------------------------------------------
    virtual error_type Post_Shutdown() = 0;

    ///-------------------------------------------------------------------------
    /// @brief
    /// Called by ProcessActiveEntities() before deciding whether to
    /// process entities.
    ///
    /// @return true if we want to process entities
    ///-------------------------------------------------------------------------
    virtual bool CheckProcessing() = 0;


    ///-------------------------------------------------------------------------
    /// @brief Called before processing entities
    ///-------------------------------------------------------------------------
    virtual void Pre_ProcessActiveEntities() = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called by ProcessActiveEntities() for base classes
    ///-------------------------------------------------------------------------
    virtual void DoProcessActiveEntities(entity_manager* a_mgr,
                                         const entity_array& a_entities) = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called after processing entities
    ///-------------------------------------------------------------------------
    virtual void Post_ProcessActiveEntities() = 0;

    ///-------------------------------------------------------------------------
    /// @brief Called by EventManager (we are/should-be a registered listener)
    ///
    /// @param  a_event The event.
    ///
    /// @return true if the message was processed, false if it was ignored.
    ///-------------------------------------------------------------------------
    bool OnEvent(const event_type& a_event);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(entity_array, DoGetActiveEntities,
                                          m_activeEntities);

  protected:
    component_type_array  m_typeFlags;
    entity_array          m_activeEntities;

    EventManager*     m_eventMgr;
    EntityManager*    m_entityMgr;

  };

  //------------------------------------------------------------------------
  // Template definition

  template <tl_size T_VarSize>
  EntitySystemBase::
    EntitySystemBase(EventManager* a_eventMgr, EntityManager* a_entityMgr,
                     const Variadic<component_type, T_VarSize>& a_typeFlags)
    : m_eventMgr(a_eventMgr)
    , m_entityMgr(a_entityMgr)
  {
    TLOC_ASSERT_NOT_NULL(a_eventMgr); TLOC_ASSERT_NOT_NULL(a_entityMgr);
    TLOC_STATIC_ASSERT(T_VarSize <= max_component_types,
                       Exceeded_max_components_supported);

    for (tl_uint i = 0; i < a_typeFlags.GetSize(); ++i)
    {
      m_typeFlags.push_back(a_typeFlags[i]);
    }

    m_eventMgr->AddListener(this, entity_events::insert_component);
    m_eventMgr->AddListener(this, entity_events::remove_component);
  }

};};};

#endif