#include "tlocShaderVariableInfo.h"

#include <tlocCore/data_structures/tlocProtectedBuffer.inl.h>

namespace tloc { namespace graphics { namespace gl {

  template class core::data_structs::
    ProtectedBuffer<char8, ShaderVariableInfo::g_buffSize>;

};};};