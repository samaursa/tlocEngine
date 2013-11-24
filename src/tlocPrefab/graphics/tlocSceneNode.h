#ifndef _TLOC_PREFAB_GRAPHICS_SCENE_NODE_H_
#define _TLOC_PREFAB_GRAPHICS_SCENE_NODE_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocSceneNode.h>

namespace tloc { namespace prefab { namespace graphics {

  class SceneNode
    : public Prefab_I
  {
  public:
    typedef SceneNode                     this_type;
    typedef gfx_cs::SceneNode             scene_node_type;
    typedef gfx_cs::SceneNode*            scene_node_ptr_type;

  public:
    SceneNode(core_cs::EntityManager* a_entMgr,
              core_cs::ComponentPoolManager* a_poolMgr)
              : Prefab_I(a_entMgr, a_poolMgr)
              , m_parent(nullptr)
    { }

    entity_type* Create();
    this_type&   Add(entity_type* a_ent);

    TLOC_DECL_PARAM_VAR(scene_node_ptr_type, Parent, m_parent);
  };

};};};

#endif