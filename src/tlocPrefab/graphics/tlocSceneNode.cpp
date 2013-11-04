#include "tlocSceneNode.h"

#include <tlocMath/component_system/tlocTransform.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

  using gfx_cs::scene_node_sptr;
  using math_cs::transform_sptr;
  using math_cs::Transform;

  // ///////////////////////////////////////////////////////////////////////
  // SceneNode

  SceneNode::entity_type*
    SceneNode::
    Create()
  {
    Entity* ent = m_entMgr->CreateEntity();

    using namespace math_cs::components;

    // Create the transform component (and the transform pool if necessary)
    typedef math_cs::transform_f32_sptr_pool  t_pool;
    math_cs::transform_f32_sptr_pool_sptr     tPool;

    if (m_compPoolMgr->Exists(transform) == false)
    { tPool = m_compPoolMgr->CreateNewPool<transform_sptr>(); }
    else
    { tPool = m_compPoolMgr->GetPool<transform_sptr>(); }

    t_pool::iterator itrTransform = tPool->GetNext();
    itrTransform->SetValue(transform_sptr(new Transform()) );

    m_entMgr->InsertComponent(ent, itrTransform->GetValue().get() );

    // Add the SceneNode component
    Add(ent);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::this_type&
    SceneNode::
    Add(entity_type* a_ent)
  {
    TLOC_ASSERT(a_ent->HasComponent(gfx_cs::SceneNode::k_component_type) == false,
      "Entity already has a SceneNode");

    using namespace gfx_cs::components;

    typedef gfx_cs::scene_node_sptr_pool        scene_node_pool;
    gfx_cs::scene_node_sptr_pool_sptr           sceneNodePool;

    if (m_compPoolMgr->Exists(scene_node) == false)
    { sceneNodePool = m_compPoolMgr->CreateNewPool<scene_node_sptr>(); }
    else
    { sceneNodePool = m_compPoolMgr->GetPool<scene_node_sptr>(); }

    scene_node_pool::iterator itrSceneNode = sceneNodePool->GetNext();
    itrSceneNode->SetValue(scene_node_sptr(new gfx_cs::SceneNode(a_ent)) );

    if (m_parent)
    { m_parent->AddChild(itrSceneNode->GetValue().get()); }

    m_entMgr->InsertComponent(a_ent, itrSceneNode->GetValue().get());

    return *this;
  }

};};};