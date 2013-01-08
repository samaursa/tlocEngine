#ifndef TLOC_MATERIAL_H
#define TLOC_MATERIAL_H

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/opengl/tlocObject.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace graphics { namespace component_system {

  class Material : public core::component_system::Component_T<Material>
  {
  public:
    typedef core::component_system::Component_T<Material>   base_type;
    typedef gl::ShaderProgramPtr                            shader_prog_ptr;

    typedef gl::ShaderOperatorPtr                           shader_op_ptr;
    typedef core::containers::tl_array<shader_op_ptr>::type shader_op_cont;

    typedef core::string::String                            string_type;

  public:
    Material();

    bool operator ==(const Material& a_other) const;
    bool operator < (const Material& a_other) const;
    TLOC_DECLARE_OPERATORS(Material);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (string_type, GetVertexSource, m_vertexProgram);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (string_type, GetFragmentSource, m_fragmentProgram);

    TLOC_DECL_AND_DEF_SETTER(string_type, SetVertexSource,
                             m_vertexProgram);
    TLOC_DECL_AND_DEF_SETTER(string_type, SetFragmentSource,
                             m_fragmentProgram);

    TLOC_DECL_AND_DEF_GETTER_DIRECT(shader_prog_ptr, GetShaderProgRef,
                                    m_shaderProgram);

    TLOC_DECL_AND_DEF_SETTER(shader_op_ptr, SetMasterShaderOperator,
                             m_masterShaderOperator);
    TLOC_DECL_AND_DEF_GETTER(shader_op_ptr, GetMasterShaderOperator,
                             m_masterShaderOperator);

    TLOC_DECL_AND_DEF_GETTER_DIRECT(shader_op_cont,  DoGetShaderOpContainerRef,
                                    m_shaderOperators);
  private:
    string_type            m_vertexProgram;
    string_type            m_fragmentProgram;

    shader_op_ptr          m_masterShaderOperator;
    shader_prog_ptr        m_shaderProgram;
    shader_op_cont         m_shaderOperators;
  };

};};};

#endif