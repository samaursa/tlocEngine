#include "tlocShaderVariableInfo.h"

#include <tlocCore/data_structures/tlocProtectedBuffer.inl.h>

namespace tloc { namespace graphics { namespace gl {

  ShaderVariableInfo::
    ShaderVariableInfo()
    : m_nameLength(0)
    , m_arraySize(0)
    , m_location(-1)
    , m_type(0)
  { }

};};};

// ///////////////////////////////////////////////////////////////////////
// Explicit instantiations

using namespace tloc;
using namespace tloc::gfx_gl;

TLOC_EXPLICITLY_INSTANTIATE_PROTECTED_BUFFER(char8, ShaderVariableInfo::g_buffSize);