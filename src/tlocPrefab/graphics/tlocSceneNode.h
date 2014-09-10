#ifndef _TLOC_PREFAB_GRAPHICS_SCENE_NODE_H_
#define _TLOC_PREFAB_GRAPHICS_SCENE_NODE_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocSceneNode.h>

namespace tloc { namespace prefab { namespace graphics {

  class SceneNode
    : public Prefab_TI<SceneNode, gfx_cs::SceneNode>
  {
  public:
    typedef SceneNode                               this_type;
    typedef Prefab_TI<this_type, component_type>    base_type;
    typedef gfx_cs::SceneNode                       scene_node_type;
    typedef gfx_cs::scene_node_vptr                 scene_node_ptr;

    typedef math_t::Vec3f32                         position_type;
    typedef math_t::Mat3f32                         orientation_type;

  public:
    SceneNode(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr   Construct(entity_ptr a_nodeEntity) const;

    entity_ptr      Create() const;
    void            Add(entity_ptr a_ent) const;

    TLOC_DECL_PARAM_VAR(scene_node_ptr, Parent, m_parent);
    TLOC_DECL_PARAM_VAR(position_type, Position, m_pos);
    TLOC_DECL_PARAM_VAR(orientation_type, Orientation, m_ori);
  };

};};};

#endif