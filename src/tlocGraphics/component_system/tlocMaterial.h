#ifndef TLOC_MATERIAL_H
#define TLOC_MATERIAL_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/opengl/tlocObject.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace graphics { namespace component_system {

  class Material
    : public core_cs::Component_T<Material, components::material>
  {
  public:
    typedef core::component_system::Component_T
      <Material, components::material>                      base_type;
    typedef gl::shader_program_vptr                         shader_prog_ptr;

    typedef gl::shader_operator_vptr                        shader_op_ptr;
    typedef gl::const_shader_operator_vptr                  const_shader_op_ptr;
    typedef gl::shader_operator_vso                         shader_op_vso;
    typedef core::containers::tl_array<shader_op_vso>::type shader_op_cont;

    typedef core::string::String                            string_type;

  public:
    Material();
    Material(const Material& a_other);

    void AddShaderOperator(const const_shader_op_ptr& a_shaderOp);
    bool RemoveShaderOperator(const const_shader_op_ptr& a_shaderOp);
    void RemoveAllShaderOperators();

    bool operator ==(const Material& a_other) const;
    bool operator < (const Material& a_other) const;
    TLOC_DECLARE_OPERATORS(Material);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (string_type, GetVertexSource, m_vertexProgram);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (string_type, GetFragmentSource, m_fragmentProgram);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (shader_prog_ptr, GetShaderProgRef, m_shaderProgram);
    TLOC_DECL_AND_DEF_GETTER_DIRECT
      (shader_op_cont, GetShaderOperators, m_shaderOperators);

    void SetVertexSource(BufferArg a_source);
    void SetFragmentSource(BufferArg a_source);
    void SetShaderProgram(const shader_prog_ptr& a_sp);

  private:
    string_type            m_vertexProgram;
    string_type            m_fragmentProgram;

    shader_prog_ptr        m_shaderProgram;
    shader_op_cont         m_shaderOperators;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(Material, material);
  TLOC_TYPEDEF_COMPONENT_POOL(Material, material);

};};};

#endif