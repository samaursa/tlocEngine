#include "tlocResource.h"
#include <tlocGraphics/media/tlocImageLoader.h>

#include <tlocCore/logging/tlocLogger.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace application { namespace resources {

  // ///////////////////////////////////////////////////////////////////////
  // Resource_I

  template <typename T>
  Resource_I::
    Resource_I(path_type a_path)
    : m_ucid(core::UCID<T>().GetClassID())
    , m_path(a_path)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Resource_I::
    ~Resource_I()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Resource_I::
    operator==(const this_type& a_other) const
  {
    return m_ucid == a_other.m_ucid &&
           m_path == a_other.m_path;
  }

  namespace f_resource {

    gfx_gl::texture_object_sptr
      LoadImageAsTextureObject(const core_io::Path& a_imagePath, 
                               const gfx_gl::TextureObject::Params& a_params)
    {
      using namespace gfx_med::f_image_loader;

      auto img = LoadImage(a_imagePath);

      if (img.second == k_image_unsupported)
      { return nullptr; }

      auto toPtr = core_sptr::MakeShared<gfx_gl::TextureObject>(a_params);

      if (img.second == k_image_png)
      { toPtr->Initialize(*img.first.Cast<gfx_med::image_sptr>()); }
      else if (img.second == k_image_jpeg)
      { toPtr->Initialize(*img.first.Cast<gfx_med::image_rgb_sptr>()); }

      return toPtr;
    }

    gfx_gl::texture_object_cube_map_sptr
      LoadImageAsTextureObjectCubeMap
      (const core_conts::ArrayFixed<core_io::Path, 6>& a_imagePaths,
       const gfx_gl::TextureObjectCubeMap::Params& a_params)
    {
      using namespace gfx_med::f_image_loader;

      auto toPtr = core_sptr::MakeShared<gfx_gl::TextureObjectCubeMap>(a_params);

      bool png = false, jpg = false;
      for (const auto& p : a_imagePaths)
      {
        const auto& ext = p.GetExtension().to_lower();

        if (ext == "png") { png = true; }
        if (ext == "jpg" || ext == "jpeg") { jpg = true; }
      }

      if (png && jpg)
      {
        TLOC_LOG_APP_ERR_FILENAME_ONLY() << "Cannot mix PNG and JPEG files";
        return nullptr;
      }

      core_conts::ArrayFixed<gfx_med::image_sptr, 6>      imagesPNG;
      core_conts::ArrayFixed<gfx_med::image_rgb_sptr, 6>  imagesJPG;

      for (int i = 0; i < 6; ++i)
      {
        auto img = LoadImage(a_imagePaths[i]);

        if (img.second == k_image_unsupported)
        { return nullptr; }

        if (img.second == k_image_png)
        { imagesPNG.push_back(img.first.Cast<gfx_med::image_sptr>()); }
        else if (img.second == k_image_jpeg)
        { imagesJPG.push_back(img.first.Cast<gfx_med::image_rgb_sptr>()); }
      }

      if (png)
      { toPtr->Initialize(imagesPNG); }
      else
      { toPtr->Initialize(imagesJPG); }

      return toPtr;
    }

  };

};};};

#include <tlocCore/containers/tlocArrayFixed.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ARRAY_FIXED(tl_core_io::Path, 6);