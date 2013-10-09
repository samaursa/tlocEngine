#ifndef TLOC_IMAGE_H
#define TLOC_IMAGE_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/error/tlocError.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tloccontainers.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>

#include <tlocGraphics/types/tlocColor.h>
#include <tlocGraphics/types/tlocDimension.h>

namespace tloc { namespace graphics { namespace media {

  class Image
  {
  public:
    typedef tl_size                                       size_type;
    typedef types::Color                                  color_type;
    typedef core::containers::tl_array<color_type>::type  pixel_container_type;
    typedef core::error::Error                            error_type;
    typedef Image                                         this_type;
    typedef types::Dimension2u                            dimension_type;

  public:
    Image();

    ///-------------------------------------------------------------------------
    /// @brief Loads color buffer from memory (assuming RGBA format)
    ///-------------------------------------------------------------------------
    error_type        LoadFromMemory(const uchar8* a_buffer,
                                     dimension_type a_dim,
                                     size_type a_channels);

    error_type        Create(dimension_type a_dim, const color_type& a_color);

    void              SetPixel(size_type a_X, size_type a_Y,
                               const color_type& a_color);

    const color_type& GetPixel(size_type a_X, size_type a_Y) const;

    TLOC_DECL_AND_DEF_GETTER(size_type, GetWidth, m_dim[types::dimension::width]);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetHeight, m_dim[types::dimension::height]);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(pixel_container_type,
                                          GetPixels, m_pixels);

  private:
    dimension_type          m_dim;
    pixel_container_type    m_pixels;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(Image, image);

};};};

#endif