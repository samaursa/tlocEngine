#include "tlocSceneGraphSystem.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocSceneNode.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  // ///////////////////////////////////////////////////////////////////////
  // typedefs

  typedef SceneGraphSystem::error_type            error_type;

  // ///////////////////////////////////////////////////////////////////////
  // Entity compare

  struct NodeCompareFromEntity
  {
    typedef SceneNode*                            node_ptr_type;
    typedef core_cs::Entity*                      entity_ptr_type;

    bool
      operator()(entity_ptr_type a_first, entity_ptr_type a_second)
    {
      TLOC_ASSERT(a_first->HasComponent(SceneNode::k_component_type),
        "Entity should have a 'Node' component");
      TLOC_ASSERT(a_second->HasComponent(SceneNode::k_component_type),
        "Entity should have a 'Node' component");

      SceneNode* firstNode = a_first->GetComponent<SceneNode>();
      SceneNode* secondNode = a_second->GetComponent<SceneNode>();

      return firstNode->GetLevel() < secondNode->GetLevel();
    }
  };

  // ///////////////////////////////////////////////////////////////////////
  // SceneGraphSystem

  SceneGraphSystem::
    SceneGraphSystem
    (event_manager_sptr a_eventMgr, entity_manager_sptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                Variadic<component_type, 1>(components::scene_node))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneGraphSystem::
    DeactivateHierarchy(const entity_type* a_node)
  {
    TLOC_ASSERT_NOT_NULL(a_node);

    a_node->Deactivate();

    if (a_node->HasComponent<gfx_cs::SceneNode>() == false)
    { return; }

    SceneNode* node = a_node->GetComponent<SceneNode>();

    for (SceneNode::node_cont_iterator
         itr = node->begin(), itrEnd = node->end(); itr != itrEnd; ++itr)
    {
      DeactivateHierarchy( (*itr)->GetEntity() );
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneGraphSystem::
    ActivateHierarchy(const entity_type* a_parent)
  {
    TLOC_ASSERT_NOT_NULL(a_parent);

    a_parent->Activate();

    if (a_parent->HasComponent(components::scene_node) == false)
    { return; }

    SceneNode* node = a_parent->GetComponent<SceneNode>();

    for (SceneNode::node_cont_iterator
         itr = node->begin(), itrEnd = node->end(); itr != itrEnd; ++itr)
    {
      ActivateHierarchy( (*itr)->GetEntity() );
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneGraphSystem::
    SortEntities()
  {
    core::sort(DoGetActiveEntities().begin(), DoGetActiveEntities().end(),
      NodeCompareFromEntity());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    SceneGraphSystem::
    Pre_Initialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    SceneGraphSystem::
    InitializeEntity(const entity_manager* , const entity_type* a_ent)
  {
    TLOC_LOG_CORE_WARN_IF(a_ent->
      HasComponent(math_cs::Transform::k_component_type) == false)
      << "Node component requires math_cs::Transform component";

    SceneNode* node = a_ent->GetComponent<SceneNode>();

    // get the level of this node relative to its parents. If the parent
    // already has a level and update hierarchy is not required, then find
    // the level from there

    SceneNode* parent = node->GetParent();

    if (parent)
    {
      if (parent->IsHierarchyUpdateRequired())
      {
        SceneNode::index_type nodeLevel = 0;
        while (parent)
        {
          ++nodeLevel;
          parent = parent->GetParent();
        }

        node->DoSetLevel(nodeLevel);
      }
      else
      {
        node->DoSetLevel(parent->GetLevel() + 1);
      }
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    SceneGraphSystem::
    Post_Initialize()
  {
    SortEntities();
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    SceneGraphSystem::
    ShutdownEntity(const entity_manager* , const entity_type* )
  {
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneGraphSystem::
    Pre_ProcessActiveEntities(f64)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneGraphSystem::
    ProcessEntity(const entity_manager* , const entity_type* a_ent, f64 )
  {
    using math_cs::Transform;

    Transform* localTransform = a_ent->GetComponent<Transform>();
    SceneNode* node = a_ent->GetComponent<SceneNode>();

    SceneNode*         nodeParent = node->GetParent();

    if (nodeParent == nullptr)
    {
      node->SetWorldTransform(localTransform->GetTransformation());
    }
    else
    {
      Transform::transform_type tr =
        nodeParent->GetWorldTransform() * localTransform->GetTransformation();

      node->SetWorldTransform(tr);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneGraphSystem::
    Post_ProcessActiveEntities(f64)
  {
  }

};};};

// ///////////////////////////////////////////////////////////////////////
// Explicit instantiations

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(SceneGraphSystem);