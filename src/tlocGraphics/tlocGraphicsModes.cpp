#include "tlocGraphicsModes.h"

#include "tlocCore/tlocArray.h"

//------------------------------------------------------------------------
// Platform specific

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
# define WIN32_LEAN_AND_MEAN
# include <Windows.h>

#else
# error "Not implemented for other platforms"

#endif

//------------------------------------------------------------------------
// Local functions/vars

namespace
{
  using namespace tloc;

  //typedef core::Array<graphics::GraphicsMode<> > graphics_modes_array;
  //graphics_modes_array g_SupportedModes;

  struct CompareModes
  {
    bool operator() (const graphics::GraphicsMode<>& a_first,
      const graphics::GraphicsMode<>& a_second)
    {
      TLOC_UNUSED(a_first);
      TLOC_UNUSED(a_second);
    }

  };

}

namespace tloc { namespace graphics {

#define GRAPHICS_MODES_TEMP   typename T_Platform
#define GRAPHICS_MODES_PARAMS T_Platform

  //------------------------------------------------------------------------
  // Properties

  template <GRAPHICS_MODES_TEMP>
  GraphicsMode<GRAPHICS_MODES_PARAMS>::Properties::
    Properties(size_type a_widght, size_type a_height,
               size_type a_bitsPerPixel, size_type a_frequency)
               : m_width(a_widght)
               , m_height(a_height)
               , m_bitsPerPixel(a_bitsPerPixel)
               , m_frequency(a_frequency)
  {
  }

  template <GRAPHICS_MODES_TEMP>
  bool GraphicsMode<GRAPHICS_MODES_PARAMS>::Properties::
    operator ==(const Properties& a_other) const
  {
    return (m_width == a_other.m_width &&
            m_height == a_other.m_height &&
            m_bitsPerPixel == a_other.m_bitsPerPixel &&
            m_frequency == a_other.m_frequency);
  }

  template <GRAPHICS_MODES_TEMP>
  bool GraphicsMode<GRAPHICS_MODES_PARAMS>::Properties::
    operator < (const Properties& a_other) const
  {
    if      (m_bitsPerPixel < a_other.m_bitsPerPixel) { return true; }
    else if (m_bitsPerPixel > a_other.m_bitsPerPixel) { return false; }

    else if (m_width < a_other.m_width) { return true; }
    else if (m_width > a_other.m_width) { return false; }

    else if (m_height < a_other.m_height) { return true; }
    else if (m_height > a_other.m_height) { return false; }

    else { return m_frequency < a_other.m_frequency; }
  }

  //------------------------------------------------------------------------
  // Graphics Mode

  template <GRAPHICS_MODES_TEMP>
  GraphicsMode<GRAPHICS_MODES_PARAMS>::GraphicsMode(const Properties& a_props)
    : m_properties(a_props)
  {
  }

  template <GRAPHICS_MODES_TEMP>
  bool GraphicsMode<GRAPHICS_MODES_PARAMS>::IsSupported() const
  {
    return false;
  }

  template <GRAPHICS_MODES_TEMP>
  bool GraphicsMode<GRAPHICS_MODES_PARAMS>::
    operator ==(const this_type& a_other) const
  {
    return m_properties == a_other.m_properties;
  }

  template <GRAPHICS_MODES_TEMP>
  bool GraphicsMode<GRAPHICS_MODES_PARAMS>::
    operator < (const this_type& a_other) const
  {
    return m_properties < a_other.m_properties;
  }

  template <GRAPHICS_MODES_TEMP>
  typename GraphicsMode<GRAPHICS_MODES_PARAMS>::properties_type
    GraphicsMode<GRAPHICS_MODES_PARAMS>::GetProperties()
  {
    return m_properties;
  }

  template GraphicsMode<>;

};};