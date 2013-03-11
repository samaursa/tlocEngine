#include "tlocEntitySystemBase.h"

#include <tlocCore/data_structures/tlocVariadic.inl>
#include <tlocCore/component_system/tlocEntity.inl>

namespace tloc { namespace core { namespace component_system {

  //////////////////////////////////////////////////////////////////////////
  // typedefs]

  typedef EntitySystemBase::error_type      error_type;

  EntitySystemBase::~EntitySystemBase()
  {
    m_eventMgr->RemoveListener(this, entity_events::insert_component);
    m_eventMgr->RemoveListener(this, entity_events::remove_component);
  }

  error_type EntitySystemBase::Initialize()
  {
    if (Pre_Initialize() == ErrorSuccess())
    {
      if (DoInitialize(m_entityMgr.get(), m_activeEntities) == ErrorSuccess())
      {
        return Post_Initialize();
      }
    }

    return ErrorFailure();
  }

  void EntitySystemBase::ProcessActiveEntities()
  {
    if (CheckProcessing())
    {
      Pre_ProcessActiveEntities();
      DoProcessActiveEntities(m_entityMgr.get(), m_activeEntities);
      Post_ProcessActiveEntities();
    }
  }

  error_type EntitySystemBase::Shutdown()
  {
    if (Pre_Shutdown() == ErrorSuccess())
    {
      if (DoShutdown(m_entityMgr.get(), m_activeEntities) == ErrorSuccess())
      {
        return Post_Shutdown();
      }
    }

    return ErrorFailure();
  }

  bool EntitySystemBase::OnEvent(const EventBase& a_event)
  {
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
            entity_ptr_array::iterator entItr = core::find_all(m_activeEntities, ent);
            if (entItr == m_activeEntities.end())
            {
              m_activeEntities.push_back(ent);
            }
          }
          else
          {
            entity_ptr_array::iterator itr = find_all(m_activeEntities, ent);
            if (itr != m_activeEntities.end())
            {
              m_activeEntities.erase(itr);
            }
          }
        }
      }
    }

    return false;
  }

};};};