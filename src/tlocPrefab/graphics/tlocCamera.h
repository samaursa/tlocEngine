#ifndef _TLOC_PREFAB_GRAPHICS_CAMERA_H_
#define _TLOC_PREFAB_GRAPHICS_CAMERA_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocMath/projection/tlocFrustum.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocAngle.h>

namespace tloc { namespace prefab { namespace graphics {

  // ///////////////////////////////////////////////////////////////////////
  // Camera

  class Camera
    : public Prefab_I
  {
  public:
    typedef Camera                                      this_type;
    typedef math_proj::frustum_f32                      frustum_type;
    typedef tl_float                                    real_type;
    typedef math_t::Vec3f32                             vec_type;
    typedef core_ds::Tuple2size                         dim_type;
    typedef math_t::Degree                              angle_type;

  public:
    Camera(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr)
      : Prefab_I(a_entMgr, a_poolMgr)
      , m_near(5.0f)
      , m_far(100.0f)
      , m_vertFOV(60.0f)
      , m_perspective(true)
    { }

    entity_ptr   Create(dim_type a_windowDimensions);
    void         Add   (entity_ptr a_ent, 
                        dim_type a_windowDimensions);

    entity_ptr   Create(const frustum_type& a_frustum);
    void         Add   (entity_ptr a_ent, 
                        const frustum_type& a_frustum);

    TLOC_DECL_PARAM_VAR(vec_type, Position, m_position);
    TLOC_DECL_PARAM_VAR(real_type, Near, m_near);
    TLOC_DECL_PARAM_VAR(real_type, Far, m_far);
    TLOC_DECL_PARAM_VAR(angle_type, VerticalFOV, m_vertFOV);
    TLOC_DECL_PARAM_VAR(bool, Perspective, m_perspective);
  };

};};};

#endif