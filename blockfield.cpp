#ifdef __APPLE__
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include "blockfield.h"
#include "mino.h"

BlockField::BlockField()
{
  for (unsigned int i = 0; i < BlockField::capacity; i++)
  {
    m_blocks[i] = 0;
  }
}

BlockField::~BlockField()
{
  for (unsigned int i = 0; i < BlockField::capacity; i++)
  {
    if (m_blocks[i])
    {
      delete m_blocks[i];
    }
  }
}

void BlockField::clearFloor(unsigned int firstFloorBlock)
{
  unsigned int firstOverheadFloorBlock = firstFloorBlock + BlockField::capacityPerFloor;
  for (unsigned int i = firstFloorBlock; i < firstOverheadFloorBlock; i++)
  {
    delete m_blocks[i];
    m_blocks[i] = 0;
  }
}

void BlockField::clearFloors()
{
  for (unsigned int i = 0; i < BlockField::capacity; i += BlockField::nFloors)
  {
    bool noFilledFloor = false;
    for (unsigned int j = 0; j < BlockField::capacityPerFloor; j++)
    {
      unsigned int block = i + j;
      if (!m_blocks[block])
      {
        noFilledFloor = true;
      }
    }
    if (!noFilledFloor)
    {
      clearFloor(i);
      lowerUpperFloors(i);
      i -= BlockField::capacityPerFloor;
    }
  }
}

bool BlockField::collidesWithBlock(Vector3 a_minoVector)
{
  unsigned int row = -(a_minoVector.z);
  unsigned int column = a_minoVector.x;
  unsigned int floor = a_minoVector.y;
  unsigned int block = floor * BlockField::capacityPerFloor + row * BlockField::capacityPerFloorColumn + column;
  if (m_blocks[block])
  {
    return true;
  }
  return false;
}

bool BlockField::crossesBounds(Vector3 a_minoVector)
{
  bool crosses = false;
  if (a_minoVector.x < 0.0 || a_minoVector.x >= 10.0 || a_minoVector.y < 0.0 || a_minoVector.z > 0.0 || a_minoVector.z <= -10.0)
  {
    crosses = true;
  }
  return crosses;
}

void BlockField::draw()
{
  GLfloat fieldBottomColor[4] = {0.5, 0.5, 0.5, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, fieldBottomColor);
  glBegin(GL_QUADS);
  // front
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, -1.0, 0.0);
  glVertex3f(10.0, -1.0, 0.0);
  glVertex3f(10.0, 0.0, 0.0);
  // right
  glVertex3f(10.0, 0.0, 0.0);
  glVertex3f(10.0, -1.0, 0.0);
  glVertex3f(10.0, -1.0, -10.0);
  glVertex3f(10.0, 0.0, -10.0);
  // back
  glVertex3f(10.0, 0.0, -10.0);
  glVertex3f(10.0, -1.0, -10.0);
  glVertex3f(0.0, -1.0, -10.0);
  glVertex3f(0.0, 0.0, -10.0);
  // left
  glVertex3f(0.0, 0.0, -10.0);
  glVertex3f(0.0, -1.0, -10.0);
  glVertex3f(0.0, -1.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  // top
  glVertex3f(0.0, 0.0, -10.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(10.0, 0.0, 0.0);
  glVertex3f(10.0, 0.0, -10.0);
  glEnd();
  for (unsigned int i = 0; i < BlockField::capacity; i++)
  {
    if (m_blocks[i])
    {
      m_blocks[i]->draw();
    }
  }
}

void BlockField::lowerUpperFloors(unsigned int firstClearedFloorBlock)
{
  for (unsigned int block = firstClearedFloorBlock;
       block < BlockField::capacity - BlockField::capacityPerFloor;
       block++)
  {
    unsigned int overheadBlock = block + BlockField::capacityPerFloor;
    if (m_blocks[overheadBlock])
    {
      m_blocks[block] = m_blocks[overheadBlock];
      m_blocks[overheadBlock] = 0;
      Vector3 blockPosition = m_blocks[block]->getPosition();
      blockPosition.y--;
      m_blocks[block]->setPosition(blockPosition);
    }
    else
    {
      m_blocks[block] = 0;
    }
  }
}

void BlockField::setBlock(Mino *a_mino)
{
  Vector3 vector = a_mino->getPosition();
  unsigned int row = -(vector.z);
  unsigned int column = vector.x;
  unsigned int floor = vector.y;
  unsigned int block = floor * BlockField::capacityPerFloor + row * BlockField::capacityPerFloorColumn + column;
  m_blocks[block] = a_mino;
}
