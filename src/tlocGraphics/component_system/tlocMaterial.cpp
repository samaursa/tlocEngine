#include "tlocMaterial.h"

namespace tloc { namespace graphics { namespace component_system {

  Material::Material()
    : base_type(component_system::components::material)
    , m_shaderProgram(new shader_prog_ptr::value_type())
  {
  }

  bool Material::operator ==(const Material& a_other) const
  {
    return GetUniqueGroupID() == a_other.GetUniqueGroupID();
  }

  bool Material::operator < (const Material& a_other) const
  {
    return GetUniqueGroupID() < a_other.GetUniqueGroupID();
  }

  //------------------------------------------------------------------------
  // Explicit Instantiation

  template class core::Array<Material::shader_op_ptr>;

};};};