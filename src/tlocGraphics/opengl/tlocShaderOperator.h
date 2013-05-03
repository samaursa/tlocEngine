#pragma once

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/error/tlocError.h>

#include <tlocGraphics/opengl/tlocAttribute.h>
#include <tlocGraphics/opengl/tlocUniform.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  class ShaderProgram;

  class ShaderOperator
  {
  public:
    typedef ShaderOperator          this_type;
    typedef uniform_sptr            uniform_ptr_type;
    typedef attribute_sptr          attribute_ptr_type;
    typedef core::error::Error      error_type;
    typedef tl_size                 size_type;
    typedef tl_int                  index_type;

    // The index_type of the pair is used to get the pointer quickly the second
    // time around
    typedef core::Pair<uniform_ptr_type, index_type>   uniform_pair_type;
    typedef core::Pair<attribute_ptr_type, index_type> attribute_pair_type;

    typedef core::containers::Array<uniform_pair_type>	 uniform_cont_type;
    typedef uniform_cont_type::iterator                  uniform_iterator;

    typedef core::containers::Array<attribute_pair_type> attribute_cont_type;
    typedef attribute_cont_type::iterator                attribute_iterator;

  public:
    ShaderOperator();

    void AddUniform(const uniform_ptr_type& a_uniform);
    void AddAttribute(const attribute_ptr_type& a_attribute);

    void RemoveUniform(const uniform_ptr_type& a_uniform);
    void RemoveAttribute(const attribute_ptr_type& a_attribute);

    void RemoveAllUniforms();
    void RemoveAllAttributes();

    uniform_iterator begin_uniform();
    uniform_iterator end_uniform();

    attribute_iterator begin_attribute();
    attribute_iterator end_attribute();

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
    void EnableAllUniforms(const ShaderProgram& a_shaderProgram);
    void EnableAllAttributes(const ShaderProgram& a_shaderProgram);

    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumberOfUniforms,
                             m_uniforms.size());
    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumberOfAttributes,
                             m_attributes.size());

  private:
    uniform_cont_type           m_uniforms;
    attribute_cont_type         m_attributes;
    core::utils::Checkpoints    m_flags;

  };

  TLOC_TYPEDEF_SHARED_PTR(ShaderOperator, shader_operator);

};};};