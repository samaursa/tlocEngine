#ifndef TLOC_VERTEX_H
#define TLOC_VERTEX_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocConditionalType.h>
#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocGraphics/types/tlocColor.h>

namespace tloc { namespace graphics { namespace types {

  // All types here are 4 bytes as that is what OpenGL works with
  namespace p_vertex_t
  {
    template <typename T>
    class VertexPos
      : public T
    {
    public:
      typedef T                                     value_type;

    public:
      const value_type& GetPosition() const
      { return *this; }

      void SetPosition(const value_type& a_position)
      { *this = static_cast<const VertexPos<T>&>(a_position); }
    };

    template <typename T>
    class VertexNorm
      : public T
    {
    public:
      typedef T                                     value_type;

    public:
      const value_type& GetNormal() const
      { return *this; }

      void SetNormal(const value_type& a_normal)
      { *this = static_cast<const VertexNorm<T>&>(a_normal); }
    };

    class VertexCol
      : public types::Color
    {
    public:
      typedef types::Color     value_type;

    public:
      const value_type& GetColor() const
      { return *this; }

      void SetColor(const value_type& a_normal)
      { *this = static_cast<const VertexCol&>(a_normal); }
    };

    class TexCoord
      : math_t::Vec2f32
    {
    public:
      typedef math::types::Vec2f32           value_type;

    public:
      const value_type& GetTexCoord() const
      { return *this; }

      void SetTexCoord(const value_type& a_coord)
      { *this = static_cast<const TexCoord&>(a_coord); }

    };

    //------------------------------------------------------------------------
    // Typedefs

    typedef VertexPos<math::types::Vec2f32>    VertexPos2f;
    typedef VertexPos<math::types::Vec3f32>    VertexPos3f;

    typedef VertexNorm<math::types::Vec2f32>   VertexNorm2f;
    typedef VertexNorm<math::types::Vec3f32>   VertexNorm3f;
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
  typedef Vertex2_T<p_vertex_t::VertexPos2f,
                    p_vertex_t::TexCoord>                    Vert2fpt;
  typedef Vertex3_T<p_vertex_t::VertexPos2f,
                    p_vertex_t::VertexNorm3f,
                    p_vertex_t::VertexCol>                   Vert2fpnc;
  typedef Vertex3_T<p_vertex_t::VertexPos2f,
                    p_vertex_t::VertexNorm2f,
                    p_vertex_t::TexCoord>                    Vert2fpnt;
  typedef Vertex4_T<p_vertex_t::VertexPos2f,
                    p_vertex_t::VertexNorm3f,
                    p_vertex_t::VertexCol,
                    p_vertex_t::TexCoord>                    Vert2fpnct;

  //````````````````````````````````````````````````````````````````````````
  // 3D
  typedef Vertex1_T<p_vertex_t::VertexPos3f>                 Vert3fp;
  typedef Vertex2_T<p_vertex_t::VertexPos3f,
                    p_vertex_t::VertexNorm3f>                Vert3fpn;
  typedef Vertex2_T<p_vertex_t::VertexPos3f,
                    p_vertex_t::TexCoord>                    Vert3fpt;
  typedef Vertex3_T<p_vertex_t::VertexPos3f,
                    p_vertex_t::VertexNorm3f,
                    p_vertex_t::VertexCol>                   Vert3fpnc;
  typedef Vertex3_T<p_vertex_t::VertexPos3f,
                    p_vertex_t::VertexNorm3f,
                    p_vertex_t::TexCoord>                    Vert3fpnt;
  typedef Vertex4_T<p_vertex_t::VertexPos3f,
                    p_vertex_t::VertexNorm3f,
                    p_vertex_t::VertexCol,
                    p_vertex_t::TexCoord>                    Vert3fpnct;

};};};

#endif