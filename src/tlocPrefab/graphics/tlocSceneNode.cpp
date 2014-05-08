#include "tlocSceneNode.h"

#include <tlocCore/tlocAssert.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocPrefab/math/tlocTransform.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;
  using core_sptr::MakeShared;

  using gfx_cs::scene_node_sptr;
  using gfx_cs::scene_node_vptr;

  using math_cs::transform_sptr;
  using math_cs::transform_vptr;
  using math_cs::Transform;

  // ///////////////////////////////////////////////////////////////////////
  // SceneNode

  SceneNode::entity_ptr
    SceneNode::
    Create()
  {
    entity_ptr ent = m_entMgr->CreateEntity();

    using namespace math_cs::components;

    // Add the SceneNode component
    Add(ent);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::this_type&
    SceneNode::
    Add(entity_ptr a_ent)
  {
    TLOC_ASSERT(a_ent->HasComponent(gfx_cs::SceneNode::k_component_type) == false,
      "Entity already has a SceneNode");

    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // SceneNode component

    using namespace gfx_cs::components;

    typedef gfx_cs::scene_node_pool             scene_node_pool;

    gfx_cs::scene_node_pool_vptr sceneNodePool
      = m_compPoolMgr->GetOrCreatePool<gfx_cs::SceneNode>();

    scene_node_pool::iterator itrSceneNode = sceneNodePool->GetNext();
    (*itrSceneNode)->SetValue
      (core_sptr::MakeShared<gfx_cs::SceneNode>(a_ent) );

    if (m_parent)
    { m_parent->AddChild( core_sptr::ToVirtualPtr(*(*itrSceneNode)->GetValuePtr()) ); }

    m_entMgr->InsertComponent(a_ent, *(*itrSceneNode)->GetValuePtr() );

    return *this;
  }

};};};