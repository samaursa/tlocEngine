#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_PRIMITIVE_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_PRIMITIVE_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocGraphics/types/tlocVertex.h>
#include <tlocGraphics/opengl/tlocGLTypes.h>

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/types/tlocAny.h>

namespace tloc { namespace graphics { namespace component_system {

  class Primitive_I
  {
  public:
    typedef Primitive_I                                       this_type;

    typedef core_t::Any                                       any_cont;
    typedef tl_size                                           size_type;
    typedef gfx_t::gl_enum                                    gl_enum;

  public:
    Primitive_I();

    template <typename T_VertType>
    this_type&  AddVertex(const T_VertType& a_vertex)
    {
      typedef core_conts::Array<T_VertType>           cont_type;
      if (m_vertices.IsEmpty())
      { DoCreateArray<T_VertType>(); }
      else
      { DoAssertIsSameType<T_VertType>(); }

      auto& arr = m_vertices.Cast<cont_type>();
      arr.push_back(a_vertex);

      m_numVertices++;

      return *this;
    }

    template <typename T_VertType>
    T_VertType   GetVertex(size_type a_position) const
    {
      typedef core_conts::Array<T_VertType>           cont_type;
      DoAssertIsSameType<T_VertType>();
      TLOC_ASSERT(m_vertices.IsEmpty() == false, "Vertex array is empty");

      auto& arr = m_vertices.Cast<cont_type>();
      return arr[a_position];
    }

    template <typename T_VertType>
    this_type&  ModifyVertex(size_type a_position, const T_VertType& a_vertex)
    {
      typedef core_conts::Array<T_VertType>           cont_type;
      DoAssertIsSameType<T_VertType>();
      TLOC_ASSERT(m_vertices.IsEmpty() == false, "Vertex array is empty");

      auto& arr = m_vertices.Cast<cont_type>();
      arr[a_position] = a_vertex;
      return *this;
    }

    template <typename T_VertType>
    typename core_conts::Array<T_VertType>::iterator          
      begin()
    {
      typedef core_conts::Array<T_VertType>           cont_type;
      DoAssertIsSameType<T_VertType>();
      TLOC_ASSERT(m_vertices.IsEmpty() == false, "Vertex array is empty");

      auto& arr = m_vertices.Cast<cont_type>();
      return arr.begin();
    }

    template <typename T_VertType>
    typename core_conts::Array<T_VertType>::iterator          
      end()
    {
      typedef core_conts::Array<T_VertType>           cont_type;
      DoAssertIsSameType<T_VertType>();
      TLOC_ASSERT(m_vertices.IsEmpty() == false, "Vertex array is empty");

      auto& arr = m_vertices.Cast<cont_type>();
      return arr.end();
    }

    template <typename T_VertType>
    typename core_conts::Array<T_VertType>::const_iterator          
      begin() const
    {
      typedef core_conts::Array<T_VertType>           cont_type;
      DoAssertIsSameType<T_VertType>();
      TLOC_ASSERT(m_vertices.IsEmpty() == false, "Vertex array is empty");

      auto& arr = m_vertices.Cast<cont_type>();
      return arr.begin();
    }

    template <typename T_VertType>
    typename core_conts::Array<T_VertType>::const_iterator          
      end() const
    {
      typedef core_conts::Array<T_VertType>           cont_type;
      DoAssertIsSameType<T_VertType>();
      TLOC_ASSERT(m_vertices.IsEmpty() == false, "Vertex array is empty");

      auto& arr = m_vertices.Cast<cont_type>();
      return arr.end();
    }

    template <typename T_VertType>
    typename core_conts::Array<T_VertType>::size_type
      size() const
    {
      typedef core_conts::Array<T_VertType>           cont_type;
      DoAssertIsSameType<T_VertType>();

      if (empty())
      { return 0; }
      else
      {
        auto& arr = m_vertices.Cast<cont_type>();
        return arr.size();
      }
    }

    template <typename T_VertType>
    const core_conts::Array<T_VertType>&
      GetVertices() const
    {
      typedef core_conts::Array<T_VertType>           cont_type;
      DoAssertIsSameType<T_VertType>();
      TLOC_ASSERT(m_vertices.IsEmpty() == false, "Vertex array is empty");

      auto& arr = m_vertices.Cast<cont_type>();
      return arr;
    }

    bool          empty() const;
    void          clear();

    TLOC_DECL_AND_DEF_GETTER(gl_enum, GetVertexType, m_vertexType);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumVertices, m_numVertices);

  private:
    template <typename T_VertType>
    void          DoCreateArray()
    {
      typedef core_conts::Array<T_VertType>           cont_type;
      TLOC_ASSERT(m_vertices.IsEmpty(), "Vertex array is NOT empty");

      m_vertexType = gfx_t::type_to_gl::Get<T_VertType>();

      m_vertices = cont_type();
    }

    template <typename T_VertType>
    void          DoAssertIsSameType() const
    {
      typedef core_conts::Array<T_VertType>           cont_type;
      TLOC_ASSERT(m_vertices.IsSameType(cont_type()), 
                  "T_VertType is not the same as previously selected.");
    }

  private:
    any_cont      m_vertices;
    size_type     m_numVertices;
    gl_enum       m_vertexType;
  };

};};};

#endif