#include "tlocCamera.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/component_system/tlocCamera.h>

namespace tloc { namespace prefab { namespace graphics {
  core_cs::Entity*
    CreateCamera(core_cs::EntityManager& a_mgr,
                 core_cs::ComponentPoolManager& a_poolMgr,
                 const math_proj::frustum_f32& a_frustum,
                 const math_t::Vec3f32 a_pos)
  {
    using math_cs::components::transform;
    using gfx_cs::components::camera;

    using namespace core_cs;
    using namespace math_cs;
    using namespace gfx_cs;

    typedef ComponentPoolManager                    pool_mgr;
    typedef tloc::math_cs::transform_f32_sptr_pool  t_pool;

    transform_f32_sptr_pool_sptr                    tPool;

    // Get or create the transform pool
    if (a_poolMgr.Exists(transform) == false)
    { tPool = a_poolMgr.CreateNewPool<transform_sptr>(); }
    else
    { tPool = a_poolMgr.GetPool<transform_sptr>(); }


    t_pool::iterator itrTransform = tPool->GetNext();
    itrTransform->SetValue(transform_f32_sptr(new Transformf32(a_pos)) );

    typedef gfx_cs::camera_sptr_pool   p_pool;

    camera_sptr_pool_sptr pPool;

    // Get or create the projection pool
    if (a_poolMgr.Exists(camera) == false)
    { pPool = a_poolMgr.CreateNewPool<camera_sptr>(); }
    else
    { pPool = a_poolMgr.GetPool<camera_sptr>(); }

    p_pool::iterator itrProjection = pPool->GetNext();
    itrProjection->SetValue(camera_sptr(new Camera(a_frustum)) );

    // Create an entity from the manager and return to user
    Entity* ent = a_mgr.CreateEntity();
    a_mgr.InsertComponent(ent, &*(itrTransform->GetValue()) );
    a_mgr.InsertComponent(ent, &*(itrProjection->GetValue()) );

    return ent;
  }

};};};