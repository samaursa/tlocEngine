#include "tlocShaderVariableInfo.h"

#include <tlocCore/containers/tlocProtectedBuffer.inl>

namespace tloc { namespace graphics { namespace gl {

  template class core::ProtectedBuffer<char8, ShaderVariableInfo::g_buffSize>;

};};};