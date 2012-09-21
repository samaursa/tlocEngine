#include "tlocImage.h"

#include <tlocCore/containers/tlocContainers.inl>

namespace tloc { namespace graphics { namespace media {

  Image::Image() : m_width(0), m_height(0)
  {
  }

  Image::error_type
    Image::LoadFromMemory(const char* a_buffer, size_type a_size)
  {
    if ((a_buffer == NULL) || (a_size == 0))
    { return error_type(common_error_types::error_no_data); }

    // Check if a_size can accommodate a whole number of Color*
    TLOC_ASSERT( ((a_size % sizeof(color_type)) == 0),
      "The buffer has an invalid size!");

    const color_type* buffer = reinterpret_cast<const color_type*>(a_buffer);
    m_pixels.assign(buffer, buffer + a_size);

    return tloc::ErrorSuccess();
  }

  Image::error_type
    Image::Create(size_type a_width, size_type a_height,
                  const color_type& a_color)
  {
    m_width = a_width;
    m_height = a_height;

    m_pixels.clear();
    m_pixels.resize(a_width * a_height, a_color);

    return tloc::ErrorSuccess();
  }

  void Image::SetPixel(size_type a_X, size_type a_Y, const color_type& a_color)
  {
    m_pixels[a_X + (a_Y * m_width)] = a_color;
  }

  const Image::color_type&  Image::GetPixel(size_type a_X, size_type a_Y) const
  {
    return m_pixels[a_X + (a_Y * m_width)];
  }

  //------------------------------------------------------------------------
  // Explicitly instantiate the container

  template class core::Array<types::Color>;

};};};