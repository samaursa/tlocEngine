#ifndef _TLOC_PREFAB_GRAPHICS_CUBOID_H_
#define _TLOC_PREFAB_GRAPHICS_CUBOID_H_

#include <tlocPrefab/tlocPrefabBase.h>
#include <tlocPrefab/graphics/tlocMesh.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocMesh.h>

#include <tlocMath/types/tlocCuboid.h>

namespace tloc { namespace prefab { namespace graphics {

  template <bool T_TexCoords = true, bool T_Normals = true>
  class Cuboid_T
    : public Prefab_TI<Cuboid_T<T_TexCoords, T_Normals>, gfx_cs::Mesh>
  {
  public:
    typedef Cuboid_T<T_TexCoords, T_Normals>            this_type;
    typedef Prefab_TI<this_type, component_type>        base_type;
    typedef math_t::Cuboidf32                           cuboid_type;

    typedef gfx_t::f_vertex::p_vertex_selector::
            TexCoords<T_TexCoords>                      texcoords_selected;
    typedef gfx_t::f_vertex::p_vertex_selector::
            Normals<T_Normals>                          normals_selected;
  public:
    Cuboid_T(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr Construct();

    entity_ptr    Create();
    void          Add(entity_ptr a_ent);

    TLOC_DECL_PARAM_VAR(cuboid_type, Dimensions, m_cuboid);
    TLOC_DECL_AND_DEF_GETTER(bool, IsNormalsEnabled, T_Normals);
    TLOC_DECL_AND_DEF_GETTER(bool, IsTexCoordsEnabled, T_TexCoords);

  private:
    pref_gfx::Mesh    m_meshPref;
  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef Cuboid_T<>                                Cuboid;
  typedef Cuboid_T<true, false>                     cuboid_tex_no_normals;
  typedef Cuboid_T<false, true>                     cuboid_normals_no_tex;
  typedef Cuboid_T<false, false>                    cuboid_no_normals_no_tex;

  TLOC_EXTERN_TEMPLATE_CLASS(Cuboid_T<>);
  TLOC_EXTERN_TEMPLATE_CLASS(Cuboid_T<true TLOC_COMMA false>);
  TLOC_EXTERN_TEMPLATE_CLASS(Cuboid_T<false TLOC_COMMA true>);
  TLOC_EXTERN_TEMPLATE_CLASS(Cuboid_T<false TLOC_COMMA false>);

};};};

#endif