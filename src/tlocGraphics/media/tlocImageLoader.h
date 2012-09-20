#ifndef TLOC_IMAGE_LOADER_H
#define TLOC_IMAGE_LOADER_H

#include <tlocCore/error/tlocError.h>
#include <tlocCore/io/tlocPath.h>

#include <tlocGraphics/media/tlocImage.h>

namespace tloc { namespace graphics { namespace media {

  class ImageLoader
  {
  public:
    typedef core::error::Error    error_type;
    typedef core::io::Path        path_type;

  public:
    ImageLoader();

    error_type    Load(const path_type& a_path);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(Image, GetImage, m_image);

  private:

    Image m_image;
  };

};};};

#endif