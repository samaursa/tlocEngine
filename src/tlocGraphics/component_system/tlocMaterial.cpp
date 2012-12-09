#include "tlocMaterial.h"

namespace tloc { namespace graphics { namespace component_system {

  Material::Material() : base_type(component_system::components::material)
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

};};};