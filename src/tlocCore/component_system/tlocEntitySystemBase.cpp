#include "tlocEntitySystemBase.h"

#include <tlocCore/data_structures/tlocVariadic.inl.h>
#include <tlocCore/component_system/tlocEntity.inl.h>

namespace tloc { namespace core { namespace component_system {

  enum
  {
    k_systemInitialized = 0,
    k_count
  };

  const tl_int EntitySystemBase::s_flagCount = k_count;

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
    m_flags.Mark(k_systemInitialized);

    if (Pre_Initialize() == ErrorSuccess)
    {
      TLOC_ASSERT_NOT_NULL(m_entityMgr);
      if (DoInitialize(m_entityMgr.get(), m_activeEntities) == ErrorSuccess)
      {
        return Post_Initialize();
      }
    }

    return ErrorFailure;
  }

  void EntitySystemBase::ProcessActiveEntities(f64 a_deltaT)
  {
    TLOC_ASSERT(m_flags.IsMarked(k_systemInitialized),
      "Did you forget to call Initialize()?");

    if (CheckProcessing())
    {
      TLOC_ASSERT_NOT_NULL(m_entityMgr);
      Pre_ProcessActiveEntities(a_deltaT);
      DoProcessActiveEntities(m_entityMgr.get(), m_activeEntities, a_deltaT);
      Post_ProcessActiveEntities(a_deltaT);
    }
  }

  error_type EntitySystemBase::Shutdown()
  {
    if (Pre_Shutdown() == ErrorSuccess)
    {
      TLOC_ASSERT_NOT_NULL(m_entityMgr);
      if (DoShutdown(m_entityMgr.get(), m_activeEntities) == ErrorSuccess)
      {
        return Post_Shutdown();
      }
    }

    return ErrorFailure;
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
              OnComponentInsert(entEvent);
              m_activeEntities.push_back(ent);
            }
          }
          else
          {
            entity_ptr_array::iterator itr = find_all(m_activeEntities, ent);
            if (itr != m_activeEntities.end())
            {
              OnComponentRemove(entEvent);
              m_activeEntities.erase(itr);
            }
          }
        }
        break;
      }
    case entity_events::disable_component:
    case entity_events::enable_component:
      {
        const EntityComponentEvent& entEvent = a_event.GetAs<EntityComponentEvent>();
        Component* comp = entEvent.GetComponent();

        for (component_type_array::iterator itr = m_typeFlags.begin(),
             itrEnd = m_typeFlags.end(); itr != itrEnd; ++itr)
        {
          if (comp->GetType() == *itr)
          {
            if (type == entity_events::disable_component)
            { OnComponentDisable(entEvent); }
            else
            { OnComponentEnable(entEvent); }
          }
        }
        break;
      }
    }

    return false;
  }

};};};