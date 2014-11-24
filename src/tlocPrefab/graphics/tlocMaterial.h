#ifndef _TLOC_PREFAB_GRAPHICS_MATERIAL_H_
#define _TLOC_PREFAB_GRAPHICS_MATERIAL_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/io/tlocPath.h>

#include <tlocGraphics/opengl/tlocUniform.h>
#include <tlocGraphics/opengl/tlocAttributeVBO.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>
#include <tlocGraphics/component_system/tlocMaterial.h>

namespace tloc { namespace prefab { namespace graphics {

  class Material
    : public Prefab_TI<Material, gfx_cs::Material>
  {
  public:
    typedef Material                                this_type;
    typedef Prefab_TI<this_type, component_type>    base_type;
    typedef gfx_gl::uniform_vptr                    uniform_ptr_type;
    typedef gfx_gl::attributeVBO_vptr               attributeVBO_ptr_type;
    typedef gfx_gl::shader_operator_vso             shader_operator_vso;
    typedef tl_size                                 size_type;

    typedef core_conts::Array<uniform_ptr_type>     uniform_array;


    typedef uniform_array::iterator                 uniform_itr;
    typedef uniform_array::const_iterator           const_uniform_itr;

  public:
    Material(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr Construct(BufferArg a_vertexShader,
                            BufferArg a_fragmentShader) const;

    entity_ptr    Create(const core_io::Path& a_vertexShader,
                         const core_io::Path& a_fragmentShader) const;
    error_type    Add(entity_ptr a_ent,
                      const core_io::Path& a_vertexShader,
                      const core_io::Path& a_fragmentShader) const;

    entity_ptr    Create(BufferArg a_vertexShader,
                         BufferArg a_fragmentShader) const;
    void          Add(entity_ptr a_ent,
                      BufferArg a_vertexShader,
                      BufferArg a_fragmentShader) const;

    Material&     AddUniform(const uniform_ptr_type& a_uniform);

    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (uniform_itr, begin_uniforms, m_newUniformPtrs.begin());
    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (uniform_itr, end_uniforms, m_newUniformPtrs.end());

    TLOC_DECL_AND_DEF_GETTER(size_type, size_uniforms, m_newUniformPtrs.size());

    TLOC_DECL_PARAM_VAR(core_str::String, AssetsPath, m_assetsPath);

  private:
    uniform_array               m_uniforms;
    shader_operator_vso         m_so;

    mutable uniform_array       m_newUniformPtrs;

  };

};};};

#endif