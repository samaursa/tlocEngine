#include "tlocCamera.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocProjectionComponent.h>

namespace tloc { namespace prefab { namespace graphics {
  core_cs::Entity*
    CreateCamera(core_cs::EntityManager& a_mgr,
                 core_cs::ComponentPoolManager& a_poolMgr,
                 const math_proj::frustum_f32& a_frustum,
                 const math_t::Vec3f32 a_pos)
  {
    using math_cs::components::transform;
    using tloc::math_cs::components::projection;

    using namespace core_cs;
    using namespace math_cs;
    using namespace tloc::graphics::component_system;

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

    typedef tloc::math_cs::projection_sptr_pool   p_pool;

    projection_sptr_pool_sptr pPool;

    // Get or create the projection pool
    if (a_poolMgr.Exists(projection) == false)
    { pPool = a_poolMgr.CreateNewPool<projection_sptr>(); }
    else
    { pPool = a_poolMgr.GetPool<projection_sptr>(); }

    p_pool::iterator itrProjection = pPool->GetNext();
    itrProjection->SetValue(projection_sptr(new Projection(a_frustum)) );

    // Create an entity from the manager and return to user
    Entity* ent = a_mgr.CreateEntity();
    a_mgr.InsertComponent(ent, &*(itrTransform->GetValue()) );
    a_mgr.InsertComponent(ent, &*(itrProjection->GetValue()) );

    return ent;
  }

};};};