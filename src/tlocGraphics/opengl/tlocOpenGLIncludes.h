#ifndef _TLOC_GRAPHICS_GL_OPENGL_INCLUDES_H_
#define _TLOC_GRAPHICS_GL_OPENGL_INCLUDES_H_

// Taken from SFML (we will trust the paths they chose for diff. platforms
#if defined(TLOC_WIN32) || defined(TLOC_WIN64)

# define NOMINMAX
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <3rdParty/Graphics/GLEW/glew.h>
# include <GL/gl.h>
# include <GL/glu.h>

#elif defined(TLOC_LINUX)

# include <GL/gl.h>
# include <GL/glu.h>

#elif defined(TLOC_OS_MAC)

# include <OpenGL/gl.h>
# include <OpenGl/glu.h>

#elif defined(TLOC_OS_IPHONE)

# include <OpenGLES/ES2/gl.h>
# include <OpenGLES/ES2/glext.h>

#endif

#endif