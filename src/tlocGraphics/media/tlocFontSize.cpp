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
	  real_type resY = 
		  core_utils::CastNumber<real_type>(a_resolution.m_value->operator [](1));

	  real_type heightInPixels = 
		  core_utils::CastNumber<real_type>(resY) * a_0to100 / 100.0f;

    m_heightInPixels = (size_type)heightInPixels;
  }

  FontSize::
    FontSize(pixels a_heightInPixels)
  {
    m_heightInPixels = a_heightInPixels;
  }

};};};

using namespace tloc::gfx_med;

#include <tlocCore/types/tlocStrongType.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_STRONG_TYPE(FontSize::dim_type, 0);
TLOC_EXPLICITLY_INSTANTIATE_STRONG_TYPE(FontSize::dim_type, 1);
TLOC_EXPLICITLY_INSTANTIATE_STRONG_TYPE(FontSize::real_type, 0);
TLOC_EXPLICITLY_INSTANTIATE_STRONG_TYPE(FontSize::size_type, 0);
TLOC_EXPLICITLY_INSTANTIATE_STRONG_TYPE(FontSize::size_type, 1);