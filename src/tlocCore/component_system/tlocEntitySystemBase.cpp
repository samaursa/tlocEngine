#include "tlocEntitySystemBase.h"

namespace tloc { namespace core { namespace component_system {

  EntitySystemBase::EntitySystemBase(EventManager* a_eventMgr,
                                     EntityManager* a_entityMgr,
                                     component_type a_typeFlag)
                                     : m_eventMgr(a_eventMgr)
                                     , m_entityMgr(a_entityMgr)
                                     , m_typeFlag(a_typeFlag)
  {
    TLOC_ASSERT_NOT_NULL(a_eventMgr); TLOC_ASSERT_NOT_NULL(a_entityMgr);

    m_eventMgr->AddListener(this, entity_event::insert_component);
    m_eventMgr->AddListener(this, entity_event::remove_component);
  }

  EntitySystemBase::~EntitySystemBase()
  {
    m_eventMgr->RemoveListener(this, entity_event::insert_component);
    m_eventMgr->RemoveListener(this, entity_event::remove_component);
  }

  void EntitySystemBase::ProcessActiveEntities()
  {
    if (CheckProcessing())
    {
      Pre_ProcessActiveEntities();
      ProcessActiveEntities(m_entityMgr, m_activeEntities);
      Post_ProcessActiveEntities();
    }
  }

  bool EntitySystemBase::OnEvent(const EventBase& a_event)
  {
    event_type type = a_event.GetType();

    switch(type)
    {
    case entity_event::insert_component:
    case entity_event::remove_component:
      {
        const EntityComponentEvent& entEvent = a_event.GetAs<EntityComponentEvent>();
        Entity* ent = entEvent.m_entity;

        if (ent->HasComponent(entEvent.m_type) )
        {
          m_activeEntities.push_back(ent);
        }
        else
        {
          entity_array::iterator itr = find(m_activeEntities, ent);
          if (itr != m_activeEntities.end())
          {
            m_activeEntities.erase(itr);
          }
        }

        return true;
      }
    }

    return false;
  }

};};};