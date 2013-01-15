#include "tlocQuad.h"

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocQuad.h>

namespace tloc { namespace prefab { namespace graphics {

  using core::component_system::Entity;
  using core::component_system::EntityManager;
  using core::component_system::ComponentPoolManager;

  using tloc::graphics::component_system::Quad;
  using tloc::graphics::component_system::QuadPtr;

  using math::types::Rectangle;
  using math::component_system::Transform;
  using math::component_system::TransformPtr;

  template <typename T_Real>
  core::component_system::Entity*
    CreateQuad(core::component_system::EntityManager& a_mgr,
               core::component_system::ComponentPoolManager& a_poolMgr,
               math::types::Rectangle<T_Real> a_rect)
  {
    using namespace tloc::graphics::component_system::components;
    using namespace tloc::math::component_system::components;

    typedef ComponentPoolManager    pool_mgr;
    typedef pool_mgr::iterator      comp_pool_ptr;

    // Create the quad (and the quad pool if necessary)
    comp_pool_ptr cpool;
    if (a_poolMgr.Exists(quad) == false)
    { cpool = a_poolMgr.CreateNewPool<QuadPtr>(quad); }
    else
    { cpool = a_poolMgr.GetPool(quad); }

    typedef tloc::graphics::component_system::QuadPool    quad_pool;

    quad_pool* quadPool = (*cpool)->GetAs<quad_pool>();

    quad_pool::iterator itrQuad = quadPool->GetNext();
    itrQuad->GetElement() = QuadPtr(new Quad(a_rect) );

    // Create the transform component (and the transform pool if necessary)
    cpool;

    if (a_poolMgr.Exists(transform) == false)
    { cpool = a_poolMgr.CreateNewPool<TransformPtr>(transform); }
    else
    { cpool = a_poolMgr.GetPool(transform); }

    typedef tloc::math::component_system::TransformPool  t_pool;

    t_pool* tPool = (*cpool)->GetAs<t_pool>();

    t_pool::iterator itrTransform = tPool->GetNext();
    itrTransform->GetElement() = TransformPtr(new Transform());

    // Create an entity from the manager and return to user
    Entity* ent = a_mgr.CreateEntity();
    a_mgr.InsertComponent(ent, &*(itrTransform->GetElement()) );
    a_mgr.InsertComponent(ent, &*(itrQuad->GetElement()) );

    return ent;
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit Instantiations

  template Entity* CreateQuad<f32>(EntityManager&, ComponentPoolManager&,
                                   Rectangle<f32>);

};};};