#pragma once

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/memory/tlocBufferArg.h>

#include <tlocGraphics/opengl/tlocAttribute.h>
#include <tlocGraphics/opengl/tlocUniform.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  class ShaderProgram;

  class ShaderOperator
  {
  public:
    typedef ShaderOperator          this_type;
    typedef core::error::Error      error_type;
    typedef tl_size                 size_type;
    typedef tl_int                  index_type;

    typedef Uniform                 uniform_type;
    typedef Attribute               attribute_type;
    typedef uniform_vptr            uniform_ptr_type;
    typedef const_uniform_vptr      const_uniform_ptr_type;
    typedef attribute_vptr          attribute_ptr_type;
    typedef const_attribute_vptr    const_attribute_ptr_type;
    typedef uniform_vso             uniform_vso;
    typedef attribute_vso           attribute_vso;
    typedef uniform_vptr            uniform_ptr;
    typedef attribute_vptr          attribute_ptr;

    // The index_type of the pair is used to get the pointer quickly the second
    // time around
    typedef core::Pair<uniform_vso, index_type>           uniform_pair_type;
    typedef core::Pair<attribute_vso, index_type>         attribute_pair_type;

    typedef core::containers::Array<uniform_pair_type>	  uniform_cont_type;
    typedef uniform_cont_type::iterator                   uniform_iterator;

    typedef core::containers::Array<attribute_pair_type>  attribute_cont_type;
    typedef attribute_cont_type::iterator                 attribute_iterator;

    typedef core_conts::tl_array<index_type>::type        index_cont_type;
    typedef index_cont_type::iterator                     index_iterator;

  public:
    ShaderOperator();
    ~ShaderOperator();

    uniform_ptr   AddUniform(const uniform_type& a_uniform);
    attribute_ptr AddAttribute(const attribute_type& a_attribute);

    void RemoveUniform(const uniform_iterator& a_uniform);
    void RemoveAttribute(const attribute_iterator& a_attribute);

    void RemoveAllUniforms();
    void RemoveAllAttributes();

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

    ///-------------------------------------------------------------------------
    /// @brief
    /// Enables all uniforms. Assumes the correct shader has been enabled.
    ///
    /// @param  a_shaderProgram The shader program.
    ///-------------------------------------------------------------------------
    void EnableAllUniforms(const ShaderProgram& a_shaderProgram) const;
    void EnableAllAttributes(const ShaderProgram& a_shaderProgram) const;

    uniform_iterator begin_uniforms();
    uniform_iterator end_uniforms();

    attribute_iterator begin_attributes();
    attribute_iterator end_attributes();

    // The following functions will destroy the uniform/attribute cache which
    // was setup when Prepare*() methods were called
    void ClearAttributesCache();
    void ClearUniformsCache();
    void ClearCache();
    bool IsAttributesCached();
    bool IsUniformsCached();

    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumberOfUniforms,
                             m_uniforms.size());
    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumberOfAttributes,
                             m_attributes.size());

  private:
    uniform_cont_type           m_uniforms;
    attribute_cont_type         m_attributes;
    core::utils::Checkpoints    m_flags;
    index_cont_type             m_enabledVertexAttrib;
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