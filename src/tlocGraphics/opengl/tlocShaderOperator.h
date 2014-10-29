#pragma once

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/memory/tlocBufferArg.h>

#include <tlocGraphics/opengl/tlocAttributeVBO.h>
#include <tlocGraphics/opengl/tlocUniform.h>
#include <tlocGraphics/opengl/tlocVertexArrayObject.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  class ShaderProgram;

  class ShaderOperator
  {
  public:
    typedef ShaderOperator                          this_type;
    typedef core::error::Error                      error_type;
    typedef tl_size                                 size_type;
    typedef tl_int                                  index_type;
    typedef core_conts::ArrayFixed<index_type, 1>   index_cont_1;
    typedef core_conts::Array<index_type>           index_cont;

    typedef Uniform                   uniform_type;
    typedef uniform_vso               uniform_vso;
    typedef uniform_vptr              uniform_ptr;
    typedef const_uniform_vptr        const_uniform_ptr;

    typedef AttributeVBO              vbo_type;
    typedef attributeVBO_vso          vbo_vso;
    typedef attributeVBO_vptr         attributeVBO_ptr;
    typedef const_attributeVBO_vptr   const_vbo_ptr;

    typedef VertexArrayObject         vao_type;
    typedef vao_vso                   vao_vso;
    typedef const_vao_vptr            const_vao_ptr;

    typedef vao_type::Bind            vao_bind_type;
    typedef vao_type::bind_sptr       vao_bind_ptr;

    // The index_type of the pair is used to get the pointer quickly the second
    // time around
    typedef core::Pair<uniform_vso, index_cont_1>         uniform_pair_type;
    typedef core::Pair<vbo_vso, index_cont>               vbo_pair_type;

    typedef core_conts::Array<uniform_pair_type>	        uniform_cont_type;
    typedef uniform_cont_type::iterator                   uniform_iterator;

    typedef core_conts::Array<vbo_pair_type>              attributeVBO_cont_type;
    typedef attributeVBO_cont_type::iterator              attributeVBO_iterator;

    typedef core_conts::tl_array<index_type>::type        index_cont_type;
    typedef index_cont_type::iterator                     index_iterator;

  public:
    ShaderOperator();
    ~ShaderOperator();

    uniform_ptr   AddUniform(const uniform_type& a_uniform);
    attributeVBO_ptr       AddAttributeVBO(const vbo_type& a_vbo);

    void RemoveUniform(const uniform_iterator& a_uniform);
    void RemoveAttributeVBO(const attributeVBO_iterator& a_vbo);

    void RemoveAllUniforms();
    void RemoveAllAttributeVBOs();

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
    error_type PrepareAllAttributeVBOs(const ShaderProgram& a_shaderProgram);

    ///-------------------------------------------------------------------------
    /// @brief
    /// Enables all uniforms. Assumes the correct shader has been enabled.
    ///
    /// @param  a_shaderProgram The shader program.
    ///-------------------------------------------------------------------------
    void EnableAllUniforms(const ShaderProgram& a_shaderProgram) const;

    uniform_iterator begin_uniforms();
    uniform_iterator end_uniforms();

    attributeVBO_iterator begin_attributeVBOs();
    attributeVBO_iterator end_attributeVBOs();

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
    void reserve_attributeVBOs(size_type a_capacity);

    // The following functions will destroy the uniform/attribute cache which
    // was setup when Prepare*() methods were called
    void ClearUniformsCache();
    void ClearAttributeVBOsCache();

    void ClearCache();

    bool IsUniformsCached();
    bool IsAttributeVBOsCached();

    TLOC_DECL_AND_DEF_GETTER(size_type, size_uniforms, m_uniforms.size());
    TLOC_DECL_AND_DEF_GETTER(size_type, size_attributeVBOs, m_VBOs.size());
    TLOC_DECL_AND_DEF_GETTER(const_vao_vptr, GetVAO, core_sptr::ToVirtualPtr(m_vao));

  private:
    uniform_cont_type           m_uniforms;
    attributeVBO_cont_type      m_VBOs;
    core::utils::Checkpoints    m_flags;
    vao_sptr                    m_vao;
  };

  TLOC_TYPEDEF_ALL_SMART_PTRS(ShaderOperator, shader_operator);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(ShaderOperator, shader_operator);

  // -----------------------------------------------------------------------

  namespace f_shader_operator {

    typedef ShaderOperator::uniform_ptr           uniform_ptr;
    typedef ShaderOperator::attributeVBO_ptr      attributeVBO_ptr;

    uniform_ptr
      GetUniform(ShaderOperator& a_so, BufferArg a_name);

    attributeVBO_ptr
      GetAttributeVBO(ShaderOperator& a_so, BufferArg a_name);

  };

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(ShaderOperator);
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(ShaderOperator);
  TLOC_EXTERN_TEMPLATE_ARRAY(ShaderOperator::uniform_pair_type);
  TLOC_EXTERN_TEMPLATE_ARRAY(vbo_vso);

  // -----------------------------------------------------------------------

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

      struct AttributeVBOName
      {
        typedef ShaderOperator::vbo_pair_type           pair_type;
        typedef BufferArg                               value_type;

        AttributeVBOName(value_type a_attributeName)
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