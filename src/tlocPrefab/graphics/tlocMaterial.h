#ifndef _TLOC_PREFAB_GRAPHICS_MATERIAL_H_
#define _TLOC_PREFAB_GRAPHICS_MATERIAL_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/io/tlocPath.h>

#include <tlocGraphics/opengl/tlocUniform.h>
#include <tlocGraphics/opengl/tlocAttribute.h>

namespace tloc { namespace prefab { namespace graphics {

  class Material
    : public Prefab_I
  {
  public:
    typedef Material                                this_type;
    typedef gfx_gl::uniform_sptr                    uniform_sptr_type;
    typedef gfx_gl::attribute_sptr                  attribute_sptr_type;

    typedef core_conts::Array<uniform_sptr_type>    uniform_array;
    typedef core_conts::Array<attribute_sptr_type>  attribute_array;

    typedef uniform_array::iterator                 uniform_itr;
    typedef attribute_array::iterator               attribute_itr;

  public:
    Material(core_cs::EntityManager* a_entMgr,
             core_cs::ComponentPoolManager* a_poolMgr)
             : Prefab_I(a_entMgr, a_poolMgr)
    { }

    entity_type*  Create(const core_io::Path& a_vertexShader,
                         const core_io::Path& a_fragmentShader);
    void          Add(entity_type* a_ent,
                      const core_io::Path& a_vertexShader,
                      const core_io::Path& a_fragmentShader);

    Material&     AddUniform(const uniform_sptr_type& a_uniform);
    Material&     AddAttribute(const attribute_sptr_type& a_attribute);

    TLOC_DECL_PARAM_VAR(core_str::String, AssetsPath, m_assetsPath);

  private:
    uniform_array       m_uniforms;
    attribute_array     m_attributes;

  };

};};};

#endif