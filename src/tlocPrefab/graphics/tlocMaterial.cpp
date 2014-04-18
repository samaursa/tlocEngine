#include "tlocMaterial.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/io/tlocFileIO.h>

#include <tlocGraphics/component_system/tlocMaterial.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;
  using core_sptr::MakeShared;

  using gfx_cs::material_sptr;

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::entity_ptr
    Material::
    Create(const core_io::Path& a_vertexShader,
           const core_io::Path& a_fragmentShader)
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_vertexShader, a_fragmentShader);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::entity_ptr
    Material::
    Create(BufferArg a_vertexShader,
           BufferArg a_fragmentShader)
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_vertexShader, a_fragmentShader);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Material::
    Add(entity_ptr a_ent,
        const core_io::Path& a_vertexShader,
        const core_io::Path& a_fragmentShader)
  {
    core_io::Path vsFullPath( (m_assetsPath + a_vertexShader.GetPath()).c_str() );
    core_io::Path fsFullPath( (m_assetsPath + a_fragmentShader.GetPath()).c_str() );

    core_io::FileIO_ReadA vsFile = core_io::FileIO_ReadA(vsFullPath);
    core_io::FileIO_ReadA fsFile = core_io::FileIO_ReadA(fsFullPath);

    core_str::String vsCode, fsCode;

    core_err::Error err = ErrorSuccess;
    err = vsFile.Open();
    TLOC_ASSERT(err == ErrorSuccess, "Could not open the vertex shader file");
    vsFile.GetContents(vsCode);
    vsFile.Close();

    err = fsFile.Open();
    TLOC_ASSERT(err == ErrorSuccess, "Could not open the fragment shader file");
    fsFile.GetContents(fsCode);
    fsFile.Close();

    Add(a_ent, vsCode, fsCode);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Material::
    Add(entity_ptr a_ent, BufferArg a_vertexShader, BufferArg a_fragmentShader)
  {
    using namespace gfx_cs::components;

    typedef ComponentPoolManager              pool_mgr;
    typedef gfx_cs::material_pool             mat_pool;

    gfx_cs::material_pool_vptr                matPool;

    if (m_compPoolMgr->Exists(material) == false)
    { matPool = m_compPoolMgr->CreateNewPool<gfx_cs::Material>(); }
    else
    { matPool = m_compPoolMgr->GetPool<gfx_cs::Material>(); }

    mat_pool::iterator  itrMat = matPool->GetNext();
    (*itrMat)->SetValue(MakeShared<gfx_cs::Material>() );

    gfx_cs::material_sptr mat = *(*itrMat)->GetValuePtr();

    mat->SetVertexSource(a_vertexShader);
    mat->SetFragmentSource(a_fragmentShader);

    gfx_gl::shader_operator_vso so;

    for (uniform_itr itr = m_uniforms.begin(), itrEnd = m_uniforms.end();
         itr != itrEnd; ++itr)
    { so->AddUniform(**itr); }

    for (attribute_itr itr = m_attributes.begin(), itrEnd = m_attributes.end();
         itr != itrEnd; ++itr)
    { so->AddAttribute(**itr); }

    mat->AddShaderOperator(*so);

    m_entMgr->InsertComponent(a_ent, mat);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material&
    Material::
    AddUniform(const uniform_ptr_type& a_uniform)
  {
    m_uniforms.push_back(a_uniform);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material&
    Material::
    AddAttribute(const attribute_ptr_type& a_attribute)
  {
    m_attributes.push_back(a_attribute);
    return *this;
  }

};};};

#include <tlocCore/containers/tlocArray.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(tloc::pref_gfx::Material::uniform_ptr_type);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(tloc::pref_gfx::Material::attribute_ptr_type);