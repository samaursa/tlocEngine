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
    enum pivot
    {
      k_pivot_center = 0,
      k_pivot_bottom,
      k_pivot_top,
      k_pivot_left,
      k_pivot_right,
      k_pivot_bottom_left,
      k_pivot_bottom_right,
      k_pivot_top_left,
      k_pivot_top_right,
    };

  public:
    typedef T_Real                    real_type;
    typedef Transform_T<real_type>    this_type;

    typedef types::Matrix4<real_type> transform_type;
    typedef types::Vector3<real_type> position_type;
    typedef types::Vector3<real_type> scale_type;
    typedef types::Vector3<real_type> pivot_type;
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
    transform_type    GetTransformation() const;

    void              SetPosition(const position_type& a_pos);
    void              SetOrientation(const orientation_type& a_ori);

    this_type         Invert() const;

    TLOC_DECL_AND_DEF_GETTER(scale_type, GetScale, m_scale);
    TLOC_DECL_AND_DEF_SETTER(scale_type, SetScale, m_scale);

  private:
    transform_type    m_transformation;
    scale_type        m_scale;
  };

  //------------------------------------------------------------------------
  // Typedefs

  typedef Transform_T<tl_float>   Transform;
  typedef Transform_T<f32>        Transformf32;
  typedef Transform_T<f64>        Transformf64;

  TLOC_TYPEDEF_SHARED_PTR(Transform, transform);
  TLOC_TYPEDEF_SHARED_PTR(Transformf32, transform_f32);
  TLOC_TYPEDEF_SHARED_PTR(Transformf64, transform_f64);

  TLOC_TYPEDEF_COMPONENT_POOL(transform_sptr, transform_sptr);
  TLOC_TYPEDEF_COMPONENT_POOL(transform_f32_sptr, transform_f32_sptr);
  TLOC_TYPEDEF_COMPONENT_POOL(transform_f64_sptr, transform_f64_sptr);

};};};

#endif