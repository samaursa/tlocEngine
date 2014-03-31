#ifndef _TLOC_PREFAB_GRAPHICS_CAMERA_H_
#define _TLOC_PREFAB_GRAPHICS_CAMERA_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocMath/projection/tlocFrustum.h>
#include <tlocMath/types/tlocVector3.h>

namespace tloc { namespace prefab { namespace graphics {

  class Camera
    : public Prefab_I
  {
  public:
    typedef Camera                                      this_type;
    typedef math_proj::frustum_f32                      frustum_type;
    typedef math_t::Vec3f32                             vec_type;

  public:
    Camera(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr)
      : Prefab_I(a_entMgr, a_poolMgr)
    { }

    entity_ptr   Create(const frustum_type& a_frustum,
                        const vec_type& a_position);
    void         Add(entity_ptr a_ent,
                     const frustum_type& a_frustum,
                     const vec_type& a_position);

  };

};};};

#endif