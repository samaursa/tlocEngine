#include "tlocRenderSystem_I.h"

namespace tloc { namespace graphics { namespace component_system {

  namespace {

    enum {

      k_enableAttrPosData = 0,
      k_enableUniMVP,
      k_enableUniModelMat,
      k_enableCameraVP,
      k_enableScaleMat,

      k_count
    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // RenderSystem_I

  RenderSystem_I::
    RenderSystem_I()
    : m_flags(k_count)
  { 
    SetEnabledUniformMVPMatrix(true);
    SetEnabledAttributePosData(true);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsUniformModelMatrixEnabled() const
  { return m_flags.IsMarked(k_enableUniModelMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformModelMatrix(bool a_value)
  { m_flags[k_enableUniModelMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsAttributePosDataEnabled() const
  { return m_flags.IsMarked(k_enableAttrPosData); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledAttributePosData(bool a_value)
  { m_flags[k_enableAttrPosData] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsUniformMVPMatrixEnabled() const
  { return m_flags.IsMarked(k_enableUniMVP); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformMVPMatrix(bool a_value)
  { m_flags[k_enableUniMVP] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsUniformVPEnabled() const
  { return m_flags.IsMarked(k_enableCameraVP); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformVPMatrix(bool a_value)
  { m_flags[k_enableCameraVP] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsUniformScaleMatrixEnabled() const
  { return m_flags.IsMarked(k_enableScaleMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformScaleMatrix(bool a_value)
  { m_flags[k_enableScaleMat] = a_value; }

};};};