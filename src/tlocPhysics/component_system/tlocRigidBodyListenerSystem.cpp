#include "tlocRigidBodyListenerSystem.h"

#include <tlocCore/error/tlocError.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocPhysics/error/tlocErrorTypes.h>
#include <tlocPhysics/component_system/tlocRigidBodyComponent.h>
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

    typedef entity_type::component_iterator           component_iterator;
    typedef entity_type::const_component_iterator     const_component_iterator;

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
      DoGetRigidBodyListener(const_component_iterator itr, 
                             const_component_iterator itrEnd)
    {
      using namespace tloc::core::component_system;

      ComponentMapper<rb_listener_component, const_component_iterator> 
        rbListenerComponentsMapped(itr, itrEnd);

      rigid_body_listener_sptr rbListenerComponent =
        rbListenerComponentsMapped[0];

      return rbListenerComponent->GetRigidBodyListener();
    }

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      DoSendOnContactBegin(const_entity_ptr a_sendToEnt,
                           const_entity_ptr a_contactWithEnt)
    {
      if (a_sendToEnt->size_components<phys_cs::RigidBodyListener>() > 0)
      {
        rb_listener_ptr rbListener;

        const_component_iterator itr, itrEnd;
        itr     = a_sendToEnt->begin_components<phys_cs::RigidBodyListener>();
        itrEnd  = a_sendToEnt->end_components<phys_cs::RigidBodyListener>();

        rbListener = DoGetRigidBodyListener(itr, itrEnd);
        rbListener->OnContactBegin(a_contactWithEnt);
      }
    }

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      SendOnContactEnd(const_entity_ptr a_sendToEnt,
                       const_entity_ptr a_contactWithEnt)
    {
      if (a_sendToEnt->size_components<phys_cs::RigidBodyListener>() > 0)
      {
        rb_listener_ptr rbListener;

        const_component_iterator itr, itrEnd;
        itr     = a_sendToEnt->begin_components<phys_cs::RigidBodyListener>();
        itrEnd  = a_sendToEnt->end_components<phys_cs::RigidBodyListener>();

        rbListener = DoGetRigidBodyListener(itr, itrEnd);
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
                register_type().Add<phys_cs::RigidBodyListener>())
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
    if (a_ent->size_components<phys_cs::RigidBody>() == 0)
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

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::phys_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(RigidBodyListenerSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(RigidBodyListenerSystem);