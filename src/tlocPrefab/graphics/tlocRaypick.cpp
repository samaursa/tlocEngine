#include "tlocRaypick.h"

#include <tlocCore/component_system/tlocComponentType.h>

#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/component_system/tlocRaypick.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_sptr::MakeShared;

  // ///////////////////////////////////////////////////////////////////////
  // Raypick

  Raypick::
    Raypick(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr)
    : base_type(a_entMgr, a_poolMgr)
    , m_distanceChecked(true)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Raypick::
    Construct() -> component_ptr
  {
    using namespace core_cs;
    using namespace gfx_cs;

    typedef ComponentPoolManager                    pool_mgr;
    typedef gfx_cs::raypick_pool                    p_pool;

    auto pPool = m_compPoolMgr->GetOrCreatePool<gfx_cs::Raypick>();

    auto itr = pPool->GetNext();
    (*itr)->SetValue(MakeShared<gfx_cs::Raypick>());

    return *(*itr)->GetValuePtr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Raypick::
    Create() -> entity_ptr
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Raypick::
    Add(entity_ptr a_ent)
  {
    // -----------------------------------------------------------------------
    // camera component

    m_entMgr->InsertComponent(insert_params(a_ent, Construct())
                              .DispatchTo(GetListeners()) );
  }

};};};