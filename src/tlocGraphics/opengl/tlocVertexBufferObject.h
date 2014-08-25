#ifndef _TLOC_GRAPHICS_GL_VERTEX_BUFFER_OBJECT_H_
#define _TLOC_GRAPHICS_GL_VERTEX_BUFFER_OBJECT_H_

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  // ///////////////////////////////////////////////////////////////////////
  // VBO options

  namespace p_vbo
  {
    namespace target {

    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // VertexBufferObject

  class VertexBufferObject
    : public Object_T<VertexBufferObject, p_object::OnlyID>
  {
  public:
    typedef VertexBufferObject                              this_type;
    typedef Object_T<this_type, p_object::OnlyID>           base_type;

  public:
    struct Bind
      : public core_bclass::NonCopyable_I
    {
    public:
      typedef core_sptr::VirtualPtr<VertexBufferObject>     vbo_ptr;

    public:
      Bind(const vbo_ptr  a_vbo);
      ~Bind();

    private:
      void DoBind() const;
    };
    TLOC_TYPEDEF_UNIQUE_PTR(Bind, bind);

  public:
    VertexBufferObject();
    ~VertexBufferObject();
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(VertexBufferObject, vbo);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(VertexBufferObject, vbo);

};};};

#endif