#include "tlocRigidBodyListenerSystem.h"

#include <tlocCore/error/tlocError.h>
#include <tlocCore/containers/tlocArray.inl>
#include <tlocCore/component_system/tlocComponentMapper.h>

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

    typedef rb_listener_component::rigid_body_listener_type
                                                      rb_listener_type;

    typedef RigidBodyListenerSystem::entity_type      entity_type;
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

    rb_listener_type*
      DoGetRigidBodyListener(const component_list* a_rbListenerComponents)
    {
      using namespace tloc::core::component_system;

      ComponentMapper<rb_listener_component>
        rbListenerComponentsMapped = *a_rbListenerComponents;

      rb_listener_component& rbListenerComponent =
        rbListenerComponentsMapped[0];

      return rbListenerComponent.GetRigidBodyListener();
    }

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      DoSendOnContactBegin(const entity_type* a_sendToEnt,
                           const entity_type* a_contactWithEnt)
    {
      const entity_type::component_list* rbListenerComponents;
      rb_listener_type* rbListener;

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
      SendOnContactEnd(const entity_type* a_sendToEnt,
                       const entity_type* a_contactWithEnt)
    {
      const entity_type::component_list* rbListenerComponents;
      rb_listener_type* rbListener;

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
    RigidBodyListenerSystem(event_manager_sptr a_eventMgr,
                            entity_manager_sptr a_entityMgr,
                            physics_manager* a_physicsMgr)
    : base_type(a_eventMgr, a_entityMgr
    , Variadic<component_type, 1>(components::k_rigidBodyListener))
    , m_physicsMgr(a_physicsMgr)
  {
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodyListenerSystem::error_type RigidBodyListenerSystem::
    Pre_Initialize()
  {
    m_physicsMgr->Register(this);
    m_allContactEvents.resize(contact::k_count);
    return ErrorSuccess();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodyListenerSystem::error_type RigidBodyListenerSystem::
    Post_Shutdown()
  {
    m_physicsMgr->UnRegister(this);
    m_allContactEvents.clear();
    return ErrorSuccess();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodyListenerSystem::error_type RigidBodyListenerSystem::
    InitializeEntity(const entity_manager* ,
                     const entity_type* a_ent)
  {
    const entity_type* ent = a_ent;

    const entity_type::component_list& rbComponents =
      ent->GetComponents(components::k_rigidBody);

    if (rbComponents.empty())
    {
      TLOC_ASSERT(false, "There is no RigidBody component attached to this \
                  entity! A RigidBody component is needed for a \
                  RigidBodyListener component to function!");

      // LOG: No RigidBody component attached to this entity!
      return error::error_rigid_body_not_attached;
    }

    return ErrorSuccess();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodyListenerSystem::error_type RigidBodyListenerSystem::
    ShutdownEntity(const entity_manager* a_mgr,
                   const entity_type* a_ent)
  {
    TLOC_UNUSED_2(a_mgr, a_ent);
    return ErrorSuccess();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void RigidBodyListenerSystem::
    Pre_ProcessActiveEntities()
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

  void RigidBodyListenerSystem::
    ProcessEntity(const entity_manager* , const entity_type* )
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool RigidBodyListenerSystem::
    OnContactBegin(const contact_event_type& a_event)
  {
    m_allContactEvents[contact::k_begin].push_back(a_event);
    return false;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool RigidBodyListenerSystem::
    OnContactEnd(const contact_event_type& a_event)
  {
    m_allContactEvents[contact::k_end].push_back(a_event);
    return false;
  }

};};};
