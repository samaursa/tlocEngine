#ifndef TLOC_IMAGE_H
#define TLOC_IMAGE_H

#include <tlocCore/containers/tlocContainers.h>

#include <tlocGraphics/data_types/tlocColor.h>

namespace tloc { namespace graphics { namespace media {

  class Image
  {
  public:
    typedef tl_size                             size_type;
    typedef types::Color                        value_type;
    typedef core::tl_array<value_type>::type    pixel_container_type;

  private:
    size_type               m_width;
    size_type               m_height;
    pixel_container_type    m_pixels;
  };

};};};

#endif