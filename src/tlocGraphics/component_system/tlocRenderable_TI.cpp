#include "tlocRenderable_TI.h"

#include <tlocGraphics/renderer/tlocDrawCommand.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace {

    const char* g_uniformNames [] = 
    {
      "u_model",
      "u_modelInv",

      "u_mv",
      "u_mvInv",

      "u_mvp",
      "u_mvpInv",

      "u_scale",
      "u_scaleInv",

      "u_scaleVec",
      "u_scaleVecInv",

      "u_normal",
      "u_normalInv",
    };

    const char* g_attributeNames [] = 
    {
      "a_vertPos",
      "a_vertNorm",
      "a_vertCol",
      "a_vertTexCoord",
      "a_multiTexCoord",
    };

  };


  // ///////////////////////////////////////////////////////////////////////
  // Renderable_I

  Renderable_I::
    Renderable_I()
    : m_drawMode(gfx_rend::mode::k_points)
    , m_uniformsUpdated(true)
  {
    m_shaderOp->reserve_uniforms(p_renderable::uniforms::k_count);

    for (p_renderable::uniforms::value_type i = 0;
         i < p_renderable::uniforms::k_count; ++i)
    {
      auto uniformName = core_str::String(g_uniformNames[i]);
      auto uniformPtr = m_shaderOp->
        AddUniform(gl::Uniform().SetName(uniformName));

      m_uniformsAndNames.push_back(core::MakePair(uniformPtr, uniformName));
      SetEnableUniform(i, false);
    }

    SetEnableUniform<p_renderable::uniforms::k_modelMatrix>();

    for (tl_size i = 0; i < p_renderable::attributes::k_count; ++i)
    { m_attributeNames.push_back(core_str::String(g_attributeNames[i])); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Renderable_I::
    ~Renderable_I()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Renderable_I::
    SetDrawMode(draw_mode a_drawMode) -> this_type&
  {
    m_drawMode = a_drawMode;
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Renderable_I::
    GetUniformName(uniform_index_type a_index) const -> const string_type&
  { return m_uniformsAndNames[a_index].second; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Renderable_I::
    GetUniform(uniform_index_type a_index) const -> uniform_ptr
  { return m_uniformsAndNames[a_index].first; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Renderable_I::
    SetEnableUniform(uniform_index_type a_index, bool a_enable) -> this_type&
  {  
    m_uniformsAndNames[a_index].first->SetEnabled(a_enable); 
    m_uniformsUpdated = true;
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Renderable_I::
    IsUniformEnabled(uniform_index_type a_index)
  {  return m_uniformsAndNames[a_index].first->IsEnabled(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Renderable_I::
    GetAttributeName(attribute_index_type a_index) const -> const string_type&
  { return m_attributeNames[a_index]; }

};};};

using namespace tloc::gfx_cs;

#include <tlocCore/containers/tlocArrayFixed.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ARRAY_FIXED(Renderable_I::uniform_string_pair, p_renderable::uniforms::k_count);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY_FIXED(Renderable_I::string_type, p_renderable::attributes::k_count);