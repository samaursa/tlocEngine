#include "tlocNode.h"

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

  Node::
    Node()
    : base_type(k_component_type)
    , m_entity(nullptr)
    , m_parent(nullptr)
    , m_level(0)
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Node::
    Node(entity_ptr_type a_entity)
    : base_type(k_component_type)
    , m_entity(a_entity)
    , m_parent(nullptr)
    , m_level(0)
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Node::
    AddChild(pointer a_childNode)
  {
    TLOC_ASSERT(a_childNode->GetParent() == nullptr, "Child already has a parent");

    a_childNode->SetHierarchyUpdateRequired(true);
    m_children.push_back(a_childNode);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Node::
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
    Node::
    HasChild(pointer a_childNode)
  {
    node_cont_iterator itr = core::find_all(m_children, a_childNode);
    return itr != m_children.end();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Node::node_cont_iterator
    Node::
    begin()
  { return m_children.begin(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Node::node_cont_const_iterator
    Node::
    begin() const
  { return m_children.begin(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Node::node_cont_iterator
    Node::
    end()
  { return m_children.end(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Node::node_cont_const_iterator
    Node::
    end() const
  { return m_children.end(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Node::
    SetLocalTransform(const transform_type& a_transform)
  {
    m_localTransform = a_transform;
    SetTransformUpdateRequired(true);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Node::
    SetHierarchyUpdateRequired(bool a_updateRequired)
  { m_flags[k_hierarchyUpdate] = a_updateRequired; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Node::
    SetTransformUpdateRequired(bool a_updateRequired)
  { m_flags[k_transformUpdate] = a_updateRequired; }

};};};