#ifndef BLOCKFIELD_H
#define BLOCKFIELD_H

#include "rgbcolor.h"
#include "vector3.h"
class Mino;


class BlockField {
  public:
    BlockField();
    ~BlockField();
    void clearFloor(unsigned int firstFloorBlock);
    void clearFloors();
    bool collidesWithBlock(Vector3 a_minoVector);
    bool crossesBounds(Vector3 a_minoVector);
    void draw();
    void lowerUpperFloors(unsigned int firstUpperFloorsBlock);
    void setBlock(Mino* a_mino);
    static const unsigned int capacity = 1000;
    static const unsigned int capacityPerFloor = 100;
    static const unsigned int capacityPerFloorColumn = 10;
    static const unsigned int nFloors = 10;
  private:
  Mino* m_blocks[1000];
};

#endif
