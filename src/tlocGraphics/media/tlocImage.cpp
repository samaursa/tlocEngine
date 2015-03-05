#include "tlocImage.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/logging/tlocLogger.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace graphics { namespace media {

  namespace
  {
    enum
    {
      width   = types::dimension::width,
      height  = types::dimension::height,
      depth   = types::dimension::depth,
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // ImageBase_TI<2D>

  ImageBase_TI<p_image::dim_2d>::
    ImageBase_TI()
    : m_dim(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ImageBase_TI<p_image::dim_2d>::
    ~ImageBase_TI()
  { }

  // ///////////////////////////////////////////////////////////////////////
  // ImageBase_TI<3D>

  ImageBase_TI<p_image::dim_3d>::
    ImageBase_TI()
    : m_dim(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ImageBase_TI<p_image::dim_3d>::
    ~ImageBase_TI()
  { }

  // ///////////////////////////////////////////////////////////////////////
  // Image_TI<>

#define TLOC_IMAGE_INTERNAL_TEMPS   typename T_Dim, typename T_ColorType
#define TLOC_IMAGE_INTERNAL_PARAMS  T_Dim, T_ColorType, p_image::storage::Internal, false
#define TLOC_IMAGE_INTERNAL_TYPE    typename Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    Image_TI()
    : base_type()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    ~Image_TI()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  TLOC_IMAGE_INTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    Load(const_color_ptr a_buffer, dimension_type a_dim, size_type a_channels)
  {
    if ( (a_buffer == nullptr) || core_ds::Sum(a_dim) == 0 || (a_channels == 0) )
    { return TLOC_ERROR(common_error_types::error_no_data); }

    // Check if a_size can accommodate a whole number of Color*
    TLOC_ASSERT( (a_channels == color_type::k_size),
      "The buffer has an invalid size!");

    const color_type* buffer = reinterpret_cast<const color_type*>(a_buffer.get());
    m_pixels.assign(buffer, buffer + (a_dim[0] * a_dim[1]));

    m_dim = a_dim;

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  TLOC_IMAGE_INTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    Load(const pixel_container_type& a_buffer, dimension_type a_dim)
  {
    if (core_ds::Product(a_dim) != a_buffer.size())
    { return TLOC_ERROR(common_error_types::error_size_mismatch); }

    m_pixels = a_buffer;
    m_dim = a_dim;
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  TLOC_IMAGE_INTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    Create(dimension_type a_dim, const color_type& a_color)
  {
    m_dim = a_dim;

    m_pixels.clear();
    m_pixels.resize(core_ds::Product(m_dim), a_color);

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_ImageTI, typename T_ColorType>
  typename T_ImageTI::error_type
    DoAddPadding(T_ImageTI* a_this, types::Dimension2 a_padding, 
                 const T_ColorType& a_color)
  {
    typedef T_ImageTI                                   this_type;
    typedef typename this_type::dimension_type          dimension_type;
    typedef typename this_type::size_type               size_type;
    typedef typename this_type::error_type              error_type;
    typedef typename this_type::pixel_container_type    pixel_container_type;

    const dimension_type m_dim     = a_this->GetDimensions();
    pixel_container_type& m_pixels = a_this->m_pixels;

    dimension_type a_paddingTotal = core_ds::Add(a_padding, a_padding);
    dimension_type newDim = core_ds::Add(m_dim, a_paddingTotal);

    pixel_container_type newImg(core_ds::Product(newDim));

    for (size_type y = 0; y < newDim[1]; ++y)
    {
      for (size_type x = 0; x < newDim[0]; ++x)
      {
        tl_int index = core_utils::GetIndex(newDim, core_ds::MakeTuple(x, y));

        if (x < a_padding[0] || (x >= m_dim[0] + a_padding[0]) ||
            y < a_padding[1] || (y >= m_dim[1] + a_padding[1]) )
        {
          newImg[index] = a_color;
        }
        else
        {
          tl_int currImgIndex = core_utils::GetIndex
            (m_dim, core_ds::MakeTuple(x - a_padding[0],
                                       y - a_padding[1]));

          newImg[index] = m_pixels[currImgIndex];
        }
      }
    }

    this_type temp;
    error_type err = a_this->Load(newImg, newDim);

    return err;
  }

  template <typename T_ImageTI, typename T_ColorType>
  typename T_ImageTI::error_type
    DoAddPadding(T_ImageTI* a_this, types::Dimension3 a_padding, 
                 const T_ColorType& a_color)
  {
    typedef T_ImageTI                                   this_type;
    typedef typename this_type::dimension_type          dimension_type;
    typedef typename this_type::size_type               size_type;
    typedef typename this_type::error_type              error_type;
    typedef typename this_type::pixel_container_type    pixel_container_type;

    const dimension_type m_dim     = a_this->GetDimensions();
    pixel_container_type& m_pixels = a_this->m_pixels;

    dimension_type a_paddingTotal = core_ds::Add(a_padding, a_padding);
    dimension_type newDim = core_ds::Add(m_dim, a_paddingTotal);

    pixel_container_type newImg(core_ds::Product(newDim));

    for (size_type z = 0; z < newDim[2]; ++z)
    {
      for (size_type y = 0; y < newDim[1]; ++y)
      {
        for (size_type x = 0; x < newDim[0]; ++x)
        {
          tl_int index = core_utils::GetIndex(newDim, core_ds::MakeTuple(x, y, z));

          if (x < a_padding[0] || (x >= m_dim[0] + a_padding[0]) ||
              y < a_padding[1] || (y >= m_dim[1] + a_padding[1]) ||
              z < a_padding[2] || (z >= m_dim[2] + a_padding[2]) )
          {
            newImg[index] = a_color;
          }
          else
          {
            tl_int currImgIndex = core_utils::GetIndex
              (m_dim, core_ds::MakeTuple(x - a_padding[0],
                                         y - a_padding[1], 
                                         z - a_padding[2]));

            newImg[index] = m_pixels[currImgIndex];
          }
        }
      }
    }

    this_type temp;
    error_type err = a_this->Load(newImg, newDim);

    return err;
  }

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  TLOC_IMAGE_INTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    AddPadding(dimension_type a_padding, const color_type& a_color)
  { return DoAddPadding(this, a_padding, a_color); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  bool
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    IsValid() const
  {
    return GetDimensions()[0] > 0 &&
           GetDimensions()[1] > 0 &&
           (m_pixels.size() == m_dim[0] * m_dim[1]);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  TLOC_IMAGE_INTERNAL_TYPE::const_color_type_ptr
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    get() const
  {
    return const_color_type_ptr(&*m_pixels.begin());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  TLOC_IMAGE_INTERNAL_TYPE::const_color_type_ptr
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    operator[](tl_int a_index) const
  {
    return const_color_type_ptr(&m_pixels[a_index]);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  void
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    DoSet(tl_int a_index, const color_type& a_color)
  { m_pixels[a_index] = a_color; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_INTERNAL_TEMPS>
  const TLOC_IMAGE_INTERNAL_TYPE::color_type&
    Image_TI<TLOC_IMAGE_INTERNAL_PARAMS>::
    DoGet(tl_int a_index) const
  { return m_pixels[a_index]; }

  // ///////////////////////////////////////////////////////////////////////
  // Image_TI<External>

#define TLOC_IMAGE_EXTERNAL_TEMPS   typename T_Dim, typename T_ColorType, bool T_Const
#define TLOC_IMAGE_EXTERNAL_PARAMS  T_Dim, T_ColorType, p_image::storage::External, T_Const
#define TLOC_IMAGE_EXTERNAL_TYPE    typename Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    Image_TI()
    : base_type()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    ~Image_TI()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  TLOC_IMAGE_EXTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    Load(color_ptr a_buffer, dimension_type a_dim, size_type a_channels)
  {
    if ( (a_buffer == nullptr) || a_dim[0] == 0 || a_dim[1] == 0 ||
         (a_channels == 0) )
    { return TLOC_ERROR(common_error_types::error_no_data); }

    if (a_channels != color_type::k_size)
    { return TLOC_ERROR(gfx_err::error_image_invalid_channels); }

    m_pixels.reset( reinterpret_cast<color_type*>(a_buffer.get()) );
    m_dim = a_dim;

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  TLOC_IMAGE_EXTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    Create(dimension_type , const color_type& )
  {
    TLOC_LOG_GFX_WARN_FILENAME_ONLY() << 
      "Create() has no effect in Image_T<> with external storage";
    return ErrorFailure;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  TLOC_IMAGE_EXTERNAL_TYPE::error_type
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    AddPadding(dimension_type , const color_type& )
  {
    TLOC_LOG_GFX_WARN_FILENAME_ONLY() << 
      "Cannot add padding to Image_T<> with external storage";
    return ErrorFailure;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  bool
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    IsValid() const
  {
    return GetDimensions()[0] > 0 &&
           GetDimensions()[1] > 0 &&
           m_pixels != nullptr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  TLOC_IMAGE_EXTERNAL_TYPE::const_color_type_ptr
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    get() const
  {
    return m_pixels;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  TLOC_IMAGE_EXTERNAL_TYPE::const_color_type_ptr
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    operator[](tl_int a_index) const
  {
    return const_color_type_ptr( &m_pixels.get()[a_index] );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Pixels, typename T_ColorType>
  void
    DoDoSet(T_Pixels& a_pixels, tl_int a_index, T_ColorType& a_color, 
          p_image::storage::non_const_storage)
  { a_pixels.get()[a_index] = a_color; }

  template <typename T_Pixels, typename T_ColorType>
  void
    DoDoSet(T_Pixels& , tl_int , T_ColorType& , 
          p_image::storage::const_storage)
  { 
    TLOC_LOG_GFX_WARN_FILENAME_ONLY() << 
      "Image with const external storage cannot set pixel values";
  }

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  void
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    DoSet(tl_int a_index, const color_type& a_color)
  { DoDoSet(m_pixels, a_index, a_color, Loki::Int2Type<T_Const>()); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_EXTERNAL_TEMPS>
  const TLOC_IMAGE_EXTERNAL_TYPE::color_type&
    Image_TI<TLOC_IMAGE_EXTERNAL_PARAMS>::
    DoGet(tl_int a_index) const
  { return m_pixels.get()[a_index]; }

  // ///////////////////////////////////////////////////////////////////////
  // Image_T<2D>

#define TLOC_IMAGE_TEMPS    typename T_ColorType, typename T_StorageType, bool T_Const
#define TLOC_IMAGE_PARAMS   p_image::dim_2d, T_ColorType, T_StorageType, T_Const
#define TLOC_IMAGE_TYPE     typename Image_T<TLOC_IMAGE_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_TEMPS>
  Image_T<TLOC_IMAGE_PARAMS>::
    Image_T()
    : base_type()
  { }


  template <TLOC_IMAGE_TEMPS>
  void
    Image_T<TLOC_IMAGE_PARAMS>::
    SetPixel(size_type a_x, size_type a_y, const color_type& a_color)
  {
    tl_int index = core_utils::GetIndex(this->GetDimensions(), 
                                        core_ds::MakeTuple(a_x, a_y));
    this->DoSet(index, a_color);
  }

  template <TLOC_IMAGE_TEMPS>
  void
    Image_T<TLOC_IMAGE_PARAMS>::
    SetImage(size_type a_x, size_type a_y, const this_type& a_image)
  {
    const dimension_type imgDim = a_image.GetDimensions();

    TLOC_ASSERT(imgDim[0] + a_x <= this->GetDimensions()[0], 
                "Incoming image does not fit in X");
    TLOC_ASSERT(imgDim[1] + a_y <= this->GetDimensions()[1], 
                "Incoming image does not fit in Y");

    for (size_type y = 0; y < imgDim[1]; ++y)
    {
      for (size_type x = 0; x < imgDim[0]; ++x)
      {
        SetPixel(x + a_x, y + a_y, a_image.GetPixel(x, y));
      }
    }
  }

  template <TLOC_IMAGE_TEMPS>
  const TLOC_IMAGE_TYPE::color_type&
    Image_T<TLOC_IMAGE_PARAMS>::
    GetPixel(size_type a_x, size_type a_y) const
  {
    tl_int index = core_utils::GetIndex(this->GetDimensions(), 
                                        core_ds::MakeTuple(a_x, a_y));
    return this->DoGet(index);
  }

  template <TLOC_IMAGE_TEMPS>
  TLOC_IMAGE_TYPE::image_sptr
    Image_T<TLOC_IMAGE_PARAMS>::
    GetImage(size_type a_x, size_type a_y, dimension_type a_dimToGet) const
  {
    TLOC_ASSERT(a_x + a_dimToGet[0] <= this->GetDimensions()[0], 
                "Dimensions out of range");
    TLOC_ASSERT(a_y + a_dimToGet[1] <= this->GetDimensions()[1], 
                "Dimensions out of range");

    image_sptr img = core_sptr::MakeShared<this_type>();
    img->Create(a_dimToGet, color_type::COLOR_BLACK);

    for (size_type y = 0; y < a_dimToGet[1]; ++y)
    {
      for (size_type x = 0; x < a_dimToGet[0]; ++x)
      {
        img->SetPixel(x, y, GetPixel(x + a_x, y + a_y));
      }
    }

    return img;
  }

  // ///////////////////////////////////////////////////////////////////////
  // Image_T<3D>

#define TLOC_IMAGE_3D_TEMPS    typename T_ColorType, typename T_StorageType, bool T_Const
#define TLOC_IMAGE_3D_PARAMS   p_image::dim_3d, T_ColorType, T_StorageType, T_Const
#define TLOC_IMAGE_3D_TYPE     typename Image_T<TLOC_IMAGE_3D_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_IMAGE_3D_TEMPS>
  Image_T<TLOC_IMAGE_3D_PARAMS>::
    Image_T()
    : base_type()
  { }


  template <TLOC_IMAGE_3D_TEMPS>
  void
    Image_T<TLOC_IMAGE_3D_PARAMS>::
    SetPixel(size_type a_x, size_type a_y, size_type a_z, 
             const color_type& a_color)
  {
    tl_int index = core_utils::GetIndex(this->GetDimensions(), 
                                        core_ds::MakeTuple(a_x, a_y, a_z));
    this->DoSet(index, a_color);
  }

  template <TLOC_IMAGE_3D_TEMPS>
  void
    Image_T<TLOC_IMAGE_3D_PARAMS>::
    SetImage(size_type a_x, size_type a_y, size_type a_z, 
             const this_type& a_image)
  {
    const dimension_type imgDim = a_image.GetDimensions();

    TLOC_ASSERT(imgDim[0] + a_x <= this->GetDimensions()[0], 
                "Incoming image does not fit in X");
    TLOC_ASSERT(imgDim[1] + a_y <= this->GetDimensions()[1], 
                "Incoming image does not fit in Y");
    TLOC_ASSERT(imgDim[2] + a_z <= this->GetDimensions()[2], 
                "Incoming image does not fit in Z");

    for (size_type z = 0; z < imgDim[2]; ++z)
    {
      for (size_type y = 0; y < imgDim[1]; ++y)
      {
        for (size_type x = 0; x < imgDim[0]; ++x)
        {
          SetPixel(x + a_x, y + a_y, z + a_z, a_image.GetPixel(x, y, z));
        }
      }
    }
  }

  template <TLOC_IMAGE_3D_TEMPS>
  const TLOC_IMAGE_3D_TYPE::color_type&
    Image_T<TLOC_IMAGE_3D_PARAMS>::
    GetPixel(size_type a_x, size_type a_y, size_type a_z) const
  {
    tl_int index = core_utils::GetIndex(this->GetDimensions(), 
                                        core_ds::MakeTuple(a_x, a_y, a_z));
    return this->DoGet(index);
  }

  template <TLOC_IMAGE_3D_TEMPS>
  TLOC_IMAGE_3D_TYPE::image_sptr
    Image_T<TLOC_IMAGE_3D_PARAMS>::
    GetImage(size_type a_x, size_type a_y, size_type a_z, 
             dimension_type a_dimToGet) const
  {
    TLOC_ASSERT(a_x + a_dimToGet[0] <= this->GetDimensions()[0], 
                "Dimensions out of range");
    TLOC_ASSERT(a_y + a_dimToGet[1] <= this->GetDimensions()[1], 
                "Dimensions out of range");
    TLOC_ASSERT(a_z + a_dimToGet[2] <= this->GetDimensions()[2], 
                "Dimensions out of range");

    image_sptr img = core_sptr::MakeShared<this_type>();
    img->Create(a_dimToGet, color_type::COLOR_BLACK);

    for (size_type z = 0; z < a_dimToGet[2]; ++z)
    {
      for (size_type y = 0; y < a_dimToGet[1]; ++y)
      {
        for (size_type x = 0; x < a_dimToGet[0]; ++x)
        {
          img->SetPixel(x, y, z, GetPixel(x + a_x, y + a_y, z + a_z));
        }
      }
    }

    return img;
  }

  template <TLOC_IMAGE_3D_TEMPS>
  TLOC_IMAGE_3D_TYPE::image_2d_sptr
    Image_T<TLOC_IMAGE_3D_PARAMS>::
    GetImage(size_type a_z) const
  {
    const auto& dim = GetDimensions();
    const auto index = core_utils::GetIndex(dim, core_ds::MakeTuple(0u, 0u, a_z));

    auto img = core_sptr::MakeShared<image_2d_type>();
    img->Load( this->operator[](index)->get(), 
               core_ds::MakeTuple(dim[0], dim[1]), color_type::k_channels);

    return img;
  }
  
  // -----------------------------------------------------------------------
  // explicitly instantiate Image_T<> types
  
  using namespace gfx_t;

  typedef p_image::storage::Internal          internal_store;
  typedef p_image::storage::External          external_store;

#define TLOC_EXPLICITLY_INSTANTIATE_IMAGE(_dim_, _colorType_)\
  template class Image_TI<_dim_, _colorType_, internal_store>;\
  template class Image_TI<_dim_, _colorType_, external_store>;\
  template class Image_TI<_dim_, _colorType_, external_store, true>;\
  template class Image_T<_dim_, _colorType_, internal_store>;\
  template class Image_T<_dim_, _colorType_, external_store>;\
  template class Image_T<_dim_, _colorType_, external_store, true>

  using p_image::dim_2d; 
  using p_image::dim_3d;
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_2d, Color);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_2d, color_rgb);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_2d, color_rg);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_2d, color_r);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_2d, color_u16_rgba);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_2d, color_u16_rgb);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_2d, color_u16_rg);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_2d, color_u16_r);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_2d, color_f32_r);

  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_3d, Color);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_3d, color_rgb);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_3d, color_rg);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_3d, color_r);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_3d, color_u16_rgba);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_3d, color_u16_rgb);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_3d, color_u16_rg);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_3d, color_u16_r);
  TLOC_EXPLICITLY_INSTANTIATE_IMAGE(dim_3d, color_f32_r);

};};};

//------------------------------------------------------------------------
// Explicitly instantiate the container

using namespace tloc::gfx_med;
using namespace tloc::gfx_t;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

// ```````````````````````````````````````````````````````````````````````
// Instantiate all color VirtualPtrs

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_rgba::color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_rgb::color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_rg::color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_r::color_type_ptr);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_rgba::color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_rgb::color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_rg::color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_r::color_type_ptr);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_f32_r::color_type_ptr);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_rgba::const_color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_rgb::const_color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_rg::const_color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_r::const_color_type_ptr);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_rgba::const_color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_rgb::const_color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_rg::const_color_type_ptr);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(image_u16_r::const_color_type_ptr);

// ```````````````````````````````````````````````````````````````````````
// u8 images

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_rgba);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_rgb);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_rg);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_r);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_rgba);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_const_rgba);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_rgb);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_const_rgb);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_rg);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_const_rg);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_r);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_const_r);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_rgba);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_rgb);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_rg);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_r);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_rgba);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_const_rgba);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_rgb);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_const_rgb);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_rg);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_const_rg);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_r);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_const_r);

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_rgba);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_rgb);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_rg);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_r);

// ```````````````````````````````````````````````````````````````````````
// u16 images

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_u16_rgba);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_u16_rgb);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_u16_rg);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_u16_r);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_u16_rgba);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_u16_const_rgba);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_u16_rgb);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_u16_const_rgb);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_u16_rg);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_u16_const_rg);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_u16_r);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_u16_const_r);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_u16_rgba);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_u16_rgb);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_u16_rg);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_u16_r);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_u16_rgba);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_u16_const_rgba);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_u16_rgb);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_u16_const_rgb);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_u16_rg);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_u16_const_rg);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_u16_r);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_u16_const_r);

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_u16_rgba);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_u16_rgb);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_u16_rg);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_u16_r);

// ```````````````````````````````````````````````````````````````````````
// special images

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_f32_r);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_f32_r);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(image_stream_f32_const_r);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_f32_r);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_f32_r);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(image_stream_f32_const_r);

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(color_f32_r);