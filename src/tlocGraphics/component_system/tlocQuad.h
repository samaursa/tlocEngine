#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_H_

#include <tlocCore/component_system/tlocComponent.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/data_types/tlocVertex.h>
#include <tlocGraphics/data_types/tlocRectangle.h>
#include <tlocGraphics/component_system/tlocComponentType.h>

namespace tloc { namespace graphics { namespace component_system {

  class Quad : public tloc::core::component_system::Component_T<Quad>
  {
  public:
    typedef Quad                      this_type;
    typedef Component_T<this_type>    base_type;
    typedef f32                       real_type;

    // If 1.0f, the Quad has a width/height of 1.0f
    typedef core::types::StrongType_T<real_type, 0>  size;

  public:
    Quad();
    Quad(size a_scale);
    void SetSize(size a_scale);

    TLOC_DECL_AND_DEF_GETTER(real_type, GetSize, m_size);

  private:
    real_type         m_size;
  };

  typedef core::smart_ptr::SharedPtr<Quad>    QuadPtr;
  typedef core::component_system::
    ComponentPool_TI<QuadPtr>                 QuadPool;

};};};

#endif