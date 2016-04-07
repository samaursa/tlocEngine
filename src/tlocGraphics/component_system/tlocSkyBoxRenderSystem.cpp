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
      " #version 330 core                                         \
        in vec3 a_vertPos;                                        \
        out vec3 TexCoords;                                       \
                                                                  \
        uniform mat4 u_proj;                                      \
        uniform mat4 u_view;                                      \
                                                                  \
        void main()                                               \
        {                                                         \
          gl_Position = u_proj * u_view * vec4(a_vertPos, 1.0);   \
          gl_Position = pos.xyww;                                 \
          TexCoords = position;                                   \
        } ";

    const char* fsSource = 
      " #version 330 core                                         \
        in vec3 TexCoords;                                        \
        out vec4 color;                                           \
                                                                  \
        uniform samplerCube skybox;                               \
                                                                  \
        void main()                                               \
        {                                                         \
          color = texture(skybox, TexCoords);                     \
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
    m_scene->AddSystem<gfx_cs::MaterialSystem>();
    m_scene->AddSystem<gfx_cs::CameraSystem>();
    m_meshSys = m_scene->AddSystem<gfx_cs::MeshRenderSystem>();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    SkyBoxRenderSystem::
    InitializeEntity(entity_ptr) -> error_type
  { 
    core_conts::Array<gfx_t::Vert3fp> cubeVerts;

    gfx_t::Vert3fp::attrib_1_type::value_type::value_type skyboxVertices[] = {
      // Positions          
      -1.0f, 1.0f, -1.0f,
      -1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
      1.0f, 1.0f, -1.0f,
      -1.0f, 1.0f, -1.0f,

      -1.0f, -1.0f, 1.0f,
      -1.0f, -1.0f, -1.0f,
      -1.0f, 1.0f, -1.0f,
      -1.0f, 1.0f, -1.0f,
      -1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f,

      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,

      -1.0f, -1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f,

      -1.0f, 1.0f, -1.0f,
      1.0f, 1.0f, -1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f, -1.0f,

      -1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f, 1.0f,
      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f, 1.0f,
      1.0f, -1.0f, 1.0f
    };

    for (auto i = 0u; i < core_utils::ArraySize(skyboxVertices); i = i+3)
    {
      gfx_t::Vert3fp vert;
      vert.SetPosition(math_t::Vec3f32(skyboxVertices[i], 
                                       skyboxVertices[i+1], 
                                       skyboxVertices[i+2]));
      cubeVerts.push_back(vert);
    }

    auto meshEnt = m_scene->CreatePrefab<pref_gfx::Mesh>().Create(cubeVerts);

    auto vertShader = core_io::FileContents(core_io::Path
        ("hard_coded_skybox_shader/skybox_shader_vs.glsl"), vsSource);

    auto fragShader = core_io::FileContents(core_io::Path
        ("hard_coded_skybox_shader/skybox_shader_fs.glsl"), fsSource);

    m_scene->CreatePrefab<pref_gfx::Material>().Add(meshEnt, vertShader, fragShader);

    auto matPtr = meshEnt->GetComponent<gfx_cs::Material>();
    matPtr->SetEnableUniform<gfx_cs::p_material::uniforms::k_viewMatrix>();
    matPtr->SetEnableUniform<gfx_cs::p_material::uniforms::k_projectionMatrix>();

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
    Post_ProcessActiveEntities(f64)
  {
    const auto paramsBak = m_renderer->GetParams();
    
    auto newParams = paramsBak;
    newParams.SetDepthFunction<gfx_rend::p_renderer::depth_function::LessEqual>();
    m_renderer->SetParams(newParams);

    m_scene->Process();

    m_renderer->ApplyRenderSettings();
    m_renderer->Render();

    m_renderer->SetParams(paramsBak);
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
  }

};};};

// -----------------------------------------------------------------------
// explicit instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(CameraSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(CameraSystem);