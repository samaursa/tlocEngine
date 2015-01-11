#ifndef TLOC_MATERIAL_H
#define TLOC_MATERIAL_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/containers/tlocArrayFixed.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/io/tlocFileContents.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/opengl/tlocObject.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // p_material

  namespace p_material {

    namespace uniforms {

      enum 
      {
        k_viewProjectionMatrix = 0,
        k_viewProjectionMatrixInverse,

        k_viewMatrix,
        k_viewMatrixInverse,

        k_projectionMatrix,
        k_projectionMatrixInverse, 

        k_count

      }; typedef s32                               value_type;                                                                

    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // Material

  template <class T1, class T2, class T3> 
  class MeshRenderSystem_T;

  class MaterialSystem;
  class QuadRenderSystem;

  class Material
    : public core_cs::Component_T<Material, 
                                 core_cs::component_group::k_graphics, 
                                 components::k_material>
  {
  public:
    template <class T1, class T2, class T3> 
    friend class MeshRenderSystem_T;

    friend class MaterialSystem;
    friend class QuadRenderSystem;

  public:
    typedef Material                                        this_type;
    typedef core_cs::Component_T
      <this_type, k_component_group, k_component_type>      base_type;

    typedef gl::shader_program_vptr                         shader_prog_ptr;
    typedef gl::const_shader_program_vptr                   const_shader_prog_ptr;
    typedef gl::shader_program_vso                          shader_prog_vso;

    typedef gl::shader_operator_vso                         shader_op_vso;
    typedef gl::shader_operator_vptr                        shader_op_ptr;
    typedef gl::ShaderOperator::uniform_iterator            shader_op_uniform_itr;

    typedef gl::Uniform                                     uniform_type;
    typedef gl::uniform_vso                                 uniform_vso;
    typedef gl::uniform_vptr                                uniform_ptr;
    typedef gl::attributeVBO_vptr                           attribute_ptr;

    typedef core_str::String                                string_type;
    typedef core::Pair<uniform_ptr, string_type>            uniform_string_pair;

    typedef p_material::uniforms::value_type                uniform_index_type;

    typedef core_conts::ArrayFixed
      <uniform_string_pair, 
       p_material::uniforms::k_count>                       uniform_pair_cont;

    typedef core_io::FileContents                           file_contents;
    typedef file_contents::path_type                        path_type;

    typedef tl_size                                         size_type;

  public:
    Material();
    Material(const Material& a_other);

    this_type& operator=(this_type a_other);
    void swap(this_type& a_other);

    this_type& AddUniform(const uniform_type& a_uniform);

    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (shader_op_uniform_itr, begin_uniforms, m_shaderOp->begin_uniforms());
    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (shader_op_uniform_itr, end_uniforms, m_shaderOp->end_uniforms());
    TLOC_DECL_AND_DEF_GETTER
      (size_type, size_uniforms, m_shaderOp->size_uniforms());

    bool operator ==(const Material& a_other) const;
    bool operator < (const Material& a_other) const;
    TLOC_DECLARE_OPERATORS(Material);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (string_type, GetVertexSource, m_vertexProgram.GetContents());
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (string_type, GetFragmentSource, m_fragmentProgram.GetContents());

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (path_type, GetVertexPath, m_vertexProgram.GetPath());
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (path_type, GetFragmentPath, m_fragmentProgram.GetPath());

    TLOC_DECL_AND_DEF_GETTER (const_shader_prog_ptr, GetShaderProg,
                              m_shaderProgram.get());
    TLOC_DECL_AND_DEF_GETTER_NON_CONST(shader_prog_ptr, GetShaderProg,
                                        m_shaderProgram.get());
    TLOC_DECL_AND_DEF_GETTER_NON_CONST(shader_op_ptr, GetShaderOperator, 
                                       m_shaderOp.get());

    this_type& SetVertexSource(const file_contents& a_vsSource);
    this_type& SetFragmentSource(const file_contents& a_fsSource);
    this_type& SetShaderProgram(const gl::ShaderProgram& a_sp);

  public: // special uniforms that are passed depending on whether 
          // they are enabled or not
    
    template <s32 T_UniformIndex>
    const string_type& GetUniformName() const;
    const string_type& GetUniformName(uniform_index_type a_index) const;

    template <s32 T_UniformIndex>
    uniform_ptr GetUniform() const;
    uniform_ptr GetUniform(uniform_index_type a_index) const;

    template <s32 T_UniformIndex>
    this_type& SetEnableUniform(bool a_enable = true);
    this_type& SetEnableUniform(uniform_index_type a_index, bool a_enable = true);

    template <s32 T_UniformIndex>
    bool IsUniformEnabled();
    bool IsUniformEnabled(uniform_index_type a_index);

  private:
    file_contents          m_vertexProgram;
    file_contents          m_fragmentProgram;

    shader_prog_vso        m_shaderProgram;
    shader_op_vso          m_shaderOp;

    shader_op_vso          m_internalShaderOp;
    uniform_pair_cont      m_internalUniforms;
    bool                   m_isDirty;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <s32 T_UniformIndex>
  const Material::string_type&
    Material::
    GetUniformName() const
  { 
    TLOC_STATIC_ASSERT(T_UniformIndex < p_material::uniforms::k_count, 
                       Uniform_index_out_of_range); 
    return GetUniformName(T_UniformIndex);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <s32 T_UniformIndex>
  Material::uniform_ptr
    Material::
    GetUniform() const
  { 
    TLOC_STATIC_ASSERT(T_UniformIndex < p_material::uniforms::k_count, 
                       Uniform_index_out_of_range); 
    return GetUniform(T_UniformIndex);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <s32 T_UniformIndex>
   Material::this_type&
    Material::
    SetEnableUniform(bool a_enable)
  { 
    TLOC_STATIC_ASSERT(T_UniformIndex < p_material::uniforms::k_count, 
                       Uniform_index_out_of_range); 
     return SetEnableUniform(T_UniformIndex, a_enable);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <s32 T_UniformIndex>
  bool
    Material::
    IsUniformEnabled()
  { 
    TLOC_STATIC_ASSERT(T_UniformIndex < p_material::uniforms::k_count, 
                       Uniform_index_out_of_range); 
    return IsUniformEnabled(T_UniformIndex);
  }

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(Material, material);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Material, material);
  TLOC_TYPEDEF_COMPONENT_POOL(Material, material);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::Material);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_cs::Material);

#endif