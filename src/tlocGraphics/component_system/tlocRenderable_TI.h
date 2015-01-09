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
        k_texCoord,
        k_multiTexCoordPrefix,

        k_count

      }; typedef s32                               value_type;                                                                

    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // Renderable_I

  class Renderable_I
  {
  public:
    typedef Renderable_I                                this_type;
    typedef core_str::String                            string_type;

    typedef gfx_gl::shader_operator_vso                 so_type;
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
    virtual ~Renderable_I();

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

  public:
    TLOC_DECL_AND_DEF_GETTER_DIRECT(so_type, GetShaderOperator, m_shaderOp);
    TLOC_DECL_AND_DEF_GETTER_NON_CONST(vao_ptr, GetVAO, m_vao.get());
    TLOC_DECL_AND_DEF_GETTER(draw_mode, GetDrawMode, m_drawMode);
    TLOC_DECL_AND_DEF_GETTER(bool, GetUniformsUpdated, m_uniformsUpdated);

    TLOC_DECL_SETTER_BY_VALUE_CHAIN(draw_mode, SetDrawMode);

  private:
    so_type                 m_shaderOp;
    vao_vso                 m_vao;
    draw_mode               m_drawMode;
    attribute_string_cont   m_attributeNames;
    uniform_pair_cont       m_uniformsAndNames;
    bool                    m_uniformsUpdated;
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
  { return GetUniform(T_UniformIndex); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <s32 T_UniformIndex>
  auto
    Renderable_I::
    SetEnableUniform(bool a_enable) -> this_type&
  { return SetEnableUniform(T_UniformIndex, a_enable); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <s32 T_UniformIndex>
  bool
    Renderable_I::
    IsUniformEnabled()
  { return IsUniformEnabled(T_UniformIndex); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <s32 T_AttributeIndex>
  auto
    Renderable_I::
    GetAttributeName() const -> const string_type&
  { return GetAttributeName(T_AttributeIndex); }

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