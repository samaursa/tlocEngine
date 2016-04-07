#include "tlocSkyBox.h"

#include <tlocCore/component_system/tlocComponentType.h>

#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocPrefab/math/tlocTransform.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_sptr::MakeShared;

  // ///////////////////////////////////////////////////////////////////////
  // Camera

  SkyBox::
    SkyBox(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : base_type(a_entMgr, a_poolMgr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    SkyBox::
    Construct(tex_obj_type a_cubeMap) ->component_ptr
  {
    using namespace core_cs;
    using namespace gfx_cs;

    typedef ComponentPoolManager                    pool_mgr;
    typedef gfx_cs::skybox_pool                     p_pool;

    auto pPool = m_compPoolMgr->GetOrCreatePool<gfx_cs::SkyBox>();

    auto itr = pPool->GetNext();
    (*itr)->SetValue(MakeShared<gfx_cs::SkyBox>(a_cubeMap) );

    return *(*itr)->GetValuePtr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    SkyBox::
    Create(tex_obj_type a_cubeMap) -> entity_ptr
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_cubeMap);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SkyBox::
    Add(entity_ptr a_ent, tex_obj_type a_cubeMap)
  {
    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // camera component

    m_entMgr->InsertComponent(insert_params(a_ent, Construct(a_cubeMap))
                              .DispatchTo(GetListeners()));
  }

};};};