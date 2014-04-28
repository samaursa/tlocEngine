#include "tlocFontSize.h"

#include <tlocMath/tlocRange.h>
#include <tlocMath/utilities/tlocScale.h>

namespace tloc { namespace graphics { namespace media {

  FontSize::
    FontSize(em a_size, dpi a_dpi)
  {
    // using the formula: pixel_size = point_size * resolution / 72
    size_type dpiY = 
      core_utils::CastNumber<size_type>(a_dpi.m_value->operator [](1));

    m_heightInPixels = a_size * dpiY / 72;
  }

  FontSize::
    FontSize(fraction a_0to100, resolution a_resolution)
  {
    TLOC_ASSERT(a_0to100 >= 0 && a_0to100 <= 100, "Fraction (a_0to1) out of range");
    size_type resY = 
      core_utils::CastNumber<size_type>(a_resolution.m_value->operator [](1));

    m_heightInPixels =  resY * a_0to100 / 100;
  }

  FontSize::
    FontSize(pixels a_heightInPixels)
  {
    m_heightInPixels = a_heightInPixels;
  }

};};};