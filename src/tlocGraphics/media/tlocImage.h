#ifndef TLOC_IMAGE_H
#define TLOC_IMAGE_H

#include <tlocCore/error/tlocError.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/containers/tlocContainers.h>

#include <tlocGraphics/data_types/tlocColor.h>

namespace tloc { namespace graphics { namespace media {

  class Image
  {
  public:
    typedef tl_size                             size_type;
    typedef types::Color                        color_type;
    typedef core::tl_array<color_type>::type    pixel_container_type;
    typedef core::error::Error                  error_type;
    typedef Image                               this_type;

  public:
    Image();

    ///-------------------------------------------------------------------------
    /// @brief Loads color buffer from memory (assuming RGBA format)
    ///-------------------------------------------------------------------------
    error_type    LoadFromMemory(const char* a_buffer, size_type a_size);

    error_type    Create(size_type a_width, size_type a_height,
                         const color_type& a_color = color_type::COLOR_BLACK);

    void              SetPixel(size_type a_X, size_type a_Y,
                               const color_type& a_color);
    const color_type& GetPixel(size_type a_X, size_type a_Y) const;

    TLOC_DECL_AND_DEF_GETTER(size_type, GetWidth, m_width);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetHeight, m_height);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(pixel_container_type,
                                          GetPixels, m_pixels);

  private:
    size_type               m_width;
    size_type               m_height;
    pixel_container_type    m_pixels;
  };

};};};

#endif