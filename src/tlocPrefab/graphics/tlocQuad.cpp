#include "tlocQuad.h"

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocQuad.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

  using tloc::graphics::component_system::Quad;
  using tloc::graphics::component_system::quad_sptr;

  using math_t::Rectangle_T;
  using math_cs::Transform;
  using math_cs::transform_sptr;

  core_cs::Entity*
    CreateQuad(core_cs::EntityManager& a_mgr,
               core_cs::ComponentPoolManager& a_poolMgr,
               const math_t::Rectf32& a_rect)
  {
    using namespace tloc::graphics::component_system::components;
    using namespace tloc::math_cs::components;

    typedef ComponentPoolManager      pool_mgr;
    typedef gfx_cs::quad_sptr_pool    quad_pool;

    gfx_cs::quad_sptr_pool_sptr       quadPool;

    // Create the quad (and the quad pool if necessary)
    if (a_poolMgr.Exists(quad) == false)
    { quadPool = a_poolMgr.CreateNewPool<quad_sptr>(); }
    else
    { quadPool = a_poolMgr.GetPool<quad_sptr>(); }

    quad_pool::iterator itrQuad = quadPool->GetNext();
    itrQuad->SetValue(quad_sptr(new Quad(a_rect) ));

    // Create the transform component (and the transform pool if necessary)
    typedef math_cs::transform_f32_sptr_pool  t_pool;
    math_cs::transform_f32_sptr_pool_sptr     tPool;

    if (a_poolMgr.Exists(transform) == false)
    { tPool = a_poolMgr.CreateNewPool<transform_sptr>(); }
    else
    { tPool = a_poolMgr.GetPool<transform_sptr>(); }

    t_pool::iterator itrTransform = tPool->GetNext();
    itrTransform->SetValue(transform_sptr(new Transform()) );

    // Create an entity from the manager and return to user
    Entity* ent = a_mgr.CreateEntity();
    a_mgr.InsertComponent(ent, &*(itrTransform->GetValue()) );
    a_mgr.InsertComponent(ent, &*(itrQuad->GetValue()) );

    return ent;
  }

};};};