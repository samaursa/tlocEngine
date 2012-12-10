#pragma once

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/smart_ptr/tlocSmartPtr.h>
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
    typedef UniformPtr              uniform_ptr_type;
    typedef AttributePtr            attribute_ptr_type;
    typedef core::error::Error      error_type;
    typedef tl_size                 size_type;

    typedef core::Array<uniform_ptr_type>	   uniform_cont_type;
    typedef uniform_cont_type::iterator      uniform_iterator;

    typedef core::Array<attribute_ptr_type>  attribute_cont_type;
    typedef attribute_cont_type::iterator    attribute_iterator;

  public:
    ShaderOperator();

    void AddUniform(const uniform_ptr_type& a_uniform);
    void AddAttribute(const attribute_ptr_type& a_attribute);

    uniform_iterator begin_uniform();
    uniform_iterator end_uniform();

    attribute_iterator begin_attribute();
    attribute_iterator end_attribute();

    error_type LoadAllUniforms(const ShaderProgram& a_shaderProgram);
    error_type LoadAllAttributes(const ShaderProgram& a_shaderProgram);

  private:
    uniform_cont_type           m_uniforms;
    attribute_cont_type         m_attributes;
    core::utils::Checkpoints    m_flags;

  };

  typedef tloc::core::smart_ptr::
          SharedPtr<ShaderOperator>  ShaderOperatorPtr;

};};};