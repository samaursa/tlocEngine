#include "tlocMath/tlocVector.h"

namespace tloc
{
  template<> const Vec2f Vec2f::ZERO      (0.0f, 0.0f);
  template<> const Vec2f Vec2f::ONE       (1.0f, 1.0f);
  template<> const Vec2f Vec2f::UNIT_X    (1.0f, 0.0f);
  template<> const Vec2f Vec2f::UNIT_Y    (0.0f, 1.0f);
  template<> const Vec2f Vec2f::NEG_UNIT_X(-1.0f, 0.0f);
  template<> const Vec2f Vec2f::NEG_UNIT_Y(0.0f, -1.0f);

  template<> const Vec3f Vec3f::ZERO      (0.0f, 0.0f, 0.0f); 
  template<> const Vec3f Vec3f::ONE       (1.0f, 1.0f, 1.0f);
  template<> const Vec3f Vec3f::UNIT_X    (1.0f, 0.0f, 0.0f);
  template<> const Vec3f Vec3f::UNIT_Y    (0.0f, 1.0f, 0.0f);
  template<> const Vec3f Vec3f::UNIT_Z    (0.0f, 0.0f, 1.0f);
  template<> const Vec3f Vec3f::NEG_UNIT_X(-1.0f, 0.0f, 0.0f);
  template<> const Vec3f Vec3f::NEG_UNIT_Y(0.0f, -1.0f, 0.0f);
  template<> const Vec3f Vec3f::NEG_UNIT_Z(0.0f, 0.0f, -1.0f);
};