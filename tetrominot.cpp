#include "tetrominot.h"
#include "mino.h"
#include "rgbcolor.h"


TetrominoT::TetrominoT() {
  m_rotationPoint.x = m_startPosition.x + 1.0;
  m_rotationPoint.y = m_startPosition.y;
  m_rotationPoint.z = m_startPosition.z;
  RgbColor color;
  color.red = 1.0;
  color.green = 0.0;
  color.blue = 1.0;
  Vector3 startPosition = m_startPosition;
  m_minos[0] = new Mino(startPosition, color);
  startPosition.x++;
  m_minos[1] = new Mino(startPosition, color);
  startPosition.y++;
  m_minos[2] = new Mino(startPosition, color);
  startPosition.y--;
  startPosition.x++;
  m_minos[3] = new Mino(startPosition, color);
}

TetrominoT::~TetrominoT() {
  delete m_minos[3];
  delete m_minos[2];
  delete m_minos[1];
  delete m_minos[0];
}
