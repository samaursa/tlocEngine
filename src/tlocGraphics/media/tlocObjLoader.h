#ifndef _TLOC_GRAPHICS_OBJ_LOADER_H_
#define _TLOC_GRAPHICS_OBJ_LOADER_H_

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/utilities/tlocCheckpoints.h>

#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector2.h>

#include <tlocGraphics/types/tlocVertex.h>

namespace tloc { namespace graphics { namespace media {

  class ObjLoader
  {
  public:
    typedef core_err::Error                       error_type;
    typedef core_str::String                      string_type;

    typedef u32                                   index_type;
    typedef math_t::Vec3f32                       pos_type;
    typedef math_t::Vec3f32                       norm_type;
    typedef math_t::Mat3f32                       tbn_type;
    typedef math_t::Vec2f32                       tcoord_type;

    typedef tl_size                               size_type;

    typedef core_conts::Array<u32>                cont_index_type;
    typedef core_conts::Array<pos_type>           cont_pos_type;
    typedef core_conts::Array<tbn_type>           cont_tbn_type;
    typedef core_conts::Array<tcoord_type>        cont_tcoord_type;

  public:
    class ObjGroup
    {
    public:
      ObjGroup() { }

      core_str::String  m_name;
      cont_index_type   m_posIndices;
      cont_index_type   m_normIndices;
      cont_index_type   m_tcoordIndices;
    };

    class Vertices
    {
    public:
      Vertices() { }

      cont_pos_type     m_pos;
      cont_tcoord_type  m_tcoords;
      cont_tbn_type     m_tbn;
    };

  public:
    typedef core_conts::Array<ObjGroup>           cont_obj_groups;
    typedef cont_obj_groups::iterator             iterator;
    typedef cont_obj_groups::const_iterator       const_iterator;
    typedef cont_pos_type::iterator               iterator_pos;
    typedef cont_pos_type::const_iterator         const_iterator_pos;
    typedef cont_tbn_type::iterator               iterator_norm;
    typedef cont_tbn_type::const_iterator         const_iterator_norm;
    typedef cont_tcoord_type::iterator            iterator_tcoord;
    typedef cont_tcoord_type::const_iterator      const_iterator_tcoord;

    typedef gfx_t::Vert3fptm                      vert_type;
    typedef core_conts::Array<vert_type>          vert_cont_type;

  public:
    ObjLoader();

    bool            IsSupported(const string_type& a_input);
    error_type      Init(const string_type& a_fileContents);

    bool            IsInitialized() const;
    bool            IsValid() const;

    const ObjGroup& GetGroup(size_type a_groupIndex) const;

    const_iterator          begin() const;
    const_iterator          end() const;

    const_iterator_pos      begin_pos() const;
    const_iterator_pos      end_pos() const;

    const_iterator_norm     begin_norms() const;
    const_iterator_norm     end_norms() const;

    const_iterator_tcoord   begin_tcoords() const;
    const_iterator_tcoord   end_tcoords() const;

    error_type              GetUnpacked(vert_cont_type& a_vertsOut,
                                        size_type a_groupIndex) const;

    TLOC_DECL_AND_DEF_GETTER(cont_obj_groups::size_type, GetNumGroups,
                             m_objects.size());
    TLOC_DECL_AND_DEF_GETTER(cont_pos_type::size_type, GetNumPositions,
                             m_vertices.m_pos.size());
    TLOC_DECL_AND_DEF_GETTER(cont_pos_type::size_type, GetNumNormals,
                             m_vertices.m_tbn.size());
    TLOC_DECL_AND_DEF_GETTER(cont_pos_type::size_type, GetNumTCoords,
                             m_vertices.m_tcoords.size());

  private:
    Vertices                m_vertices;
    cont_obj_groups         m_objects;
    core_utils::Checkpoints m_flags;

  };

  TLOC_TYPEDEF_ALL_SMART_PTRS(ObjLoader, obj_loader);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(ObjLoader, obj_loader);

  namespace f_obj_loader {

    obj_loader_sptr
      LoadObjFile (const core_io::Path& a_filePath);

  };

};};};

#endif