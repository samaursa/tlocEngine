#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_NODE_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_NODE_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/error/tlocError.h>

#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocMath/component_system/tlocTransform.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // Node

  class SceneGraphSystem;

  class Node
    : public core_cs::Component_T<Node, components::node>
  {
    friend class SceneGraphSystem;

  public:
    typedef core_cs::Component_T<Node, components::node>  base_type;

    typedef Node                                          this_type;
    typedef this_type*                                    pointer;
    typedef this_type&                                    reference;

    typedef core_err::Error                               error_type;

    typedef const core_cs::Entity*                        entity_ptr_type;

    typedef core_conts::tl_array<pointer>::type   node_cont_type;
    typedef node_cont_type::iterator              node_cont_iterator;
    typedef node_cont_type::const_iterator        node_cont_const_iterator;

    typedef math_cs::Transform::transform_type    transform_type;
    typedef tl_size                               index_type;

  public:
    Node();
    explicit Node(entity_ptr_type a_entity);

    void        AddChild(pointer a_childNode);
    bool        HasChild(pointer a_childNode);
    void        RemoveChild(pointer a_childNode);

    node_cont_iterator        begin();
    node_cont_iterator        end();

    node_cont_const_iterator  begin() const;
    node_cont_const_iterator  end() const;

    TLOC_DECL_SETTER(transform_type, SetWorldTransform);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (transform_type, GetWorldTransform, m_worldTransform);
    TLOC_DECL_AND_DEF_GETTER(index_type, GetLevel, m_level);

    TLOC_DECL_GETTER(bool, IsHierarchyUpdateRequired);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetHierarchyUpdateRequired);

    TLOC_DECL_GETTER(bool, IsTransformUpdateRequired);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetTransformUpdateRequired);

    TLOC_DECL_GETTER(entity_ptr_type, GetEntity);
    TLOC_DECL_AND_DEF_GETTER(pointer, GetParent, m_parent);

  private:
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(index_type, DoSetLevel, m_level);

  private:
    entity_ptr_type         m_entity;

    pointer                 m_parent;
    node_cont_type          m_children;
    index_type              m_level;

    transform_type          m_worldTransform;
    core_utils::Checkpoints m_flags;

  };

  // ///////////////////////////////////////////////////////////////////////
  // NodeCompare

  template <typename T_NodeType>
  struct NodeCompareByLevel
  { TLOC_STATIC_ASSERT_FALSE(T_NodeType, Unsupported_node_type); };

  template <>
  struct NodeCompareByLevel<Node>
  {
  public:
    typedef Node                value_type;

  public:
    bool
      operator()(const value_type& a_first, const value_type& a_second) const
    {
      return a_first.GetLevel() < a_second.GetLevel();
    }
  };

  template <>
  struct NodeCompareByLevel<Node*>
  {
  public:
    typedef Node*               value_type;

  public:
    bool
      operator()(value_type a_first, value_type a_second) const
    {
      return a_first->GetLevel() < a_second->GetLevel();
    }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // Node compare by entity pointer

  struct NodeCompare
  {
  public:
    typedef Node::entity_ptr_type             entity_ptr_type;
    typedef Node::pointer                     node_ptr_type;

  public:

    NodeCompare(entity_ptr_type a_entityPtr)
      : m_entToCompare(a_entityPtr)
    { }

    bool operator()(node_ptr_type a_other) const
    {
      return m_entToCompare == a_other->GetEntity();
    }

  private:
    entity_ptr_type m_entToCompare;
  };

  // ///////////////////////////////////////////////////////////////////////
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(Node, node);
  TLOC_TYPEDEF_COMPONENT_POOL(node_sptr, node_sptr);

};};};

#endif