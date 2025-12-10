#include "tetris.h"
#include "tetromino.h"
const int TICK_DURATION = 1000;
const GLfloat FIELD_ROTATION_STEP = 2.0;
extern int g_windowId;
BlockField* Tetromino::blockField;

Tetris::Tetris()
  : m_lastTick(0)
  , m_tickDuration(TICK_DURATION)
  , m_fieldRotationAngle(0.0)
  , m_fallingTetromino(0) {
  Tetromino::blockField = &m_blockField;
  m_fallingTetromino = m_tetrominoBag.getNext();
}

Tetris::~Tetris() {
  delete m_fallingTetromino;
}

void Tetris::draw() {
  if (m_fieldRotationAngle != 0.0) {
    glTranslatef(5.0, 0.0, -5.0);
    glRotatef(m_fieldRotationAngle, 0.0, 1.0, 0.0);
    glTranslatef(-5.0, 0.0, 5.0);
  }
  m_fallingTetromino->draw();
  m_blockField.draw();
}

void Tetris::onDownKeyPressed() {
  m_fallingTetromino->moveBack();
}

void Tetris::onLeftKeyPressed() {
  m_fallingTetromino->moveLeft();
}

void Tetris::onRightKeyPressed() {
  m_fallingTetromino->moveRight();
}

void Tetris::onRotateFieldLeftKeyPressed() {
  m_fieldRotationAngle -= FIELD_ROTATION_STEP;
}

void Tetris::onRotateFieldRightKeyPressed() {
  m_fieldRotationAngle += FIELD_ROTATION_STEP;
}

void Tetris::onSoftDropKeyPressed() {
  bool locked = m_fallingTetromino->moveDown();
  if (locked) {
    onTetrominoLocked();
  }
  m_lastTick = glutGet(GLUT_ELAPSED_TIME);
}

void Tetris::onTetrominoLocked() {
  m_fallingTetromino->transferBlocks();
  delete m_fallingTetromino;
  m_blockField.clearFloors();
  Vector3 unobstructablePosition = {4.5, 10.5, -5.5};
  bool positionObstructed = m_blockField.collidesWithBlock(unobstructablePosition);
  if (positionObstructed) {
    glutDestroyWindow(g_windowId);
    g_windowId = 0;
    exit(0);
  }
  m_fallingTetromino = m_tetrominoBag.getNext();
}

void Tetris::onUpKeyPressed() {
  m_fallingTetromino->moveForward();
}

void Tetris::onXRotateKeyPressed() {
  m_fallingTetromino->rotateOnXAxis();
}

void Tetris::onYRotateKeyPressed() {
  m_fallingTetromino->rotateOnYAxis();
}

void Tetris::onZRotateKeyPressed() {
  m_fallingTetromino->rotateOnZAxis();
}

void Tetris::update() {
  int elapsedMs = glutGet(GLUT_ELAPSED_TIME);
  int nMsSinceLastTick = elapsedMs - m_lastTick;
  if (nMsSinceLastTick >= m_tickDuration) {
    bool locked = m_fallingTetromino->moveDown();
    if (locked) {
      onTetrominoLocked();
    }
    m_lastTick = elapsedMs;
  }
}
