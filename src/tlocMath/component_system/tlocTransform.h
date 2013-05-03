#ifndef _TLOC_CORE_COMPONENT_SYSTEM_TRANSFORM_H_
#define _TLOC_CORE_COMPONENT_SYSTEM_TRANSFORM_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>
#include <tlocMath/component_system/tlocComponentType.h>

namespace tloc { namespace math { namespace component_system {

  template <typename T_Real>
  class Transform_T
    : public core::component_system::Component_T<Transform_T<T_Real>,
                                                 components::transform>
  {
  public:
    typedef T_Real                    real_type;
    typedef Transform_T<real_type>    this_type;

    typedef types::Matrix4<real_type> transform_type;
    typedef types::Vector3<real_type> position_type;
    typedef types::Matrix3<real_type> orientation_type;

    typedef core::component_system::Component_T
      <this_type, components::transform>    base_type;

  public:
    Transform_T();
    explicit Transform_T(const position_type& a_position);
    explicit Transform_T(const position_type& a_position,
                         const orientation_type& a_orientation);

    position_type     GetPosition() const;
    orientation_type  GetOrientation() const;

    void              SetPosition(const position_type& a_pos);
    void              SetOrientation(const orientation_type& a_ori);

    this_type         Invert() const;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (transform_type, GetTransformation, m_transformation);

  private:
    transform_type    m_transformation;
  };

  //------------------------------------------------------------------------
  // Typedefs

  typedef Transform_T<tl_float>   Transform;
  typedef Transform_T<f32>        Transformf32;
  typedef Transform_T<f64>        Transformf64;

  TLOC_TYPEDEF_SHARED_PTR(Transform, transform);
  TLOC_TYPEDEF_SHARED_PTR(Transform, transform_f32);
  TLOC_TYPEDEF_SHARED_PTR(Transform, transform_f64);

  typedef core::component_system::
          ComponentPool_TI<transform_sptr>              TransformPool;
  typedef core::component_system::
          ComponentPool_TI<transform_f32_sptr>          TransformPool32;
  typedef core::component_system::
          ComponentPool_TI<transform_f64_sptr>          TransformPool64;

};};};

#endif