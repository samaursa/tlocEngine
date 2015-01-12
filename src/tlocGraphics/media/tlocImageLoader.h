#ifndef TLOC_IMAGE_LOADER_H
#define TLOC_IMAGE_LOADER_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/error/tlocError.h>
#include <tlocCore/io/tlocPath.h>

#include <tlocGraphics/media/tlocImage.h>

namespace tloc { namespace graphics { namespace media {

  template <typename T_DerivedClass>
  class ImageLoader_TI
  {
  public:
    typedef T_DerivedClass            derived_type;
    typedef core::error::Error        error_type;
    typedef core::io::Path            path_type;
    typedef tl_size                   size_type;
    typedef image_sptr                image_ptr;
    typedef Image::dimension_type     dimention_type;
    typedef Image::const_color_ptr    const_color_ptr;

  public:
    error_type Load(const path_type& a_path);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(image_ptr, GetImage, m_image);

  protected:

    error_type DoLoadImageFromMemory(const_color_ptr a_buffer,
                                     dimention_type a_dim,
                                     size_type a_channels);

  private:
    image_ptr m_image;
  };

  class ImageLoaderPng : public ImageLoader_TI<ImageLoaderPng>
  {
  public:
    typedef ImageLoader_TI<ImageLoaderPng>   base_type;
    friend base_type;
    using base_type::error_type;
    using base_type::path_type;
    using base_type::size_type;

  protected:
    error_type  DoLoad(const path_type& a_path);

  };

  // -----------------------------------------------------------------------
  // extern template

  class ImageLoaderPng;
  TLOC_EXTERN_TEMPLATE_CLASS(ImageLoader_TI<ImageLoaderPng>);

  namespace p_image_loader {

    core_err::Error
      SaveImage(const Image::const_color_type_ptr& a_imgToWrite);

  };

  // -----------------------------------------------------------------------

  namespace f_image_loader {

    core_err::Error
      SaveImage(const Image& a_imgToWrite, 
                const core_io::Path& a_path);

  };

};};};

#endif