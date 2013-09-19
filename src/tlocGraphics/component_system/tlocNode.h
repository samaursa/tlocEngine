#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_NODE_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_NODE_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocMath/component_system/tlocTransform.h>

namespace tloc { namespace graphics { namespace component_system {

  class Node
    : public core_cs::Component_T<Node, components::node>
  {
  public:
    typedef core_cs::Component_T<Node, components::node>  base_type;

    typedef Node                                          this_type;
    typedef this_type*                                    pointer;
    typedef this_type&                                    reference;

    typedef core_conts::tl_array<pointer>::type   node_cont_type;
    typedef node_cont_type::iterator              node_cont_iterator;
    typedef node_cont_type::const_iterator        node_cont_const_iterator;

    typedef math_cs::Transformf32                 transform_type;

  public:
    Node();

    TLOC_DECL_AND_DEF_SETTER(transform_type, SetLocalTransform, m_localTransform);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (transform_type, GetLocalTransform, m_localTransform);

  private:
    this_type*      m_parent;
    node_cont_type  m_children;

    transform_type  m_localTransform;

  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(Node, node);
  TLOC_TYPEDEF_COMPONENT_POOL(node_sptr, node_sptr);

};};};

#endif