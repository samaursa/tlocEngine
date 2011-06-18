#include "tlocMath/tlocVector2.h"

namespace tloc
{
  template<> const Vec2f Vec2f::UNIT_X    ( 1.0f,  0.0f);
  template<> const Vec2f Vec2f::UNIT_Y    ( 0.0f,  1.0f);
  template<> const Vec2f Vec2f::NEG_UNIT_X(-1.0f, 0.0f);
  template<> const Vec2f Vec2f::NEG_UNIT_Y( 0.0f, -1.0f);

  template<> const Vec2d Vec2d::UNIT_X    ( 1.0,  0.0);
  template<> const Vec2d Vec2d::UNIT_Y    ( 0.0,  1.0);
  template<> const Vec2d Vec2d::NEG_UNIT_X(-1.0,  0.0);
  template<> const Vec2d Vec2d::NEG_UNIT_Y( 0.0, -1.0);
};