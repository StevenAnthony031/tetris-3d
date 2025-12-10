#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#ifdef __APPLE__
#else
#include <GL/glut.h>
#endif

struct RgbColor {
  GLfloat red;
  GLfloat green;
  GLfloat blue;
};

#endif
