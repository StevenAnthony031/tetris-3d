#ifndef TETRIS_H
#define TETRIS_H

#ifdef __APPLE__
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include "blockfield.h"
#include "tetrominobag.h"
class Tetromino;


class Tetris {
  public:
    Tetris();
    ~Tetris();
    void draw();
    void onDownKeyPressed();
    void onLeftKeyPressed();
    void onRightKeyPressed();
    void onRotateFieldLeftKeyPressed();
    void onRotateFieldRightKeyPressed();
    void onSoftDropKeyPressed();
    void onUpKeyPressed();
    void onXRotateKeyPressed();
    void onYRotateKeyPressed();
    void onZRotateKeyPressed();
    void update();
  private:
    void onTetrominoLocked();
    int m_lastTick;
    int m_tickDuration;
    GLfloat m_fieldRotationAngle;
    BlockField m_blockField;
    Tetromino* m_fallingTetromino;
    TetrominoBag m_tetrominoBag;
};

#endif
