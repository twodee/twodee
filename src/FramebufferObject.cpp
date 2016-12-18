#include <cassert>
#include <iostream>

#include "twodee/FramebufferObject.h"

namespace td {

/* ------------------------------------------------------------------------- */

FramebufferObject::FramebufferObject() {
  Initialize();
}

/* ------------------------------------------------------------------------- */

FramebufferObject::FramebufferObject(const Texture *texture) {
  Initialize();
  Bind();
  if (texture->GetChannels() == Texture::DEPTH) {
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, 0); 
    glDrawBuffer(GL_NONE);
    AddDepth(texture);
  } else {
    AddColor(texture);
    AddDepth();
  }
  Unbind();
}

/* ------------------------------------------------------------------------- */

FramebufferObject::~FramebufferObject() {
  if (depth_id > 0) {
    glDeleteRenderbuffers(1, &depth_id);
  }
  glDeleteFramebuffers(1, &framebuffer_id);
  Unbind();
}

/* ------------------------------------------------------------------------- */

void FramebufferObject::Initialize() {
  glGenFramebuffers(1, &framebuffer_id); 
  depth_id = 0;
  width = -1;
  height = -1;
}

/* ------------------------------------------------------------------------- */

void FramebufferObject::Bind() {
  glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer_id); 
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer_id); 
}

/* ------------------------------------------------------------------------- */

void FramebufferObject::Unbind() {
  glBindFramebuffer(GL_READ_FRAMEBUFFER, 0); 
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); 
}

/* ------------------------------------------------------------------------- */

void FramebufferObject::AddDepth() {
  assert(color_attachments.size() > 0);
  assert(depth_id == 0);
  glGenRenderbuffers(1, &depth_id);
  glBindRenderbuffer(GL_RENDERBUFFER, depth_id);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, color_attachments[0]->GetWidth(), color_attachments[0]->GetHeight());
  glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_id);
}

/* ------------------------------------------------------------------------- */

void FramebufferObject::AddColor(const Texture *texture) {
  if (width == -1 || height == -1) {
    width = texture->GetWidth();
    height = texture->GetHeight();
  } else {
    assert(texture->GetWidth() == width && texture->GetHeight() == height);
  }
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + color_attachments.size(), GL_TEXTURE_2D, texture->GetID(), 0);
  color_attachments.push_back(texture);
}

/* ------------------------------------------------------------------------- */

void FramebufferObject::AddDepth(const Texture *texture) {
  if (width == -1 || height == -1) {
    width = texture->GetWidth();
    height = texture->GetHeight();
  } else {
    assert(texture->GetWidth() == width && texture->GetHeight() == height);
  }
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->GetID(), 0);
}

/* ------------------------------------------------------------------------- */

int FramebufferObject::GetWidth() const {
  return width;
}

/* ------------------------------------------------------------------------- */

int FramebufferObject::GetHeight() const {
  return height; 
}

/* ------------------------------------------------------------------------- */

}
