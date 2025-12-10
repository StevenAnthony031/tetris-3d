#ifndef VECTOR3_H
#define VECTOR3_H

#ifdef __APPLE__
#else
#include <GL/glut.h>
#endif

struct Vector3 {
  GLfloat x;
  GLfloat y;
  GLfloat z;
};

#endif
