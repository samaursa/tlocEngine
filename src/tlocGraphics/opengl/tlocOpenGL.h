#ifndef TLOC_OPENGL_H
#define TLOC_OPENGL_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>

// Taken from SFML (we will trust the paths they chose for diff. platforms

namespace tloc { namespace graphics {

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <3rdParty/Graphics/GLEW/glew.h>
//# include <GL/gl.h>
//# include <GL/glu.h>

#elif defined(TLOC_LINUX)

# include <GL/gl.h>
# include <GL/glu.h>

#elif defined(TLOC_OS_MAC)

# include <OpenGL/gl.h>
# include <OpenGl/glu.h>

#elif defined(TLOC_OS_IPHONE)

# include <OpenGLES/ES2/gl.h>

#endif

};};

#endif