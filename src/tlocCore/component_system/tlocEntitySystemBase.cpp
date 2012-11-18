#include "tlocEntitySystemBase.h"

#include <tlocCore/data_structures/tlocVariadic.inl>
#include <tlocCore/component_system/tlocEntity.inl>

namespace tloc { namespace core { namespace component_system {

  EntitySystemBase::~EntitySystemBase()
  {
    m_eventMgr->RemoveListener(this, entity_events::insert_component);
    m_eventMgr->RemoveListener(this, entity_events::remove_component);
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
    Pre_OnEvent(a_event);

    event_value_type type = a_event.GetType();

    switch(type)
    {
    case entity_events::insert_component:
    case entity_events::remove_component:
      {
        const EntityComponentEvent& entEvent = a_event.GetAs<EntityComponentEvent>();
        Entity* ent = entEvent.GetEntity();

        for (component_type_array::iterator itr = m_typeFlags.begin(),
             itrEnd = m_typeFlags.end(); itr != itrEnd; ++itr)
        {
          if (ent->HasComponent(*itr) )
          {

            entity_array::iterator entItr = core::find_all(m_activeEntities, ent);
            if (entItr == m_activeEntities.end())
            {
              m_activeEntities.push_back(ent);
            }
          }
          else
          {
            entity_array::iterator itr = find_all(m_activeEntities, ent);
            if (itr != m_activeEntities.end())
            {
              m_activeEntities.erase(itr);
            }
          }
        }
      }
    }

    Post_OnEvent(a_event);
    return false;
  }

};};};