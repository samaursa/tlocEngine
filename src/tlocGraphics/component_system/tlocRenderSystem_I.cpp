#include "tlocRenderSystem_I.h"

namespace tloc { namespace graphics { namespace component_system {

  namespace {

    enum {

      k_enableSortingByMaterial,
      k_enableSortingFrontToBack,
      k_enableSortingBackToFront,
      k_enableSortingFrontToBack_2d,
      k_enableSortingBackToFront_2d,

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
    SetEnabledSortingFrontToBack(true);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RenderSystem_I::
    ~RenderSystem_I()
  { }

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

  bool
    RenderSystem_I::
    IsSortingFrontToBackEnabled() const
  { return m_flags.IsMarked(k_enableSortingFrontToBack); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledSortingFrontToBack(bool a_value)
  { 
    m_flags[k_enableSortingFrontToBack] = a_value; 

    if (IsSortingFrontToBackEnabled())
    { 
      SetEnabledSortingBackToFront_2D(false);
      SetEnabledSortingFrontToBack_2D(false);
      SetEnabledSortingBackToFront(false);
    }

    m_flags.Mark(k_isDirty);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsSortingBackToFrontEnabled() const
  { return m_flags.IsMarked(k_enableSortingBackToFront); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledSortingBackToFront(bool a_value)
  { 
    m_flags[k_enableSortingBackToFront] = a_value; 

    if (IsSortingBackToFrontEnabled())
    { 
      SetEnabledSortingBackToFront_2D(false);
      SetEnabledSortingFrontToBack_2D(false);
      SetEnabledSortingFrontToBack(false);
    }

    m_flags.Mark(k_isDirty); 
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsSortingFrontToBackEnabled_2D() const
  { return m_flags.IsMarked(k_enableSortingFrontToBack_2d); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledSortingFrontToBack_2D(bool a_value)
  { 
    m_flags[k_enableSortingFrontToBack_2d] = a_value; 

    if (IsSortingFrontToBackEnabled_2D())
    { 
      SetEnabledSortingBackToFront_2D(false);
      SetEnabledSortingFrontToBack(false);
      SetEnabledSortingBackToFront(false);
    }

    m_flags.Mark(k_isDirty);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsSortingBackToFrontEnabled_2D() const
  { return m_flags.IsMarked(k_enableSortingBackToFront_2d); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledSortingBackToFront_2D(bool a_value)
  { 
    m_flags[k_enableSortingBackToFront_2d] = a_value; 

    if (IsSortingBackToFrontEnabled_2D())
    { 
      SetEnabledSortingFrontToBack_2D(false);
      SetEnabledSortingFrontToBack(false);
      SetEnabledSortingBackToFront(false);
    }

    m_flags.Mark(k_isDirty); 
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // has any flag changed?

  bool
    RenderSystem_I::
    DoGetDirtyAndUmark()
  { return m_flags.ReturnAndUnmark(k_isDirty); }

};};};