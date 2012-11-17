#pragma once

#ifdef __MINGW32__
#include <GL/glew.h>
#endif

#define GL3_PROTOTYPES
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU

#include <GL/glfw.h>
