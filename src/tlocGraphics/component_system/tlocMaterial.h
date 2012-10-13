#ifndef TLOC_MATERIAL_H
#define TLOC_MATERIAL_H

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/opengl/tlocObject.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace graphics { namespace component_system {

  class Material : public core::component_system::Component_T<Material>
  {
  public:
    typedef core::component_system::Component_T<Material>  base_type;
    typedef gl::Object::base_type::object_handle           shader_handle;

    Material();

    bool operator ==(const Material& a_other) const;
    bool operator < (const Material& a_other) const;
    TLOC_DECLARE_OPERATORS(Material);

    TLOC_DECL_AND_DEF_GETTER(core::String, GetVertexSource,
                             m_vertexProgram);
    TLOC_DECL_AND_DEF_GETTER(core::String, GetFragmentSource,
                             m_fragmentProgram);

    TLOC_DECL_AND_DEF_SETTER(core::String, GetVertexSource,
                             m_vertexProgram);
    TLOC_DECL_AND_DEF_SETTER(core::String, GetFragmentSource,
                             m_fragmentProgram);

    TLOC_DECL_AND_DEF_GETTER(shader_handle, GetShaderHandle,
                             m_shaderId);
    TLOC_DECL_AND_DEF_SETTER(shader_handle, SetShaderHandle,
                             m_shaderId);

  private:

    shader_handle           m_shaderId;
    core::String            m_vertexProgram;
    core::String            m_fragmentProgram;

  };

};};};

#endif