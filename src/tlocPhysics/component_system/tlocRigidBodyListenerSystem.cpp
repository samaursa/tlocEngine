#include "tlocRigidBodyListenerSystem.h"

#include <tlocCore/error/tlocError.h>
#include <tlocCore/containers/tlocArray.inl>
#include <tlocCore/component_system/tlocComponentMapper.h>

#include <tlocPhysics/component_system/tlocRigidbodyListenerComponent.h>
#include <tlocPhysics/component_system/tlocComponentType.h>
#include <tlocPhysics/box2d/tlocPhysicsManager.h>

TLOC_DEF_TYPE(tloc::physics::component_system::RigidBodyListenerSystem);

namespace tloc { namespace physics { namespace component_system {

  namespace contact
  {
    enum type
    {
      k_begin,
      k_end,

      k_count
    };
  };

  RigidBodyListenerSystem::RigidBodyListenerSystem(event_manager* a_eventMgr,
                                                   entity_manager* a_entityMgr,
                                                   physics_manager* a_physicsMgr)
    : base_type(a_eventMgr, a_entityMgr
    , core::Variadic<component_type, 1>(components::k_rigid_body_listener))
    , m_physicsMgr(a_physicsMgr)
  {
  }

  RigidBodyListenerSystem::error_type
    RigidBodyListenerSystem::Pre_Initialize()
  {
    m_physicsMgr->Register(this);
    m_allContactEvents.resize(contact::k_count);
    return ErrorSuccess();
  }

  RigidBodyListenerSystem::error_type
    RigidBodyListenerSystem::Post_Shutdown()
  {
    m_allContactEvents.clear();
    return ErrorSuccess();
  }

  RigidBodyListenerSystem::error_type
    RigidBodyListenerSystem::InitializeEntity(entity_manager* a_mgr,
                                              entity_type* a_ent)
  {
    TLOC_UNUSED_2(a_mgr, a_ent);
    return ErrorSuccess();
  }

  RigidBodyListenerSystem::error_type
    RigidBodyListenerSystem::ShutdownEntity(entity_manager* a_mgr,
                                            entity_type* a_ent)
  {
    TLOC_UNUSED_2(a_mgr, a_ent);
    return ErrorSuccess();
  }

  void RigidBodyListenerSystem::Pre_ProcessActiveEntities()
  {
    using namespace tloc::core::component_system;

    typedef RigidBodyListener                       rb_listener_component_type;

    typedef rb_listener_component_type::rigid_body_listener_type
      rb_listener_type;

    typedef contact_event_list::const_iterator      const_contact_iterator;

    contact_event_list* currContactEventList =
      &m_allContactEvents[contact::k_begin];

    const_contact_iterator contactItr = currContactEventList->begin();
    const_contact_iterator contactItrEnd = currContactEventList->end();

    const entity_type::component_list* rbListenerComponents;

    for (/* */; contactItr != contactItrEnd; ++contactItr)
    {
      rbListenerComponents =
        &contactItr->m_entityA->GetComponents(components::k_rigid_body_listener);

      if (!rbListenerComponents->empty())
      {
        ComponentMapper<rb_listener_component_type>
          rbListenerComponentsMapped = *rbListenerComponents;

        rb_listener_component_type& rbListenerComponent =
          rbListenerComponentsMapped[0];

        rb_listener_type* rbListener =
          rbListenerComponent.GetRigidBodyListener();

        rbListener->OnContactBegin(contactItr->m_entityB);
      }

      rbListenerComponents =
        &contactItr->m_entityB->GetComponents(components::k_rigid_body_listener);

      if (!rbListenerComponents->empty())
      {
        ComponentMapper<rb_listener_component_type>
          rbListenerComponentsMapped = *rbListenerComponents;

        rb_listener_component_type& rbListenerComponent =
          rbListenerComponentsMapped[0];

        rb_listener_type* rbListener =
          rbListenerComponent.GetRigidBodyListener();

        rbListener->OnContactBegin(contactItr->m_entityA);
      }

    }

    currContactEventList = &m_allContactEvents[contact::k_end];

    contactItr = currContactEventList->begin();
    contactItrEnd = currContactEventList->end();

    for (/* */; contactItr != contactItrEnd; ++contactItr)
    {
      rbListenerComponents =
        &contactItr->m_entityA->GetComponents(components::k_rigid_body_listener);

      if (!rbListenerComponents->empty())
      {
        ComponentMapper<rb_listener_component_type>
          rbListenerComponentsMapped = *rbListenerComponents;

        rb_listener_component_type& rbListenerComponent =
          rbListenerComponentsMapped[0];

        rb_listener_type* rbListener =
          rbListenerComponent.GetRigidBodyListener();

        rbListener->OnContactEnd(contactItr->m_entityB);
      }

      rbListenerComponents =
        &contactItr->m_entityB->GetComponents(components::k_rigid_body_listener);

      if (!rbListenerComponents->empty())
      {
        ComponentMapper<rb_listener_component_type>
          rbListenerComponentsMapped = *rbListenerComponents;

        rb_listener_component_type& rbListenerComponent =
          rbListenerComponentsMapped[0];

        rb_listener_type* rbListener =
          rbListenerComponent.GetRigidBodyListener();

        rbListener->OnContactEnd(contactItr->m_entityA);
      }
    }
  }

  void RigidBodyListenerSystem::ProcessEntity(entity_manager* a_mgr,
                                              entity_type* a_ent)
  {
    TLOC_UNUSED_2(a_mgr, a_ent);
  }

  bool RigidBodyListenerSystem::OnContactBegin(const contact_event_type& a_event)
  {
    m_allContactEvents[contact::k_begin].push_back(a_event);
    return false;
  }

  bool RigidBodyListenerSystem::OnContactEnd(const contact_event_type& a_event)
  {
    m_allContactEvents[contact::k_end].push_back(a_event);
    return false;
  }

};};};
