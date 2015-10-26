#include "tlocTestCommon.h"

#include <tlocPhysics/component_system/tlocRigidBodyComponent.h>
#include <tlocPhysics/component_system/tlocRigidBodyShapeComponent.h>
#include <tlocPhysics/component_system/tlocRigidBodySystem.h>
#include <tlocPhysics/box2d/tlocPhysicsManager.h>

#include <tlocPrefab/physics/tlocRigidBody.h>

namespace 
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef phys_cs::RigidBody                      component_type;
  typedef phys_cs::rigid_body_sptr                component_ptr;

  typedef phys_cs::rigid_body_system_vso          system_vso;

  TEST_CASE("prefab/physics/RigidBody", "")
  {
    core_cs::component_pool_mgr_vso compMgr;
    core_cs::event_manager_vso      evtMgr;
    core_cs::entity_manager_vso     entMgr(evtMgr.get());

    phys_box2d::PhysicsManager::vec_type g(0, -2.0f);
    phys_box2d::PhysicsManager  physMgr;
    physMgr.Initialize(phys_box2d::PhysicsManager::gravity(g));

    system_vso                      system(evtMgr.get(), entMgr.get(), &physMgr.GetWorld());
    TLOC_UNUSED(system);

    //SECTION("Construct", "")
    {
      phys_box2d::rigid_body_def_sptr rbDef =
        core_sptr::MakeShared<phys_box2d::RigidBodyDef>();
      rbDef->SetPosition(phys_box2d::RigidBodyDef::vec_type(0, 1.0f));
      rbDef->SetType<phys_box2d::p_rigid_body::DynamicBody>();

      component_ptr ptr = pref_phys::RigidBody(entMgr.get(), compMgr.get())
        .Construct(rbDef);

      CHECK( (ptr->GetRigidBodyDef() == rbDef) );
    }

    //SECTION("Construct", "")
    {
      phys_box2d::rigid_body_def_sptr rbDef =
        core_sptr::MakeShared<phys_box2d::RigidBodyDef>();
      rbDef->SetPosition(phys_box2d::RigidBodyDef::vec_type(0, 1.0f));
      rbDef->SetType<phys_box2d::p_rigid_body::DynamicBody>();

      entity_ptr ent = pref_phys::RigidBody(entMgr.get(), compMgr.get())
        .Create(rbDef);

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK( (ptr->GetRigidBodyDef() == rbDef) );
    }

    //SECTION("Add", "")
    {
      phys_box2d::rigid_body_def_sptr rbDef =
        core_sptr::MakeShared<phys_box2d::RigidBodyDef>();
      rbDef->SetPosition(phys_box2d::RigidBodyDef::vec_type(0, 1.0f));
      rbDef->SetType<phys_box2d::p_rigid_body::DynamicBody>();

      entity_ptr ent = entMgr->CreateEntity();

      pref_phys::RigidBody(entMgr.get(), compMgr.get())
        .Add(ent, rbDef);

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK( (ptr->GetRigidBodyDef() == rbDef) );
    }
  }
};
