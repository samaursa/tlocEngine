#ifndef _TLOC_PREFAB_MATH_TRANSFORM_H_
#define _TLOC_PREFAB_MATH_TRANSFORM_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/component_system/tlocTransform.h>

namespace tloc { namespace prefab { namespace math {

  class Transform
    : public Prefab_TI<math_cs::Transform>
  {
  public:
    typedef Prefab_TI<component_type>                     base_type;

    typedef Transform                                     this_type;
    typedef math_t::Vec3f32                               position_type;
    typedef math_t::Mat3f32                               orientation_type;

  public:
    Transform(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr   Construct() const;

    entity_ptr      Create() const;
    void            Add(entity_ptr a_ent) const;

    TLOC_DECL_PARAM_VAR(position_type, Position, m_pos);
    TLOC_DECL_PARAM_VAR(orientation_type, Orientation, m_ori);

  };

};};};

#endif