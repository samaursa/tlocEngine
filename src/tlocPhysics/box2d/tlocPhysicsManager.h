#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_PHYSICS_MANAGER_H_
#define _TLOC_PHYSICS_BOX2D_PHYSICS_MANAGER_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/base_classes/tlocTemplateDispatchDefaults.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/utilities/tlocCheckpoints.h>

#include <tlocMath/vector/tlocVector2.h>

namespace tloc { namespace physics { namespace box2d {
  
  class ContactListener;
  class World;

  struct ContactEvent
  {
    typedef core::component_system::Entity entity_type;
    
    ContactEvent
      (const entity_type* a_entityA = NULL, const entity_type* a_entityB = NULL)
      : m_entityA(a_entityA), m_entityB(a_entityB) {}

    const entity_type* m_entityA;
    const entity_type* m_entityB;
  };

  struct ContactCallbacks
  {
    virtual bool OnContactBegin(const ContactEvent& a_event) = 0;
    virtual bool OnContactEnd(const ContactEvent& a_event) = 0;
  };

  template <typename T>
  struct ContactCallbackGroupT :
    public core::CallbackGroupTArray<T, ContactCallbacks>::type
  {
    typedef typename core::CallbackGroupTArray<T, ContactCallbacks>::type
      base_type;
    typedef typename base_type::size_type size_type;

    using base_type::m_observers;

    virtual bool OnContactBegin(const ContactEvent& a_event)
    {
      for (size_type i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->OnContactBegin(a_event) == true)
        {
          return true; // Veto - event will not be passed to remaining observers
        }
      }
      return false;
    }

    virtual bool OnContactEnd(const ContactEvent& a_event)
    {
      for (size_type i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->OnContactEnd(a_event) == true)
        {
          return true; // Veto - event will not be passed to remaining observers
        }
      }
      return false;
    }
  };

  class PhysicsManager : 
    public core::DispatcherBaseArray<ContactCallbacks, ContactCallbackGroupT>::type
  {
  public:
    typedef PhysicsManager                              this_type;
    typedef core::DispatcherBaseArray
      <ContactCallbacks, ContactCallbackGroupT>::type   base_type;

    typedef base_type::size_type  size_type;
    typedef s32                   int_type;
    typedef math::Vec2f           vec_type;
    typedef core::error::Error    error_type;
    typedef World                 world_type;
    typedef ContactEvent          contact_event_type;
    typedef ContactListener       contact_listener_type;

    typedef core::types::StrongType_T<int_type, 0> velocity_iterations;
    typedef core::types::StrongType_T<int_type, 1> position_iterations;

    typedef core::types::StrongType_T<vec_type, 0> gravity;

  public:
    PhysicsManager();

    error_type Initialize(gravity a_gravity, 
                          velocity_iterations a_vel = velocity_iterations(8), 
                          position_iterations a_pos = position_iterations(3));

    error_type Shutdown();

    void Update(tl_float a_timeStep);

    world_type& GetWorld();
    const world_type& GetWorld() const;

    TLOC_DECL_AND_DEF_GETTER(int_type, GetVelocityIterations, 
                             m_velocityIterations);
    TLOC_DECL_AND_DEF_GETTER(int_type, GetPositionIterations, 
                             m_positionIterations);

    TLOC_DECL_AND_DEF_SETTER(int_type, SetVelocityIterations, 
                             m_velocityIterations);
    TLOC_DECL_AND_DEF_SETTER(int_type, SetPositionIterations, 
                             m_positionIterations);

  public:
    void SendOnContactBegin(const contact_event_type& a_event);
    void SendOnContactEnd(const contact_event_type& a_event);

  private:
    core::utils::Checkpoints m_flags;
    world_type* m_world;
    int_type m_velocityIterations;
    int_type m_positionIterations;
    contact_listener_type* m_contactListener;
  };

};};};

#endif