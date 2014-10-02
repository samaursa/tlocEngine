#pragma once

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/memory/tlocBufferArg.h>

#include <tlocGraphics/opengl/tlocAttribute.h>
#include <tlocGraphics/opengl/tlocUniform.h>
#include <tlocGraphics/opengl/tlocVertexBufferObject.h>
#include <tlocGraphics/opengl/tlocVertexArrayObject.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  class ShaderProgram;

  class ShaderOperator
  {
  public:
    typedef ShaderOperator            this_type;
    typedef core::error::Error        error_type;
    typedef tl_size                   size_type;
    typedef tl_int                    index_type;

    typedef Attribute                 attribute_type;
    typedef attribute_vso             attribute_vso;
    typedef attribute_vptr            attribute_ptr;
    typedef const_attribute_vptr      const_attribute_ptr;

    typedef Uniform                   uniform_type;
    typedef uniform_vso               uniform_vso;
    typedef uniform_vptr              uniform_ptr;
    typedef const_uniform_vptr        const_uniform_ptr;

    typedef AttributeVBO              vbo_type;
    typedef attributeVBO_vso          vbo_vso;
    typedef attributeVBO_vptr         vbo_ptr;
    typedef const_attributeVBO_vptr   const_vbo_ptr;

    typedef VertexArrayObject         vao_type;
    typedef vao_vso                   vao_vso;
    typedef vao_vptr                  vao_ptr;
    typedef const_vao_vptr            const_vao_ptr;

    typedef vao_type::Bind            vao_bind_type;
    typedef vao_type::bind_sptr       vao_bind_ptr;

    // The index_type of the pair is used to get the pointer quickly the second
    // time around
    typedef core::Pair<uniform_vso, index_type>           uniform_pair_type;
    typedef core::Pair<attribute_vso, index_type>         attribute_pair_type;
    typedef core::Pair<vbo_vso, index_type>               vbo_pair_type;

    typedef core_conts::Array<uniform_pair_type>	        uniform_cont_type;
    typedef uniform_cont_type::iterator                   uniform_iterator;

    typedef core_conts::Array<attribute_pair_type>        attribute_cont_type;
    typedef attribute_cont_type::iterator                 attribute_iterator;

    typedef core_conts::Array<vbo_pair_type>              vbo_cont_type;
    typedef vbo_cont_type::iterator                       vbo_iterator;

    typedef core_conts::tl_array<index_type>::type        index_cont_type;
    typedef index_cont_type::iterator                     index_iterator;

  public:
    ShaderOperator();
    ~ShaderOperator();

    uniform_ptr   AddUniform(const uniform_type& a_uniform);
    attribute_ptr AddAttribute(const attribute_type& a_attribute);
    vbo_ptr       AddVBO(const vbo_type& a_vbo);

    void RemoveUniform(const uniform_iterator& a_uniform);
    void RemoveAttribute(const attribute_iterator& a_attribute);
    void RemoveVBO(const vbo_iterator& a_vbo);

    void RemoveAllUniforms();
    void RemoveAllAttributes();
    void RemoveAllVBOs();

    ///-------------------------------------------------------------------------
    /// @brief
    /// Loads all uniforms and caches their locations. This should be
    /// called only once after adding attributes/uniforms.
    ///
    /// @param  a_shaderProgram The shader program.
    ///
    /// @return all uniforms.
    ///-------------------------------------------------------------------------
    error_type PrepareAllUniforms(const ShaderProgram& a_shaderProgram);
    error_type PrepareAllAttributes(const ShaderProgram& a_shaderProgram);
    error_type PrepareAllVBOs(const ShaderProgram& a_shaderProgram);

    ///-------------------------------------------------------------------------
    /// @brief
    /// Enables all uniforms. Assumes the correct shader has been enabled.
    ///
    /// @param  a_shaderProgram The shader program.
    ///-------------------------------------------------------------------------
    void EnableAllUniforms(const ShaderProgram& a_shaderProgram) const;
    void EnableAllAttributes(const ShaderProgram& a_shaderProgram) const;
    vao_bind_ptr EnableAllVBOs(const ShaderProgram& a_shaderProgram) const;

    uniform_iterator begin_uniforms();
    uniform_iterator end_uniforms();

    attribute_iterator begin_attributes();
    attribute_iterator end_attributes();

    vbo_iterator begin_VBOs();
    vbo_iterator end_VBOs();

    ///-------------------------------------------------------------------------
    /// @brief
    /// Allows the operator to preallocate space for a number of 
    /// uniforms/attributes. This is useful to ensure that the 
    /// uniform_vptr/attribute_vptr returned are valid until a 
    /// uniform/attribute is added (which may cause a reallocation) or any of
    /// the remove methods are called
    ///-------------------------------------------------------------------------
    void reserve_uniforms(size_type a_capacity);

    ///-------------------------------------------------------------------------
    /// @brief
    /// see reserve_uniforms()
    ///-------------------------------------------------------------------------
    void reserve_attributes(size_type a_capacity);

    ///-------------------------------------------------------------------------
    /// @brief
    /// see reserve_uniforms()
    ///-------------------------------------------------------------------------
    void reserve_vertexBufferObjects(size_type a_capacity);

    // The following functions will destroy the uniform/attribute cache which
    // was setup when Prepare*() methods were called
    void ClearAttributesCache();
    void ClearUniformsCache();
    void ClearVBOs();

    void ClearCache();

    bool IsAttributesCached();
    bool IsUniformsCached();
    bool IsVBOsCached();

    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumberOfUniforms,
                             m_uniforms.size());
    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumberOfAttributes,
                             m_attributes.size());
    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumberOfVBOs,
                             m_VBOs.size());

  private:
    uniform_cont_type           m_uniforms;
    attribute_cont_type         m_attributes;
    vbo_cont_type               m_VBOs;
    core::utils::Checkpoints    m_flags;
    index_cont_type             m_enabledVertexAttrib;
    vao_vso                     m_vao;
  };

  TLOC_TYPEDEF_ALL_SMART_PTRS(ShaderOperator, shader_operator);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(ShaderOperator, shader_operator);

  namespace algos { namespace shader_operator {

    namespace compare {

      struct UniformName
      {
        typedef ShaderOperator::uniform_pair_type       pair_type;
        typedef BufferArg                               value_type;

        UniformName(value_type a_uniformName)
          : m_name(a_uniformName)
        { }

        bool operator()(const pair_type& a_so) const
        {
          return a_so.first->GetName().compare(m_name) == 0;
        }

        value_type m_name;
      };

      struct AttributeName
      {
        typedef ShaderOperator::attribute_pair_type     pair_type;
        typedef BufferArg                               value_type;

        AttributeName(value_type a_attributeName)
          : m_name(a_attributeName)
        { }

        bool operator()(const pair_type& a_so) const
        {
          return a_so.first->GetName().compare(m_name) == 0;
        }

        value_type m_name;
      };

    };

  };};

};};};