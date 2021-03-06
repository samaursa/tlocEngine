#include "tlocMaterial.h"

#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace graphics { namespace component_system {

  namespace {

    const char* g_uniformNames [] = 
    {
      "u_vp",
      "u_vpInv",

      "u_view",
      "u_viewInv",

      "u_proj",
      "u_projInv",
    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // Material

  Material::
    Material()
    : base_type("Material")
  { 
    m_internalShaderOp->reserve_uniforms(p_material::uniforms::k_count);

    for (p_material::uniforms::value_type i = 0;
         i < p_material::uniforms::k_count; ++i)
    {
      auto uniformName = core_str::String(g_uniformNames[i]);
      auto uniformPtr = m_internalShaderOp->
        AddUniform(gl::Uniform().SetName(uniformName));

      m_internalUniforms.push_back(core::MakePair(uniformPtr, uniformName));
      SetEnableUniform(i, false);
    }

    SetEnableUniform<p_material::uniforms::k_viewProjectionMatrix>();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::
    Material(const Material& a_other)
    : base_type(a_other)
    , m_vertexProgram(a_other.m_vertexProgram)
    , m_fragmentProgram(a_other.m_fragmentProgram)
    , m_shaderProgram(a_other.m_shaderProgram)
    , m_shaderOp(a_other.m_shaderOp)
    , m_internalShaderOp(a_other.m_internalShaderOp)
  { 
    auto itr = m_internalShaderOp->begin_uniforms(),
         itrEnd = m_internalShaderOp->end_uniforms();
    for (tl_size i = 0; i < p_material::uniforms::k_count; ++i)
    {
      auto itrCopy = itr;
      core::advance(itrCopy, i);

      TLOC_ASSERT(itrCopy != itrEnd, "Iterator went out of bounds");
      TLOC_UNUSED(itrEnd);

      m_internalUniforms.push_back(core::MakePair(itrCopy->first.get(), g_uniformNames[i]));
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::this_type& 
    Material::
    operator =(this_type a_other)
  {
    swap(a_other);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Material::
    swap(this_type& a_other)
  {
    using core::swap;
    swap(m_vertexProgram, a_other.m_vertexProgram);
    swap(m_fragmentProgram, a_other.m_fragmentProgram);
    swap(m_shaderProgram, a_other.m_shaderProgram);
    swap(m_shaderOp, a_other.m_shaderOp);
    swap(m_internalUniforms, a_other.m_internalUniforms);
    swap(m_internalUniforms, a_other.m_internalUniforms);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::this_type&
    Material::
    AddUniform(const uniform_type& a_uniform)
  { m_shaderOp->AddUniform(a_uniform); return *this; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::this_type&
    Material::
    SetVertexSource(const file_contents& a_fsSource)
  {
    m_vertexProgram = a_fsSource;
    SetUpdateRequired(true);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::this_type&
    Material::
    SetFragmentSource(const file_contents& a_vsSource)
  {
    m_fragmentProgram = a_vsSource;
    SetUpdateRequired(true);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::this_type&
    Material::
    SetShaderProgram(const gl::ShaderProgram& a_sp)
  {
    *m_shaderProgram = a_sp;
    SetUpdateRequired(true);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const Material::string_type&
    Material::
    GetUniformName(uniform_index_type a_index) const
  { return m_internalUniforms[a_index].second; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::uniform_ptr
    Material::
    GetUniform(uniform_index_type a_index) const
  { return m_internalUniforms[a_index].first; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Material::this_type&
    Material::
    SetEnableUniform(uniform_index_type a_index, bool a_enable)
  {  
    m_internalUniforms[a_index].first->SetEnabled(a_enable); 
    SetUpdateRequired(true);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Material::
    IsUniformEnabled(uniform_index_type a_index)
  {  return m_internalUniforms[a_index].first->IsEnabled(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool 
    Material::
    operator ==(const Material& a_other) const
  {
    return GetUniqueGroupID() == a_other.GetUniqueGroupID();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool 
    Material::
    operator < (const Material& a_other) const
  {
    return GetUniqueGroupID() < a_other.GetUniqueGroupID();
  }

  // -----------------------------------------------------------------------
  
  namespace f_material { 

    core_err::Error
      CompileAndLinkShaderProgram(Material& a_mat)
    {
      gl::VertexShader          vShader;
      gl::FragmentShader        fShader;

      auto  result   = ErrorSuccess;
      auto  sp       = a_mat.GetShaderProg();
      const auto& vsSource = a_mat.GetVertexSource();
      const auto& fsSource = a_mat.GetFragmentSource();

      if (sp->IsLinked() == false)
      {
        // TODO: Log this instead
        const auto vertSourceSize = vsSource.size();
        const auto fragSourceSize = fsSource.size();

        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(vertSourceSize == 0)
          << "Vertex shader source is empty";
        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(fragSourceSize == 0)
          << "Fragment shader source is empty";

        result = vShader.Load(a_mat.GetVertexSource().c_str() );
        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(result != ErrorSuccess)
          << "Failed to load the shader: " << a_mat.GetVertexPath().GetPath();
        result = vShader.Compile();
        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(result != ErrorSuccess)
          << "Could not compile vertex shader: " 
          << a_mat.GetVertexPath().GetPath() << "\n"
          << vShader.GetError().c_str();

        result = fShader.Load(a_mat.GetFragmentSource().c_str());
        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(result != ErrorSuccess)
          << "Failed to load the shader: " << a_mat.GetVertexPath().GetPath();
        result = fShader.Compile();
        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(result != ErrorSuccess)
          << "Could not compile fragment shader: "
          << a_mat.GetFragmentPath().GetPath() << "\n"
          << fShader.GetError().c_str();

        result = sp->AttachShaders
          (gl::ShaderProgram::two_shader_components(&vShader, &fShader) );
        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(result != ErrorSuccess)
          << "Could not attach shader program(s)";

        result = sp->Link();

        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(result != ErrorSuccess)
          << "Could not link shader(s): " << a_mat.GetVertexPath().GetPath()
          << " and " << a_mat.GetFragmentPath().GetPath() << "\n"
          << sp->GetError().c_str();

        if (result == ErrorSuccess)
        {
          core_str::String vsFileName, fsFileName;
          a_mat.GetVertexPath().GetFileName(vsFileName);
          a_mat.GetFragmentPath().GetFileName(fsFileName);

          TLOC_LOG_GFX_INFO_NO_FILENAME() << "Shader ID#" << sp->GetHandle()
            << " compiled successfully with programs (" << vsFileName 
            << ") and (" << fsFileName << ")";
        }
      }

      if (result == ErrorSuccess)
      {

        sp->LoadUniformInfo();
        sp->LoadAttributeInfo();
        sp->Disable();

        //------------------------------------------------------------------------
        // Add user attributes and uniforms

        sp->Enable();

        auto so = a_mat.GetShaderOperator();
        auto err = ErrorSuccess;

        core_str::String vsFileName, fsFileName;
        a_mat.GetVertexPath().GetFileName(vsFileName);
        a_mat.GetFragmentPath().GetFileName(fsFileName);

        err = so->PrepareAllUniforms(*sp);
        TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(err != ErrorSuccess) 
          << "Shader ID#" << sp->GetHandle() << "  with programs (" 
          << a_mat.GetVertexPath().GetFileName() << ") and (" 
          << a_mat.GetFragmentPath().GetFileName() << ") "
          << "- unable to prepare all uniforms";

        sp->Disable();
      }

      return result;
    }
  };

};};};

//------------------------------------------------------------------------
// Explicit Instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/containers/tlocArrayFixed.inl.h>

using namespace tloc::gfx_cs;

// array
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Material::shader_op_ptr);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY_FIXED(Material::uniform_string_pair, p_material::uniforms::k_count);

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Material);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(Material);
