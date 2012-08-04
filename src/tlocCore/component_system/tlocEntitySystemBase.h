#ifndef TLOC_ENTITY_SYSTEM_BASE_H
#define TLOC_ENTITY_SYSTEM_BASE_H

#include <tlocCore/component_system/tlocEvent.h>
#include <tlocCore/component_system/tlocEntityEvent.h>
#include <tlocCore/component_system/tlocEntityManager.h>

#include <tlocCore/containers/tlocContainers.h>

namespace tloc { namespace core { namespace component_system {

  class EntitySystemBase : public EventListener
  {
    typedef EventBase::event_type       event_type;
    typedef components::value_type      component_type;

    EntitySystemBase(EventManager* a_eventMgr, EntityManager* a_entityMgr,
                     component_type a_typeFlag);
    ~EntitySystemBase();

    ///-------------------------------------------------------------------------
    /// @brief
    /// Process the active entities. The entities are not processed if
    /// CheckProcessing returns 0.
    ///-------------------------------------------------------------------------
    void ProcessActiveEntities();

    ///-------------------------------------------------------------------------
    /// @brief Called by ProcessActiveEntities() for base classes
    ///-------------------------------------------------------------------------
    virtual void ProcessActiveEntities(EntityManager* a_mgr,
                                       const entity_array& a_entities) = 0;

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
    bool OnEvent(const EventBase& a_event);

  private:

    component_type    m_typeFlag;
    entity_array      m_activeEntities;

    EventManager*     m_eventMgr;
    EntityManager*    m_entityMgr;

  };

};};};

#endif