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

    typedef ComponentPoolManager    pool_mgr;
    typedef pool_mgr::iterator      comp_pool_ptr;

    comp_pool_ptr cpool;

    // Get or create the transform pool
    if (a_poolMgr.Exists(transform) == false)
    { cpool = a_poolMgr.CreateNewPool<TransformPtr>(transform); }
    else
    { cpool = a_poolMgr.GetPool(transform); }

    typedef tloc::math_cs::TransformPool  t_pool;

    t_pool* tPool = (*cpool)->GetAs<t_pool>();

    t_pool::iterator itrTransform = tPool->GetNext();
    itrTransform->GetElement() = TransformPtr32(new Transformf32(a_pos));

    // Get or create the projection pool
    if (a_poolMgr.Exists(projection) == false)
    { cpool = a_poolMgr.CreateNewPool<ProjectionPtr>(projection); }
    else
    { cpool = a_poolMgr.GetPool(projection); }

    typedef tloc::math_cs::ProjectionPool p_pool;

    p_pool* pPool = (*cpool)->GetAs<p_pool>();

    p_pool::iterator itrProjection = pPool->GetNext();
    itrProjection->GetElement() = ProjectionPtr(new Projection(a_frustum));

    // Create an entity from the manager and return to user
    Entity* ent = a_mgr.CreateEntity();
    a_mgr.InsertComponent(ent, &*(itrTransform->GetElement()) );
    a_mgr.InsertComponent(ent, &*(itrProjection->GetElement()) );

    return ent;
  }

};};};