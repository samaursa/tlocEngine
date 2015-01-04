#include "tlocQuadRenderSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/tlocAlgorithms.h>

#include <tlocMath/types/tlocRectangle.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>

#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix4.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core::data_structs;

  typedef math::types::Vec3f32                              vec3_type;
  typedef math::types::Mat4f32                              matrix_type;

  typedef core_conts::tl_array<vec3_type>::type             vec3_cont_type;


  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef QuadRenderSystem::error_type    error_type;

  //QuadRenderSystem::instances QuadRenderSystem::m_quadsToDraw;

  //////////////////////////////////////////////////////////////////////////
  // QuadRenderSystem

  QuadRenderSystem::
    QuadRenderSystem(event_manager_ptr a_eventMgr,
                     entity_manager_ptr a_entityMgr)
     : base_type(a_eventMgr, a_entityMgr,
                 register_type().Add<Quad>(), "QuadRenderSystem")
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  
  QuadRenderSystem::
    ~QuadRenderSystem()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoMakeQuadVertices(const gfx_cs::quad_sptr& a_quad, vec3_cont_type& a_out)
  {
    typedef math::types::Rectf32_c    rect_type;

    const rect_type& rect = a_quad->GetRectangleRef();

    a_out.resize(4);
    a_out.at(0) = vec3_type(rect.GetValue<rect_type::right>(),
                            rect.GetValue<rect_type::top>(), 0);
    a_out.at(1) = vec3_type(rect.GetValue<rect_type::left>(),
                            rect.GetValue<rect_type::top>(), 0);
    a_out.at(2) = vec3_type(rect.GetValue<rect_type::right>(),
                            rect.GetValue<rect_type::bottom>(), 0);
    a_out.at(3) = vec3_type(rect.GetValue<rect_type::left>(),
                            rect.GetValue<rect_type::bottom>(), 0);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  QuadRenderSystem::error_type
    QuadRenderSystem::
    Pre_Initialize()
  {
    base_type::SortEntities();

    typedef core_conts::Array<gfx_t::Vert3fpt>      quad_buffer_cont;

    instance_info_sptr           currInstanceInfo;

    quad_buffer_cont             qList;

    for (auto itr = DoGetActiveEntities().begin(), 
              itrEnd = DoGetActiveEntities().end(); itr != itrEnd; ++itr)
    {
      auto ent = itr->first;

      if (ent->HasComponent<gfx_cs::Material>() == false)
      { continue; }

      auto quadPtr = ent->GetComponent<gfx_cs::Quad>();
      quadPtr->SetUpdateRequired(false);

      auto matPtr = ent->GetComponent<gfx_cs::Material>();

      if (m_quadsToDraw.empty() || m_quadsToDraw.back()->m_mat != matPtr)
      {
        if (currInstanceInfo)
        {
          using namespace p_material::Attributes;

          auto texCoordPrefix = 
            currInstanceInfo->m_mat->GetAttributeName<p_material::Attributes::k_texCoordPrefix>();

          gfx_gl::AttributeVBO vboQuad;
          vboQuad.AddName(matPtr->GetAttributeName<k_vertexPosition>());
          vboQuad.AddName(core_str::Format("%s0", texCoordPrefix.c_str()) );

          vboQuad.SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer,
                             gfx_gl::p_vbo::usage::StaticDraw>(qList);

          currInstanceInfo->m_so.reserve_attributeVBOs(2);
          currInstanceInfo->m_so.AddAttributeVBO(vboQuad);
        }

        m_quadsToDraw.resize(m_quadsToDraw.size() + 1);
        m_quadsToDraw.back() = core_sptr::MakeShared<InstanceInfo>();
        currInstanceInfo = m_quadsToDraw.back();
        currInstanceInfo->m_mat = matPtr;
      }

      TLOC_ASSERT_NOT_NULL(currInstanceInfo);

      currInstanceInfo->m_entities.push_back(ent);

      vec3_cont_type currQuadList;
      DoMakeQuadVertices(quadPtr, currQuadList);

      gfx_t::Vert3fpt v0, v1, v2, v3;
      v0.SetPosition(currQuadList[0]);
      v1.SetPosition(currQuadList[1]);
      v2.SetPosition(currQuadList[3]);
      v3.SetPosition(currQuadList[2]);

      auto tcPtr = ent->GetComponent<gfx_cs::TextureCoords>(0);
      tcPtr->SetUpdateRequired(false);

      typedef gfx_cs::TextureCoords::set_index        set_index;
      auto texCoordCont = tcPtr->GetCoords(set_index(tcPtr->GetCurrentSet()));

      v0.SetTexCoord(texCoordCont->at(0));
      v1.SetTexCoord(texCoordCont->at(1));
      v2.SetTexCoord(texCoordCont->at(3));
      v3.SetTexCoord(texCoordCont->at(2));

      qList.push_back(v0);
      qList.push_back(v1);
      qList.push_back(v2);
      qList.push_back(v3);
    }

    if (currInstanceInfo)
    {
      using namespace p_material::Attributes;

      auto texCoordPrefix =
        currInstanceInfo->m_mat->GetAttributeName<p_material::Attributes::k_texCoordPrefix>();

      gfx_gl::AttributeVBO vboQuad;
      vboQuad.AddName(currInstanceInfo->m_mat->GetAttributeName<k_vertexPosition>());
      vboQuad.AddName(core_str::Format("%s0", texCoordPrefix.c_str()));

      vboQuad.SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer,
                         gfx_gl::p_vbo::usage::StaticDraw>(qList);

      currInstanceInfo->m_so.reserve_attributeVBOs(2);
      currInstanceInfo->m_so.AddAttributeVBO(vboQuad);
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type 
    QuadRenderSystem::
    InitializeEntity(entity_ptr a_ent)
  { 
    //gfx_cs::quad_sptr quadPtr = a_ent->GetComponent<gfx_cs::Quad>();
    //quadPtr->SetUpdateRequired(false);

    //gfx_cs::material_sptr matPtr;
    //if (a_ent->HasComponent<gfx_cs::Material>())
    //{ matPtr = a_ent->GetComponent<gfx_cs::Material>(); }
    //else // create material temporarily for names
    //{ matPtr = core_sptr::MakeShared<gfx_cs::Material>(); }

    //vec3_cont_type quadList;
    //DoMakeQuadVertices(quadPtr, quadList);

    //const gfx_gl::shader_operator_vptr so =  quadPtr->GetShaderOperator().get();

    //using namespace p_material::Attributes;
    //gfx_gl::AttributeVBO vbo;
    //vbo.AddName(matPtr->GetAttributeName<k_vertexPosition>())
    //   .SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer, 
    //               gfx_gl::p_vbo::usage::StaticDraw>(quadList);

    //so->AddAttributeVBO(vbo);

    //if (a_ent->HasComponent<gfx_cs::TextureCoords>())
    //{ base_type::DoInitializeTexCoords(a_ent, *so); }

    return base_type::InitializeEntity(a_ent);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type 
    QuadRenderSystem::
    ShutdownEntity(entity_ptr)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoUpdateQuad(QuadRenderSystem::entity_ptr a_ent, gfx_cs::quad_sptr a_quadPtr)
  {
    //------------------------------------------------------------------------
    // Update the quad

    gfx_cs::material_sptr matPtr;
    if (a_ent->HasComponent<gfx_cs::Material>())
    { matPtr = a_ent->GetComponent<gfx_cs::Material>(); }
    else // create material temporarily for names
    { matPtr = core_sptr::MakeShared<gfx_cs::Material>(); }

    typedef math::types::Rectf32_c            rect_type;

    const gfx_gl::shader_operator_vptr so =  a_quadPtr->GetShaderOperator().get();

    using gl::algos::shader_operator::compare::AttributeVBOName;
    using namespace p_material::Attributes;
    gl::ShaderOperator::attributeVBO_iterator itr = 
      core::find_if(so->begin_attributeVBOs(), so->end_attributeVBOs(), 
                    AttributeVBOName(matPtr->GetAttributeName<k_vertexPosition>()));

    if (itr == so->end_attributeVBOs())
    { return; }

    a_quadPtr->SetUpdateRequired(false);

    vec3_cont_type      quadList;
    DoMakeQuadVertices(a_quadPtr, quadList);

    itr->first->UpdateData(quadList);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    QuadRenderSystem::
    Pre_ProcessActiveEntities(f64 a_deltaT)
  {
    base_type::Pre_ProcessActiveEntities(a_deltaT);

    typedef core_conts::Array<math_t::Mat4f32>      transform_cont;

    for (auto itr = m_quadsToDraw.begin(), itrEnd = m_quadsToDraw.end(); 
         itr != itrEnd; ++itr)
    {
      auto info = itr->get();
      auto& entities = info->m_entities;

      transform_cont transList;
      for (auto entItr = entities.begin(), entItrEnd = entities.end(); 
           entItr != entItrEnd; ++entItr)
      {
        auto ent = *entItr;
        transList.push_back
          (ent->GetComponent<math_cs::Transform>()->GetTransformation());
        transList.push_back
          (ent->GetComponent<math_cs::Transform>()->GetTransformation());
        transList.push_back
          (ent->GetComponent<math_cs::Transform>()->GetTransformation());
        transList.push_back
          (ent->GetComponent<math_cs::Transform>()->GetTransformation());
      }

      auto soPtr = &(*itr)->m_so;

      // add or update the transformation vbo
      if (soPtr->size_attributeVBOs() == 1)
      { 
        gfx_gl::AttributeVBO vboQuad;
        vboQuad.AddName("a_model");

        vboQuad.SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer,
                           gfx_gl::p_vbo::usage::DynamicDraw>(transList);
        soPtr->AddAttributeVBO(vboQuad);
      }
      else
      {
        auto vboItr = soPtr->begin_attributeVBOs();
        ++vboItr;
        vboItr->first->UpdateData(transList);
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    QuadRenderSystem::
    ProcessEntity(entity_ptr , f64)
  {
    /*if (a_ent->HasComponent<gfx_cs::Material>() == false)
    { return; }

    gfx_cs::quad_sptr quadPtr = a_ent->GetComponent<gfx_cs::Quad>();

    if (quadPtr->IsUpdateRequired())
    { DoUpdateQuad(a_ent, quadPtr); }

    base_type::DrawInfo di(a_ent, GL_TRIANGLE_STRIP, 4);
    di.m_shaderOp = core_sptr::ToVirtualPtr(quadPtr->GetShaderOperator());
    di.m_meshVAO = quadPtr->GetVAO();

    base_type::DoDrawEntity(di);*/
  }

  void
    QuadRenderSystem::
    Post_ProcessActiveEntities(f64 a_deltaT)
  {
    using namespace p_material::Uniforms;

    for (auto itr = m_quadsToDraw.begin(), itrEnd = m_quadsToDraw.end();
         itr != itrEnd; ++itr)
    {
      auto matPtr = (*itr)->m_mat.get();
      auto shaderPtr = matPtr->GetShaderProg();

      shaderPtr->Enable();

      auto matSO = matPtr->GetShaderOperator();
      auto internalSO = matPtr->m_internalShaderOp.get();

      matPtr->GetUniform<k_modelViewProjectionMatrix>()->SetEnabled(false);
      matPtr->GetUniform<k_viewProjectionMatrix>()->SetEnabled(true);
      matPtr->GetUniform<k_viewProjectionMatrix>()->SetValueAs(base_type::m_vpMatrix);

      matSO->PrepareAllUniforms(*shaderPtr);
      matSO->EnableAllUniforms(*shaderPtr);

      internalSO->PrepareAllUniforms(*shaderPtr);
      internalSO->EnableAllUniforms(*shaderPtr);

      auto so = &(*itr)->m_so;

      so->PrepareAllUniforms(*shaderPtr);
      so->EnableAllUniforms(*shaderPtr);

      so->PrepareAllAttributeVBOs(*shaderPtr, (*itr)->m_vao);

      gl::VertexArrayObject::Bind b((*itr)->m_vao);
      glDrawArrays(GL_QUADS, 0, (*itr)->m_entities.size() * 4);

    }

    base_type::Post_ProcessActiveEntities(a_deltaT);
  }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(QuadRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(QuadRenderSystem);

#include <tlocCore/containers/tlocList.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_LIST(tloc::core_cs::entity_vptr);