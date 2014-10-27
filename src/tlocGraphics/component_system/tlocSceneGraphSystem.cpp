#include "tlocSceneGraphSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>

#include <tlocCore/component_system/tlocComponentType.h>
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
    typedef scene_node_sptr                               node_ptr_type;
    typedef core_cs::EntitySystemBase::entity_count_pair  entity_ptr_type;

    bool
      operator()(entity_ptr_type a, entity_ptr_type b)
    {
      TLOC_ASSERT(a.first->HasComponent<gfx_cs::SceneNode>(),
        "Entity should have a 'Node' component");
      TLOC_ASSERT(b.first->HasComponent<gfx_cs::SceneNode>(),
        "Entity should have a 'Node' component");

      node_ptr_type firstNode = a.first->GetComponent<SceneNode>();
      node_ptr_type secondNode = b.first->GetComponent<SceneNode>();

      return firstNode->GetLevel() < secondNode->GetLevel();
    }
  };

  // ///////////////////////////////////////////////////////////////////////
  // SceneGraphSystem

  SceneGraphSystem::
    SceneGraphSystem(event_manager_ptr a_eventMgr,
                     entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                register_type().Add<gfx_cs::SceneNode>())
  { }

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
    InitializeEntity(entity_ptr a_ent)
  {
    TLOC_LOG_CORE_WARN_IF(a_ent->HasComponent<math_cs::Transform>() == false)
      << "Node component requires math_cs::Transform component";

    scene_node_sptr node = a_ent->GetComponent<SceneNode>();

    // get the level of this node relative to its parents. If the parent
    // already has a level and update hierarchy is not required, then find
    // the level from there

    scene_node_vptr parent = node->GetParent();

    if (parent)
    {
      // check if the parent is disabled, if yes, disable us as well
      if (parent->GetEntity()->IsActive() == false)
      { DoGetEntityManager()->DeactivateEntity(a_ent); }

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
    ShutdownEntity(entity_ptr)
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
    ProcessEntity(entity_ptr a_ent, f64 )
  {
    using namespace math_cs;

    transform_sptr localTransform = a_ent->GetComponent<Transform>();
    scene_node_sptr node = a_ent->GetComponent<SceneNode>();

    scene_node_vptr nodeParent = node->GetParent();

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

  // -----------------------------------------------------------------------
  // meta functions

  namespace f_scene_graph {
    void
      DeactivateHierarchy(entity_manager_ptr a_mgr, entity_ptr a_parent)
    {
      TLOC_ASSERT_NOT_NULL(a_parent);

      a_mgr->DeactivateEntity(a_parent);

      if (a_parent->HasComponent<gfx_cs::SceneNode>() == false)
      { return; }

      scene_node_sptr node = a_parent->GetComponent<SceneNode>();

      for (SceneNode::node_cont_iterator
           itr = node->begin(), itrEnd = node->end(); itr != itrEnd; ++itr)
      {
        DeactivateHierarchy( a_mgr, (*itr)->GetEntity());
      }
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      ActivateHierarchy(entity_manager_ptr a_mgr, entity_ptr a_parent)
    {
      TLOC_ASSERT_NOT_NULL(a_parent);

      a_mgr->ActivateEntity(a_parent);

      if (a_parent->HasComponent<gfx_cs::SceneNode>() == false)
      { return; }

      scene_node_sptr node = a_parent->GetComponent<SceneNode>();

      for (SceneNode::node_cont_iterator
           itr = node->begin(), itrEnd = node->end(); itr != itrEnd; ++itr)
      {
        ActivateHierarchy( a_mgr, (*itr)->GetEntity());
      }
    }
  };

};};};

// ///////////////////////////////////////////////////////////////////////
// Explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(SceneGraphSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(SceneGraphSystem);