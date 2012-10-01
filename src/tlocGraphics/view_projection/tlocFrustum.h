#ifndef _TLOC_GRAPHICS_VIEW_PROJECTION_FRUSTUM_H
#define _TLOC_GRAPHICS_VIEW_PROJECTION_FRUSTUM_H

#include <tlocCore/data_structures/tlocTuple.h>

namespace tloc { namespace graphics { namespace view_projection {

  class Frustum
  {
  public:
    struct Planes
    {
      enum
      {
        k_near = 0,
        k_far,
        k_top,
        k_bottom,
        k_left,
        k_right,
        k_count,
      };

    private:
      Planes();
    };

  public:
    typedef tl_float                                    real_type;
    typedef core::Tuple<real_type, Planes::k_count>     cont_type;
    typedef tl_size                                     size_type;

  public:
    Frustum();
    ~Frustum();

    void BuildFrustum();

  private:
    cont_type m_planes;
  };

};};};

#endif