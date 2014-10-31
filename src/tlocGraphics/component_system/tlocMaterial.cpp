#include "tlocMaterial.h"

#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  // -----------------------------------------------------------------------
  // typedefs

  typedef Material::uniform_vso_cont::iterator        shader_op_cont_itr;
  typedef Material::uniform_vso_cont::const_iterator  shader_op_cont_const_itr;

  // ///////////////////////////////////////////////////////////////////////
  // Material

  Material::Material()
    : base_type("Material")
  { }

  Material::Material(const Material& a_other)
    : base_type(a_other)
    , m_vertexProgram(a_other.m_vertexProgram)
    , m_fragmentProgram(a_other.m_fragmentProgram)
    , m_shaderProgram(a_other.m_shaderProgram)
    , m_uniformCont(a_other.m_uniformCont)
  { }

  void
    Material::
    AddUniform(const uniform_type& a_uniform)
  { m_uniformCont.push_back( uniform_vso(MakeArgs(a_uniform)) ); }

  void Material::
    SetVertexSource(BufferArg a_source)
  {
    m_vertexProgram = a_source;
    SetUpdateRequired(true);
  }

  void Material::
    SetFragmentSource(BufferArg a_source)
  {
    m_fragmentProgram = a_source;
    SetUpdateRequired(true);
  }

  void Material::
    SetShaderProgram(const gl::ShaderProgram& a_sp)
  {
    *m_shaderProgram = a_sp;
    SetUpdateRequired(true);
  }

  bool Material::operator ==(const Material& a_other) const
  {
    return GetUniqueGroupID() == a_other.GetUniqueGroupID();
  }

  bool Material::operator < (const Material& a_other) const
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