#include "tlocTransform.h"

#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

#include <tlocMath/types/tlocVector4.h>

namespace tloc { namespace math { namespace component_system {

#define TRANSFORM_TEMPS   typename T_Real
#define TRANSFORM_PARAMS  T_Real
#define TRANSFORM_TYPE    typename Transform_T<TRANSFORM_PARAMS>

  using types::Vector_T;

  template <TRANSFORM_TEMPS>
  Transform_T<TRANSFORM_PARAMS>::
    Transform_T()
    : base_type("Transform")
    , m_transformation(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1)
    , m_scale(scale_type::ONE)
  { }

  template <TRANSFORM_TEMPS>
  Transform_T<TRANSFORM_PARAMS>::
    Transform_T(const position_type& a_position,
                const orientation_type& a_orientation)
    : base_type("Transform")
    , m_transformation(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1)
    , m_scale(scale_type::ONE)
  {
    SetPosition(a_position);
    SetOrientation(a_orientation);
  }

  template <TRANSFORM_TEMPS>
  Transform_T<TRANSFORM_PARAMS>::
    Transform_T(const transform_type& a_tr)
    : base_type("Transform")
    , m_transformation(a_tr)
    , m_scale(scale_type::ONE)
  { }

  template <TRANSFORM_TEMPS>
  TRANSFORM_TYPE::position_type
    Transform_T<TRANSFORM_PARAMS>::
    GetPosition() const
  {
    position_type       pos3;
    Vector_T<real_type, 4>  pos4;

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

    orientation_type scaleMat(0);
    scaleMat.MakeDiagonal(m_scale);

    ori3 = ori3 * scaleMat;

    return ori3;
  }

  template <TRANSFORM_TEMPS>
  TRANSFORM_TYPE::transform_type
    Transform_T<TRANSFORM_PARAMS>::
    GetTransformation() const
  {
    transform_type t(m_transformation);

    transform_type scaleMat(0);
    scaleMat.
      MakeDiagonal(m_scale.template ConvertTo<math_t::Vector_T<real_type, 4> >());

    t = t * scaleMat;

    return t;
  }

  template <TRANSFORM_TEMPS>
  void
    Transform_T<TRANSFORM_PARAMS>::
    SetPosition(const position_type& a_pos)
  {
    this->SetUpdateRequired(true);
    m_transformation[12] = a_pos[0];
    m_transformation[13] = a_pos[1];
    m_transformation[14] = a_pos[2];
  }

  template <TRANSFORM_TEMPS>
  void
    Transform_T<TRANSFORM_PARAMS>
    ::SetOrientation(const orientation_type& a_ori)
  {
    this->SetUpdateRequired(true);
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

  template <TRANSFORM_TEMPS>
  void
    Transform_T<TRANSFORM_PARAMS>::
    SetTransformation(const transform_type& a_tr, const scale_type& a_scale)
  {
    m_transformation = a_tr;
    m_scale = a_scale;
  }

  template <TRANSFORM_TEMPS>
  TRANSFORM_TYPE::this_type
    Transform_T<TRANSFORM_PARAMS>::
    Invert() const
  {
    // from: http://stackoverflow.com/a/2625420/368599
    //inv(A) = [ inv(M)   -inv(M) * b ]
    //         [   0            1     ]

    orientation_type rotMat = GetOrientation();
    rotMat = rotMat.Inverse();

    position_type posV = GetPosition();
    posV = (rotMat * -1) * posV;

    return this_type(position_type(posV), orientation_type(rotMat));
  }

  template <TRANSFORM_TEMPS>
  void
    Transform_T<TRANSFORM_PARAMS>::
    LookAt(position_type a_target)
  {
    position_type newDir = a_target - 
      m_transformation.GetCol(3).template ConvertTo<position_type>();
    newDir.Normalize();

    orientation_type ori =
      m_transformation.template ConvertTo<orientation_type>();

    if (newDir.IsParallel(position_type::UNIT_Y) == false)
    { ori.Orient(typename orientation_type::dir(newDir)); }
    else // parallel
    {
      position_type newUp = 
        ori.GetCol(2).template ConvertTo<position_type>().Inverse();
      newUp.Normalize();

      ori.Orient(typename orientation_type::dir(newDir),
                 typename orientation_type::up(newUp));
    }

    m_transformation.ConvertFrom(ori, core_ds::p_tuple::overflow_same());
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template class Transform_T<f32>;
  template class Transform_T<f64>;

};};};

//------------------------------------------------------------------------
// Explicit instantiations

using namespace tloc;
using namespace tloc::math_cs;

// SmartPtr

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Transformf32);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Transformf64);

TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(Transformf32);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(Transformf64);