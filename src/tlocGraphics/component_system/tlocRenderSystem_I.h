#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_I_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_I_H_

#include <tlocCore/utilities/tlocCheckpoints.h>

namespace tloc { namespace graphics { namespace component_system {

  class RenderSystem_I
  {
  public: // model matrix
    TLOC_DECL_GETTER(bool, IsUniformModelMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformModelMatrix);

    TLOC_DECL_GETTER(bool, IsUniformModelInverseMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformModelInverseMatrix);

  public: // model view projection matrix
    TLOC_DECL_GETTER(bool, IsUniformMVPMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformMVPMatrix);

    TLOC_DECL_GETTER(bool, IsUniformMVPInverseMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformMVPInverseMatrix);

  public: // view projection matrix
    TLOC_DECL_GETTER(bool, IsUniformVPMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformVPMatrix);

    TLOC_DECL_GETTER(bool, IsUniformVPInverseMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformVPInverseMatrix);

  public: // model view matrix
    TLOC_DECL_GETTER(bool, IsUniformMVMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformMVMatrix);

    TLOC_DECL_GETTER(bool, IsUniformMVInverseMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformMVInverseMatrix);

  public: // view matrix
    TLOC_DECL_GETTER(bool, IsUniformViewMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformViewMatrix);

    TLOC_DECL_GETTER(bool, IsUniformViewMatrixInverseEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformViewInverseMatrix);

  public: // projection matrix
    TLOC_DECL_GETTER(bool, IsUniformProjectionEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformProjectionMatrix);

    TLOC_DECL_GETTER(bool, IsUniformProjectionInverseEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformProjectionInverseMatrix);

  public: // scale matrix
    TLOC_DECL_GETTER(bool, IsUniformScaleMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformScaleMatrix);

    TLOC_DECL_GETTER(bool, IsUniformScaleInverseMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformScaleInverseMatrix);

  public: // normal matrix
    TLOC_DECL_GETTER(bool, IsUniformNormalMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformNormalMatrix);

  public: // position attribute
    TLOC_DECL_GETTER(bool, IsAttributePosDataEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledAttributePosData);

  public:
    TLOC_DECL_GETTER(bool, IsSortingByMaterialEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledSortingByMaterial);

  protected:
    RenderSystem_I();

  private:
    core_utils::Checkpoints   m_flags;
  };

};};};

#endif