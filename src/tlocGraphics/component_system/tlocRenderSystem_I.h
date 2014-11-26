#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_I_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_I_H_

#include <tlocCore/utilities/tlocCheckpoints.h>

namespace tloc { namespace graphics { namespace component_system {

  class RenderSystem_I
  {
  public:
    TLOC_DECL_GETTER(bool, IsSortingByMaterialEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledSortingByMaterial);

  protected:
    TLOC_DECL_GETTER_NON_CONST(bool, DoGetDirtyAndUmark);

  protected:
    RenderSystem_I();

  private:
    core_utils::Checkpoints   m_flags;
  };

};};};

#endif