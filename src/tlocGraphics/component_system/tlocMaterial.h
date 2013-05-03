#ifndef TLOC_MATERIAL_H
#define TLOC_MATERIAL_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
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
    : public core::component_system::Component_T<Material, components::material>
  {
  public:
    typedef core::component_system::Component_T
      <Material, components::material>                      base_type;
    typedef gl::shader_program_sptr                         shader_prog_ptr;

    typedef gl::shader_operator_sptr                        shader_op_ptr;
    typedef core::containers::tl_array<shader_op_ptr>::type shader_op_cont;

    typedef shader_op_cont::iterator                  shader_op_cont_itr;
    typedef shader_op_cont::const_iterator            shader_op_cont_const_itr;

    typedef core::string::String                            string_type;

  public:
    Material();
    Material(const Material& a_other);

    void AddShaderOperator(shader_op_ptr a_shaderOp);
    bool RemoveShaderOperator(shader_op_ptr a_shaderOp);
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
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (shader_op_cont, GetShaderOperators, m_shaderOperators);

    TLOC_DECL_AND_DEF_COMPONENT_SETTER(string_type, SetVertexSource,
                                       m_vertexProgram);
    TLOC_DECL_AND_DEF_COMPONENT_SETTER(string_type, SetFragmentSource,
                                       m_fragmentProgram);
    TLOC_DECL_AND_DEF_SETTER(shader_prog_ptr, SetShaderProgram,
                             m_shaderProgram);
  private:
    string_type            m_vertexProgram;
    string_type            m_fragmentProgram;

    shader_prog_ptr        m_shaderProgram;
    shader_op_cont         m_shaderOperators;
  };

  //------------------------------------------------------------------------
  // typedefs

  typedef core::smart_ptr::SharedPtr<Material>    MaterialPtr;
  typedef core::component_system::
    ComponentPool_TI<MaterialPtr>                 MaterialPool;

};};};

#endif