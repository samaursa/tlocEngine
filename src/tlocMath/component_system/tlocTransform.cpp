#include "tlocTransform.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

#include <tlocMath/types/tlocVector4.h>

namespace tloc { namespace math { namespace component_system {

#define TRANSFORM_TEMPS   typename T_Real
#define TRANSFORM_PARAMS  T_Real
#define TRANSFORM_TYPE    typename Transform_T<TRANSFORM_PARAMS>

  using types::Vector4;

  template <TRANSFORM_TEMPS>
  Transform_T<TRANSFORM_PARAMS>::
    Transform_T()
    : base_type(k_component_type)
    , m_transformation(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1)
  { }

  template <TRANSFORM_TEMPS>
  Transform_T<TRANSFORM_PARAMS>::
    Transform_T(const position_type& a_position)
    : base_type(k_component_type)
    , m_transformation(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1)
  {
    SetPosition(a_position);
  }

  template <TRANSFORM_TEMPS>
  Transform_T<TRANSFORM_PARAMS>::
    Transform_T(const position_type& a_position,
                const orientation_type& a_orientation)
    : base_type(k_component_type)
    , m_transformation(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1)
  {
    SetPosition(a_position);
    SetOrientation(a_orientation);
  }

  template <TRANSFORM_TEMPS>
  TRANSFORM_TYPE::position_type
    Transform_T<TRANSFORM_PARAMS>::
    GetPosition() const
  {
    position_type       pos3;
    Vector4<real_type>  pos4;

    m_transformation.GetCol(3, pos4);
    pos3.ConvertFrom(pos4);

    return pos3;
  }

  template <TRANSFORM_TEMPS>
  TRANSFORM_TYPE::orientation_type
    Transform_T<TRANSFORM_PARAMS>::
    GetOrientation() const
  {
    orientation_type
      ori3(m_transformation[0], m_transformation[4], m_transformation[8],
           m_transformation[1], m_transformation[5], m_transformation[9],
           m_transformation[2], m_transformation[6], m_transformation[10]);

    return ori3;
  }

  template <TRANSFORM_TEMPS>
  void Transform_T<TRANSFORM_PARAMS>
    ::SetPosition(const position_type& a_pos)
  {
    m_transformation[12] = a_pos[0];
    m_transformation[13] = a_pos[1];
    m_transformation[14] = a_pos[2];
  }

  template <TRANSFORM_TEMPS>
  void Transform_T<TRANSFORM_PARAMS>
    ::SetOrientation(const orientation_type& a_ori)
  {
    m_transformation[0] = a_ori[0];
    m_transformation[1] = a_ori[1];
    m_transformation[2] = a_ori[2];

    m_transformation[4]	= a_ori[3];
    m_transformation[5]	= a_ori[4];
    m_transformation[6]	= a_ori[5];

    m_transformation[8]	 = a_ori[6];
    m_transformation[9]	 = a_ori[7];
    m_transformation[10] = a_ori[8];
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template class Transform_T<f32>;
  template class Transform_T<f64>;

  // SmartPtr
  template class core::smart_ptr::SharedPtr<Transform_T<f32> >;
  template class core::smart_ptr::SharedPtr<Transform_T<f64> >;

  // Pool
  template class core::component_system::ComponentPool_TI<TransformPtr32>;
  template class core::component_system::ComponentPool_TI<TransformPtr64>;

};};};