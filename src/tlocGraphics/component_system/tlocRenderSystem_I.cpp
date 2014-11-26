#include "tlocRenderSystem_I.h"

namespace tloc { namespace graphics { namespace component_system {

  namespace {

    enum {

      k_enableSortingByMaterial,

      k_isDirty,

      k_count
    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // RenderSystem_I

  RenderSystem_I::
    RenderSystem_I()
    : m_flags(k_count)
  { 
    SetEnabledSortingByMaterial(true);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // sorting

  bool
    RenderSystem_I::
    IsSortingByMaterialEnabled() const
  { return m_flags.IsMarked(k_enableSortingByMaterial); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledSortingByMaterial(bool a_value)
  { m_flags[k_enableSortingByMaterial] = a_value; m_flags.Mark(k_isDirty); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // has any flag changed?

  bool
    RenderSystem_I::
    DoGetDirtyAndUmark()
  { return m_flags.ReturnAndUnmark(k_isDirty); }

};};};