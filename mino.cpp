#ifdef __APPLE__
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include "mino.h"

Mino::Mino(Vector3 a_startPosition, RgbColor a_color)
  : m_color(a_color)
  , m_position(a_startPosition)
{}

void Mino::draw() {
  GLfloat rgbaColor[4] = {m_color.red, m_color.green, m_color.blue, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rgbaColor);
  glColor3f(m_color.red, m_color.green, m_color.blue);
  glPushMatrix();
  glTranslatef(m_position.x, m_position.y, m_position.z);
  glutSolidCube(1.0);
  glPopMatrix();
}

RgbColor Mino::getColor() {
  return m_color;
}

Vector3 Mino::getPosition() {
  return m_position;
}

void Mino::setPosition(Vector3 a_vector) {
  m_position = a_vector;
}
