#ifndef TLOC_IMAGE_H
#define TLOC_IMAGE_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/error/tlocError.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>

#include <tlocGraphics/types/tlocColor.h>
#include <tlocGraphics/types/tlocDimension.h>

namespace tloc { namespace graphics { namespace media {

  namespace p_image
  {
    namespace storage 
    {
      class Internal {};
      class External {};
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Image_I

  class Image_I
  { 
  public:

    typedef tl_size                                       size_type;
    typedef core::error::Error                            error_type;
    typedef types::Dimension2                             dimension_type;

    TLOC_DECL_AND_DEF_GETTER(size_type, GetWidth, m_dim[types::dimension::width]);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetHeight, m_dim[types::dimension::height]);
    TLOC_DECL_AND_DEF_GETTER(dimension_type, GetDimensions, m_dim);

  protected:
    Image_I();
    ~Image_I();

  protected:
    dimension_type          m_dim;
  };

  // ///////////////////////////////////////////////////////////////////////
  // Image_TI<>

  template <typename T_ColorType, typename T_StorageType>
  class Image_TI;

  // ///////////////////////////////////////////////////////////////////////
  // Image_TI<Internal>

  template <typename T_ColorType>
  class Image_TI<T_ColorType, p_image::storage::Internal>
    : public Image_I
  {
    TLOC_STATIC_ASSERT
      ( (Loki::Conversion<T_ColorType, gfx_t::priv::ColorType>::exists),
      Unsupported_color_type_selected);

  public:
    typedef T_ColorType                                   value_type;
    typedef p_image::storage::Internal                    storage_type;

    typedef Image_I                                       base_type;
    typedef Image_TI<value_type, storage_type>            this_type;

    typedef value_type                                    color_type;
    typedef typename color_type::value_type               color_value_type;
    typedef typename
      core::containers::tl_array<color_type>::type        pixel_container_type;

    typedef core_sptr::VirtualPtr<color_type>             color_type_ptr;
    typedef core_sptr::VirtualPtr<const color_type>       const_color_type_ptr;
    typedef core_sptr::VirtualPtr<color_value_type>       color_ptr;
    typedef core_sptr::VirtualPtr<const color_value_type> const_color_ptr;

  public:
    error_type        Load(const_color_ptr a_buffer, dimension_type a_dim,
                           size_type a_channels);
    error_type        Load(const pixel_container_type& a_buffer,
                           dimension_type a_dim);
    error_type        Create(dimension_type a_dim, const color_type& a_color);
    error_type        AddPadding(dimension_type a_padding,
                                 const color_type& a_color);
    bool              IsValid() const;

    const_color_type_ptr   get() const;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(pixel_container_type,
                                          GetPixels, m_pixels);

  protected:
    Image_TI();
    ~Image_TI();

    void              DoSet(tl_int a_index, const color_type& a_color);
    const color_type& DoGet(tl_int a_index) const;

  private:
    pixel_container_type    m_pixels;
  };

  // ///////////////////////////////////////////////////////////////////////
  // Image_TI<External>

  template <typename T_ColorType>
  class Image_TI<T_ColorType, p_image::storage::External>
    : public Image_I
  {
    TLOC_STATIC_ASSERT
      ( (Loki::Conversion<T_ColorType, gfx_t::priv::ColorType>::exists),
      Unsupported_color_type_selected);

  public:
    typedef T_ColorType                                   value_type;
    typedef p_image::storage::External                    storage_type;

    typedef Image_I                                       base_type;
    typedef Image_TI<value_type, storage_type>            this_type;

    typedef value_type                                    color_type;
    typedef typename color_type::value_type               color_value_type;
    typedef typename
      core::containers::tl_array<color_type>::type        pixel_container_type;

    typedef core_sptr::VirtualPtr<color_type>             color_type_ptr;
    typedef core_sptr::VirtualPtr<const color_type>       const_color_type_ptr;
    typedef core_sptr::VirtualPtr<color_value_type>       color_ptr;
    typedef core_sptr::VirtualPtr<const color_value_type> const_color_ptr;

  public:
    error_type        Load(color_ptr a_buffer, dimension_type a_dim,
                           size_type a_channels);
    error_type        Create(dimension_type a_dim, const color_type& a_color);
    error_type        AddPadding(dimension_type a_padding,
                                 const color_type& a_color);
    bool              IsValid() const;

    const_color_type_ptr   get() const;

    TLOC_DECL_AND_DEF_GETTER(color_type_ptr, GetPixels, m_pixels);
    TLOC_DECL_AND_DEF_GETTER_DIRECT(color_type_ptr, GetPixels, m_pixels);

  protected:
    Image_TI();
    ~Image_TI();

    void              DoSet(tl_int a_index, const color_type& a_color);
    const color_type& DoGet(tl_int a_index) const;

  private:
    color_type_ptr    m_pixels;
  };

  // ///////////////////////////////////////////////////////////////////////
  // Image_T<> 

  template <typename T_ColorType = types::Color, 
            typename T_StorageType = p_image::storage::Internal>
  class Image_T
    : public Image_TI<T_ColorType, T_StorageType>
  {
  public:
    typedef T_ColorType                                   value_type;
    typedef T_StorageType                                 storage_type;

    typedef Image_TI<value_type, storage_type>            base_type;
    typedef Image_T<value_type, storage_type>             this_type;

    typedef typename base_type::color_type                color_type;
    typedef typename base_type::color_value_type          color_value_type;
    typedef typename base_type::pixel_container_type      pixel_container_type;

    typedef typename base_type::color_type_ptr            color_type_ptr;
    typedef typename base_type::color_ptr                 color_ptr;
    typedef typename base_type::const_color_ptr           const_color_ptr;
    typedef typename base_type::size_type                 size_type;

    typedef typename base_type::error_type                error_type;
    typedef typename base_type::dimension_type            dimension_type;

    typedef core_sptr::VirtualPtr<this_type>              image_ptr;
    typedef core_sptr::SharedPtr<this_type>               image_sptr;
    typedef core_conts::Array<image_ptr>                  image_ptr_cont;

  public:
    Image_T();

    void              SetPixel(size_type a_X, size_type a_Y,
                               const color_type& a_color);
    void              SetImage(size_type a_x, size_type a_y,
                               const this_type& a_image);
    const color_type& GetPixel(size_type a_X, size_type a_Y) const;
    image_sptr        GetImage(size_type a_x, size_type a_y,
                               dimension_type a_dimToGet) const;

    using base_type::Load;
    using base_type::Create;
    using base_type::AddPadding;
    using base_type::GetWidth;
    using base_type::GetHeight;
    using base_type::GetDimensions;
    using base_type::GetPixels;
    using base_type::IsValid;
  };

  // -----------------------------------------------------------------------
  // typedefs

  // default image type
  typedef Image_T<gfx_t::Color>                             Image;

  typedef Image_T<gfx_t::color_rgba>                        image_rgba;
  typedef Image_T<gfx_t::color_rgb>                         image_rgb;
  typedef Image_T<gfx_t::color_rg>                          image_rg;
  typedef Image_T<gfx_t::color_r>                           image_r;

  typedef Image_T<gfx_t::color_u16_rgba>                    image_u16_rgba;
  typedef Image_T<gfx_t::color_u16_rgb>                     image_u16_rgb;
  typedef Image_T<gfx_t::color_u16_rg>                      image_u16_rg;
  typedef Image_T<gfx_t::color_u16_r>                       image_u16_r;

  typedef Image_T<gfx_t::color_f32_r>                       image_f32_r;

  TLOC_TYPEDEF_ALL_SMART_PTRS(Image, image);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Image, image);

  typedef Image_T<gfx_t::color_rgba, p_image::storage::External>      image_stream_rgba;
  typedef Image_T<gfx_t::color_rgb, p_image::storage::External>       image_stream_rgb;
  typedef Image_T<gfx_t::color_rg, p_image::storage::External>        image_stream_rg;
  typedef Image_T<gfx_t::color_r, p_image::storage::External>         image_stream_r;

  typedef Image_T<gfx_t::color_u16_rgba, p_image::storage::External>  image_stream_u16_rgba;
  typedef Image_T<gfx_t::color_u16_rgb, p_image::storage::External>   image_stream_u16_rgb;
  typedef Image_T<gfx_t::color_u16_rg, p_image::storage::External>    image_stream_u16_rg;
  typedef Image_T<gfx_t::color_u16_r, p_image::storage::External>     image_stream_u16_r;

  typedef Image_T<gfx_t::color_f32_r, p_image::storage::External>     image_stream_f32_r;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::Color>);

  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_rgba>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_rgb>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_rg>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_r>);

  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_u16_rgba>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_u16_rgb>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_u16_rg>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_u16_r>);

  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_f32_r>);
  
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_rgba TLOC_COMMA p_image::storage::External>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_rgb TLOC_COMMA p_image::storage::External>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_rg TLOC_COMMA p_image::storage::External>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_r TLOC_COMMA p_image::storage::External>);

  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_u16_rgba TLOC_COMMA p_image::storage::External>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_u16_rgb TLOC_COMMA p_image::storage::External>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_u16_rg TLOC_COMMA p_image::storage::External>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_u16_r TLOC_COMMA p_image::storage::External>);

  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<gfx_t::color_f32_r TLOC_COMMA p_image::storage::External>);

  // ```````````````````````````````````````````````````````````````````````
  // u8 images

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_rgba, image_rgba);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_rgba, image_stream_rgba);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_rgba, image_rgba);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_rgba, image_stream_rgba);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_rgb, image_rgb);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_rgb, image_stream_rgb);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_rgb, image_rgb);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_rgb, image_stream_rgb);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_rg, image_rg);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_rg, image_stream_rg);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_rg, image_rg);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_rg, image_stream_rg);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_r, image_r);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_r, image_stream_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_r, image_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_r, image_stream_r);

  // ```````````````````````````````````````````````````````````````````````
  // u16 images

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_u16_rgba, image_u16_rgba);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_u16_rgba, image_stream_u16_rgba);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_u16_rgba, image_u16_rgba);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_u16_rgba, image_stream_u16_rgba);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_u16_rgb, image_u16_rgb);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_u16_rgb, image_stream_u16_rgb);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_u16_rgb, image_u16_rgb);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_u16_rgb, image_stream_u16_rgb);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_u16_rg, image_u16_rg);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_u16_rg, image_stream_u16_rg);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_u16_rg, image_u16_rg);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_u16_rg, image_stream_u16_rg);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_u16_r, image_u16_r);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_u16_r, image_stream_u16_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_u16_r, image_u16_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_u16_r, image_stream_u16_r);

  // ```````````````````````````````````````````````````````````````````````
  // special images

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_f32_r, image_f32_r);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_f32_r, image_stream_f32_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_f32_r, image_f32_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_f32_r, image_stream_f32_r);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::Image);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::Image);

// -----------------------------------------------------------------------
// extern templates

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_rgba);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_rgba);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_rgba);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_rgba);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_rgb);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_rgb);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_rgb);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_rgb);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_rg);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_rg);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_rg);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_rg);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_r);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_r);

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_u16_rgba);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_u16_rgba);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_u16_rgba);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_u16_rgba);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_u16_rgb);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_u16_rgb);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_u16_rgb);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_u16_rgb);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_u16_rg);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_u16_rg);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_u16_rg);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_u16_rg);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_u16_r);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_u16_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_u16_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_u16_r);

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_f32_r);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_f32_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_f32_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_f32_r);

#endif