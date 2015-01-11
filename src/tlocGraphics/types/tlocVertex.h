#ifndef TLOC_VERTEX_H
#define TLOC_VERTEX_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocConditionalType.h>
#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix4.h>
#include <tlocGraphics/types/tlocColor.h>

namespace tloc { namespace graphics { namespace types {

  // All types here are 4 bytes as that is what OpenGL works with
  namespace p_vertex_t
  {
    template <typename T>
    class VertexPos_T
      : public T
    {
    public:
      typedef T                                     value_type;

    public:
      const value_type& GetPosition() const
      { return *this; }

      void SetPosition(const value_type& a_position)
      { *this = static_cast<const VertexPos_T<T>&>(a_position); }
    };

    template <typename T>
    class VertexOrientation_T
      : public T
    {
    public:
      typedef T                                     value_type;

    public:
      const value_type& GetOrientation() const
      { return *this; }

      void SetOrientation(const value_type& a_position)
      { *this = static_cast<const VertexOrientation_T<T>&>(a_position); }
    };

    template <typename T>
    class VertexNorm_T
      : public T
    {
    public:
      typedef T                                     value_type;

    public:
      const value_type& GetNormal() const
      { return *this; }

      void SetNormal(const value_type& a_normal)
      { *this = static_cast<const VertexNorm_T<T>&>(a_normal); }
    };

    class VertexCol
      : public math_t::Vec4f32
    {
    public:
      typedef math_t::Vec4f32                     value_type;
      typedef types::Color                        color_type;

    public:
      value_type GetColor() const
      { 
        return value_type(Get(0), Get(1), Get(2), Get(3)); 
      }

      void SetColor(const value_type& a_color)
      { *this = static_cast<const VertexCol&>(a_color); }

      void SetColor(const color_type& a_color)
      { 
        math_t::Vec4f32 temp;
        a_color.GetAs<gfx_t::p_color::format::RGBA>(temp); 
        operator[](0) = temp[0];
        operator[](1) = temp[1];
        operator[](2) = temp[2];
        operator[](3) = temp[3];
      }
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

    typedef VertexPos_T<math::types::Vec2f32>             VertexPos2f;
    typedef VertexPos_T<math::types::Vec3f32>             VertexPos3f;

    typedef VertexOrientation_T<math::types::Mat4f32>     VertexOri4f;

    typedef VertexNorm_T<math::types::Vec2f32>            VertexNorm2f;
    typedef VertexNorm_T<math::types::Vec3f32>            VertexNorm3f;
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
    typedef T_Attrib2                           attrib_2_type;

  public:
    ~Vertex2_T() {}
  };

  template <class T_Attrib1, class T_Attrib2, class T_Attrib3>
  class Vertex3_T : public T_Attrib1, public T_Attrib2, public T_Attrib3
  {
  public:
    typedef T_Attrib1                           attrib_1_type;
    typedef T_Attrib2                           attrib_2_type;
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
    typedef T_Attrib2                           attrib_2_type;
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
                    p_vertex_t::VertexNorm3f,
                    p_vertex_t::TexCoord>                    Vert2fpnt;
  typedef Vertex4_T<p_vertex_t::VertexPos2f,
                    p_vertex_t::VertexNorm3f,
                    p_vertex_t::TexCoord,
                    p_vertex_t::VertexOri4f>                 Vert2fpnto;
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
                    p_vertex_t::TexCoord,
                    p_vertex_t::VertexOri4f>                 Vert3fpnto;
  typedef Vertex4_T<p_vertex_t::VertexPos3f,
                    p_vertex_t::VertexNorm3f,
                    p_vertex_t::VertexCol,
                    p_vertex_t::TexCoord>                    Vert3fpnct;

  typedef Vertex1_T<p_vertex_t::VertexOri4f>                 Vert4fo;

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

#define TLOC_GL_POSITION2F_NORMAL3F_TEXTURE2F_ORIENTATION 0xF
#define TLOC_GL_POSITION3F_NORMAL3F_TEXTURE2F_ORIENTATION 0x10

#define TLOC_GL_ORIENTATION4F                             0x11

  namespace f_vertex {

    // ///////////////////////////////////////////////////////////////////////
    // Vertex to GL pointer info

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

    // ///////////////////////////////////////////////////////////////////////
    // VertexSelector and filler
    // NOTES: These classes are useful for filling a generic vertex properly
    //        with the available values.

    namespace p_vertex_selector
    {
      class Pos2D      {};
      class Pos3D      {};

      template <bool T_Enable = true>
      class Normals    { public: enum { k_value = T_Enable }; };

      template <bool T_Enable = true>
      class Color      { public: enum { k_value = T_Enable }; };

      template <bool T_Enable = true>
      class TexCoords  { public: enum { k_value = T_Enable }; };
    };

    // -----------------------------------------------------------------------
    // template base

    template <typename T_PositionType, 
              typename T_Normals, 
              typename T_Color, 
              typename T_TexCoords>
    struct VertexSelector
    {
      TLOC_STATIC_ASSERT(
        (Loki::IsSameType<T_PositionType, p_vertex_selector::Pos2D>::value ||
        (Loki::IsSameType<T_PositionType, p_vertex_selector::Pos3D>::value)),
         Use_p_vertex_selector_Pos2D_or_Pos3D);

      TLOC_STATIC_ASSERT(
        (Loki::IsSameType<T_Normals, p_vertex_selector::Normals<true>>::value ||
        (Loki::IsSameType<T_Normals, p_vertex_selector::Normals<false>>::value)),
         Use_p_vertex_selector_Normals);

      TLOC_STATIC_ASSERT(
        (Loki::IsSameType<T_Color, p_vertex_selector::Color<true>>::value ||
        (Loki::IsSameType<T_Color, p_vertex_selector::Color<false>>::value)),
         Use_p_vertex_selector_Color);

      TLOC_STATIC_ASSERT(
        (Loki::IsSameType<T_Color, p_vertex_selector::TexCoords<true>>::value ||
        (Loki::IsSameType<T_Color, p_vertex_selector::TexCoords<false>>::value)),
         Use_p_vertex_selector_TexCoords);
    };

    // -----------------------------------------------------------------------
    // 2D vertices

    template <>
    struct VertexSelector<p_vertex_selector::Pos2D, 
                          p_vertex_selector::Normals<true>, 
                          p_vertex_selector::Color<true>,
                          p_vertex_selector::TexCoords<true>>
    {
      typedef gfx_t::Vert2fpnct                       value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;
      typedef value_type::attrib_2_type::value_type   norm_type;
      typedef value_type::attrib_3_type::value_type   col_type;
      typedef value_type::attrib_4_type::value_type   tex_coord_type;

      value_type Fill(pos_type a_pos, norm_type a_norm, col_type a_col, 
                      tex_coord_type a_texCoord)
      {
        value_type vert;
        vert.SetPosition(a_pos);
        vert.SetNormal(a_norm);
        vert.SetColor(a_col);
        vert.SetTexCoord(a_texCoord);

        return vert;
      }
    };

    template <>
    struct VertexSelector<p_vertex_selector::Pos2D, 
                          p_vertex_selector::Normals<true>, 
                          p_vertex_selector::Color<true>,
                          p_vertex_selector::TexCoords<false>>
    {
      typedef gfx_t::Vert2fpnc                        value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;
      typedef value_type::attrib_2_type::value_type   norm_type;
      typedef value_type::attrib_3_type::value_type   col_type;

      template <typename T_TexCoordType>
      value_type Fill(pos_type a_pos, norm_type a_norm, col_type a_col, 
                      T_TexCoordType )
      {
        value_type vert;
        vert.SetPosition(a_pos);
        vert.SetNormal(a_norm);
        vert.SetColor(a_col);

        return vert;
      }
    };

    template <>
    struct VertexSelector<p_vertex_selector::Pos2D, 
                          p_vertex_selector::Normals<true>, 
                          p_vertex_selector::Color<false>,
                          p_vertex_selector::TexCoords<true>>
    {
      typedef gfx_t::Vert2fpnt                        value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;
      typedef value_type::attrib_2_type::value_type   norm_type;
      typedef value_type::attrib_3_type::value_type   tex_coord_type;

      template <typename T_ColType>
      value_type Fill(pos_type a_pos, norm_type a_norm, T_ColType , 
                      tex_coord_type a_texCoord)
      {
        value_type vert;
        vert.SetPosition(a_pos);
        vert.SetNormal(a_norm);
        vert.SetTexCoord(a_texCoord);

        return vert;
      }
    };

    template <>
    struct VertexSelector<p_vertex_selector::Pos2D, 
                          p_vertex_selector::Normals<false>, 
                          p_vertex_selector::Color<false>,
                          p_vertex_selector::TexCoords<true>>
    {
      typedef gfx_t::Vert2fpt                         value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;
      typedef value_type::attrib_2_type::value_type   tex_coord_type;

      template <typename T_NormType, typename T_ColType>
      value_type Fill(pos_type a_pos, T_NormType , T_ColType , 
                      tex_coord_type a_texCoord)
      {
        value_type vert;
        vert.SetPosition(a_pos);
        vert.SetTexCoord(a_texCoord);

        return vert;
      }
    };

    template <>
    struct VertexSelector<p_vertex_selector::Pos2D, 
                          p_vertex_selector::Normals<false>, 
                          p_vertex_selector::Color<true>,
                          p_vertex_selector::TexCoords<false>>
    {
      typedef gfx_t::Vert2fpc                         value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;
      typedef value_type::attrib_2_type::value_type   col_type;

      template <typename T_NormType, typename T_TexCoordType>
      value_type Fill(pos_type a_pos, T_NormType , col_type a_col, 
                      T_TexCoordType )
      {
        value_type vert;
        vert.SetPosition(a_pos);
        vert.SetColor(a_col);

        return vert;
      }
    };

    template <>
    struct VertexSelector<p_vertex_selector::Pos2D, 
                          p_vertex_selector::Normals<true>, 
                          p_vertex_selector::Color<false>,
                          p_vertex_selector::TexCoords<false>>
    {
      typedef gfx_t::Vert2fpn                         value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;
      typedef value_type::attrib_2_type::value_type   norm_type;

      template <typename T_ColType, typename T_TexCoordType>
      value_type Fill(pos_type a_pos, norm_type a_norm, T_ColType , 
                      T_TexCoordType a_texCoord)
      {
        value_type vert;
        vert.SetPosition(a_pos);
        vert.SetNormal(a_norm);

        return vert;
      }
    };

    template <>
    struct VertexSelector<p_vertex_selector::Pos2D, 
                          p_vertex_selector::Normals<false>, 
                          p_vertex_selector::Color<false>,
                          p_vertex_selector::TexCoords<false>>
    {
      typedef gfx_t::Vert2fp                          value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;

      template <typename T_NormType, typename T_ColType, typename T_TexCoordType>
      value_type Fill(pos_type a_pos, T_NormType , T_ColType , 
                      T_TexCoordType )
      {
        value_type vert;
        vert.SetPosition(a_pos);

        return vert;
      }
    };

    // -----------------------------------------------------------------------
    // 3D vertices

    template <>
    struct VertexSelector<p_vertex_selector::Pos3D, 
                          p_vertex_selector::Normals<true>, 
                          p_vertex_selector::Color<true>,
                          p_vertex_selector::TexCoords<true>>
    {
      typedef gfx_t::Vert3fpnct                       value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;
      typedef value_type::attrib_2_type::value_type   norm_type;
      typedef value_type::attrib_3_type::value_type   col_type;
      typedef value_type::attrib_4_type::value_type   tex_coord_type;

      value_type Fill(pos_type a_pos, norm_type a_norm, col_type a_col, 
                      tex_coord_type a_texCoord)
      {
        value_type vert;
        vert.SetPosition(a_pos);
        vert.SetNormal(a_norm);
        vert.SetColor(a_col);
        vert.SetTexCoord(a_texCoord);

        return vert;
      }
    };

    template <>
    struct VertexSelector<p_vertex_selector::Pos3D, 
                          p_vertex_selector::Normals<true>, 
                          p_vertex_selector::Color<true>,
                          p_vertex_selector::TexCoords<false>>
    {
      typedef gfx_t::Vert3fpnc                        value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;
      typedef value_type::attrib_2_type::value_type   norm_type;
      typedef value_type::attrib_3_type::value_type   col_type;

      template <typename T_TexCoordType>
      value_type Fill(pos_type a_pos, norm_type a_norm, col_type a_col, 
                      T_TexCoordType )
      {
        value_type vert;
        vert.SetPosition(a_pos);
        vert.SetNormal(a_norm);
        vert.SetColor(a_col);

        return vert;
      }
    };

    template <>
    struct VertexSelector<p_vertex_selector::Pos3D, 
                          p_vertex_selector::Normals<true>, 
                          p_vertex_selector::Color<false>,
                          p_vertex_selector::TexCoords<true>>
    {
      typedef gfx_t::Vert3fpnt                        value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;
      typedef value_type::attrib_2_type::value_type   norm_type;
      typedef value_type::attrib_3_type::value_type   tex_coord_type;

      template <typename T_ColType>
      value_type Fill(pos_type a_pos, norm_type a_norm, T_ColType , 
                      tex_coord_type a_texCoord)
      {
        value_type vert;
        vert.SetPosition(a_pos);
        vert.SetNormal(a_norm);
        vert.SetTexCoord(a_texCoord);

        return vert;
      }
    };

    template <>
    struct VertexSelector<p_vertex_selector::Pos3D, 
                          p_vertex_selector::Normals<false>, 
                          p_vertex_selector::Color<false>,
                          p_vertex_selector::TexCoords<true>>
    {
      typedef gfx_t::Vert3fpt                         value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;
      typedef value_type::attrib_2_type::value_type   tex_coord_type;

      template <typename T_NormType, typename T_ColType>
      value_type Fill(pos_type a_pos, T_NormType , T_ColType , 
                      tex_coord_type a_texCoord)
      {
        value_type vert;
        vert.SetPosition(a_pos);
        vert.SetTexCoord(a_texCoord);

        return vert;
      }
    };

    template <>
    struct VertexSelector<p_vertex_selector::Pos3D, 
                          p_vertex_selector::Normals<false>, 
                          p_vertex_selector::Color<true>,
                          p_vertex_selector::TexCoords<false>>
    {
      typedef gfx_t::Vert3fpc                         value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;
      typedef value_type::attrib_2_type::value_type   col_type;

      template <typename T_NormType, typename T_TexCoordType>
      value_type Fill(pos_type a_pos, T_NormType , col_type a_col, 
                      T_TexCoordType )
      {
        value_type vert;
        vert.SetPosition(a_pos);
        vert.SetColor(a_col);

        return vert;
      }
    };

    template <>
    struct VertexSelector<p_vertex_selector::Pos3D, 
                          p_vertex_selector::Normals<true>, 
                          p_vertex_selector::Color<false>,
                          p_vertex_selector::TexCoords<false>>
    {
      typedef gfx_t::Vert3fpn                         value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;
      typedef value_type::attrib_2_type::value_type   norm_type;

      template <typename T_ColType, typename T_TexCoordType>
      value_type Fill(pos_type a_pos, norm_type a_norm, T_ColType , 
                      T_TexCoordType )
      {
        value_type vert;
        vert.SetPosition(a_pos);
        vert.SetNormal(a_norm);

        return vert;
      }
    };

    template <>
    struct VertexSelector<p_vertex_selector::Pos3D, 
                          p_vertex_selector::Normals<false>, 
                          p_vertex_selector::Color<false>,
                          p_vertex_selector::TexCoords<false>>
    {
      typedef gfx_t::Vert3fp                          value_type;
      typedef value_type::attrib_1_type::value_type   pos_type;

      template <typename T_NormType, typename T_ColType, typename T_TexCoordType>
      value_type Fill(pos_type a_pos, T_NormType , T_ColType , 
                      T_TexCoordType )
      {
        value_type vert;
        vert.SetPosition(a_pos);

        return vert;
      }
    };

  };

};};};

#endif