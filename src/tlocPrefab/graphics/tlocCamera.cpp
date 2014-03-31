#include "tlocCamera.h"

#include <tlocCore/component_system/tlocComponentType.h>

#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocCamera.h>

namespace tloc { namespace prefab { namespace graphics {

  Camera::entity_ptr
    Camera::
    Create(const frustum_type& a_frustum, const vec_type& a_position)
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_frustum, a_position);

    return ent;
  }

  void
    Camera::
    Add(entity_ptr a_ent, const frustum_type& a_frustum,
        const vec_type& a_position)
  {
    using math_cs::components::transform;
    using gfx_cs::components::camera;

    using namespace core_cs;
    using namespace math_cs;
    using namespace gfx_cs;

    typedef ComponentPoolManager                    pool_mgr;
    typedef tloc::math_cs::transform_f32_pool       t_pool;

    transform_f32_pool_vptr                         tPool;

    // Get or create the transform pool
    if (m_compPoolMgr->Exists(transform) == false)
    { tPool = m_compPoolMgr->CreateNewPool<math_cs::Transformf32>(); }
    else
    { tPool = m_compPoolMgr->GetPool<math_cs::Transformf32>(); }


    t_pool::iterator itrTransform = tPool->GetNext();
    (*itrTransform)->SetValue(Transformf32(a_position) );

    typedef gfx_cs::camera_pool                     p_pool;

    camera_pool_vptr                                pPool;

    // Get or create the projection pool
    if (m_compPoolMgr->Exists(camera) == false)
    { pPool = m_compPoolMgr->CreateNewPool<gfx_cs::Camera>(); }
    else
    { pPool = m_compPoolMgr->GetPool<gfx_cs::Camera>(); }

    p_pool::iterator itrProjection = pPool->GetNext();
    (*itrProjection)->SetValue(gfx_cs::Camera(a_frustum) );

    // Create an entity from the manager and return to user
    m_entMgr->InsertComponent(a_ent, (*itrTransform)->GetValue() );
    m_entMgr->InsertComponent(a_ent, (*itrProjection)->GetValue() );
  }

};};};