#ifndef TLOC_IMAGE_H
#define TLOC_IMAGE_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/error/tlocError.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>
#include <tlocCore/utilities/tlocContainerUtils.h>

#include <tlocGraphics/types/tlocColor.h>
#include <tlocGraphics/types/tlocDimension.h>

namespace tloc { namespace graphics { namespace media {

  namespace p_image
  {
    namespace storage 
    {
      class Internal      {};
      class External      {};

      typedef type_true   const_storage;
      typedef type_false  non_const_storage;
    };

    typedef gfx_t::Dimension2       dim_2d;
    typedef gfx_t::Dimension3       dim_3d;
  };

  // ///////////////////////////////////////////////////////////////////////
  // ImageBase_TI

  template <typename T_Dim>
  class ImageBase_TI;

  template <>
  class ImageBase_TI<p_image::dim_2d>
  {
  public:

    typedef tl_size                                       size_type;
    typedef core::error::Error                            error_type;
    typedef types::Dimension2                             dimension_type;

    TLOC_DECL_AND_DEF_GETTER(size_type, GetWidth, m_dim[types::dimension::width]);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetHeight, m_dim[types::dimension::height]);
    TLOC_DECL_AND_DEF_GETTER(dimension_type, GetDimensions, m_dim);

  protected:
    ImageBase_TI();
    ~ImageBase_TI();

  protected:
    dimension_type          m_dim;
  };

  template <>
  class ImageBase_TI<p_image::dim_3d>
  { 
  public:

    typedef tl_size                                       size_type;
    typedef core::error::Error                            error_type;
    typedef types::Dimension3                             dimension_type;

    TLOC_DECL_AND_DEF_GETTER(size_type, GetWidth,   m_dim[types::dimension::width]);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetHeight,  m_dim[types::dimension::height]);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetDepth,   m_dim[types::dimension::depth]);
    TLOC_DECL_AND_DEF_GETTER(dimension_type, GetDimensions, m_dim);

  protected:
    ImageBase_TI();
    ~ImageBase_TI();

  protected:
    dimension_type          m_dim;
  };

  // ///////////////////////////////////////////////////////////////////////
  // Image_TI<>

  // const storage only affects external storage type
  template <typename T_Dim, typename T_ColorType, typename T_StorageType, 
            bool T_Const = false>
  class Image_TI
  {
    TLOC_STATIC_ASSERT( !(Loki::IsSameType<T_StorageType, p_image::storage::Internal>::value && T_Const == true),
      Only_external_storage_type_can_be_const);
  };

  // ///////////////////////////////////////////////////////////////////////
  // Image_TI<Internal>

  template <typename T_Dim, typename T_ColorType>
  class Image_TI<T_Dim, T_ColorType, p_image::storage::Internal, false>
    : public ImageBase_TI<T_Dim>
  {
    TLOC_STATIC_ASSERT
      ( (Loki::Conversion<T_ColorType, gfx_t::priv::ColorType>::exists),
      Unsupported_color_type_selected);

  public:
    typedef T_ColorType                                   value_type;
    typedef T_Dim                                         dimension_type;
    typedef p_image::storage::Internal                    storage_type;

    typedef ImageBase_TI<dimension_type>                  base_type;
    typedef Image_TI<dimension_type, value_type,
                     storage_type, false>                 this_type;

    typedef typename base_type::size_type                 size_type;
    typedef typename base_type::error_type                error_type;

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
    error_type        Create(dimension_type a_dim, 
                             const color_type& a_color = color_type::COLOR_BLACK);
    error_type        AddPadding(dimension_type a_padding,
                                 const color_type& a_color);
    bool              IsValid() const;

    color_type_ptr         get();
    const_color_type_ptr   get() const;

    color_type&            operator[](tl_int a_index);
    color_type             operator[](tl_int a_index) const;

  protected:
    Image_TI();
    ~Image_TI();

    void              DoSet(tl_int a_index, const color_type& a_color);
    color_type&       DoGet(tl_int a_index);
    const color_type& DoGet(tl_int a_index) const;

  private:

    template <typename T_ImageTI, typename T_ColorType>
    friend 
    typename T_ImageTI::error_type
    DoAddPadding(T_ImageTI*, types::Dimension2, const T_ColorType& );

    template <typename T_ImageTI, typename T_ColorType>
    friend 
    typename T_ImageTI::error_type
    DoAddPadding(T_ImageTI*, types::Dimension3, const T_ColorType& );

  private:
    pixel_container_type    m_pixels;

  public:
    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_pixels, m_pixels);
  };

  // ///////////////////////////////////////////////////////////////////////
  // Image_TI<External>

  template <typename T_Dim, typename T_ColorType, bool T_Const>
  class Image_TI<T_Dim, T_ColorType, p_image::storage::External, T_Const>
    : public ImageBase_TI<T_Dim>
  {
    TLOC_STATIC_ASSERT
      ( (Loki::Conversion<T_ColorType, gfx_t::priv::ColorType>::exists),
      Unsupported_color_type_selected);

  public:
    typedef T_ColorType                                   value_type;
    typedef T_Dim                                         dimension_type;
    typedef p_image::storage::External                    storage_type;

    typedef ImageBase_TI<dimension_type>                  base_type;
    typedef Image_TI<dimension_type, value_type, 
                     storage_type, T_Const>               this_type;

    typedef typename base_type::size_type                 size_type;
    typedef typename base_type::error_type                error_type;

    // const external storage can only work with const color type
    typedef typename Loki::Select
      <T_Const, const value_type, value_type>::Result     color_type;

    // const external storage can only work with const color::value_type
    typedef typename Loki::Select
      <T_Const, 
       const typename color_type::value_type, 
       typename color_type::value_type>::Result           color_value_type;

    typedef typename
      core::containers::tl_array<color_type>::type        pixel_container_type;

    typedef core_sptr::VirtualPtr<color_type>             color_type_ptr;
    typedef core_sptr::VirtualPtr<const color_type>       const_color_type_ptr;
    typedef core_sptr::VirtualPtr<color_value_type>       color_ptr;
    typedef core_sptr::VirtualPtr<const color_value_type> const_color_ptr;

  public:
    error_type        Load(color_ptr a_buffer, dimension_type a_dim,
                           size_type a_channels);
    error_type        Create(dimension_type a_dim, 
                             const color_type& a_color = color_type::COLOR_BLACK);
    error_type        AddPadding(dimension_type a_padding,
                                 const color_type& a_color);
    bool              IsValid() const;

    color_type_ptr         get();
    const_color_type_ptr   get() const;

    color_type&            operator[](tl_int a_index);
    color_type             operator[](tl_int a_index) const;

  protected:
    Image_TI();
    ~Image_TI();

    void              DoSet(tl_int a_index, const color_type& a_color);
    color_type&       DoGet(tl_int a_index);
    const color_type& DoGet(tl_int a_index) const;

  private:
    color_type_ptr    m_pixels;
  };

  // ///////////////////////////////////////////////////////////////////////
  // Image_T<> 

  template <typename T_Dim = p_image::dim_2d,
            typename T_ColorType = types::Color, 
            typename T_StorageType = p_image::storage::Internal,
            bool T_Const = false>
  class Image_T;

  // -----------------------------------------------------------------------
  // Image_T<2D>

  template <typename T_ColorType, 
            typename T_StorageType, bool T_Const>
  class Image_T<p_image::dim_2d, T_ColorType, T_StorageType, T_Const>
    : public Image_TI<p_image::dim_2d, T_ColorType, T_StorageType, T_Const>
  {
  public:
    typedef T_ColorType                                   value_type;
    typedef T_StorageType                                 storage_type;

    typedef Image_TI<p_image::dim_2d, 
                     value_type, storage_type, T_Const>   base_type;
    typedef Image_T<p_image::dim_2d, value_type, 
                    storage_type, T_Const>                this_type;

    typedef typename base_type::color_type                color_type;
    typedef typename base_type::size_type                 size_type;
    typedef typename base_type::dimension_type            dimension_type;

    typedef core_sptr::SharedPtr<this_type>               image_sptr;

  public:
    Image_T();

    void              SetPixel(dimension_type a_dim,
                               const color_type& a_color);
    void              SetPixel(size_type a_x, size_type a_y,
                               const color_type& a_color);

    void              SetImage(dimension_type a_dim,
                               const this_type& a_image);
    void              SetImage(size_type a_x, size_type a_y,
                               const this_type& a_image);

    const color_type& GetPixel(dimension_type a_dim) const;
    const color_type& GetPixel(size_type a_x, size_type a_y) const;

    image_sptr        GetImage(dimension_type a_dim,
                               dimension_type a_dimToGet) const;
    image_sptr        GetImage(size_type a_x, size_type a_y,
                               dimension_type a_dimToGet) const;

    using base_type::Load;
    using base_type::Create;
    using base_type::AddPadding;
    using base_type::GetWidth;
    using base_type::GetHeight;
    using base_type::GetDimensions;
    using base_type::IsValid;
  };

  // -----------------------------------------------------------------------
  // Image_T<3D>

  template <typename T_ColorType, 
            typename T_StorageType, bool T_Const>
  class Image_T<p_image::dim_3d, T_ColorType, T_StorageType, T_Const>
    : public Image_TI<p_image::dim_3d, T_ColorType, T_StorageType, T_Const>
  {
  public:
    typedef T_ColorType                                   value_type;
    typedef T_StorageType                                 storage_type;

    typedef Image_TI<p_image::dim_3d, 
                     value_type, storage_type, T_Const>   base_type;
    typedef Image_T<p_image::dim_3d, value_type, 
                    storage_type, T_Const>                this_type;
    typedef Image_T<p_image::dim_2d, value_type,
                    p_image::storage::External, true>     image_2d_type;

    typedef typename base_type::color_type                color_type;
    typedef typename base_type::size_type                 size_type;
    typedef typename base_type::dimension_type            dimension_type;

    typedef core_sptr::SharedPtr<this_type>               image_sptr;
    typedef core_sptr::SharedPtr<image_2d_type>           image_2d_sptr;

  public:
    Image_T();

    void              SetPixel(dimension_type a_dim,
                               const color_type& a_color);
    void              SetPixel(size_type a_x, size_type a_y, size_type a_z,
                               const color_type& a_color);

    void              SetImage(dimension_type a_dim,
                               const this_type& a_image);
    void              SetImage(size_type a_x, size_type a_y, size_type a_z,
                               const this_type& a_image);

    const color_type& GetPixel(dimension_type a_dim) const;
    const color_type& GetPixel(size_type a_x, size_type a_y, size_type a_z) const;

    image_sptr        GetImage(dimension_type a_dim,
                               dimension_type a_dimToGet) const;
    image_sptr        GetImage(size_type a_x, size_type a_y, size_type a_z,
                               dimension_type a_dimToGet) const;

    image_2d_sptr     GetImage(size_type a_z) const;

    template <typename T_Storage>
    void              SetImage(dimension_type a_dim,
                               const Image_T<p_image::dim_2d, value_type, T_Storage>& a_image);

    template <typename T_Storage>
    void              SetImage(size_type a_x, size_type a_y, size_type a_z, 
                               const Image_T<p_image::dim_2d, value_type, T_Storage>& a_image);

    using base_type::Load;
    using base_type::Create;
    using base_type::AddPadding;
    using base_type::GetWidth;
    using base_type::GetHeight;
    using base_type::GetDimensions;
    using base_type::IsValid;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_ColorType, typename T_StorageType, bool T_Const>
  template <typename T_Storage>
  void
    Image_T<p_image::dim_3d, T_ColorType, T_StorageType, T_Const>::
    SetImage(dimension_type a_dim,
             const Image_T<p_image::dim_2d, value_type, T_Storage>& a_image)
  { SetImage(a_dim[0], a_dim[1], a_dim[2], a_image); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_ColorType, typename T_StorageType, bool T_Const>
  template <typename T_Storage>
  void
    Image_T<p_image::dim_3d, T_ColorType, T_StorageType, T_Const>::
    SetImage(size_type a_x, size_type a_y, size_type a_z, 
             const Image_T<p_image::dim_2d, value_type, T_Storage>& a_image)
  {
    const auto imgDim = a_image.GetDimensions();

    TLOC_ASSERT(imgDim[0] + a_x <= this->GetDimensions()[0], 
                "Incoming image does not fit in X");
    TLOC_ASSERT(imgDim[1] + a_y <= this->GetDimensions()[1], 
                "Incoming image does not fit in Y");
    TLOC_ASSERT(a_z <= this->GetDimensions()[2], 
                "Incoming image does not fit in Z");

    for (size_type y = 0; y < imgDim[1]; ++y)
    {
      for (size_type x = 0; x < imgDim[0]; ++x)
      {
        SetPixel(x + a_x, y + a_y, a_z, a_image.GetPixel(x, y));
      }
    }
  }

  // -----------------------------------------------------------------------
  // typedefs

  // -----------------------------------------------------------------------
  // 2D

  // default image type
  typedef Image_T<p_image::dim_2d, gfx_t::Color>            Image;

  typedef Image_T<p_image::dim_2d, gfx_t::color_rgba>       image_rgba;
  typedef Image_T<p_image::dim_2d, gfx_t::color_rgb>        image_rgb;
  typedef Image_T<p_image::dim_2d, gfx_t::color_rg>         image_rg;
  typedef Image_T<p_image::dim_2d, gfx_t::color_r>          image_r;

  typedef Image_T<p_image::dim_2d, gfx_t::color_u16_rgba>   image_u16_rgba;
  typedef Image_T<p_image::dim_2d, gfx_t::color_u16_rgb>    image_u16_rgb;
  typedef Image_T<p_image::dim_2d, gfx_t::color_u16_rg>     image_u16_rg;
  typedef Image_T<p_image::dim_2d, gfx_t::color_u16_r>      image_u16_r;

  typedef Image_T<p_image::dim_2d, gfx_t::color_f32_rgba>   image_f32_rgba;
  typedef Image_T<p_image::dim_2d, gfx_t::color_f32_rgb>    image_f32_rgb;
  typedef Image_T<p_image::dim_2d, gfx_t::color_f32_rg>     image_f32_rg;
  typedef Image_T<p_image::dim_2d, gfx_t::color_f32_r>      image_f32_r;

  TLOC_TYPEDEF_ALL_SMART_PTRS(Image, image);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Image, image);

  typedef Image_T<p_image::dim_2d, gfx_t::color_rgba, 
                  p_image::storage::External>                image_stream_rgba;
  typedef Image_T<p_image::dim_2d, gfx_t::color_rgb, 
                  p_image::storage::External>                image_stream_rgb;
  typedef Image_T<p_image::dim_2d, gfx_t::color_rg, 
                  p_image::storage::External>                image_stream_rg;
  typedef Image_T<p_image::dim_2d, gfx_t::color_r, 
                  p_image::storage::External>                image_stream_r;

  typedef Image_T<p_image::dim_2d, gfx_t::color_u16_rgba, 
                  p_image::storage::External>                image_stream_u16_rgba;
  typedef Image_T<p_image::dim_2d, gfx_t::color_u16_rgb, 
                  p_image::storage::External>                image_stream_u16_rgb;
  typedef Image_T<p_image::dim_2d, gfx_t::color_u16_rg, 
                  p_image::storage::External>                image_stream_u16_rg;
  typedef Image_T<p_image::dim_2d, gfx_t::color_u16_r, 
                  p_image::storage::External>                image_stream_u16_r;

  typedef Image_T<p_image::dim_2d, gfx_t::color_f32_rgba, 
                  p_image::storage::External>                image_stream_f32_rgba;
  typedef Image_T<p_image::dim_2d, gfx_t::color_f32_rgb, 
                  p_image::storage::External>                image_stream_f32_rgb;
  typedef Image_T<p_image::dim_2d, gfx_t::color_f32_rg, 
                  p_image::storage::External>                image_stream_f32_rg;
  typedef Image_T<p_image::dim_2d, gfx_t::color_f32_r, 
                  p_image::storage::External>                image_stream_f32_r;

  typedef Image_T<p_image::dim_2d, gfx_t::color_rgba, 
                  p_image::storage::External, true>          image_stream_const_rgba;
  typedef Image_T<p_image::dim_2d, gfx_t::color_rgb, 
                  p_image::storage::External, true>          image_stream_const_rgb;
  typedef Image_T<p_image::dim_2d, gfx_t::color_rg, 
                  p_image::storage::External, true>          image_stream_const_rg;
  typedef Image_T<p_image::dim_2d, gfx_t::color_r, 
                  p_image::storage::External, true>          image_stream_const_r;

  typedef Image_T<p_image::dim_2d, gfx_t::color_u16_rgba, 
                  p_image::storage::External, true>          image_stream_u16_const_rgba;
  typedef Image_T<p_image::dim_2d, gfx_t::color_u16_rgb, 
                  p_image::storage::External, true>          image_stream_u16_const_rgb;
  typedef Image_T<p_image::dim_2d, gfx_t::color_u16_rg, 
                  p_image::storage::External, true>          image_stream_u16_const_rg;
  typedef Image_T<p_image::dim_2d, gfx_t::color_u16_r, 
                  p_image::storage::External, true>          image_stream_u16_const_r;

  typedef Image_T<p_image::dim_2d, gfx_t::color_f32_rgba, 
                  p_image::storage::External, true>          image_stream_f32_const_rgba;
  typedef Image_T<p_image::dim_2d, gfx_t::color_f32_rgb, 
                  p_image::storage::External, true>          image_stream_f32_const_rgb;
  typedef Image_T<p_image::dim_2d, gfx_t::color_f32_rg, 
                  p_image::storage::External, true>          image_stream_f32_const_rg;
  typedef Image_T<p_image::dim_2d, gfx_t::color_f32_r, 
                  p_image::storage::External, true>          image_stream_f32_const_r;

  // -----------------------------------------------------------------------
  // 3D

  // default image type
  typedef Image_T<p_image::dim_3d, gfx_t::Color>            Image3D;

  typedef Image_T<p_image::dim_3d, gfx_t::color_rgba>       image_3d_rgba;
  typedef Image_T<p_image::dim_3d, gfx_t::color_rgb>        image_3d_rgb;
  typedef Image_T<p_image::dim_3d, gfx_t::color_rg>         image_3d_rg;
  typedef Image_T<p_image::dim_3d, gfx_t::color_r>          image_3d_r;

  typedef Image_T<p_image::dim_3d, gfx_t::color_u16_rgba>   image_3d_u16_rgba;
  typedef Image_T<p_image::dim_3d, gfx_t::color_u16_rgb>    image_3d_u16_rgb;
  typedef Image_T<p_image::dim_3d, gfx_t::color_u16_rg>     image_3d_u16_rg;
  typedef Image_T<p_image::dim_3d, gfx_t::color_u16_r>      image_3d_u16_r;

  typedef Image_T<p_image::dim_3d, gfx_t::color_f32_r>      image_3d_f32_r;

  TLOC_TYPEDEF_ALL_SMART_PTRS(Image3D, image_3d);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Image3D, image_3d);

  typedef Image_T<p_image::dim_3d, gfx_t::color_rgba,
                  p_image::storage::External>               image_3d_stream_rgba;
  typedef Image_T<p_image::dim_3d, gfx_t::color_rgb, 
                  p_image::storage::External>               image_3d_stream_rgb;
  typedef Image_T<p_image::dim_3d, gfx_t::color_rg,
                  p_image::storage::External>               image_3d_stream_rg;
  typedef Image_T<p_image::dim_3d, gfx_t::color_r, 
                  p_image::storage::External>               image_3d_stream_r;

  typedef Image_T<p_image::dim_3d, gfx_t::color_u16_rgba,
                  p_image::storage::External>               image_3d_stream_u16_rgba;
  typedef Image_T<p_image::dim_3d, gfx_t::color_u16_rgb,
                  p_image::storage::External>               image_3d_stream_u16_rgb;
  typedef Image_T<p_image::dim_3d, gfx_t::color_u16_rg, 
                  p_image::storage::External>               image_3d_stream_u16_rg;
  typedef Image_T<p_image::dim_3d, gfx_t::color_u16_r, 
                  p_image::storage::External>               image_3d_stream_u16_r;

  typedef Image_T<p_image::dim_3d, gfx_t::color_f32_r,
                  p_image::storage::External>               image_3d_stream_f32_r;

  typedef Image_T<p_image::dim_3d, gfx_t::color_rgba,
                  p_image::storage::External, true>         image_3d_stream_const_rgba;
  typedef Image_T<p_image::dim_3d, gfx_t::color_rgb,
                  p_image::storage::External, true>         image_3d_stream_const_rgb;
  typedef Image_T<p_image::dim_3d, gfx_t::color_rg,
                  p_image::storage::External, true>         image_3d_stream_const_rg;
  typedef Image_T<p_image::dim_3d, gfx_t::color_r,
                  p_image::storage::External, true>         image_3d_stream_const_r;

  typedef Image_T<p_image::dim_3d, gfx_t::color_u16_rgba,
                  p_image::storage::External, true>         image_3d_stream_u16_const_rgba;
  typedef Image_T<p_image::dim_3d, gfx_t::color_u16_rgb,
                  p_image::storage::External, true>         image_3d_stream_u16_const_rgb;
  typedef Image_T<p_image::dim_3d, gfx_t::color_u16_rg, 
                  p_image::storage::External, true>         image_3d_stream_u16_const_rg;
  typedef Image_T<p_image::dim_3d, gfx_t::color_u16_r, 
                  p_image::storage::External, true>         const_jimage_3d_stream_u16_r;

  typedef Image_T<p_image::dim_3d, gfx_t::color_f32_r,
                  p_image::storage::External, true>         image_3d_stream_f32_const_r;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::Color>);

  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_rgba>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_rgb>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_rg>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_r>);

  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_u16_rgba>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_u16_rgb>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_u16_rg>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_u16_r>);

  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_f32_r>);
  
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_rgba TLOC_COMMA p_image::storage::External>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_rgb TLOC_COMMA p_image::storage::External>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_rg TLOC_COMMA p_image::storage::External>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_r TLOC_COMMA p_image::storage::External>);

  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_u16_rgba TLOC_COMMA p_image::storage::External>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_u16_rgb TLOC_COMMA p_image::storage::External>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_u16_rg TLOC_COMMA p_image::storage::External>);
  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_u16_r TLOC_COMMA p_image::storage::External>);

  TLOC_EXTERN_TEMPLATE_CLASS(Image_T<p_image::dim_2d TLOC_COMMA gfx_t::color_f32_r TLOC_COMMA p_image::storage::External>);

  // ```````````````````````````````````````````````````````````````````````
  // u8 images

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_rgba, image_rgba);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_rgba, image_stream_rgba);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_const_rgba, image_stream_const_rgba);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_rgba, image_rgba);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_rgba, image_stream_rgba);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_const_rgba, image_stream_const_rgba);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_rgb, image_rgb);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_rgb, image_stream_rgb);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_const_rgb, image_stream_const_rgb);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_rgb, image_rgb);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_rgb, image_stream_rgb);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_const_rgb, image_stream_const_rgb);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_rg, image_rg);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_rg, image_stream_rg);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_const_rg, image_stream_const_rg);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_rg, image_rg);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_rg, image_stream_rg);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_const_rg, image_stream_const_rg);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_r, image_r);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_r, image_stream_r);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_const_r, image_stream_const_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_r, image_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_r, image_stream_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_const_r, image_stream_const_r);

  // ```````````````````````````````````````````````````````````````````````
  // u16 images

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_u16_rgba, image_u16_rgba);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_u16_rgba, image_stream_u16_rgba);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_u16_const_rgba, image_stream_u16_const_rgba);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_u16_rgba, image_u16_rgba);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_u16_rgba, image_stream_u16_rgba);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_u16_const_rgba, image_stream_u16_const_rgba);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_u16_rgb, image_u16_rgb);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_u16_rgb, image_stream_u16_rgb);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_u16_const_rgb, image_stream_u16_const_rgb);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_u16_rgb, image_u16_rgb);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_u16_rgb, image_stream_u16_rgb);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_u16_const_rgb, image_stream_u16_const_rgb);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_u16_rg, image_u16_rg);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_u16_rg, image_stream_u16_rg);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_u16_const_rg, image_stream_u16_const_rg);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_u16_rg, image_u16_rg);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_u16_rg, image_stream_u16_rg);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_u16_const_rg, image_stream_u16_const_rg);

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_u16_r, image_u16_r);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_u16_r, image_stream_u16_r);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_u16_const_r, image_stream_u16_const_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_u16_r, image_u16_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_u16_r, image_stream_u16_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_u16_const_r, image_stream_u16_const_r);

  // ```````````````````````````````````````````````````````````````````````
  // special images

  TLOC_TYPEDEF_ALL_SMART_PTRS(image_f32_r, image_f32_r);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_f32_r, image_stream_f32_r);
  TLOC_TYPEDEF_ALL_SMART_PTRS(image_stream_f32_const_r, image_stream_f32_const_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_f32_r, image_f32_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_f32_r, image_stream_f32_r);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(image_stream_f32_const_r, image_stream_f32_const_r);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::Image);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::Image);

// -----------------------------------------------------------------------
// extern templates

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_rgba);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_rgba);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_const_rgba);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_rgba);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_rgba);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_const_rgba);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_rgb);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_rgb);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_const_rgb);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_rgb);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_rgb);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_const_rgb);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_rg);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_rg);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_const_rg);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_rg);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_rg);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_const_rg);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_r);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_r);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_const_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_const_r);

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_u16_rgba);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_u16_rgba);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_u16_const_rgba);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_u16_rgba);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_u16_rgba);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_u16_const_rgba);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_u16_rgb);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_u16_rgb);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_u16_const_rgb);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_u16_rgb);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_u16_rgb);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_u16_const_rgb);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_u16_rg);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_u16_rg);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_u16_const_rg);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_u16_rg);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_u16_rg);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_u16_const_rg);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_u16_r);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_u16_r);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_u16_const_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_u16_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_u16_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_u16_const_r);

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_f32_r);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_f32_r);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_med::image_stream_f32_const_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_f32_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_f32_r);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_med::image_stream_f32_const_r);

#endif