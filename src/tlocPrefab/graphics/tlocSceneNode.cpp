#include "tlocSceneNode.h"

#include <tlocMath/component_system/tlocTransform.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

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

    // Create the transform component (and the transform pool if necessary)
    typedef math_cs::transform_f32_pool         t_pool;
    math_cs::transform_f32_pool_vptr            tPool;

    if (m_compPoolMgr->Exists(transform) == false)
    { tPool = m_compPoolMgr->CreateNewPool<math_cs::Transformf32>(); }
    else
    { tPool = m_compPoolMgr->GetPool<math_cs::Transformf32>(); }

    t_pool::iterator itrTransform = tPool->GetNext();
    (*itrTransform)->SetValue(Transform() );

    m_entMgr->InsertComponent(ent, (*itrTransform)->GetValue() );

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

    using namespace gfx_cs::components;

    typedef gfx_cs::scene_node_pool             scene_node_pool;
    gfx_cs::scene_node_pool_vptr                sceneNodePool;

    if (m_compPoolMgr->Exists(scene_node) == false)
    { sceneNodePool = m_compPoolMgr->CreateNewPool<gfx_cs::SceneNode>(); }
    else
    { sceneNodePool = m_compPoolMgr->GetPool<gfx_cs::SceneNode>(); }

    scene_node_pool::iterator itrSceneNode = sceneNodePool->GetNext();
    (*itrSceneNode)->SetValue(gfx_cs::SceneNode(a_ent) );

    if (m_parent)
    { m_parent->AddChild( (*itrSceneNode)->GetValue() ); }

    m_entMgr->InsertComponent(a_ent, (*itrSceneNode)->GetValue() );

    return *this;
  }

};};};