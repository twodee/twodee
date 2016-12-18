#ifndef FRAMEBUFFEROBJECT_H
#define FRAMEBUFFEROBJECT_H

#include "twodee/Configuration.h"

#include "twodee/Texture.h"
#include "twodee/UtilitiesOpenGL.h"

namespace td {

/* ------------------------------------------------------------------------- */

class FramebufferObject {
  public:
    FramebufferObject();
    FramebufferObject(const Texture *texture);
    ~FramebufferObject();

    void Bind();
    void Unbind();

    // Assumes bound.
    void AddColor(const Texture *texture);
    void AddDepth(const Texture *texture);
    void AddDepth();

    int GetWidth() const;
    int GetHeight() const;

  private:
    void Initialize();

    // Framebuffer object ID.
    GLuint framebuffer_id;
    GLuint depth_id;
    std::vector<const Texture *> color_attachments;

    int width;
    int height;
};

/* ------------------------------------------------------------------------- */

}
#endif
