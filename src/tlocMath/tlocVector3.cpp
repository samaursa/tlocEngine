#include "tlocMath/tlocVector3.h"

namespace tloc
{
  template<> const Vec3f Vec3f::UNIT_X    (1.0f, 0.0f, 0.0f);
  template<> const Vec3f Vec3f::UNIT_Y    (0.0f, 1.0f, 0.0f);
  template<> const Vec3f Vec3f::UNIT_Z    (0.0f, 0.0f, 1.0f);
  template<> const Vec3f Vec3f::NEG_UNIT_X(-1.0f, 0.0f, 0.0f);
  template<> const Vec3f Vec3f::NEG_UNIT_Y(0.0f, -1.0f, 0.0f);
  template<> const Vec3f Vec3f::NEG_UNIT_Z(0.0f, 0.0f, -1.0f);

  template<> const Vec3d Vec3d::UNIT_X    (1.0, 0.0, 0.0);
  template<> const Vec3d Vec3d::UNIT_Y    (0.0, 1.0, 0.0);
  template<> const Vec3d Vec3d::UNIT_Z    (0.0, 0.0, 1.0);
  template<> const Vec3d Vec3d::NEG_UNIT_X(-1.f, 0.0, 0.0);
  template<> const Vec3d Vec3d::NEG_UNIT_Y(0.0, -1.0, 0.0);
  template<> const Vec3d Vec3d::NEG_UNIT_Z(0.0, 0.0, -1.0);
};