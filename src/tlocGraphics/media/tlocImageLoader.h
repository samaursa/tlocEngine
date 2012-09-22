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
    typedef Image::dimension_type dimention_type;

    error_type Load(const path_type& a_path);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(Image, GetImage, m_image);

  protected:

    error_type DoLoadImageFromMemory(const uchar8* a_buffer,
                                     dimention_type a_dim,
                                     size_type a_channels);

  private:
    Image m_image;
  };

  class ImageLoaderPng : public ImageLoader<ImageLoaderPng>
  {
  public:
    typedef ImageLoader<ImageLoaderPng>   base_type;
    friend class base_type;
    using base_type::error_type;
    using base_type::path_type;
    using base_type::size_type;

  protected:
    error_type  DoLoad(const path_type& a_path);

  };

};};};

#endif