#include "tlocSceneNode.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

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
    : base_type("SceneNode")
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
    SceneNode(entity_ptr a_entity)
    : base_type("SceneNode")
    , m_entity(a_entity)
    , m_parent(nullptr)
    , m_level(0)
    , m_worldTransform(transform_type::IDENTITY)
    , m_flags(k_count)
  {
    m_flags.MarkAll();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::this_type&
    SceneNode::
    AddChild(pointer a_childNode)
  {
    TLOC_ASSERT(a_childNode->GetParent() == nullptr, "Child already has a parent");

    a_childNode->SetHierarchyUpdateRequired(true);
    a_childNode->m_parent.reset(this);
    m_children.push_back(a_childNode);

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::this_type&
    SceneNode::
    RemoveChild(pointer a_childNode)
  {
    TLOC_ASSERT(a_childNode->GetParent().get() == this,
      "'this' is not the parent of the child");

    node_cont_iterator itr = core::find_all(m_children, a_childNode);

    TLOC_ASSERT(itr != m_children.end(),
      "Child/parent hierarchy was not added properly in these methods");

    (*itr)->m_parent = nullptr;
    (*itr)->SetHierarchyUpdateRequired(true);

    m_children.erase(itr);

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::this_type&
    SceneNode::
    RemoveParent()
  {
    TLOC_ASSERT_NOT_NULL(m_parent);
    m_parent->RemoveChild(pointer(this));

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::this_type&
    SceneNode::
    SetParent(pointer a_parentNode)
  {
    a_parentNode->AddChild(pointer(this));
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::entity_ptr
    SceneNode::
    GetEntity()
  { return m_entity; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::const_entity_ptr
    SceneNode::
    GetEntity() const
  { return m_entity; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::pointer
    SceneNode::
    GetParent()
  { return m_parent; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::const_pointer
    SceneNode::
    GetParent() const
  { return m_parent; }

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
    const_pointer p = GetParent();
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

  SceneNode::this_type&
    SceneNode::
    SetWorldTransform(const transform_type& a_transform)
  {
    m_worldTransform = a_transform;
    SetTransformUpdateRequired(true);

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    SceneNode::
    IsHierarchyUpdateRequired() const
  {
    return m_flags.IsMarked(k_hierarchyUpdate);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::this_type&
    SceneNode::
    SetHierarchyUpdateRequired(bool a_updateRequired)
  { m_flags[k_hierarchyUpdate] = a_updateRequired; return *this; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    SceneNode::
    IsTransformUpdateRequired() const
  {
    return m_flags.IsMarked(k_transformUpdate);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  SceneNode::this_type&
    SceneNode::
    SetTransformUpdateRequired(bool a_updateRequired)
  { m_flags[k_transformUpdate] = a_updateRequired; return *this; }

};};};


// ///////////////////////////////////////////////////////////////////////
// explicit instantiations

using namespace tloc::gfx_cs;

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(SceneNode);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(SceneNode);