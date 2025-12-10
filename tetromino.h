#ifndef TETROMINO_H
#define TETROMINO_H

#ifdef __APPLE__
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include "blockfield.h"
#include "vector3.h"
class Mino;


class Tetromino {
  public:
    Tetromino();
    virtual ~Tetromino() {}
    void draw();
    void moveBack();
    bool moveDown();
    void moveForward();
    void moveLeft();
    void moveRight();
    Vector3 multiplyVectorMatrix(Vector3 a_vector, const GLfloat a_matrix[]);
    void rotate(const GLfloat a_matrix[]);
    void rotateOnXAxis();
    void rotateOnYAxis();
    void rotateOnZAxis();
    void transferBlocks();
    static const unsigned int nBlocks = 4;
    static BlockField* blockField;
  protected:
    unsigned int m_nMinos;
    Mino* m_minos[4];
    Vector3 m_rotationPoint;
    Vector3 m_startPosition;
};

#endif
