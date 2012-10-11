#ifndef TLOC_VERTEX_H
#define TLOC_VERTEX_H

#include <tlocCore/types/tlocConditionalType.h>
#include <tlocMath/vector/tlocVector3.h>
#include <tlocGraphics/data_types/tlocColor.h>

namespace tloc { namespace graphics { namespace types {

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
    public:

      typedef T     value_type;

      core::ConditionalType<T, T_Declare> m_value;
    };
  };

  template <bool T_Position, bool T_Normal, bool T_Color, typename T_RealType>
  class Vertex_T : public detail::VertexPos<T_RealType, T_Position>,
                   public detail::VertexNorm<math::Vec3f, T_Normal>,
                   public detail::VertexCol<types::Color, T_Color>
  {
  public:

    typedef T_RealType                                      value_type;
    typedef detail::VertexPos<value_type, T_Position>       position_type;
    typedef detail::VertexNorm<value_type, T_Normal>        normal_type;
    typedef detail::VertexCol<value_type, T_Color>          color_type;

    typedef typename position_type::value_type              position_value_type;
    typedef typename normal_type::value_type                normal_value_type;
    typedef typename color_type::value_type                 color_value_type;

    typedef Loki::Select<T_Position, type_true, type_false> position_selected;
    typedef Loki::Select<T_Normal, type_true, type_false>   normal_selected;
    typedef Loki::Select<T_Color, type_true, type_false>    color_selected;

    typedef position_type         position_base_type;
    typedef normal_type           normal_base_type;
    typedef color_type            color_base_type;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (position_value_type, GetPosition, position_base_type::m_value);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (normal_value_type, GetNormal, normal_base_type::m_value);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (color_value_type, GetColor, color_base_type::m_value);

    TLOC_DECL_AND_DEF_SETTER(position_value_type, SetPosition,
                             position_base_type::m_value);
    TLOC_DECL_AND_DEF_SETTER(normal_value_type, SetNormal,
                             normal_base_type::m_value);
    TLOC_DECL_AND_DEF_SETTER(color_value_type, SetColor,
                             color_base_type::m_value);
  };

  template <bool T_Position, bool T_Normal, bool T_Color>
  class Vertex2f_T: public Vertex_T<T_Position, T_Normal, T_Color, math::Vec3f>
  {
  public:
    typedef Vertex_T<T_Position, T_Normal, T_Color, math::Vec3f>      base_type;

    typedef typename base_type::value_type                  value_type;
    typedef typename base_type::position_type               position_type;
    typedef typename base_type::normal_type                 normal_type;
    typedef typename base_type::color_type                  color_type;

    typedef typename base_type::position_selected	          position_selected;
    typedef typename base_type::normal_selected		          normal_selected;
    typedef typename base_type::color_selected		          color_selected;

    typedef typename base_type::position_base_type          position_base_type;
    typedef typename base_type::normal_base_type            normal_base_type;
    typedef typename base_type::color_base_type             color_base_type;

  public:
    using base_type::GetPosition;
    using base_type::GetNormal;
    using base_type::GetColor;

    using base_type::SetPosition;
    using base_type::SetNormal;
    using base_type::SetColor;
  };

  template <bool T_Position, bool T_Normal, bool T_Color>
  class Vertex3f_T : public Vertex_T<T_Position, T_Normal, T_Color, math::Vec3f>
  {
  public:
    typedef Vertex_T<T_Position, T_Normal, T_Color, math::Vec3f>      base_type;

    typedef typename base_type::value_type                  value_type;
    typedef typename base_type::position_type               position_type;
    typedef typename base_type::normal_type                 normal_type;
    typedef typename base_type::color_type                  color_type;

    typedef typename base_type::position_selected	          position_selected;
    typedef typename base_type::normal_selected		          normal_selected;
    typedef typename base_type::color_selected		          color_selected;

    typedef typename base_type::position_base_type          position_base_type;
    typedef typename base_type::normal_base_type            normal_base_type;
    typedef typename base_type::color_base_type             color_base_type;

  public:
    using base_type::GetPosition;
    using base_type::GetNormal;
    using base_type::GetColor;

    using base_type::SetPosition;
    using base_type::SetNormal;
    using base_type::SetColor;
  };

  //------------------------------------------------------------------------
  // Typedefs

  typedef Vertex2f_T<true, false, false>      Vert2fP;
  typedef Vertex2f_T<true, true, false>       Vert2fPN;
  typedef Vertex2f_T<true, true, true>        Vert2fPNC;

  typedef Vertex3f_T<true, false, false>      Vert3fP;
  typedef Vertex3f_T<true, true, false>       Vert3fPN;
  typedef Vertex3f_T<true, true, true>        Vert3fPNC;

};};};

#endif