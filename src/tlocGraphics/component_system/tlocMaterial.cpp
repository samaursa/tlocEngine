#include "tlocMaterial.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  Material::Material()
    : base_type(k_component_type)
    , m_shaderProgram(new shader_prog_ptr::value_type())
  {
  }

  Material::Material(const Material& a_other)
    : base_type(k_component_type)
    , m_vertexProgram(a_other.m_vertexProgram)
    , m_fragmentProgram(a_other.m_fragmentProgram)
    , m_shaderProgram(a_other.m_shaderProgram)
    , m_shaderOperators(a_other.m_shaderOperators)
  {
  }

  void Material::
    AddShaderOperator(shader_op_ptr a_shaderOp)
  {
    m_shaderOperators.push_back(a_shaderOp);
    SetUpdateRequired(true);
  }

  bool Material::
    RemoveShaderOperator(shader_op_ptr a_shaderOp)
  {
    shader_op_cont_itr itr = core::remove_all(m_shaderOperators, a_shaderOp);
    if (itr != m_shaderOperators.end())
    {
      SetUpdateRequired(true);
      return true;
    }

    return false;
  }

  void Material::
    RemoveAllShaderOperators()
  {
    m_shaderOperators.clear();
  }

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
    SetShaderProgram(const shader_prog_ptr& a_sp)
  {
    m_shaderProgram = a_sp;
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

using namespace tloc::gfx_cs;

// array
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Material::shader_op_ptr);

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Material);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(material_sptr);