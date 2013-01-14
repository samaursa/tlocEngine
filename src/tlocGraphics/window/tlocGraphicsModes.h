#ifndef TLOC_GRAPHICS_MODES_H
#define TLOC_GRAPHICS_MODES_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/platform/tlocPlatform.h>

namespace tloc { namespace graphics { namespace win {

  //////////////////////////////////////////////////////////////////////////
  /// This class was written (initially - modifications may follow) by
  /// following SFML (Simply and Fast Multi-media library).
  template <typename T_Platform = typename core::PlatformInfo<>::platform_type>
  class GraphicsMode
  {
  public:

    typedef tl_size                       size_type;
    typedef GraphicsMode<T_Platform>      this_type;

    struct Properties
    {
      typedef typename GraphicsMode::size_type  size_type;

      Properties(size_type a_width, size_type a_height,
                 size_type a_bitsPerPixel = 32, size_type a_frequency = 60);

      bool operator ==(const Properties& a_other) const;
      bool operator < (const Properties& a_other) const;
      TLOC_DECLARE_OPERATORS(Properties);

      size_type m_width;
      size_type m_height;
      size_type m_bitsPerPixel;
      size_type m_frequency;
    };
    typedef Properties                    properties_type;

    GraphicsMode(const Properties& a_props);

    //------------------------------------------------------------------------
    // Methods

    bool IsSupported() const;
    bool operator ==(const this_type& a_other) const;
    bool operator < (const this_type& a_other) const;
    TLOC_DECLARE_OPERATORS(GraphicsMode);

    properties_type&  GetProperties();
    properties_type   GetProperties() const;

    //------------------------------------------------------------------------
    // Static Methods

    static this_type GetCurrentMode() {return this_type(Properties(0, 0));}
    static this_type GetMode(size_type a_index) {TLOC_UNUSED(a_index); return this_type(Properties(0, 0)); }
    static size_type GetTotalModes() { return 0; }

  protected:

    properties_type m_properties;

  };

};};};

#endif