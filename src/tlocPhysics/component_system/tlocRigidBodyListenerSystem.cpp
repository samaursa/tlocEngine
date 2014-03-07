#include "tlocRigidBodyListenerSystem.h"

#include <tlocCore/error/tlocError.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocPhysics/error/tlocErrorTypes.h>
#include <tlocPhysics/component_system/tlocRigidbodyListenerComponent.h>
#include <tlocPhysics/component_system/tlocComponentType.h>
#include <tlocPhysics/box2d/tlocPhysicsManager.h>

TLOC_DEF_TYPE(tloc::physics::component_system::RigidBodyListenerSystem);

namespace tloc { namespace physics { namespace component_system {

  using namespace core::data_structs;

  //////////////////////////////////////////////////////////////////////////
  // Free functions and definitions

  namespace {

    typedef RigidBodyListener                         rb_listener_component;

    typedef rb_listener_component::rigid_body_listener_ptr
                                                      rb_listener_ptr;

    typedef RigidBodyListenerSystem::entity_type      entity_type;
    typedef RigidBodyListenerSystem::entity_ptr       entity_ptr;
    typedef RigidBodyListenerSystem::const_entity_ptr const_entity_ptr;
    typedef entity_type::component_list               component_list;

    namespace contact
    {
      enum type
      {
        k_begin,
        k_end,

        k_count
      };
    };

    rb_listener_ptr
      DoGetRigidBodyListener(const component_list* a_rbListenerComponents)
    {
      using namespace tloc::core::component_system;

      ComponentMapper<rb_listener_component>
        rbListenerComponentsMapped = *a_rbListenerComponents;

      rigid_body_listener_vptr rbListenerComponent =
        rbListenerComponentsMapped[0];

      return rbListenerComponent->GetRigidBodyListener();
    }

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      DoSendOnContactBegin(const_entity_ptr a_sendToEnt,
                           const_entity_ptr a_contactWithEnt)
    {
      const entity_type::component_list* rbListenerComponents;
      rb_listener_ptr rbListener;

      rbListenerComponents =
        &a_sendToEnt->GetComponents(components::k_rigidBodyListener);

      if (!rbListenerComponents->empty())
      {
        rbListener = DoGetRigidBodyListener(rbListenerComponents);
        rbListener->OnContactBegin(a_contactWithEnt);
      }
    }

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      SendOnContactEnd(const_entity_ptr a_sendToEnt,
                       const_entity_ptr a_contactWithEnt)
    {
      const entity_type::component_list* rbListenerComponents;
      rb_listener_ptr rbListener;

      rbListenerComponents =
        &a_sendToEnt->GetComponents(components::k_rigidBodyListener);

      if (!rbListenerComponents->empty())
      {
        rbListener = DoGetRigidBodyListener(rbListenerComponents);
        rbListener->OnContactEnd(a_contactWithEnt);
      }
    }
  };

  //////////////////////////////////////////////////////////////////////////
  // RigidBodyListenerSystem

  RigidBodyListenerSystem::
    RigidBodyListenerSystem(event_manager_ptr a_eventMgr,
                            entity_manager_ptr a_entityMgr,
                            physics_manager* a_physicsMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>(components::k_rigidBodyListener))
    , m_physicsMgr(a_physicsMgr)
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodyListenerSystem::error_type
    RigidBodyListenerSystem::
    Pre_Initialize()
  {
    m_physicsMgr->Register(this);
    m_allContactEvents.resize(contact::k_count);
    return ErrorSuccess;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodyListenerSystem::error_type
    RigidBodyListenerSystem::
    Post_Shutdown()
  {
    m_physicsMgr->UnRegister(this);
    m_allContactEvents.clear();
    return ErrorSuccess;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodyListenerSystem::error_type
    RigidBodyListenerSystem::
    InitializeEntity(entity_ptr a_ent)
  {
    const entity_type::component_list& rbComponents =
      a_ent->GetComponents(components::k_rigidBody);

    if (rbComponents.empty())
    {
      TLOC_LOG_PHYS_WARN()
        << "There is no RigidBody component attached to this "
        << "entity. A RigidBody component is needed for a RigidBodyListener "
        << "component to function.";

      // LOG: No RigidBody component attached to this entity!
      return TLOC_ERROR(error::error_rigid_body_not_attached);
    }

    return ErrorSuccess;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodyListenerSystem::error_type
    RigidBodyListenerSystem::
    ShutdownEntity(entity_ptr)
  { return ErrorSuccess; }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void RigidBodyListenerSystem::
    Pre_ProcessActiveEntities(f64)
  {
    typedef contact_event_list::const_iterator      const_contact_iterator;

    contact_event_list* currContactEventList =
      &m_allContactEvents[contact::k_begin];

    const_contact_iterator contactItr = currContactEventList->begin();
    const_contact_iterator contactItrEnd = currContactEventList->end();

    for (/* */; contactItr != contactItrEnd; ++contactItr)
    {
      DoSendOnContactBegin(contactItr->m_entityA, contactItr->m_entityB);
      DoSendOnContactBegin(contactItr->m_entityB, contactItr->m_entityA);
    }

    currContactEventList = &m_allContactEvents[contact::k_end];

    contactItr = currContactEventList->begin();
    contactItrEnd = currContactEventList->end();

    for (/* */; contactItr != contactItrEnd; ++contactItr)
    {
      SendOnContactEnd(contactItr->m_entityA, contactItr->m_entityB);
      SendOnContactEnd(contactItr->m_entityB, contactItr->m_entityA);
    }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBodyListenerSystem::
    ProcessEntity(entity_ptr, f64 )
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RigidBodyListenerSystem::
    OnContactBegin(const contact_event_type& a_event)
  {
    m_allContactEvents[contact::k_begin].push_back(a_event);
    return false;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RigidBodyListenerSystem::
    OnContactEnd(const contact_event_type& a_event)
  {
    m_allContactEvents[contact::k_end].push_back(a_event);
    return false;
  }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

using namespace tloc::phys_cs;

TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(RigidBodyListenerSystem);
