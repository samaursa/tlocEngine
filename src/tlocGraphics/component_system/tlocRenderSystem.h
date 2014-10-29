#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_TI_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_TI_H_

#include <tlocCore/data_structures/tlocVariadic.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>

#include <tlocMath/types/tlocMatrix4.h>

#include <tlocGraphics/component_system/tlocRenderSystem_I.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/tlocGraphicsBase.h>
#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace p_render_system {

    struct Attribute    {};
    struct AttributeVBO {};

  };

  template <typename T_RendererSptr>
  class RenderSystem_TI
    : public core_cs::EntityProcessingSystem
    , public RenderSystem_I
  {
  public:
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_sptr>::value ||
       Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_depth32_sptr>::value ||
       Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_depth64_sptr>::value),
       Unsupported_renderer_Renderer_must_be_a_shared_ptr);

  public:
    typedef core_cs::EntityProcessingSystem               base_type;
    typedef RenderSystem_I                                other_base_type;
    typedef T_RendererSptr                                renderer_type;
    typedef RenderSystem_TI<renderer_type>                this_type;

    typedef typename
      renderer_type::value_type::render_one_frame_uptr    rof_uptr;
    typedef math::types::Mat4f32                          matrix_type;

    typedef gl::ShaderOperator                            so_type;
    typedef gl::uniform_vptr                              uniform_ptr;
    typedef gl::shader_operator_vptr                      shader_operator_ptr;
    typedef gl::const_shader_program_vptr                 const_shader_prog_ptr;

    typedef core_conts::Array<uniform_ptr>                uniform_array;

  public:

    void         SetCamera(const_entity_ptr a_cameraEntity);

    TLOC_DECL_AND_DEF_GETTER(const_entity_ptr, GetCamera, m_sharedCam);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (matrix_type, GetViewProjectionMatrix, m_vpMatrix);
    TLOC_DECL_AND_DEF_GETTER(renderer_type, GetRenderer, m_renderer);
    TLOC_DECL_AND_DEF_SETTER(renderer_type, SetRenderer, m_renderer);

  public:
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (core_str::String, GetMVPMatrixUniformName, m_uniMVPMat.second);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (core_str::String, GetVPMatrixUniformName, m_uniVPMat.second);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (core_str::String, GetViewMatrixUniformName, m_uniViewMat.second);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (core_str::String, GetModelMatrixUniformName, m_uniModelMat.second);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (core_str::String, GetScaleMatrixUniformName, m_uniModelMat.second);

    TLOC_DECL_AND_DEF_SETTER
      (core_str::String, SetMVPMatrixUniformName, m_uniMVPMat.second);
    TLOC_DECL_AND_DEF_SETTER
      (core_str::String, SetVPMatrixUniformName, m_uniMVPMat.second);
    TLOC_DECL_AND_DEF_SETTER
      (core_str::String, SetViewMatrixUniformName, m_uniViewMat.second);
    TLOC_DECL_AND_DEF_SETTER
      (core_str::String, SetModelMatrixUniformName, m_uniModelMat.second);
    TLOC_DECL_AND_DEF_SETTER
      (core_str::String, SetScaleMatrixUniformName, m_uniModelMat.second);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (core_str::String, GetVertexAttributeName, m_vertexAttribName);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (core_str::String, GetTextureAttributePrefix, m_textureAttribPrefix);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (core_str::String, GetNormalAttributeName, m_normalAttribName);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (core_str::String, GetColorAttributeName, m_colorAttribName);

    TLOC_DECL_AND_DEF_SETTER
      (core_str::String, SetVertexAttributeName, m_vertexAttribName);
    TLOC_DECL_AND_DEF_SETTER
      (core_str::String, SetTextureAttributePrefix, m_textureAttribPrefix);
    TLOC_DECL_AND_DEF_SETTER
      (core_str::String, SetNormalAttributeName, m_normalAttribName);
    TLOC_DECL_AND_DEF_SETTER
      (core_str::String, SetColorAttributeName, m_colorAttribName);

  protected:

    struct DrawInfo
    {
    public:
      DrawInfo();
      DrawInfo(entity_ptr a_ent, 
               gfx_t::gl_int a_drawCommand, 
               gfx_t::gl_sizei a_numVertices);

    public:
      entity_ptr                m_entity;
      gl::shader_operator_vptr  m_shaderOp;

      gfx_t::gl_int     m_drawCommand;
      gfx_t::gl_sizei   m_numVertices;

    };

  protected:
    RenderSystem_TI(event_manager_ptr              a_eventMgr,
                    entity_manager_ptr             a_entityMgr,
                    register_type                  a_registerTypes);

    virtual void              SortEntities();

    virtual error_type        Pre_Initialize();
    void                      DoInitializeTexCoords(entity_ptr a_ent, 
                                                    so_type& a_so) const;
    void                      DoUpdateTexCoords(entity_ptr a_ent, 
                                                so_type& a_so) const;
    virtual error_type        InitializeEntity(entity_ptr a_ent);
    virtual error_type        Post_Initialize();

    virtual error_type        Post_ReInitialize();

    virtual void              Pre_ProcessActiveEntities(f64);
    virtual void              Post_ProcessActiveEntities(f64);

    void                      DoDrawEntity(const DrawInfo& a_di);

  private:
    typedef core::Pair<uniform_ptr, core_str::String>     uniform_string_pair;

  private:
    const_shader_prog_ptr     m_shaderPtr;

    const_entity_ptr          m_sharedCam;
    renderer_type             m_renderer;
    rof_uptr                  m_renderOneFrame;
    matrix_type               m_vpMatrix;
    matrix_type               m_projMat;
    matrix_type               m_viewMatrix;

    gl::shader_operator_vso   m_shaderOp;

    uniform_string_pair       m_uniMVPMat;
    uniform_string_pair       m_uniMVPInverseMat;

    uniform_string_pair       m_uniVPMat;
    uniform_string_pair       m_uniVPInverseMat;

    uniform_string_pair       m_uniMVMat;
    uniform_string_pair       m_uniMVInverseMat;

    uniform_string_pair       m_uniProjMat;
    uniform_string_pair       m_uniProjInverseMat;

    uniform_string_pair       m_uniViewMat;
    uniform_string_pair       m_uniViewInverseMat;

    uniform_string_pair       m_uniModelMat;
    uniform_string_pair       m_uniModelInverseMat;

    uniform_string_pair       m_uniScaleMat;
    uniform_string_pair       m_uniScaleInverseMat;

    uniform_string_pair       m_uniNormalMat;

    core_str::String          m_vertexAttribName;
    core_str::String          m_textureAttribPrefix;
    core_str::String          m_normalAttribName;
    core_str::String          m_colorAttribName;
  };

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(RenderSystem_TI<gfx_rend::renderer_depth32_sptr>);
  TLOC_EXTERN_TEMPLATE_CLASS(RenderSystem_TI<gfx_rend::renderer_depth64_sptr>);

};};};

#endif