#include "tlocTransform.h"

#include <tlocCore/smart_ptr/tlocSmartPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

#include <tlocMath/vector/tlocVector4.h>
#include <tlocMath/component_system/tlocComponentType.h>

namespace tloc { namespace math { namespace component_system {

#define TRANSFORM_TEMPS   typename T_Real
#define TRANSFORM_PARAMS  T_Real
#define TRANSFORM_TYPE    typename Transform_T<TRANSFORM_PARAMS>

  template <TRANSFORM_TEMPS>
  Transform_T<TRANSFORM_PARAMS>::Transform_T()
    : base_type(components::transform)
    , m_transformation(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1)
  { }

  template <TRANSFORM_TEMPS>
  TRANSFORM_TYPE::position_type
    Transform_T<TRANSFORM_PARAMS>::GetPosition() const
  {
    position_type       pos3;
    Vector4<real_type>  pos4;

    m_transformation.GetCol(3, pos4);
    pos3.ConvertFrom(pos4);

    return pos3;
  }

  template <TRANSFORM_TEMPS>
  TRANSFORM_TYPE::orientation_type
    Transform_T<TRANSFORM_PARAMS>::GetOrientation() const
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

  template Transform_T<f32>;
  template Transform_T<f64>;

  // SmartPtr
  template core::smart_ptr::SharedPtr<Transform_T<f32> >;
  template core::smart_ptr::SharedPtr<Transform_T<f64> >;

  // Pool
  template core::component_system::ComponentPool_TI<TransformPtr>;
  template core::component_system::ComponentPool_TI<TransformPtr32>;
  template core::component_system::ComponentPool_TI<TransformPtr64>;

};};};