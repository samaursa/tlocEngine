#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_I_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_I_H_

#include <tlocCore/utilities/tlocCheckpoints.h>

namespace tloc { namespace graphics { namespace component_system {

  class RenderSystem_I
  {
  public:
    TLOC_DECL_GETTER(bool, IsSortingByMaterialEnabled);
    virtual TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledSortingByMaterial);

    TLOC_DECL_GETTER(bool, IsSortingFrontToBackEnabled);
    virtual TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledSortingFrontToBack);

    TLOC_DECL_GETTER(bool, IsSortingBackToFrontEnabled);
    virtual TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledSortingBackToFront);

    TLOC_DECL_GETTER(bool, IsSortingFrontToBackEnabled_2D);
    virtual TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledSortingFrontToBack_2D);

    TLOC_DECL_GETTER(bool, IsSortingBackToFrontEnabled_2D);
    virtual TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledSortingBackToFront_2D);

    virtual void DisableSorting();

  protected:
    TLOC_DECL_GETTER_NON_CONST(bool, DoGetDirtyAndUmark);

  protected:
    RenderSystem_I();
    virtual ~RenderSystem_I();

  private:
    core_utils::Checkpoints   m_flags;
  };

};};};

#endif