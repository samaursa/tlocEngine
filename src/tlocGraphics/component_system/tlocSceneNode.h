#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_NODE_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_NODE_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/containers/tlocContainers.h>
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

  class SceneNode
    : public core_cs::Component_T<SceneNode, 
                                  core_cs::component_group::k_graphics, 
                                  components::k_scene_node>
  {
    friend class SceneGraphSystem;

  public:
    typedef SceneNode                                     this_type;
    typedef core_cs::Component_T
      <this_type, k_component_group, k_component_type>    base_type;

    typedef core_sptr::VirtualPtr<this_type>              pointer;
    typedef core_sptr::VirtualPtr<const this_type>        const_pointer;
    typedef this_type&                                    reference;

    typedef core_err::Error                               error_type;

    typedef core_cs::const_entity_vptr                   const_entity_ptr;
    typedef core_cs::entity_vptr                         entity_ptr;

    typedef core_conts::tl_array<pointer>::type   node_cont_type;
    typedef node_cont_type::iterator              node_cont_iterator;
    typedef node_cont_type::const_iterator        node_cont_const_iterator;

    typedef math_cs::Transform::transform_type    transform_type;
    typedef tl_size                               index_type;

  public:
    SceneNode();
    explicit SceneNode(entity_ptr a_entity);

    this_type&                AddChild(pointer a_childNode);
    bool                      HasChild(pointer a_childNode);
    this_type&                RemoveChild(pointer a_childNode);

    this_type&                RemoveParent();
    this_type&                SetParent(pointer a_parentNode);

    entity_ptr                GetEntity();
    const_entity_ptr          GetEntity() const;

    pointer                   GetParent();
    const_pointer             GetParent() const;

    node_cont_iterator        begin();
    node_cont_iterator        end();

    node_cont_const_iterator  begin() const;
    node_cont_const_iterator  end() const;

    node_cont_type::size_type size() const;

    bool                      IsParentDisabled() const;

    TLOC_DECL_SETTER_CHAIN(transform_type, SetWorldTransform);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (transform_type, GetWorldTransform, m_worldTransform);
    TLOC_DECL_AND_DEF_GETTER(index_type, GetLevel, m_level);

    TLOC_DECL_AND_DEF_GETTER(bool, HasParent, m_parent != nullptr);

    TLOC_DECL_GETTER(bool, IsHierarchyUpdateRequired);
    TLOC_DECL_SETTER_BY_VALUE_CHAIN(bool, SetHierarchyUpdateRequired);

    TLOC_DECL_GETTER(bool, IsTransformUpdateRequired);
    TLOC_DECL_SETTER_BY_VALUE_CHAIN(bool, SetTransformUpdateRequired);

  private:
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(index_type, DoSetLevel, m_level);

  private:
    entity_ptr              m_entity;

    pointer                 m_parent;
    node_cont_type          m_children;
    index_type              m_level;

    transform_type          m_worldTransform;
    core_utils::Checkpoints m_flags;

  };

  // ///////////////////////////////////////////////////////////////////////
  // NodeCompare

  template <typename T_NodeType>
  struct SceneNodeCompareByLevel
  { TLOC_STATIC_ASSERT_FALSE(T_NodeType, Unsupported_node_type); };

  template <>
  struct SceneNodeCompareByLevel<SceneNode>
  {
  public:
    typedef SceneNode                value_type;

  public:
    bool
      operator()(const value_type& a_first, const value_type& a_second) const
    {
      return a_first.GetLevel() < a_second.GetLevel();
    }
  };

  template <>
  struct SceneNodeCompareByLevel<SceneNode*>
  {
  public:
    typedef SceneNode*               value_type;

  public:
    bool
      operator()(value_type a_first, value_type a_second) const
    {
      return a_first->GetLevel() < a_second->GetLevel();
    }
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // Node compare by entity pointer

  struct SceneNodeCompare
  {
  public:
    typedef SceneNode::entity_ptr             entity_ptr_type;
    typedef SceneNode::pointer                     node_ptr_type;

  public:

    SceneNodeCompare(entity_ptr_type a_entityPtr)
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

  TLOC_TYPEDEF_ALL_SMART_PTRS(SceneNode, scene_node);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(SceneNode, scene_node);
  TLOC_TYPEDEF_COMPONENT_POOL(SceneNode, scene_node);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::SceneNode);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_cs::SceneNode);

#endif