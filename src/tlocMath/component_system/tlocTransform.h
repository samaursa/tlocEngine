#ifndef _TLOC_CORE_COMPONENT_SYSTEM_TRANSFORM_H_
#define _TLOC_CORE_COMPONENT_SYSTEM_TRANSFORM_H_

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocMath/vector/tlocVector3.h>
#include <tlocMath/matrix/tlocMatrix3.h>
#include <tlocMath/matrix/tlocMatrix4.h>

namespace tloc { namespace math { namespace component_system {

  template <typename T_Real>
  class Transform_T
    : public core::component_system::Component_T<Transform_T<T_Real> >
  {
  public:
    typedef T_Real                    real_type;
    typedef Transform_T<real_type>    this_type;

    typedef Matrix4<real_type>        transform_type;
    typedef Vector3<T_Real>           position_type;
    typedef Matrix3<T_Real>           orientation_type;

    typedef core::component_system::Component_T<this_type>    base_type;

  public:
    Transform_T();

    position_type     GetPosition() const;
    orientation_type  GetOrientation() const;

    void              SetPosition(const position_type& a_pos);
    void              SetOrientation(const orientation_type& a_ori);

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

};};};

#endif