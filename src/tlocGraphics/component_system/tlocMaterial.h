#ifndef TLOC_MATERIAL_H
#define TLOC_MATERIAL_H

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocGraphics/component_system/tlocGfxComponentType.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace graphics { namespace component_system {

  class Material : public core::component_system::ComponentT<Material>
  {
  public:
    typedef core::component_system::ComponentT<Material>  base_type;

    Material();

    bool operator ==(const Material& a_other) const;
    bool operator < (const Material& a_other) const;
    TLOC_DECLARE_OPERATORS(Material);

    TLOC_DECL_AND_DEF_GETTERS_DIRECT (core::String, GetVertexProgram,
                                      m_vertexProgram);
    TLOC_DECL_AND_DEF_GETTERS_DIRECT (core::String, GetFragmentProgram,
                                      m_fragmentProgram);

  private:

    core::String  m_vertexProgram;
    core::String  m_fragmentProgram;

  };

};};};

#endif