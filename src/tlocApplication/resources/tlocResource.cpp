#include "tlocResource.h"
#include <tlocGraphics/media/tlocImageLoader.h>

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

  };

};};};