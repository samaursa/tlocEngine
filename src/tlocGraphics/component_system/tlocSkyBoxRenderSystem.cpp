#include "tlocSkyBoxRenderSystem.h"

#include <tlocGraphics/component_system/tlocSkyBox.h>
#include <tlocGraphics/component_system/tlocMaterialSystem.h>
#include <tlocGraphics/component_system/tlocCameraSystem.h>

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocProjectionComponent.h>

#include <tlocPrefab/graphics/tlocMesh.h>
#include <tlocPrefab/graphics/tlocMaterial.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // typedefs

  using namespace core::data_structs;

  namespace {

    const char* vsSource = 
      "#version 330 core                                                  \n\
       in vec3 a_vertPos;                                                 \n\
       out vec3 v_uvCoord;                                                \n\
                                                                          \n\
       uniform mat4 u_proj;                                               \n\
       uniform mat4 u_view;                                               \n\
                                                                          \n\
       void main()                                                        \n\
       {                                                                  \n\
         vec4 pos = u_proj * vec4(mat3(u_view) * vec3(a_vertPos), 1.0);   \n\
         gl_Position = pos.xyww;                                          \n\
         v_uvCoord = a_vertPos;                                           \n\
       } ";

    const char* fsSource = 
      "#version 330 core                                            \n\
       in vec3 v_uvCoord;                                           \n\
       out vec4 color;                                              \n\
                                                                    \n\
       uniform samplerCube s_texture;                               \n\
                                                                    \n\
       void main()                                                  \n\
       {                                                            \n\
         color = texture(s_texture, v_uvCoord);                     \n\
       }";
  };

  // ///////////////////////////////////////////////////////////////////////

  SkyBoxRenderSystem::
    SkyBoxRenderSystem(event_manager_ptr a_eventMgr, entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                register_type().Add<SkyBox>(), 
                "SkyBox")
    , m_scene(core_sptr::MakeUnique<core_cs::ECS>("SkyBox Scene"))
  { 
    m_scene->AddSystem<gfx_cs::MaterialSystem>("Render");
    m_meshSys = m_scene->AddSystem<gfx_cs::MeshRenderSystem>("Render");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    SkyBoxRenderSystem::
    InitializeEntity(entity_ptr a_ent) -> error_type
  { 
    auto sb = a_ent->GetComponent<gfx_cs::SkyBox>();

    core_conts::Array<gfx_t::Vert3fp> cubeVerts;

    gfx_t::Vert3fp::attrib_1_type::value_type::value_type skyboxVertices[] = {
      // Positions          
      -1.0f,  1.0f, -1.0f,
      -1.0f, -1.0f, -1.0f,
       1.0f, -1.0f, -1.0f,
       1.0f, -1.0f, -1.0f,
       1.0f,  1.0f, -1.0f,
      -1.0f,  1.0f, -1.0f,

      -1.0f, -1.0f,  1.0f,
      -1.0f, -1.0f, -1.0f,
      -1.0f,  1.0f, -1.0f,
      -1.0f,  1.0f, -1.0f,
      -1.0f,  1.0f,  1.0f,
      -1.0f, -1.0f,  1.0f,

       1.0f, -1.0f, -1.0f,
       1.0f, -1.0f,  1.0f,
       1.0f,  1.0f,  1.0f,
       1.0f,  1.0f,  1.0f,
       1.0f,  1.0f, -1.0f,
       1.0f, -1.0f, -1.0f,

      -1.0f, -1.0f,  1.0f,
      -1.0f,  1.0f,  1.0f,
       1.0f,  1.0f,  1.0f,
       1.0f,  1.0f,  1.0f,
       1.0f, -1.0f,  1.0f,
      -1.0f, -1.0f,  1.0f,

      -1.0f,  1.0f, -1.0f,
       1.0f,  1.0f, -1.0f,
       1.0f,  1.0f,  1.0f,
       1.0f,  1.0f,  1.0f,
      -1.0f,  1.0f,  1.0f,
      -1.0f,  1.0f, -1.0f,

      -1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f,  1.0f,
       1.0f, -1.0f, -1.0f,
       1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f,  1.0f,
       1.0f, -1.0f,  1.0f,
    };

    for (auto i = 0u; i < core_utils::ArraySize(skyboxVertices); i = i+3)
    {
      gfx_t::Vert3fp vert;
      vert.SetPosition(math_t::Vec3f32(skyboxVertices[i], 
                                       skyboxVertices[i+1], 
                                       skyboxVertices[i+2]));
      cubeVerts.push_back(vert);
    }

    sb->m_skyBox = m_scene->CreatePrefab<pref_gfx::Mesh>().Create(cubeVerts);
    sb->GetSkyBoxEntity()->GetComponent<gfx_cs::Mesh>()->
      SetEnableUniform<gfx_cs::p_renderable::uniforms::k_modelMatrix>(false);

    auto vertShader = core_io::FileContents(core_io::Path
        ("hard_coded_skybox_shader/skybox_shader_vs.glsl"), vsSource);

    auto fragShader = core_io::FileContents(core_io::Path
        ("hard_coded_skybox_shader/skybox_shader_fs.glsl"), fsSource);

    gfx_gl::uniform_vso u_skybox;
    u_skybox->SetName("s_texture").SetValueAs(sb->GetCubeMap());

    m_scene->CreatePrefab<pref_gfx::Material>()
      .AddUniform(u_skybox.get())
      .Add(sb->GetSkyBoxEntity(), vertShader, fragShader);

    auto matPtr = sb->GetSkyBoxEntity()->GetComponent<gfx_cs::Material>();
    matPtr->SetEnableUniform<gfx_cs::p_material::uniforms::k_viewMatrix>();
    matPtr->SetEnableUniform<gfx_cs::p_material::uniforms::k_projectionMatrix>();

    matPtr->SetEnableUniform<gfx_cs::p_material::uniforms::k_viewProjectionMatrix>(false);

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    SkyBoxRenderSystem::
    Post_Initialize() -> error_type
  { 
    m_scene->Initialize();

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SkyBoxRenderSystem::
    ProcessEntity(entity_ptr a_ent, f64)
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SkyBoxRenderSystem::
    Post_ProcessActiveEntities(f64 a_deltaT)
  {
    m_scene->Process(a_deltaT);

    m_renderer->ApplyRenderSettings();
    m_renderer->Render();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SkyBoxRenderSystem::
    SetCamera(const_entity_ptr a_cameraEntity)
  {
    m_meshSys->SetCamera(a_cameraEntity);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SkyBoxRenderSystem::
    SetRenderer(renderer_ptr a_renderer)
  {
    m_meshSys->SetRenderer(a_renderer);
    m_renderer = a_renderer;
  }

};};};

// -----------------------------------------------------------------------
// explicit instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(SkyBoxRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(SkyBoxRenderSystem);