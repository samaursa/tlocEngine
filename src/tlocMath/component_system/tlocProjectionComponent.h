#ifndef _TLOC_MATH_COMPONENT_SYSTEM_PROJECTION_COMPONENT_H_
#define _TLOC_MATH_COMPONENT_SYSTEM_PROJECTION_COMPONENT_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocMath/projection/tlocFrustum.h>
#include <tlocMath/component_system/tlocComponentType.h>

namespace tloc { namespace math { namespace component_system {

  class Projection
    : public core_cs::Component_T<Projection, 
                                  core_cs::component_group::k_math, 
                                  components::k_projection>
  {
  public:
    typedef core::component_system::Component_T
      <Projection, k_component_group, k_component_type>   base_type;

    typedef proj::frustum_f32                             frustum_type;

  public:
    Projection();
    explicit Projection(const frustum_type& a_frustum);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(frustum_type, GetFrustumRef, m_frustum);
    TLOC_DECL_AND_DEF_SETTER(frustum_type, SetFrustum, m_frustum);

  private:
    frustum_type  m_frustum;
  };

  //------------------------------------------------------------------------
  // Typedefs

  TLOC_TYPEDEF_SHARED_PTR(Projection, projection);
  TLOC_TYPEDEF_COMPONENT_POOL(projection_sptr, projection_sptr);

};};};

#endif