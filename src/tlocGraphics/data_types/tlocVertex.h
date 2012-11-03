#ifndef TLOC_VERTEX_H
#define TLOC_VERTEX_H

#include <tlocCore/types/tlocConditionalType.h>
#include <tlocMath/vector/tlocVector2.h>
#include <tlocMath/vector/tlocVector3.h>
#include <tlocGraphics/data_types/tlocColor.h>

namespace tloc { namespace graphics { namespace types {

  namespace p_vertex_t
  {
    template <typename T>
    class VertexPos
    {
    public:
      typedef T                                     value_type;

    public:
      TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(value_type, GetPosition, m_value);
      TLOC_DECL_AND_DEF_SETTER(value_type, SetPosition, m_value);

    private:
      value_type    m_value;
    };

    template <typename T>
    class VertexNorm
    {
    public:
      typedef T                                     value_type;

    public:
      TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(value_type, GetNormal, m_value);
      TLOC_DECL_AND_DEF_SETTER(value_type, SetNormal, m_value);

    private:
      value_type    m_value;
    };

    class VertexCol
    {
    public:
      typedef types::Color     value_type;

    public:
      TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(value_type, GetColor, m_value);
      TLOC_DECL_AND_DEF_SETTER(value_type, SetColor, m_value);

    private:
      value_type   m_value;
    };

    class TexCoord
    {
    public:
      typedef math::Vec2f           value_type;

    public:
      TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(value_type, GetTexCoord, m_value);
      TLOC_DECL_AND_DEF_SETTER(value_type, SetTexCoord, m_value);

    private:
      value_type   m_value;

    };

    //------------------------------------------------------------------------
    // Typedefs

    typedef VertexPos<math::Vec2f>    VertexPos2f;
    typedef VertexPos<math::Vec3f>    VertexPos3f;

    typedef VertexNorm<math::Vec2f>   VertexNorm2f;
    typedef VertexNorm<math::Vec3f>   VertexNorm3f;
  };

  template <class T_Position,
            class T_Normal = EmptyType_T<0>,
            class T_Color = EmptyType_T<1>,
            class T_TexCoord = EmptyType_T<2>>
  class Vertex_T : public T_Position,
                   public T_Normal,
                   public T_Color,
                   public T_TexCoord
  {
  public:
    typedef T_Position                                  position_type;
    typedef T_Normal                                    normal_type;
    typedef T_Color                                     color_type;
    typedef T_TexCoord                                  tex_coord_type;

    typedef typename position_type::value_type          position_value_type;
    typedef typename normal_type::value_type            normal_value_type;
    typedef typename color_type::value_type             color_value_type;
    typedef typename tex_coord_type::value_type         tex_coord_value_type;

    typedef position_type                               position_base_type;
    typedef normal_type                                 normal_base_type;
    typedef color_type                                  color_base_type;
    typedef tex_coord_type                              tex_coord_base_type;
  };

  //------------------------------------------------------------------------
  // Typedefs

  //````````````````````````````````````````````````````````````````````````
  // 2D
  typedef Vertex_T<p_vertex_t::VertexPos2f>                 Vert2fp;
  typedef Vertex_T<p_vertex_t::VertexPos2f,
                   p_vertex_t::VertexNorm2f>                Vert2fpn;
  typedef Vertex_T<p_vertex_t::VertexPos2f,
                   p_vertex_t::VertexNorm2f,
                   p_vertex_t::VertexCol>                   Vert2fpnc;
  typedef Vertex_T<p_vertex_t::VertexPos2f,
                   p_vertex_t::VertexNorm2f,
                   p_vertex_t::VertexCol,
                   p_vertex_t::TexCoord>                    Vert2fpnct;
  typedef Vertex_T<p_vertex_t::VertexPos2f,
                   EmptyType_T<0>, EmptyType_T<1>,
                   p_vertex_t::TexCoord>                    Vert2fpt;

  //````````````````````````````````````````````````````````````````````````
  // 3D
  typedef Vertex_T<p_vertex_t::VertexPos3f>                 Vert3fp;
  typedef Vertex_T<p_vertex_t::VertexPos3f,
                   p_vertex_t::VertexNorm3f>                Vert3fpn;
  typedef Vertex_T<p_vertex_t::VertexPos3f,
                   p_vertex_t::VertexNorm3f,
                   p_vertex_t::VertexCol>                   Vert3fpnc;
  typedef Vertex_T<p_vertex_t::VertexPos3f,
                   p_vertex_t::VertexNorm3f,
                   p_vertex_t::VertexCol,
                   p_vertex_t::TexCoord>                    Vert3fpnct;
  typedef Vertex_T<p_vertex_t::VertexPos3f,
                   EmptyType_T<0>, EmptyType_T<1>,
                   p_vertex_t::TexCoord>                    Vert3fpt;

};};};

#endif