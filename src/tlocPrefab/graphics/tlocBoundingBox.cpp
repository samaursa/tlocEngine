#include "tlocBoundingBox.h"

#include <tlocCore/component_system/tlocComponentPoolManager.h>

namespace tloc { namespace prefab { namespace graphics {

  // ///////////////////////////////////////////////////////////////////////
  // BoundingBox2D

  BoundingBox2D::
    BoundingBox2D(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr)
    : base_type(a_entMgr, a_poolMgr)
    , m_circular(false)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    BoundingBox2D::
    Construct() -> component_ptr
  {
    using namespace core_cs;
    using namespace gfx_cs;

    typedef ComponentPoolManager                pool_mgr;
    typedef bounding_box_2d_pool                p_pool;

    auto pPool = m_compPoolMgr->GetOrCreatePool<component_type>();

    auto itr = pPool->GetNext();

    if (m_circular)
    { 
      auto circBoundsType = component_type::circular_bounds_type();
      ( *itr )->SetValue(core_sptr::MakeShared<component_type>(circBoundsType));
    }
    else
    { ( *itr )->SetValue(core_sptr::MakeShared<component_type>()); }

    return *(*itr)->GetValuePtr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    BoundingBox2D::
    Create() -> entity_ptr
  {
    auto ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    BoundingBox2D::
    Add(entity_ptr a_ent)
  {
    m_entMgr->InsertComponent
      (insert_params(a_ent, Construct()).DispatchTo(GetListeners()) );
  }

  // ///////////////////////////////////////////////////////////////////////
  // BoundingBox3D

  BoundingBox3D::
    BoundingBox3D(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr)
    : base_type(a_entMgr, a_poolMgr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    BoundingBox3D::
    Construct() -> component_ptr
  {
    using namespace core_cs;
    using namespace gfx_cs;

    typedef ComponentPoolManager                pool_mgr;
    typedef bounding_box_3d_pool                p_pool;

    auto pPool = m_compPoolMgr->GetOrCreatePool<component_type>();

    auto itr = pPool->GetNext();
    (*itr)->SetValue(core_sptr::MakeShared<component_type>());

    return *(*itr)->GetValuePtr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    BoundingBox3D::
    Create() -> entity_ptr
  {
    auto ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    BoundingBox3D::
    Add(entity_ptr a_ent)
  {
    m_entMgr->InsertComponent
      (insert_params(a_ent, Construct()).DispatchTo(GetListeners()) );
  }

};};};