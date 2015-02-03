#include "tlocUserData.h"

#include <tlocCore/component_system/tlocComponentType.h>

namespace tloc { namespace prefab { namespace core {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;
  using core_sptr::MakeShared;

  using namespace core_cs;
  using namespace core_cs::components;

  UserData::
    UserData(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr)
    : base_type(a_entMgr, a_poolMgr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    UserData::
    Construct() const -> component_ptr
  {
    typedef ComponentPoolManager    pool_mgr;

    auto pool = m_compPoolMgr->GetOrCreatePool<core_cs::UserData>();

    auto itr = pool->GetNext();
    (*itr)->SetValue(MakeShared<core_cs::UserData>(m_data));
    
    return *(*itr)->GetValuePtr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    UserData::
    Create() const -> entity_ptr
  {
    auto ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }
  
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    UserData::
    Add(entity_ptr a_ent) const
  {
    // Create an entity from the manager and return to user
    // Transform components don't have a system - known as orphan components
    m_entMgr->InsertComponent(insert_params(a_ent, Construct())
                              .DispatchTo(GetListeners()).Orphan(true));
  }

};};};