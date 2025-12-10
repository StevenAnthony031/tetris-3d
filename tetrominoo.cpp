#include "tetrominoo.h"
#include "mino.h"
#include "rgbcolor.h"


TetrominoO::TetrominoO() {
  m_rotationPoint.x = m_startPosition.x + 1.5;
  m_rotationPoint.y = m_startPosition.y + 0.5;
  m_rotationPoint.z = m_startPosition.z + 0.5;
  RgbColor color;
  color.red = 1.0;
  color.green = 1.0;
  color.blue = 0.0;
  Vector3 startPosition = m_startPosition;
  startPosition.x++;
  m_minos[0] = new Mino(startPosition, color);
  startPosition.y++;
  m_minos[1] = new Mino(startPosition, color);
  startPosition.x++;
  m_minos[2] = new Mino(startPosition, color);
  startPosition.y--;
  m_minos[3] = new Mino(startPosition, color);
}

TetrominoO::~TetrominoO() {
  delete m_minos[3];
  delete m_minos[2];
  delete m_minos[1];
  delete m_minos[0];
}
