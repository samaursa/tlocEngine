#include "tlocCamera.h"

#include <tlocCore/component_system/tlocComponentType.h>

#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocCamera.h>

#include <tlocPrefab/math/tlocTransform.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_sptr::MakeShared;

  Camera::entity_ptr
    Camera::
    Create(dim_type a_windowDimensions)
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_windowDimensions);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Camera::
    Add(entity_ptr a_ent, dim_type a_windowDimensions)
  {
    using namespace math_t;
    using namespace math_proj;

    core_ds::Tuple2f dim = a_windowDimensions.Cast<core_ds::Tuple2f>();

    if (m_perspective)
    {
      AspectRatio ar = AspectRatio (AspectRatio::width(dim[0]), 
                                    AspectRatio::height(dim[1]));

      FOV fov(m_vertFOV, ar, p_FOV::vertical());

      FrustumPersp::Params params(fov);
      params.SetNear(m_near)
            .SetFar(m_far);

      FrustumPersp frPersp(params);
      frPersp.BuildFrustum();

      Add(a_ent, frPersp);
    }
    else
    {
      Rectf_c fRect =
        Rectf_c(Rectf_c::width(dim[0]), Rectf_c::height(dim[1]));

      FrustumOrtho frOrtho = FrustumOrtho(fRect, m_near, m_far);
      frOrtho.BuildFrustum();

      Add(a_ent, frOrtho);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Camera::entity_ptr
    Camera::
    Create(const frustum_type& a_frustum)
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_frustum);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Camera::
    Add(entity_ptr a_ent, const frustum_type& a_frustum)
  {
    using math_cs::components::transform;
    using gfx_cs::components::camera;

    using namespace core_cs;
    using namespace math_cs;
    using namespace gfx_cs;

    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Position(m_position).Add(a_ent); }

    // -----------------------------------------------------------------------
    // camera component

    typedef ComponentPoolManager                    pool_mgr;
    typedef gfx_cs::camera_pool                     p_pool;
    camera_pool_vptr  pPool
      = m_compPoolMgr->GetOrCreatePool<gfx_cs::Camera>();

    p_pool::iterator itrProjection = pPool->GetNext();
    (*itrProjection)->SetValue(MakeShared<gfx_cs::Camera>(a_frustum) );

    m_entMgr->InsertComponent(a_ent, *(*itrProjection)->GetValuePtr() );
  }

};};};