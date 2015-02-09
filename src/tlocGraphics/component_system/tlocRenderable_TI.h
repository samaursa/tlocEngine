#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDERABLE_TI_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDERABLE_TI_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>
#include <tlocGraphics/renderer/tlocDrawCommand.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace p_renderable {

    namespace uniforms {

      enum {

        k_modelMatrix = 0,
        k_modelMatrixInverse,

        k_modelViewMatrix,
        k_modelViewMatrixInverse,

        k_modelViewProjectionMatrix,
        k_modelViewProjectionMatrixInverse,

        k_scaleMatrix,
        k_scaleMatrixInverse,

        k_scaleVector,
        k_scaleVectorInverse,

        k_normalMatrix,
        k_normalMatrixInverse,

        k_count

      }; typedef s32                                        value_type;

    };

    namespace attributes {

      enum 
      {
        k_vertexPosition = 0,
        k_vertexNormal,
        k_vertexColor,
        k_texCoordPrefix,

        k_count

      }; typedef s32                               value_type;                                                                

    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // Renderable_I

  template <class T1, class T2, class T3>
  class MeshRenderSystem_T;

  class Renderable_I
  {
    template <class T1, class T2, class T3> 
    friend class MeshRenderSystem_T;

  public:
    typedef Renderable_I                                this_type;
    typedef core_str::String                            string_type;

    typedef gfx_gl::shader_operator_vso                 so_type;
    typedef gfx_gl::shader_operator_vptr                so_ptr;
    typedef gfx_gl::vao_vso                             vao_vso;
    typedef gfx_gl::vao_vptr                            vao_ptr;

    typedef p_renderable::uniforms::value_type          uniform_index_type;
    typedef p_renderable::attributes::value_type        attribute_index_type;

    typedef core_conts::ArrayFixed
      <string_type, 
       p_renderable::attributes::k_count>               attribute_string_cont;

    typedef gl::uniform_vptr                            uniform_ptr;
    typedef core::Pair<uniform_ptr, string_type>        uniform_string_pair;

    typedef core_conts::ArrayFixed
      <uniform_string_pair, 
       p_renderable::uniforms::k_count>                 uniform_pair_cont;

    typedef gfx_rend::mode::value_type                  draw_mode;

  public:

    Renderable_I();
    Renderable_I(const this_type& a_other);
    virtual ~Renderable_I();

    this_type& operator=(this_type a_other);
    void swap(this_type& a_other);

    template <s32 T_AttributeIndex>
    const string_type& GetAttributeName() const;
    const string_type& GetAttributeName(attribute_index_type a_index) const;

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

    TLOC_DECL_AND_DEF_GETTER(draw_mode, GetDrawMode, m_drawMode);
    TLOC_DECL_AND_DEF_GETTER(bool, GetUniformsUpdated, m_uniformsUpdated);
    TLOC_DECL_AND_DEF_GETTER_NON_CONST(so_ptr, GetUserShaderOperator, m_userShaderOp.get());

    TLOC_DECL_SETTER_BY_VALUE_CHAIN(draw_mode, SetDrawMode);

    TLOC_DECL_AND_DEF_GETTER_NON_CONST(so_ptr, GetShaderOperator, m_shaderOp.get());
    TLOC_DECL_AND_DEF_GETTER_NON_CONST(vao_ptr, GetVAO, m_vao.get());

  private:
    void DoUpdateUniformAndNames();

  private:
    draw_mode               m_drawMode;

    so_type                 m_shaderOp;
    attribute_string_cont   m_attributeNames;
    uniform_pair_cont       m_uniformsAndNames;
    bool                    m_uniformsUpdated;

    so_type                 m_userShaderOp;

    vao_vso                 m_vao;
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <s32 T_UniformIndex>
  auto
    Renderable_I::
    GetUniformName() const -> const string_type&
  { return GetUniformName(T_UniformIndex); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <s32 T_UniformIndex>
  auto
    Renderable_I::
    GetUniform() const -> uniform_ptr
  { 
    TLOC_STATIC_ASSERT(T_UniformIndex < p_renderable::uniforms::k_count, 
                       Uniform_index_out_of_range); 
    return GetUniform(T_UniformIndex);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <s32 T_UniformIndex>
  auto
    Renderable_I::
    SetEnableUniform(bool a_enable) -> this_type&
  { 
    TLOC_STATIC_ASSERT(T_UniformIndex < p_renderable::uniforms::k_count, 
                       Uniform_index_out_of_range); 
    return SetEnableUniform(T_UniformIndex, a_enable);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <s32 T_UniformIndex>
  bool
    Renderable_I::
    IsUniformEnabled()
  { 
    TLOC_STATIC_ASSERT(T_UniformIndex < p_renderable::uniforms::k_count, 
                       Uniform_index_out_of_range); 
    return IsUniformEnabled(T_UniformIndex);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <s32 T_AttributeIndex>
  auto
    Renderable_I::
    GetAttributeName() const -> const string_type&
  { 
    TLOC_STATIC_ASSERT(T_AttributeIndex < p_renderable::attributes::k_count, 
                       Attribute_index_out_of_range); 
    return GetAttributeName(T_AttributeIndex);
  }

  // ///////////////////////////////////////////////////////////////////////
  // Renderable_TI

  template <typename T_Component, tl_int T_ComponentEnumType>
  class Renderable_TI
    : public core_cs::Component_T<T_Component, 
                                  core_cs::component_group::k_graphics, 
                                  T_ComponentEnumType>
    , public Renderable_I
  {
  public:
    typedef core_cs::Component_T
      <T_Component,
       core_cs::component_group::k_graphics,
       T_ComponentEnumType>                             base_type;
    typedef Renderable_I                                renderable_base_type;
    
    typedef Renderable_TI<T_Component,
                          base_type::k_component_type>  this_type;

    typedef typename base_type::component_type          component_type;

  protected:
    Renderable_TI(BufferArg a_debugName);
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_Component, tl_int T_ComponentEnumType>
  Renderable_TI<T_Component, T_ComponentEnumType>::
    Renderable_TI(BufferArg a_debugName)
    : base_type(a_debugName)
  { }

};};};

#endif