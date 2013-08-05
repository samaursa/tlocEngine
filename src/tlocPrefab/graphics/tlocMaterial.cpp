#include "tlocMaterial.h"

#include <tlocGraphics/component_system/tlocMaterial.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

  using gfx_cs::material_sptr;

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::entity_type*
    Material::
    Create(const core_io::Path& a_vertexShader,
           const core_io::Path& a_fragmentShader)
  {
    Entity* ent = m_entMgr->CreateEntity();
    Add(ent, a_vertexShader, a_fragmentShader);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Material::
    Add(entity_type* a_ent,
        const core_io::Path& a_vertexShader,
        const core_io::Path& a_fragmentShader)
  {
    using namespace gfx_cs::components;

    core_io::Path vsFullPath( (m_assetsPath + a_vertexShader.GetPath()).c_str() );
    core_io::Path fsFullPath( (m_assetsPath + a_fragmentShader.GetPath()).c_str() );

    core_io::FileIO_ReadA vsFile(vsFullPath.GetPath());
    core_io::FileIO_ReadA fsFile(fsFullPath.GetPath());

    core_err::Error err = ErrorSuccess;
    err = vsFile.Open();
    TLOC_ASSERT(err == ErrorSuccess, "Could not open the vertex shader file");

    err = fsFile.Open();
    TLOC_ASSERT(err == ErrorSuccess, "Could not open the fragment shader file");

    core_str::String vsCode, fsCode;

    vsFile.GetContents(vsCode);
    fsFile.GetContents(fsCode);

    typedef ComponentPoolManager              pool_mgr;
    typedef gfx_cs::material_sptr_pool        mat_pool;

    gfx_cs::material_sptr_pool_sptr matPool;

    if (m_compPoolMgr->Exists(material) == false)
    { matPool = m_compPoolMgr->CreateNewPool<material_sptr>(); }
    else
    { matPool = m_compPoolMgr->GetPool<material_sptr>(); }

    mat_pool::iterator  itrMat = matPool->GetNext();
    itrMat->SetValue(material_sptr(new gfx_cs::Material()) );

    gfx_cs::material_sptr mat = itrMat->GetValue();

    mat->SetVertexSource(vsCode);
    mat->SetFragmentSource(fsCode);

    gfx_gl::shader_operator_sptr so =
      gfx_gl::shader_operator_sptr(new gfx_gl::ShaderOperator());

    for (uniform_itr itr = m_uniforms.begin(), itrEnd = m_uniforms.end();
         itr != itrEnd; ++itr)
    { so->AddUniform(*itr); }

    for (attribute_itr itr = m_attributes.begin(), itrEnd = m_attributes.end();
         itr != itrEnd; ++itr)
    { so->AddAttribute(*itr); }

    mat->AddShaderOperator(so);

    m_entMgr->InsertComponent(a_ent, mat.get());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material&
    Material::
    AddUniform(const uniform_sptr_type& a_uniform)
  {
    m_uniforms.push_back(a_uniform);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material&
    Material::
    AddAttribute(const attribute_sptr_type& a_attribute)
  {
    m_attributes.push_back(a_attribute);
    return *this;
  }

};};};