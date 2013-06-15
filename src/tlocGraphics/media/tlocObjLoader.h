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

namespace tloc { namespace graphics { namespace media {

  class ObjLoader
  {
  public:
    typedef core_err::Error                       error_type;
    typedef core_str::String                      string_type;

    typedef u32                                   index_type;
    typedef math_t::Vec3f32                       pos_type;
    typedef math_t::Vec3f32                       norm_type;
    typedef math_t::Vec2f32                       tcoord_type;

    typedef tl_size                               size_type;

    typedef core_conts::Array<u32>                cont_index_type;
    typedef core_conts::Array<pos_type>           cont_pos_type;
    typedef core_conts::Array<norm_type>          cont_norm_type;
    typedef core_conts::Array<tcoord_type>        cont_tcoord_type;

  public:
    struct ObjGroup
    {
      cont_index_type   m_posIndices;
      cont_index_type   m_normIndices;
      cont_index_type   m_tcoordIndices;
      cont_pos_type     m_pos;
      cont_norm_type    m_norms;
      cont_tcoord_type  m_tcoords;
    };

  public:
    typedef core_conts::Array<ObjGroup>           cont_obj_groups;
    typedef cont_obj_groups::iterator             iterator;
    typedef cont_obj_groups::const_iterator       const_iterator;

  public:
    ObjLoader();

    bool       IsSupported(const string_type& a_input);
    error_type Init(const string_type& a_fileContents);

    bool       IsInitialized() const;

    const ObjGroup& GetGroup(size_type a_groupIndex) const;

    const_iterator   begin() const;
    const_iterator   end() const;

    TLOC_DECL_AND_DEF_GETTER(cont_obj_groups::size_type, GetNumGroups,
                             m_objects.size());


  private:
    cont_obj_groups   m_objects;

  };

};};};

#endif