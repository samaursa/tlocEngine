#ifndef TLOC_IMAGE_LOADER_H
#define TLOC_IMAGE_LOADER_H

#include <tlocCore/error/tlocError.h>
#include <tlocCore/io/tlocPath.h>

#include <tlocGraphics/media/tlocImage.h>

namespace tloc { namespace graphics { namespace media {

  template <typename T_DerivedClass>
  class ImageLoader
  {
  public:
    typedef T_DerivedClass        derived_type;
    typedef core::error::Error    error_type;
    typedef core::io::Path        path_type;
    typedef tl_size               size_type;

    error_type Load(const path_type& a_path);

  protected:

    error_type DoLoadImageFromMemory(const char* a_buffer, size_type a_length);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(Image, GetImage, m_image);

  private:
    Image m_image;
  };

  class ImageLoaderPng : public ImageLoader<ImageLoaderPng>
  {
  public:
    typedef ImageLoader     base_type;
    using base_type::error_type;
    using base_type::path_type;
    using base_type::size_type;

  public:
    error_type  Load(const path_type& a_path);

  };

};};};

#endif