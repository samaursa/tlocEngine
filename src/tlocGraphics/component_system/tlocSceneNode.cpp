#include "tlocSceneNode.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // Flags

  enum
  {
    k_hierarchyUpdate = 0,
    k_transformUpdate,
    k_count
  };

  // ///////////////////////////////////////////////////////////////////////
  // Node

  SceneNode::
    SceneNode()
    : base_type(k_component_type)
    , m_entity(nullptr)
    , m_parent(nullptr)
    , m_level(0)
    , m_worldTransform(transform_type::IDENTITY)
    , m_flags(k_count)
  {
    m_flags.MarkAll();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::
    SceneNode(entity_ptr_type a_entity)
    : base_type(k_component_type)
    , m_entity(a_entity)
    , m_parent(nullptr)
    , m_level(0)
    , m_worldTransform(transform_type::IDENTITY)
    , m_flags(k_count)
  {
    m_flags.MarkAll();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneNode::
    AddChild(pointer a_childNode)
  {

    TLOC_ASSERT(a_childNode->GetParent() == nullptr, "Child already has a parent");

    a_childNode->SetHierarchyUpdateRequired(true);
    a_childNode->m_parent = this;
    m_children.push_back(a_childNode);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneNode::
    RemoveChild(pointer a_childNode)
  {
    TLOC_ASSERT(a_childNode->GetParent() == this,
      "'this' is not the parent of the child");

    node_cont_iterator itr = core::find_all(m_children, a_childNode);

    TLOC_ASSERT(itr != m_children.end(),
      "Child/parent hierarchy was not added properly in these methods");

    (*itr)->m_parent = nullptr;
    (*itr)->SetHierarchyUpdateRequired(true);

    m_children.erase(itr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    SceneNode::
    HasChild(pointer a_childNode)
  {
    node_cont_iterator itr = core::find_all(m_children, a_childNode);
    return itr != m_children.end();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::node_cont_iterator
    SceneNode::
    begin()
  { return m_children.begin(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::node_cont_const_iterator
    SceneNode::
    begin() const
  { return m_children.begin(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::node_cont_iterator
    SceneNode::
    end()
  { return m_children.end(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::node_cont_const_iterator
    SceneNode::
    end() const
  { return m_children.end(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    SceneNode::
    IsParentDisabled() const
  {
    // Disable us if our parent is disabled
    SceneNode* p = GetParent();
    while(p)
    {
      if (p->GetEntity()->IsActive() == false)
      { return true; }

      p = p->GetParent();
    }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::node_cont_type::size_type
    SceneNode::
    size() const
  { return m_children.size(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneNode::
    SetWorldTransform(const transform_type& a_transform)
  {
    m_worldTransform = a_transform;
    SetTransformUpdateRequired(true);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const bool
    SceneNode::
    IsHierarchyUpdateRequired() const
  {
    return m_flags.IsMarked(k_hierarchyUpdate);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneNode::
    SetHierarchyUpdateRequired(bool a_updateRequired)
  { m_flags[k_hierarchyUpdate] = a_updateRequired; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const bool
    SceneNode::
    IsTransformUpdateRequired() const
  {
    return m_flags.IsMarked(k_transformUpdate);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SceneNode::
    SetTransformUpdateRequired(bool a_updateRequired)
  { m_flags[k_transformUpdate] = a_updateRequired; }

  // ///////////////////////////////////////////////////////////////////////
  // explicit instantiations

  // SmartPtr
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(SceneNode);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(scene_node_sptr);

};};};