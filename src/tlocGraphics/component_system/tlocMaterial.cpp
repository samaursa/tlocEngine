#include "tlocMaterial.h"

#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////

  const char* g_uniformNames [] = 
  {
    "u_model",
    "u_modelInv",

    "u_mv",
    "u_mvInv",

    "u_mvp",
    "u_mvpInv",

    "u_vp",
    "u_vpInv",

    "u_view",
    "u_viewInv",

    "u_proj",
    "u_projInv",

    "u_scale",
    "u_scaleInv",

    "u_normal",
    "u_normalInv",
  };

  const char* g_attributeNames [] = 
  {
    "a_vertPos",
    "a_vertNorm",
    "a_vertCol",
    "a_vertTexCoord"
  };

  // ///////////////////////////////////////////////////////////////////////
  // Material

  Material::
    Material()
    : base_type("Material")
    , m_isDirty(true)
  { 
    m_internalShaderOp->reserve_uniforms(p_material::Uniforms::k_count);

    for (tl_size i = 0; i < p_material::Uniforms::k_count; ++i)
    {
      auto uniformName = g_uniformNames[i];
      auto uniformPtr = m_internalShaderOp->
        AddUniform(gl::Uniform().SetName(uniformName));

      m_internalUniforms.push_back(core::MakePair(uniformPtr, uniformName));
      SetEnableUniform(i, false);
    }

    SetEnableUniform<p_material::Uniforms::k_modelViewProjectionMatrix>();

    for (tl_size i = 0; i < p_material::Attributes::k_count; ++i)
    { m_attributeNames.push_back(g_attributeNames[i]); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::
    Material(const Material& a_other)
    : base_type(a_other)
    , m_vertexProgram(a_other.m_vertexProgram)
    , m_fragmentProgram(a_other.m_fragmentProgram)
    , m_shaderProgram(a_other.m_shaderProgram)
    , m_shaderOp(a_other.m_shaderOp)
    , m_internalShaderOp(a_other.m_internalShaderOp)
    , m_isDirty(true)
  { 
    auto itr = m_internalShaderOp->begin_uniforms(),
         itrEnd = m_internalShaderOp->end_uniforms();
    for (tl_size i = 0; i < p_material::Uniforms::k_count; ++i)
    {
      auto itrCopy = itr;
      core::advance(itrCopy, i);

      TLOC_ASSERT(itrCopy != itrEnd, "Iterator went out of bounds");

      m_internalUniforms.push_back(core::MakePair(itrCopy->first.get(), g_uniformNames[i]));
    }

    for (tl_size i = 0; i < p_material::Attributes::k_count; ++i)
    { m_attributeNames.push_back(g_attributeNames[i]); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::this_type&
    Material::
    AddUniform(const uniform_type& a_uniform)
  { m_shaderOp->AddUniform(a_uniform); return *this; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::this_type&
    Material::
    SetVertexSource(BufferArg a_source)
  {
    m_vertexProgram = a_source;
    SetUpdateRequired(true);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::this_type&
    Material::
    SetFragmentSource(BufferArg a_source)
  {
    m_fragmentProgram = a_source;
    SetUpdateRequired(true);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::this_type&
    Material::
    SetShaderProgram(const gl::ShaderProgram& a_sp)
  {
    *m_shaderProgram = a_sp;
    SetUpdateRequired(true);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::this_type&
    Material::
    SetUniformName(uniform_index_type a_index, BufferArg a_name)
  { m_internalUniforms[a_index].second = a_name; return *this; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const Material::string_type&
    Material::
    GetUniformName(uniform_index_type a_index) const
  { return m_internalUniforms[a_index].second; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::uniform_ptr
    Material::
    GetUniform(uniform_index_type a_index) const
  { return m_internalUniforms[a_index].first; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::this_type&
    Material::
    SetEnableUniform(uniform_index_type a_index, bool a_enable)
  {  m_internalUniforms[a_index].first->SetEnabled(a_enable); return *this; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Material::
    IsUniformEnabled(uniform_index_type a_index)
  {  return m_internalUniforms[a_index].first->IsEnabled(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::this_type&
    Material::
    SetAttributeName(attribute_index_type a_index, BufferArg a_name)
  { m_attributeNames[a_index] = a_name; return *this; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const Material::string_type&
    Material::
    GetAttributeName(attribute_index_type a_index) const
  { return m_attributeNames[a_index]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool 
    Material::
    operator ==(const Material& a_other) const
  {
    return GetUniqueGroupID() == a_other.GetUniqueGroupID();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool 
    Material::
    operator < (const Material& a_other) const
  {
    return GetUniqueGroupID() < a_other.GetUniqueGroupID();
  }

};};};

//------------------------------------------------------------------------
// Explicit Instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

// array
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Material::shader_op_ptr);

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Material);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(Material);