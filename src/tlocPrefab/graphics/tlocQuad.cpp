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

    typedef ComponentPoolManager    pool_mgr;
    typedef pool_mgr::iterator      comp_pool_ptr;

    // Create the quad (and the quad pool if necessary)
    comp_pool_ptr cpool;
    if (a_poolMgr.Exists(quad) == false)
    { cpool = a_poolMgr.CreateNewPool<quad_sptr>(quad); }
    else
    { cpool = a_poolMgr.GetPool(quad); }

    typedef tloc::graphics::component_system::QuadPool    quad_pool;

    quad_pool* quadPool = (*cpool)->GetAs<quad_pool>();

    quad_pool::iterator itrQuad = quadPool->GetNext();
    itrQuad->SetElement(quad_sptr(new Quad(a_rect) ));

    // Create the transform component (and the transform pool if necessary)

    if (a_poolMgr.Exists(transform) == false)
    { cpool = a_poolMgr.CreateNewPool<transform_sptr>(transform); }
    else
    { cpool = a_poolMgr.GetPool(transform); }

    typedef tloc::math_cs::TransformPool  t_pool;

    t_pool* tPool = (*cpool)->GetAs<t_pool>();

    t_pool::iterator itrTransform = tPool->GetNext();
    itrTransform->SetElement(transform_sptr(new Transform()) );

    // Create an entity from the manager and return to user
    Entity* ent = a_mgr.CreateEntity();
    a_mgr.InsertComponent(ent, &*(itrTransform->GetElement()) );
    a_mgr.InsertComponent(ent, &*(itrQuad->GetElement()) );

    return ent;
  }

};};};