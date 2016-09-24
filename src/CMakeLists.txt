set (
  TWODEE_SOURCES
  Camera.cpp
  FieldTraits.cpp
  Log.cpp
  MessagedException.cpp
  NFieldBase.cpp
  Scanner.cpp
  Trimesh.cpp
  Utilities.cpp
)

if (OPENGL_FOUND)
  list (
    APPEND
    TWODEE_SOURCES
    FramebufferObject.cpp
    ShaderProgram.cpp
    Texture.cpp
    Trackball.cpp
    UniformManager.cpp
    UtilitiesOpenGL.cpp
    VertexArray.cpp
    VertexAttributes.cpp
  )
endif()

add_library (
  twodee
  STATIC
  ${TWODEE_SOURCES}
)
