#pragma once
#ifndef _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_LISTENER_SYSTEM_H_
#define _TLOC_PHYSICS_COMPONENT_SYSTEM_RIGID_BODY_LISTENER_SYSTEM_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/containers/tlocArray.h>

#include <tlocPhysics/component_system/tlocComponentType.h>


#include <tlocCore/error/tlocError.h>
#include <tlocCore/containers/tlocArray.inl>
#include <tlocCore/component_system/tlocComponentMapper.h>

#include <tlocPhysics/component_system/tlocRigidbodyListenerComponent.h>
#include <tlocPhysics/box2d/tlocPhysicsManager.h>

namespace tloc { namespace physics { namespace box2d {

  struct ContactEvent;
  class PhysicsManager;

};};};

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

  class RigidBodyListenerSystem : 
    public core::component_system::EntityProcessingSystem
  {
  public:
    typedef core::component_system::EntityProcessingSystem base_type;
    typedef base_type::component_type   component_type;
    typedef base_type::error_type       error_type;
    
    typedef base_type::event_manager    event_manager;
    typedef base_type::entity_manager   entity_manager;
    typedef base_type::entity_type      entity_type;
    typedef base_type::event_type       event_type;
    typedef base_type::event_value_type event_value_type;

    typedef box2d::ContactEvent             contact_event_type;
    typedef box2d::PhysicsManager           physics_manager;
    typedef core::Array<contact_event_type> contact_event_list;
    typedef core::Array<contact_event_list> contact_event_list_list;

  public:
    RigidBodyListenerSystem(event_manager* a_eventMgr, entity_manager* a_entityMgr, 
                            physics_manager* a_physicsMgr)
      : base_type(a_eventMgr, a_entityMgr
      , core::Variadic<component_type, 1>(components::k_rigid_body_listener))
      , m_physicsMgr(a_physicsMgr)
    {
    }

    virtual error_type Pre_Initialize()
    {
      m_physicsMgr->Register(this);
      m_allContactEvents.resize(contact::k_count);
      return ErrorSuccess();
    }

    virtual error_type InitializeEntity(entity_manager* a_mgr, entity_type* a_ent)
    {
      TLOC_UNUSED_2(a_mgr, a_ent);
      return ErrorSuccess();
    }

    virtual error_type ShutdownEntity(entity_manager* a_mgr, entity_type* a_ent)
    {
      TLOC_UNUSED_2(a_mgr, a_ent);
      return ErrorSuccess();
    }

    virtual error_type Post_Shutdown()
    {
      m_allContactEvents.clear();
      return ErrorSuccess();
    }

    virtual void Pre_ProcessActiveEntities()
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

    virtual void ProcessEntity(entity_manager* a_mgr, entity_type* a_ent)
    {
      TLOC_UNUSED_2(a_mgr, a_ent);
    }

  public:
    bool OnContactBegin(const contact_event_type& a_event)
    {
      m_allContactEvents[contact::k_begin].push_back(a_event);
      return false;
    }

    bool OnContactEnd(const contact_event_type& a_event)
    {
      m_allContactEvents[contact::k_end].push_back(a_event);
      return false;
    }

  private:
    physics_manager* m_physicsMgr;
    contact_event_list_list m_allContactEvents;
  };

};};};

TLOC_DEF_TYPE(tloc::physics::component_system::RigidBodyListenerSystem);

#endif