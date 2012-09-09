#ifndef TLOC_VERTEX_H
#define TLOC_VERTEX_H

#include <tlocCore/types/tlocConditionalType.h>
#include <tlocMath/vector/tlocVector3.h>

namespace tloc { namespace graphics {

  namespace detail
  {
    template <typename T, bool T_Declare>
    class VertexPos
    {
    protected:

      typedef T     value_type;

      core::ConditionalType<T, T_Declare> m_value;
    };

    template <typename T, bool T_Declare>
    class VertexNorm
    {
    protected:

      typedef T     value_type;

      core::ConditionalType<T, T_Declare> m_value;
    };

    template <typename T, bool T_Declare>
    class VertexCol
    {
    protected:

      typedef T     value_type;

      core::ConditionalType<T, T_Declare> m_value;
    };
  };

  template <bool T_Position, bool T_Normal, bool T_Color>
  class Vertex : detail::VertexPos<math::Vec3f, T_Position>,
                 detail::VertexNorm<math::Vec3f, T_Normal>,
                 detail::VertexCol<math::Vec3f, T_Color>
  {
  public:
    ~Vertex() {}

    typedef math::Vec3f                                     value_type;
    typedef detail::VertexPos<value_type, T_Position>       position_type;
    typedef detail::VertexNorm<value_type, T_Normal>        normal_type;
    typedef detail::VertexCol<value_type, T_Color>          color_type;

    typedef Loki::Select<T_Position, type_true, type_false> position_selected;
    typedef Loki::Select<T_Normal, type_true, type_false>   normal_selected;
    typedef Loki::Select<T_Color, type_true, type_false>    color_selected;

    typedef position_type         position_base_type;
    typedef normal_type           normal_base_type;
    typedef color_type            color_base_type;

    TLOC_DECL_AND_DEF_GETTERS_DIRECT
      (math::Vec3f, GetPosition, position_base_type::m_value);
    TLOC_DECL_AND_DEF_GETTERS_DIRECT
      (math::Vec3f, GetNormal, normal_base_type::m_value);
    TLOC_DECL_AND_DEF_GETTERS_DIRECT
      (math::Vec3f, GetColor, color_base_type::m_value);
  };

};};

#endif