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

  SceneNode::
    SceneNode(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : base_type(a_entMgr, a_poolMgr)
    , m_parent(nullptr)
    , m_pos(0)
    , m_ori(orientation_type::IDENTITY)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::component_ptr
    SceneNode::
    Construct(entity_ptr a_nodeEntity) const
  {
    using namespace gfx_cs::components;

    typedef gfx_cs::scene_node_pool             scene_node_pool;

    gfx_cs::scene_node_pool_vptr sceneNodePool
      = m_compPoolMgr->GetOrCreatePool<gfx_cs::SceneNode>();

    scene_node_pool::iterator itrSceneNode = sceneNodePool->GetNext();
    (*itrSceneNode)->SetValue
      (core_sptr::MakeShared<gfx_cs::SceneNode>(a_nodeEntity) );

    if (m_parent)
    { m_parent->AddChild( core_sptr::ToVirtualPtr(*(*itrSceneNode)->GetValuePtr()) ); }

    return *(*itrSceneNode)->GetValuePtr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::entity_ptr
    SceneNode::
    Create() const
  {
    entity_ptr ent = m_entMgr->CreateEntity();

    using namespace math_cs::components;

    // Add the SceneNode component
    Add(ent);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneNode::
    Add(entity_ptr a_ent) const
  {
    TLOC_ASSERT(a_ent->HasComponent(gfx_cs::SceneNode::k_component_type) == false,
      "Entity already has a SceneNode");

    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { 
      pref_math::Transform(m_entMgr, m_compPoolMgr)
        .Position(m_pos)
        .Orientation(m_ori)
        .Add(a_ent);
    }
    else
    {
      math_cs::transform_sptr t = a_ent->GetComponent<math_cs::Transform>();
      t->SetPosition(m_pos);
      t->SetOrientation(m_ori);
    }

    // -----------------------------------------------------------------------
    // SceneNode component

    m_entMgr->InsertComponent( insert_params(a_ent, Construct(a_ent))
                              .DispatchTo(GetListeners()) );
  }

};};};