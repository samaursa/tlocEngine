#include "tlocRenderSystem_I.h"

namespace tloc { namespace graphics { namespace component_system {

  namespace {

    enum {

      k_enableAttrPosData = 0,
      k_enableUniMVPMat,
      k_enableUniMVPInverseMat,
      k_enableUniModelMat,
      k_enableUniModelInverseMat,
      k_enableVPMat,
      k_enableVPInverseMat,
      k_enableMVMat,
      k_enableMVInverseMat,
      k_enableUniViewMat,
      k_enableUniViewInverseMat,
      k_enableUniProjMat,
      k_enableUniProjInverseMat,
      k_enableScaleMat,
      k_enableScaleInverseMat,
      k_enableNormalMat,

      k_enableSortingByMaterial,

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
    SetEnabledSortingByMaterial(true);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // model matrix

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
    IsUniformModelInverseMatrixEnabled() const
  { return m_flags.IsMarked(k_enableUniModelInverseMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformModelInverseMatrix(bool a_value)
  { m_flags[k_enableUniModelInverseMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // model view projection matrix

  bool
    RenderSystem_I::
    IsUniformMVPMatrixEnabled() const
  { return m_flags.IsMarked(k_enableUniMVPMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformMVPMatrix(bool a_value)
  { m_flags[k_enableUniMVPMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsUniformMVPInverseMatrixEnabled() const
  { return m_flags.IsMarked(k_enableUniMVPInverseMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformMVPInverseMatrix(bool a_value)
  { m_flags[k_enableUniMVPInverseMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // view projection matrix

  bool
    RenderSystem_I::
    IsUniformVPMatrixEnabled() const
  { return m_flags.IsMarked(k_enableVPMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformVPMatrix(bool a_value)
  { m_flags[k_enableVPMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsUniformVPInverseMatrixEnabled() const
  { return m_flags.IsMarked(k_enableVPInverseMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformVPInverseMatrix(bool a_value)
  { m_flags[k_enableVPInverseMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // model view matrix

  bool
    RenderSystem_I::
    IsUniformMVMatrixEnabled() const
  { return m_flags.IsMarked(k_enableMVMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformMVMatrix(bool a_value)
  { m_flags[k_enableMVMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsUniformMVInverseMatrixEnabled() const
  { return m_flags.IsMarked(k_enableMVInverseMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformMVInverseMatrix(bool a_value)
  { m_flags[k_enableMVInverseMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // view matrix

  bool
    RenderSystem_I::
    IsUniformViewMatrixEnabled() const
  { return m_flags.IsMarked(k_enableUniViewMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformViewMatrix(bool a_value)
  { m_flags[k_enableUniViewMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsUniformViewMatrixInverseEnabled() const
  { return m_flags.IsMarked(k_enableUniViewInverseMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformViewInverseMatrix(bool a_value)
  { m_flags[k_enableUniViewInverseMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // projection matrix

  bool
    RenderSystem_I::
    IsUniformProjectionEnabled() const
  { return m_flags.IsMarked(k_enableUniProjMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformProjectionMatrix(bool a_value)
  { m_flags[k_enableUniProjMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsUniformProjectionInverseEnabled() const
  { return m_flags.IsMarked(k_enableUniProjInverseMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformProjectionInverseMatrix(bool a_value)
  { m_flags[k_enableUniProjInverseMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // scale matrix

  bool
    RenderSystem_I::
    IsUniformScaleMatrixEnabled() const
  { return m_flags.IsMarked(k_enableScaleMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformScaleMatrix(bool a_value)
  { m_flags[k_enableScaleMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsUniformScaleInverseMatrixEnabled() const
  { return m_flags.IsMarked(k_enableScaleInverseMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformScaleInverseMatrix(bool a_value)
  { m_flags[k_enableScaleInverseMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    RenderSystem_I::
    IsUniformNormalMatrixEnabled() const
  { return m_flags.IsMarked(k_enableNormalMat); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RenderSystem_I::
    SetEnabledUniformNormalMatrix(bool a_value)
  { m_flags[k_enableNormalMat] = a_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // position attribute

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
  { m_flags[k_enableSortingByMaterial] = a_value; }

};};};