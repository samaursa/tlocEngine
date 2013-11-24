#include "tlocShaderVariableInfo.h"

#include <tlocCore/data_structures/tlocProtectedBuffer.inl.h>

// ///////////////////////////////////////////////////////////////////////
// Explicit instantiations

using namespace tloc;
using namespace tloc::gfx_gl;

TLOC_EXPLICITLY_INSTANTIATE_PROTECTED_BUFFER(char8, ShaderVariableInfo::g_buffSize);