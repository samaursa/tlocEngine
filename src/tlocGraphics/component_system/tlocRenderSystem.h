#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_H_

#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/data_structures/tlocVariadic.h>

#include <tlocMath/types/tlocMatrix4.h>

#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/tlocGraphicsBase.h>
#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>

namespace tloc { namespace graphics { namespace component_system {

  class RenderSystemBase
  {
  public:

    TLOC_DECL_GETTER(bool, IsUniformModelMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformModelMatrix);

    TLOC_DECL_GETTER(bool, IsAttributePosDataEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledAttributePosData);

    TLOC_DECL_GETTER(bool, IsUniformMVPMatrixEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformMVPMatrix);

    TLOC_DECL_GETTER(bool, IsUniformVPEnabled);
    TLOC_DECL_SETTER_BY_VALUE(bool, SetEnabledUniformVPMatrix);

  protected:
    RenderSystemBase();

  private:
    core_utils::Checkpoints   m_flags;
  };

  template <typename T_RendererSptr>
  class RenderSystem_TI
    : public core_cs::EntityProcessingSystem
    , public RenderSystemBase
  {
  public:
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_sptr>::value ||
       Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_depth32_sptr>::value ||
       Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_depth64_sptr>::value),
       Unsupported_renderer_Renderer_must_be_a_shared_ptr);

  public:
    typedef core_cs::EntityProcessingSystem               base_type;
    typedef RenderSystemBase                              other_base_type;

    typedef T_RendererSptr                                renderer_type;
    typedef typename
      renderer_type::value_type::render_one_frame_uptr    rof_uptr;
    typedef math::types::Mat4f32                          matrix_type;

    typedef gl::uniform_vptr                              uniform_ptr;
    typedef gl::attribute_vptr                            attribute_ptr;

    typedef gl::const_shader_program_vptr                 const_shader_prog_ptr;


    typedef core_conts::Array<uniform_ptr>                uniform_array;
    typedef core_conts::Array<attribute_ptr>              attribute_array;

    typedef core_conts::ArrayFixed<attribute_ptr, 8>     attribute_ptr_cont;

  public:

    void         SetCamera(const_entity_ptr a_cameraEntity);

    TLOC_DECL_AND_DEF_GETTER(const_entity_ptr, GetCamera, m_sharedCam);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (matrix_type, GetViewProjectionMatrix, m_vpMatrix);
    TLOC_DECL_AND_DEF_GETTER(renderer_type, GetRenderer, m_renderer);
    TLOC_DECL_AND_DEF_SETTER(renderer_type, SetRenderer, m_renderer);

  public:
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (core_str::String, GetMVPMatrixUniformName, m_mvpMat.second);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (core_str::String, GetVPMatrixUniformName, m_vpMat.second);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (core_str::String, GetModelMatrixUniformName, m_modelMat.second);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (core_str::String, GetVertexDataAttributeName, m_vertexData.second);

    TLOC_DECL_AND_DEF_SETTER
      (core_str::String, SetMVPMatrixUniformName, m_mvpMat.second);
    TLOC_DECL_AND_DEF_SETTER
      (core_str::String, SetVPMatrixUniformName, m_mvpMat.second);
    TLOC_DECL_AND_DEF_SETTER
      (core_str::String, SetModelMatrixUniformName, m_modelMat.second);
    TLOC_DECL_AND_DEF_SETTER
      (core_str::String, SetVertexDataAttributeName, m_vertexData.second);

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
    template <size_type T_VarSize>
    RenderSystem_TI(event_manager_ptr              a_eventMgr,
                    entity_manager_ptr             a_entityMgr,
                    const core_ds::Variadic
                      <component_type, T_VarSize>&  a_typeFlags);

    virtual error_type        Pre_Initialize();
    virtual error_type        InitializeEntity(entity_ptr a_ent);

    virtual void              Pre_ProcessActiveEntities(f64);
    virtual void              Post_ProcessActiveEntities(f64);

    void                      DoDrawEntity(const DrawInfo& a_di);

    TLOC_DECL_AND_DEF_GETTER(attribute_ptr, DoGetVertexDataAttribute, 
                             m_vertexData.first);

  private:
    typedef core::Pair<uniform_ptr, core_str::String>     uniform_string_pair;
    typedef core::Pair<attribute_ptr, core_str::String>   attribute_string_pair;

  private:
    const_shader_prog_ptr     m_shaderPtr;

    const_entity_ptr          m_sharedCam;
    renderer_type             m_renderer;
    rof_uptr                  m_renderOneFrame;
    matrix_type               m_vpMatrix;
    attribute_ptr_cont        m_tData;

    gl::shader_operator_vso   m_shaderOp;

    uniform_string_pair       m_mvpMat;
    uniform_string_pair       m_vpMat;
    uniform_string_pair       m_modelMat;
    attribute_string_pair     m_vertexData;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_RendererSptr>
  template <tl_size T_VarSize>
  RenderSystem_TI<T_RendererSptr>::
    RenderSystem_TI(event_manager_ptr a_eventMgr,
                   entity_manager_ptr a_entityMgr,
                   const core_ds::Variadic
                    <component_type, T_VarSize>&  a_typeFlags)
    : base_type(a_eventMgr, a_entityMgr, a_typeFlags)
    , m_sharedCam(nullptr)
    , m_renderer(nullptr)
  { }

};};};

#endif