#ifndef _TLOC_GRAPHICS_GL_VERTEX_ARRAY_OBJECT_H_
#define _TLOC_GRAPHICS_GL_VERTEX_ARRAY_OBJECT_H_

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  // ///////////////////////////////////////////////////////////////////////
  // VertexArrayObject

  class VertexArrayObject
    : public Object_T<VertexArrayObject, p_object::OnlyID>
  {
  public:
    typedef VertexArrayObject                               this_type;
    typedef Object_T<this_type, p_object::OnlyID>           base_type;

  public:
    struct Bind
      : public core_bclass::NonCopyable_I
    {
    public:
      typedef core_sptr::VirtualPtr<VertexArrayObject>      vao_ptr;

    public:
      Bind(const vao_ptr a_vao);
      ~Bind();
    };
    TLOC_TYPEDEF_UNIQUE_PTR(Bind, bind);

  public:
    VertexArrayObject();
    ~VertexArrayObject();
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(VertexArrayObject, vao);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(VertexArrayObject, vao);

};};};

#endif