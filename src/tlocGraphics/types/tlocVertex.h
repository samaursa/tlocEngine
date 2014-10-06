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

  public:
    ~Vertex1_T() {}
  };

  template <class T_Attrib1, class T_Attrib2>
  class Vertex2_T : public T_Attrib1, public T_Attrib2
  {
  public:
    typedef T_Attrib1                           attrib_1_type;
    typedef T_Attrib1                           attrib_2_type;

  public:
    ~Vertex2_T() {}
  };

  template <class T_Attrib1, class T_Attrib2, class T_Attrib3>
  class Vertex3_T : public T_Attrib1, public T_Attrib2, public T_Attrib3
  {
  public:
    typedef T_Attrib1                           attrib_1_type;
    typedef T_Attrib1                           attrib_2_type;
    typedef T_Attrib3                           attrib_3_type;

  public:
    ~Vertex3_T() {}
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

  public:
    ~Vertex4_T() {}
  };

  //------------------------------------------------------------------------
  // Typedefs

  //````````````````````````````````````````````````````````````````````````
  // 2D
  typedef Vertex1_T<p_vertex_t::VertexPos2f>                 Vert2fp;
  typedef Vertex2_T<p_vertex_t::VertexPos2f,
                    p_vertex_t::VertexNorm3f>                Vert2fpn;
  typedef Vertex2_T<p_vertex_t::VertexPos2f,
                    p_vertex_t::VertexCol>                   Vert2fpc;
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
  typedef Vertex2_T<p_vertex_t::VertexPos3f,
                    p_vertex_t::VertexCol>                   Vert3fpc;
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

  // -----------------------------------------------------------------------
  // custom GL type enumerators

#define TLOC_GL_POSITION2F                                0x1
#define TLOC_GL_POSITION2F_NORMAL3F                       0x2
#define TLOC_GL_POSITION2F_TEXTURE2F                      0x3
#define TLOC_GL_POSITION2F_COLOR4F                        0x4
#define TLOC_GL_POSITION2F_NORMAL3F_COLOR4F               0x5
#define TLOC_GL_POSITION2F_NORMAL3F_TEXTURE2F             0x6
#define TLOC_GL_POSITION2F_NORMAL3F_COLOR4F_TEXTURE2F     0x7

#define TLOC_GL_POSITION3F                                0x8
#define TLOC_GL_POSITION3F_NORMAL3F                       0x9
#define TLOC_GL_POSITION3F_TEXTURE2F                      0xA
#define TLOC_GL_POSITION3F_COLOR4F                        0xB
#define TLOC_GL_POSITION3F_NORMAL3F_COLOR4F               0xC
#define TLOC_GL_POSITION3F_NORMAL3F_TEXTURE2F             0xD
#define TLOC_GL_POSITION3F_NORMAL3F_COLOR4F_TEXTURE2F     0xE

  namespace f_vertex {

    struct VertexAttribPointerInfo 
    {
      typedef s32                                       gl_int;
      typedef s32                                       gl_sizei;
      typedef tl_size                                   size_type;

      VertexAttribPointerInfo();

      VertexAttribPointerInfo(gl_int a_size, gl_sizei a_stride, 
                              size_type a_pointerIndex);

      gl_int          m_size;
      gl_sizei        m_stride;
      size_type       m_pointerIndex;
    };

    VertexAttribPointerInfo 
      GetCustomGLTypeInfo(tl_int a_customGlType, tl_size a_interleaveIndex = 0);

  };

};};};

#endif