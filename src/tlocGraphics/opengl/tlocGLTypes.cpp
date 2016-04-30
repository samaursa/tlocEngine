#include "tlocGLTypes.h"

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/types/tlocVertex.h>
#include <tlocGraphics/opengl/tlocTextureObject.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>
#include <tlocMath/types/tlocMatrix2.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>

namespace tloc { namespace graphics { namespace types {

  using namespace math_t;
  using namespace core_conts;
  using namespace core_ds;
  using namespace gfx_gl;

  namespace {
    template <typename T> struct tlToGl;
  }

#define TLOC_DECL_TL_TO_GL(_type_, _glType_)\
  namespace {\
    template <> struct tlToGl< _type_ >\
    { enum { k_glType = _glType_ }; };\
  };\
  namespace type_to_gl {\
    template gl_enum Get<_type_>();\
  }

  TLOC_DECL_TL_TO_GL(s8, GL_BYTE);
  TLOC_DECL_TL_TO_GL(u8, GL_UNSIGNED_BYTE);

  TLOC_DECL_TL_TO_GL(short, GL_SHORT);
  TLOC_DECL_TL_TO_GL(ushort, GL_UNSIGNED_SHORT);

  TLOC_DECL_TL_TO_GL(f32, GL_FLOAT);

  TLOC_DECL_TL_TO_GL(Vec2f32, GL_FLOAT_VEC2);
  TLOC_DECL_TL_TO_GL(Vec3f32, GL_FLOAT_VEC3);
  TLOC_DECL_TL_TO_GL(Vec4f32, GL_FLOAT_VEC4);

  TLOC_DECL_TL_TO_GL(s32, GL_INT);

  TLOC_DECL_TL_TO_GL(Tuple2s32, GL_INT_VEC2);
  TLOC_DECL_TL_TO_GL(Tuple3s32, GL_INT_VEC3);
  TLOC_DECL_TL_TO_GL(Tuple4s32, GL_INT_VEC4);

  TLOC_DECL_TL_TO_GL(u32, GL_UNSIGNED_INT);

  TLOC_DECL_TL_TO_GL(bool, GL_BOOL);

  TLOC_DECL_TL_TO_GL(Tuple2b, GL_BOOL_VEC2);
  TLOC_DECL_TL_TO_GL(Tuple3b, GL_BOOL_VEC3);
  TLOC_DECL_TL_TO_GL(Tuple4b, GL_BOOL_VEC4);

  TLOC_DECL_TL_TO_GL(Mat2f32, GL_FLOAT_MAT2);
  TLOC_DECL_TL_TO_GL(Mat3f32, GL_FLOAT_MAT3);
  TLOC_DECL_TL_TO_GL(Mat4f32, GL_FLOAT_MAT4);

  TLOC_DECL_TL_TO_GL(Array<s8>,     GL_BYTE);
  TLOC_DECL_TL_TO_GL(Array<u8>,     GL_UNSIGNED_BYTE);
  TLOC_DECL_TL_TO_GL(Array<short>,  GL_SHORT);
  TLOC_DECL_TL_TO_GL(Array<ushort>, GL_UNSIGNED_SHORT);

  TLOC_DECL_TL_TO_GL(Array<f32>,     GL_FLOAT);
  TLOC_DECL_TL_TO_GL(Array<Vec2f32>, GL_FLOAT_VEC2);
  TLOC_DECL_TL_TO_GL(Array<Vec3f32>, GL_FLOAT_VEC3);
  TLOC_DECL_TL_TO_GL(Array<Vec4f32>, GL_FLOAT_VEC4);

  TLOC_DECL_TL_TO_GL(Array<Mat2f32>, GL_FLOAT_MAT2);
  TLOC_DECL_TL_TO_GL(Array<Mat3f32>, GL_FLOAT_MAT3);
  TLOC_DECL_TL_TO_GL(Array<Mat4f32>, GL_FLOAT_MAT4);

  TLOC_DECL_TL_TO_GL(Array<s32>,       GL_INT);
  TLOC_DECL_TL_TO_GL(Array<Tuple2s32>, GL_INT_VEC2);
  TLOC_DECL_TL_TO_GL(Array<Tuple3s32>, GL_INT_VEC3);
  TLOC_DECL_TL_TO_GL(Array<Tuple4s32>, GL_INT_VEC4);

  TLOC_DECL_TL_TO_GL(Array<u32>,       GL_UNSIGNED_INT);

  TLOC_DECL_TL_TO_GL(Array<bool>,    GL_BOOL);
  TLOC_DECL_TL_TO_GL(Array<Tuple2b>, GL_BOOL_VEC2);
  TLOC_DECL_TL_TO_GL(Array<Tuple3b>, GL_BOOL_VEC3);
  TLOC_DECL_TL_TO_GL(Array<Tuple4b>, GL_BOOL_VEC4);

  TLOC_DECL_TL_TO_GL(TextureObject, GL_SAMPLER_2D);
  TLOC_DECL_TL_TO_GL(TextureObject3D, GL_SAMPLER_3D);
  TLOC_DECL_TL_TO_GL(TextureObjectCubeMap, GL_SAMPLER_CUBE);

  // -----------------------------------------------------------------------
  // 2LoC types

  TLOC_DECL_TL_TO_GL(gfx_t::Vert2fp,       GL_FLOAT_VEC2);
  TLOC_DECL_TL_TO_GL(gfx_t::Vert2fpn,      TLOC_GL_POSITION2F_NORMAL3F);
  TLOC_DECL_TL_TO_GL(gfx_t::Vert2fpt,      TLOC_GL_POSITION2F_TEXTURE2F);
  TLOC_DECL_TL_TO_GL(gfx_t::Vert2fpc,      TLOC_GL_POSITION2F_COLOR4F);
  TLOC_DECL_TL_TO_GL(gfx_t::Vert2fpnc,     TLOC_GL_POSITION2F_NORMAL3F_COLOR4F);
  TLOC_DECL_TL_TO_GL(gfx_t::Vert2fpnt,     TLOC_GL_POSITION2F_NORMAL3F_TEXTURE2F);
  TLOC_DECL_TL_TO_GL(gfx_t::Vert2fpnct,    TLOC_GL_POSITION2F_NORMAL3F_COLOR4F_TEXTURE2F);

  TLOC_DECL_TL_TO_GL(gfx_t::Vert3fp,       GL_FLOAT_VEC3);
  TLOC_DECL_TL_TO_GL(gfx_t::Vert3fpn,      TLOC_GL_POSITION3F_NORMAL3F);
  TLOC_DECL_TL_TO_GL(gfx_t::Vert3fpc,      TLOC_GL_POSITION3F_COLOR4F);
  TLOC_DECL_TL_TO_GL(gfx_t::Vert3fpt,      TLOC_GL_POSITION3F_TEXTURE2F);
  TLOC_DECL_TL_TO_GL(gfx_t::Vert3fpnc,     TLOC_GL_POSITION3F_NORMAL3F_COLOR4F);
  TLOC_DECL_TL_TO_GL(gfx_t::Vert3fpnt,     TLOC_GL_POSITION3F_NORMAL3F_TEXTURE2F);
  TLOC_DECL_TL_TO_GL(gfx_t::Vert3fptm,     TLOC_GL_POSITION3F_TEXTURE2F_TBN);
  TLOC_DECL_TL_TO_GL(gfx_t::Vert3fpnct,    TLOC_GL_POSITION3F_NORMAL3F_COLOR4F_TEXTURE2F);

  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert2fp>,       GL_FLOAT_VEC2);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert2fpn>,      TLOC_GL_POSITION2F_NORMAL3F);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert2fpt>,      TLOC_GL_POSITION2F_TEXTURE2F);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert2fpc>,      TLOC_GL_POSITION2F_COLOR4F);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert2fpnc>,     TLOC_GL_POSITION2F_NORMAL3F_COLOR4F);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert2fpnt>,     TLOC_GL_POSITION2F_NORMAL3F_TEXTURE2F);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert2fpnct>,    TLOC_GL_POSITION2F_NORMAL3F_COLOR4F_TEXTURE2F);

  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert3fp>,       GL_FLOAT_VEC3);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert3fpn>,      TLOC_GL_POSITION3F_NORMAL3F);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert3fpt>,      TLOC_GL_POSITION3F_TEXTURE2F);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert3fpc>,      TLOC_GL_POSITION3F_COLOR4F);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert3fpnc>,     TLOC_GL_POSITION3F_NORMAL3F_COLOR4F);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert3fpnt>,     TLOC_GL_POSITION3F_NORMAL3F_TEXTURE2F);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert3fptm>,     TLOC_GL_POSITION3F_TEXTURE2F_TBN);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert3fpnct>,    TLOC_GL_POSITION3F_NORMAL3F_COLOR4F_TEXTURE2F);

  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert2fpnto>,    TLOC_GL_POSITION2F_NORMAL3F_TEXTURE2F_ORIENTATION);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert3fpnto>,    TLOC_GL_POSITION3F_NORMAL3F_TEXTURE2F_ORIENTATION);

  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert3TBN>,      GL_FLOAT_MAT3);
  TLOC_DECL_TL_TO_GL(Array<gfx_t::Vert4fo>,       GL_FLOAT_MAT4);

#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL
  TLOC_DECL_TL_TO_GL(Tuple2u32, GL_UNSIGNED_INT_VEC2);
  TLOC_DECL_TL_TO_GL(Tuple3u32, GL_UNSIGNED_INT_VEC3);
  TLOC_DECL_TL_TO_GL(Tuple4u32, GL_UNSIGNED_INT_VEC4);

  TLOC_DECL_TL_TO_GL(Array<Tuple2u32>, GL_UNSIGNED_INT_VEC2);
  TLOC_DECL_TL_TO_GL(Array<Tuple3u32>, GL_UNSIGNED_INT_VEC3);
  TLOC_DECL_TL_TO_GL(Array<Tuple4u32>, GL_UNSIGNED_INT_VEC4);

  TLOC_DECL_TL_TO_GL(TextureObjectShadow, GL_SAMPLER_2D_SHADOW);
#elif defined (TLOC_OS_IPHONE)
  TLOC_DECL_TL_TO_GL(TextureObjectShadow, GL_SAMPLER_2D_SHADOW_EXT);
#endif

  // -----------------------------------------------------------------------

  namespace type_to_gl {
    template <typename T>
    gl_enum Get()
    { return tlToGl<T>::k_glType; };
  }

};};};
