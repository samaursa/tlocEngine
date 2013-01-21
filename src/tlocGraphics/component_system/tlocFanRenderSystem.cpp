#include "tlocFanRenderSystem.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl>

#include <tlocMath/types/tlocCircle.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocFan.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocProjectionComponent.h>


namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef FanRenderSystem::error_type    error_type;

  //////////////////////////////////////////////////////////////////////////
  // QuadRenderSystem

  FanRenderSystem::FanRenderSystem
    (event_manager* a_eventMgr, entity_manager* a_entityMgr)
     : base_type(a_eventMgr, a_entityMgr,
                 Variadic<component_type, 1>(components::fan))
     , m_sharedCam(nullptr)
  {
    m_vertList.reserve(30);

    m_vData = gl::AttributePtr(new gl::Attribute());
    m_vData->SetName("a_vPos");

    m_projectionOperator = gl::ShaderOperatorPtr(new gl::ShaderOperator());
  }

  void FanRenderSystem::AttachCamera(const entity_type* a_cameraEntity)
  {
    m_sharedCam = a_cameraEntity;

    // Ensure that camera entity has the projection component
    TLOC_ASSERT( m_sharedCam->HasComponent(components::projection),
      "The passed entity does not have the projection component!");
  }

  error_type FanRenderSystem::Pre_Initialize()
  {
    using namespace core::component_system;
    using namespace math::component_system::components;
    using namespace graphics::component_system::components;

    matrix_type viewMat;
    viewMat.Identity();

    if (m_sharedCam)
    {
      if (m_sharedCam->HasComponent(transform))
      {
        ComponentMapper<math::component_system::Transform> viewMatList =
          m_sharedCam->GetComponents(math::component_system::components::transform);
      }

      if (m_sharedCam->HasComponent(projection))
      {
      }
    }

    return ErrorSuccess();
  }

  error_type FanRenderSystem::InitializeEntity(entity_manager*, entity_type* )
  { return ErrorSuccess(); }

  error_type FanRenderSystem::ShutdownEntity(entity_manager*, entity_type*)
  { return ErrorSuccess(); }

  void FanRenderSystem::Pre_ProcessActiveEntities()
  {
    using namespace core::component_system;
    using namespace math::component_system::components;
    using namespace graphics::component_system::components;

    matrix_type viewMat;
    viewMat.Identity();
    m_vpMatrix.Identity();

    // vMVP, but since we are doing column major, it becomes PVMv

    if (m_sharedCam)
    {
      if (m_sharedCam->HasComponent(projection))
      {
        ComponentMapper<graphics::component_system::Projection> projMatList =
          m_sharedCam->GetComponents(graphics::component_system::components::projection);
        m_vpMatrix = projMatList[0].GetFrustumRef().GetProjectionMatrix();
      }

      if (m_sharedCam->HasComponent(transform))
      {
        ComponentMapper<math::component_system::Transform> viewMatList =
          m_sharedCam->GetComponents(math::component_system::components::transform);
        viewMat = viewMatList[0].GetTransformation();
      }
    }

    m_vpMatrix.Mul(viewMat);

    gl::UniformPtr vpMat(new gl::Uniform());
    vpMat->SetName("u_mvp").SetValueAs(m_vpMatrix);

    m_projectionOperator->RemoveAllUniforms();
    m_projectionOperator->AddUniform(vpMat);
  }

  void FanRenderSystem::ProcessEntity(entity_manager*, entity_type* a_ent)
  {
    using namespace core::component_system;
    using math::types::Degree32;

    typedef math::component_system::Transform     transform_type;
    typedef graphics::component_system::Fan       fan_type;
    typedef graphics::component_system::Material  material_type;
    typedef material_type::shader_op_ptr          shader_op_ptr;

    const entity_type* ent = a_ent;

    if (ent->HasComponent(components::material))
    {

      ComponentMapper<material_type> matArr =
        ent->GetComponents(components::material);
      material_type& mat = matArr[0];

      ComponentMapper<fan_type> fan = ent->GetComponents(components::fan);
      Fan& f = fan[0];

      //------------------------------------------------------------------------
      // Prepare the Fan

      typedef math::types::Circlef32 circle_type;
      using math::types::Vec3f32;
      using math::types::Vec4f32;
      using math::types::Mat4f32;

      m_vertList.clear();
      const circle_type& circ = f.GetEllipseRef();

      const tl_int    numSides = f.GetNumSides();
      const tl_float  angleInterval = 360.0f/numSides;

      ComponentMapper<transform_type> posList =
        ent->GetComponents(math::component_system::components::transform);
      math::component_system::Transform& pos = posList[0];
      const Mat4f32& tMatrix = pos.GetTransformation();

      // Push the center vertex
      {
        Vec4f32 newCoord = circ.GetPosition().
          ConvertTo<Vec4f32, p_tuple::overflow_zero>();
        newCoord[3] = 1;
        newCoord = tMatrix * newCoord;
        m_vertList.push_back(newCoord.ConvertTo<Vec3f32>());
      }

      for (int i = 0; i <= numSides; ++i)
      {
        Vec4f32 newCoord = (circ.GetCoord(Degree32(angleInterval * i))
          .ConvertTo<Vec4f32, p_tuple::overflow_zero>());
        newCoord[3] = 1;
        newCoord = tMatrix * newCoord;

        m_vertList.push_back(newCoord.ConvertTo<Vec3f32>());
      }

      m_vData->SetVertexArray(m_vertList, gl::p_shader_variable_ti::CopyArray() );

      shader_op_ptr so_fan = shader_op_ptr(new shader_op_ptr::value_type());
      so_fan->AddAttribute(m_vData);


      //------------------------------------------------------------------------
      // Enable the shader

      material_type::shader_prog_ptr sp = mat.GetShaderProgRef();

      // Don't 're-enable' the shader if it was already enabled by the previous
      // entity
      if ( !m_shaderPtr && m_shaderPtr.get() != sp.get() )
      {
        sp->Enable();
        m_shaderPtr = sp;

        material_type::shader_op_cont::iterator itr, itrEnd;
        material_type::shader_op_cont& cont = mat.DoGetShaderOpContainerRef();

        for (itr = cont.begin(), itrEnd = cont.end(); itr != itrEnd; ++itr)
        {
          material_type::shader_op_ptr so = *itr;

          so->EnableAllUniforms(*m_shaderPtr);
          so->EnableAllAttributes(*m_shaderPtr);
        }

        // Add the mvp
        m_projectionOperator->PrepareAllUniforms(*m_shaderPtr);
        m_projectionOperator->EnableAllUniforms(*m_shaderPtr);
      }

      so_fan->PrepareAllAttributes(*m_shaderPtr);
      so_fan->EnableAllAttributes(*m_shaderPtr);

      glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertList.size());

      //sp->Disable();
    }
  }

  void FanRenderSystem::Post_ProcessActiveEntities()
  {
    m_shaderPtr->Disable();
    m_shaderPtr.reset();
  }

};};};