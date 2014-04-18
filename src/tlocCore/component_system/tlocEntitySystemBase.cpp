#include "tlocEntitySystemBase.h"

#include <tlocCore/tlocAssert.h>
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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  EntitySystemBase::
    ~EntitySystemBase()
  {
    m_eventMgr->RemoveListener(this, entity_events::insert_component);
    m_eventMgr->RemoveListener(this, entity_events::remove_component);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    EntitySystemBase::
    Initialize()
  {
    m_flags.Mark(k_systemInitialized);

    if (Pre_Initialize() == ErrorSuccess)
    {
      TLOC_ASSERT_NOT_NULL(m_entityMgr);
      if (DoInitialize(m_activeEntities) == ErrorSuccess)
      {
        return Post_Initialize();
      }
    }

    return ErrorFailure;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    EntitySystemBase::
    ProcessActiveEntities(f64 a_deltaT)
  {
    TLOC_ASSERT(m_flags.IsMarked(k_systemInitialized),
      "Did you forget to call Initialize()?");

    if (CheckProcessing())
    {
      TLOC_ASSERT_NOT_NULL(m_entityMgr);
      Pre_ProcessActiveEntities(a_deltaT);
      DoProcessActiveEntities(m_activeEntities, a_deltaT);
      Post_ProcessActiveEntities(a_deltaT);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    EntitySystemBase::
    Shutdown()
  {
    if (Pre_Shutdown() == ErrorSuccess)
    {
      TLOC_ASSERT_NOT_NULL(m_entityMgr);
      if (DoShutdown(m_activeEntities) == ErrorSuccess)
      {
        return Post_Shutdown();
      }
    }

    return ErrorFailure;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    EntitySystemBase::
    OnEvent(const EventBase& a_event)
  {
    event_value_type type = a_event.GetType();

    switch(type)
    {
    case entity_events::insert_component:
      {
        const EntityComponentEvent& entEvent = a_event.GetAs<EntityComponentEvent>();
        entity_vptr ent = entEvent.GetEntity();

        for (component_type_array::iterator itr = m_typeFlags.begin(),
             itrEnd = m_typeFlags.end(); itr != itrEnd; ++itr)
        {
          if (ent->HasComponent(*itr) )
          {
            entity_count_cont::iterator entItr = 
              core::find_if_all(m_activeEntities, 
              algos::compare::pair::MakeFirst(ent));

            if (entItr == m_activeEntities.end())
            {
              OnComponentInsert(entEvent);
              m_activeEntities.push_back(MakePair(ent, 1));
            }
            else
            {
              entItr->second++;
            }
          }
        }
        break;
      }
    case entity_events::remove_component:
      {
        const EntityComponentEvent& entEvent = a_event.GetAs<EntityComponentEvent>();
        entity_vptr ent = entEvent.GetEntity();

        for (component_type_array::iterator itr = m_typeFlags.begin(),
             itrEnd = m_typeFlags.end(); itr != itrEnd; ++itr)
        {
          if (ent->HasComponent(*itr) )
          {
            entity_count_cont::iterator entItr = 
              core::find_if_all(m_activeEntities, 
              algos::compare::pair::MakeFirst(ent));

            if (entItr != m_activeEntities.end())
            {
              OnComponentRemove(entEvent);
              if (entItr->second == 1)
              {
                m_activeEntities.erase(entItr);
              }
              else
              {
                entItr->second--;
              }
            }
          }
        }
        break;
      }

    case entity_events::disable_component:
    case entity_events::enable_component:
      {
        const EntityComponentEvent& entEvent = a_event.GetAs<EntityComponentEvent>();
        component_sptr comp = entEvent.GetComponent();

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