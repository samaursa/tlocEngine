#include "tlocTransform.h"

#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>

namespace tloc { namespace prefab { namespace math {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;
  using core_sptr::MakeShared;

  using namespace core_cs;
  using namespace math_cs;
  using namespace math_cs::components;

  Transform::
    Transform(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr)
    : Prefab_I(a_entMgr, a_poolMgr)
    , m_pos(0)
    , m_ori(orientation_type::IDENTITY)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Transform::entity_ptr
    Transform::
    Create()
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }
  
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Transform::
    Add(entity_ptr a_ent)
  {
    typedef ComponentPoolManager    pool_mgr;

    typedef math_cs::transform_f32_pool         t_pool;

    math_cs::transform_pool_vptr tPool
      = m_compPoolMgr->GetOrCreatePool<math_cs::Transform>();

    t_pool::iterator itrTransform = tPool->GetNext();
    (*itrTransform)->SetValue(MakeShared<math_cs::Transform>(m_pos, m_ori));

    // Create an entity from the manager and return to user
    // Transform components don't have a system - known as orphan components
    m_entMgr->InsertComponent(a_ent, *(*itrTransform)->GetValuePtr(), 
                              EntityManager::orphan(true));
  }

};};};