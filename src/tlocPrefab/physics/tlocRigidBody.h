#ifndef _TLOC_PREFAB_PHYSICS_RIGID_BODY_H_
#define _TLOC_PREFAB_PHYSICS_RIGID_BODY_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/types/tlocStrongType.h>

#include <tlocPhysics/component_system/tlocRigidBodyComponent.h>
#include <tlocPhysics/component_system/tlocRigidBodyShapeComponent.h>
#include <tlocPhysics/component_system/tlocRigidbodyListenerComponent.h>

namespace tloc { namespace prefab { namespace physics {

  // ///////////////////////////////////////////////////////////////////////
  // RigidBody

  class RigidBody
    : public Prefab_I
  {
    public:
      typedef RigidBody                         this_type;
      typedef phys_box2d::rigid_body_def_sptr   rb_def_sptr;

    public:
      RigidBody(entity_mgr_ptr  a_entMgr,
                comp_pool_mgr_ptr a_poolMgr)
                : Prefab_I(a_entMgr, a_poolMgr)
      { }

      entity_ptr    Create(const rb_def_sptr& a_rbDef);
      void          Add(entity_ptr a_ent, const rb_def_sptr& a_rbDef);
  };

  // ///////////////////////////////////////////////////////////////////////
  // RigidBodyShape

  class RigidBodyShape
    : public Prefab_I
  {
    public:
      typedef RigidBodyShape                      this_type;
      typedef phys_box2d::RigidBodyShapeDef       rb_shape_def;
      typedef core_conts::tl_array
        <const rb_shape_def>::type                rb_shape_def_cont;

      typedef core_t::StrongType_T<tl_float, 0>   density;

    public:
      RigidBodyShape(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr)
                     : Prefab_I(a_entMgr, a_poolMgr)
      { }

      entity_ptr    Create(rb_shape_def a_rbDef);
      void          Add(entity_ptr  a_ent, rb_shape_def a_rbShape);
      void          Add(entity_ptr  a_ent, const rb_shape_def_cont& a_rbShapes);

      template <typename T_Shape>
      void          Add(entity_ptr  a_ent, const T_Shape a_shape,
                        density a_density)
      {
        tloc::physics::box2d::RigidBodyShapeDef rbShape(a_shape);
        rbShape.SetDensity(a_density);

        Add(a_ent, rbShape);
      }
  };

  // ///////////////////////////////////////////////////////////////////////
  // RigidBodyListener

  class RigidBodyListener
    : public Prefab_I
  {
    public:
      typedef RigidBodyListener                         this_type;
      typedef tloc::physics::RigidBodyListener          rb_listener;
      typedef tloc::physics::rigid_body_listener_vptr   rb_listener_ptr;
      typedef phys_cs::RigidBodyListener                rb_listener_comp;

    public:
      RigidBodyListener(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr)
                        : Prefab_I(a_entMgr, a_poolMgr)
      { }

      void Add(entity_ptr a_ent, rb_listener_ptr a_listener);
  };

};};};

#endif