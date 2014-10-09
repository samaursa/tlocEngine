#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_I_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_I_H_

#include <tlocCore/utilities/tlocCheckpoints.h>

namespace tloc { namespace graphics { namespace component_system {

  class RenderSystem_I
  {
  public:

    TLOC_DECL_GETTER(bool, IsUniformModelMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformModelMatrix);

    TLOC_DECL_GETTER(bool, IsAttributePosDataEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledAttributePosData);

    TLOC_DECL_GETTER(bool, IsUniformMVPMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformMVPMatrix);

    TLOC_DECL_GETTER(bool, IsUniformVPEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformVPMatrix);

    TLOC_DECL_GETTER(bool, IsUniformScaleMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformScaleMatrix);

  protected:
    RenderSystem_I();

  private:
    core_utils::Checkpoints   m_flags;
  };

};};};

#endif