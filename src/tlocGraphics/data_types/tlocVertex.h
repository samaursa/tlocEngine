#ifndef TLOC_VERTEX_H
#define TLOC_VERTEX_H

#include <tlocCore/types/tlocConditionalType.h>
#include <tlocMath/vector/tlocVector2.h>
#include <tlocMath/vector/tlocVector3.h>
#include <tlocGraphics/data_types/tlocColor.h>

namespace tloc { namespace graphics { namespace types {

  // All types here are 4 bytes as that is what OpenGL works with
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
      typedef math::Vec2f32           value_type;

    public:
      TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(value_type, GetTexCoord, m_value);
      TLOC_DECL_AND_DEF_SETTER(value_type, SetTexCoord, m_value);

    private:
      value_type   m_value;

    };

    //------------------------------------------------------------------------
    // Typedefs

    typedef VertexPos<math::Vec2f32>    VertexPos2f;
    typedef VertexPos<math::Vec3f32>    VertexPos3f;

    typedef VertexNorm<math::Vec2f32>   VertexNorm2f;
    typedef VertexNorm<math::Vec3f32>   VertexNorm3f;
  };

  template <class T_Attrib1>
  class Vertex1_T : public T_Attrib1
  {
  public:
    typedef T_Attrib1                           attrib_1_type;
  };

  template <class T_Attrib1, class T_Attrib2>
  class Vertex2_T : public T_Attrib1, public T_Attrib2
  {
  public:
    typedef T_Attrib1                           attrib_1_type;
    typedef T_Attrib1                           attrib_2_type;
  };

  template <class T_Attrib1, class T_Attrib2, class T_Attrib3>
  class Vertex3_T : public T_Attrib1, public T_Attrib2, public T_Attrib3
  {
  public:
    typedef T_Attrib1                           attrib_1_type;
    typedef T_Attrib1                           attrib_2_type;
    typedef T_Attrib3                           attrib_3_type;
  };

  template <class T_Attrib1, class T_Attrib2, class T_Attrib3, class T_Attrib4>
  class Vertex4_T : public T_Attrib1, public T_Attrib2,
                    public T_Attrib3, public T_Attrib4
  {
  public:
    typedef T_Attrib1                           attrib_1_type;
    typedef T_Attrib1                           attrib_2_type;
    typedef T_Attrib3                           attrib_3_type;
    typedef T_Attrib4                           attrib_4_type;
  };

  //------------------------------------------------------------------------
  // Typedefs

  //````````````````````````````````````````````````````````````````````````
  // 2D
  typedef Vertex1_T<p_vertex_t::VertexPos2f>                 Vert2fp;
  typedef Vertex2_T<p_vertex_t::VertexPos2f,
                    p_vertex_t::VertexNorm3f>                Vert2fpn;
  typedef Vertex3_T<p_vertex_t::VertexPos2f,
                    p_vertex_t::VertexNorm3f,
                    p_vertex_t::VertexCol>                   Vert2fpnc;
  typedef Vertex4_T<p_vertex_t::VertexPos2f,
                    p_vertex_t::VertexNorm3f,
                    p_vertex_t::VertexCol,
                    p_vertex_t::TexCoord>                    Vert2fpnct;
  typedef Vertex2_T<p_vertex_t::VertexPos2f,
                    p_vertex_t::TexCoord>                    Vert2fpt;

  //````````````````````````````````````````````````````````````````````````
  // 3D
  typedef Vertex1_T<p_vertex_t::VertexPos3f>                 Vert3fp;
  typedef Vertex2_T<p_vertex_t::VertexPos3f,
                    p_vertex_t::VertexNorm3f>                Vert3fpn;
  typedef Vertex3_T<p_vertex_t::VertexPos3f,
                    p_vertex_t::VertexNorm3f,
                    p_vertex_t::VertexCol>                   Vert3fpnc;
  typedef Vertex4_T<p_vertex_t::VertexPos3f,
                    p_vertex_t::VertexNorm3f,
                    p_vertex_t::VertexCol,
                    p_vertex_t::TexCoord>                    Vert3fpnct;
  typedef Vertex2_T<p_vertex_t::VertexPos3f,
                    p_vertex_t::TexCoord>                    Vert3fpt;

};};};

#endif