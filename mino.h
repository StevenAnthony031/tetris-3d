#ifndef MINO_H
#define MINO_H

#include "rgbcolor.h"
#include "vector3.h"


class Mino {
  public:
    Mino(Vector3 a_startPosition, RgbColor a_color);
    void draw();
    RgbColor getColor();
    Vector3 getPosition();
    void setPosition(Vector3 a_vector);
  private:
    RgbColor m_color;
    Vector3 m_position;
};

#endif
