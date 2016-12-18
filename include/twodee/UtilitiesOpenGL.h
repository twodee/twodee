#ifndef UTILITIESOPENGL_H
#define UTILITIESOPENGL_H

#define GL_GLEXT_PROTOTYPES

#ifdef __APPLE__
#include "OpenGL/gl3.h"
#else
#include <GL/gl.h>
#endif

#include <string>
#include <vector>

namespace td {

/* ------------------------------------------------------------------------- */

/**
 A container for several OpenGL utility methods.
 */
class OpenGL {
  public:

    template<typename T>
    class Types {
      public:
        static const GLenum type;
    };

    template<int ndims>
    class Channels {
      public:
        static const GLenum mode;
    };

    /**
     Compiles the GLSL code in the specified file and returns the OpenGL shader
     object ID.
     @param shader_type The type of shader, GL_VERTEX_SHADER,
     GL_FRAGMENT_SHADER, or GL_GEOMETRY_SHADER
     @param path The name of the shader file
     @return Shader object ID
     */
    static GLuint CompileGLSLFile(GLenum shader_type,
                                  const char *path);

    /**
     Compiles the specified GLSL code and returns the OpenGL shader object ID.
     @param shader_type The type of shader, GL_VERTEX_SHADER,
     GL_FRAGMENT_SHADER, or GL_GEOMETRY_SHADER
     @param src The shader code
     @return Shader object ID
     */
    static GLuint CompileGLSL(GLenum shader_type,
                              const char *src);

    /**
     Links the vertex, fragment, and geometry shaders together in the specified
     shader program.
     @param pid Shader program ID
     @param vertex_sid Vertex shader object ID
     @param fragment_sid Fragment shader object ID
     @param geo_sid Geometry shader object ID
     */
    static void LinkGLSL(GLuint pid,
                         GLuint vertex_sid,
                         GLuint fragment_sid,
                         GLuint geo_sid = 0);

    /**
     Checks for an OpenGL error. If one has been raised, prints the specified
     label.
     @param label Text to print if error has been raised
     */
    static void CheckError(const std::string& label);

#ifndef ANDROID
    static void SetupGLEW();
    static bool is_glew_initialized;
#endif
};


/* ------------------------------------------------------------------------- */

}

#endif
