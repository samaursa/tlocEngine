#ifndef _TLOC_PREFAB_CORE_USER_DATA_H_
#define _TLOC_PREFAB_CORE_USER_DATA_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocUserData.h>

namespace tloc { namespace prefab { namespace core {

  class UserData
    : public Prefab_TI<UserData, core_cs::UserData>
  {
  public:
    typedef UserData                                      this_type;
    typedef Prefab_TI<this_type, component_type>          base_type;

    typedef component_type::any_type                      any_type;

  public:
    UserData(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr   Construct() const;

    entity_ptr      Create() const;
    void            Add(entity_ptr a_ent) const;

    TLOC_DECL_PARAM_VAR(any_type, Data, m_data);
  };

};};};

#endif