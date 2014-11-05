#ifndef _TLOC_CORE_COMPONENT_SYSTEM_TRANSFORM_H_
#define _TLOC_CORE_COMPONENT_SYSTEM_TRANSFORM_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>
#include <tlocMath/component_system/tlocComponentType.h>

namespace tloc { namespace math { namespace component_system {

  template <typename T_Real>
  class Transform_T
    : public core_cs::Component_T<Transform_T<T_Real>, 
                                  core_cs::component_group::k_math, 
                                  components::k_transform>
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
    typedef T_Real                                      real_type;
    typedef Transform_T<real_type>                      this_type;
    typedef core_cs::Component_T
      <this_type, core_cs::component_group::k_math,
                  components::k_transform>              base_type;

    typedef types::Matrix_T<real_type, 4>       transform_type;
    typedef types::Vector_T<real_type, 3>       position_type;
    typedef types::Vector_T<real_type, 3>       scale_type;
    typedef types::Vector_T<real_type, 3>       pivot_type;
    typedef types::Matrix_T<real_type, 3>       orientation_type;

  public:
    Transform_T();
    explicit Transform_T
      (const position_type& a_position,
       const orientation_type& a_orientation = orientation_type::IDENTITY);
    explicit Transform_T (const transform_type& a_tr);

    position_type     GetPosition() const;
    orientation_type  GetOrientation() const;
    transform_type    GetTransformation() const;

    void              SetPosition(const position_type& a_pos);
    void              SetOrientation(const orientation_type& a_ori);
    void              SetTransformation(const transform_type& a_tr,
                                        const scale_type& a_scale =
                                        scale_type::ONE);

    this_type         Invert() const;
    void              LookAt(position_type a_target);

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

  TLOC_TYPEDEF_ALL_SMART_PTRS(Transform, transform);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Transformf32, transform_f32);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Transformf64, transform_f64);

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Transform, transform);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Transformf32, transform_f32);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Transformf64, transform_f64);

  TLOC_TYPEDEF_COMPONENT_POOL(Transformf32, transform);
  TLOC_TYPEDEF_COMPONENT_POOL(Transformf32, transform_f32);
  TLOC_TYPEDEF_COMPONENT_POOL(Transformf64, transform_f64);

};};};

#endif