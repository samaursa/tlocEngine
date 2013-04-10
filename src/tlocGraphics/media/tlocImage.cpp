#include "tlocImage.h"

#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

namespace tloc { namespace graphics { namespace media {

  namespace
  {
    enum
    {
      width = types::dimension::width,
      height = types::dimension::height,
    };
  };

  Image::Image() : m_dim(0, 0)
  {
  }

  Image::error_type
    Image::LoadFromMemory(const uchar8* a_buffer, dimension_type a_dim,
                          size_type a_channels)
  {
    if ( (a_buffer == nullptr) || a_dim[0] == 0 || a_dim[1] == 0 ||
         (a_channels == 0) )
    { return error_type(common_error_types::error_no_data); }

    // Check if a_size can accommodate a whole number of Color*
    TLOC_ASSERT( ((a_channels % sizeof(color_type)) == 0),
      "The buffer has an invalid size!");

    const color_type* buffer = reinterpret_cast<const color_type*>(a_buffer);
    m_pixels.assign(buffer, buffer + (a_dim[0] * a_dim[1]));

    m_dim = a_dim;

    return tloc::ErrorSuccess;
  }

  Image::error_type
    Image::Create(dimension_type a_dim, const color_type& a_color)
  {
    m_dim = a_dim;

    m_pixels.clear();
    m_pixels.resize(m_dim[width] * m_dim[height] , a_color);

    return tloc::ErrorSuccess;
  }

  void Image::SetPixel(size_type a_X, size_type a_Y, const color_type& a_color)
  {
    m_pixels[a_X + (a_Y * m_dim[width])] = a_color;
  }

  const Image::color_type&  Image::GetPixel(size_type a_X, size_type a_Y) const
  {
    return m_pixels[a_X + (a_Y * m_dim[width])];
  }

  //------------------------------------------------------------------------
  // Explicitly instantiate the container

  template class core::containers::Array<types::Color>;

  template class core::smart_ptr::SharedPtr<Image>;

};};};