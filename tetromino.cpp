#include "tetromino.h"
#include "blockfield.h"
#include "mino.h"
const GLfloat X90_ROTATION_MATRIX[16] = {
  1.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 1.0, 0.0,
  0.0, -1.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 1.0
};
const GLfloat Y90_ROTATION_MATRIX[16] = {
  0.0, 0.0, -1.0, 0.0,
  0.0, 1.0, 0.0, 0.0,
  1.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 1.0
};
const GLfloat Z90_ROTATION_MATRIX[16] = {
  0.0, 1.0, 0.0, 0.0,
  -1.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 1.0, 0.0,
  0.0, 0.0, 0.0, 1.0
};


Tetromino::Tetromino() {
  m_startPosition.x = 3.5;
  m_startPosition.y = 10.5;
  m_startPosition.z = -5.5;
}

void Tetromino::draw() {
  for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
    m_minos[i]->draw();
  }
}

void Tetromino::moveBack() {
  Vector3 minoVectors[Tetromino::nBlocks];
  bool collided = false;
  for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
    minoVectors[i] = m_minos[i]->getPosition();
    minoVectors[i].z += 1.0;
    if (Tetromino::blockField->collidesWithBlock(minoVectors[i])
        || Tetromino::blockField->crossesBounds(minoVectors[i])) {
      collided = true;
    }
  }
  if (!collided) {
    m_rotationPoint.z += 1.0;
    for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
      m_minos[i]->setPosition(minoVectors[i]);
    }
  }
}

bool Tetromino::moveDown() {
  Vector3 minoVectors[Tetromino::nBlocks];
  bool collided = false;
  for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
    minoVectors[i] = m_minos[i]->getPosition();
    minoVectors[i].y -= 1.0;
    if (Tetromino::blockField->collidesWithBlock(minoVectors[i])
        || Tetromino::blockField->crossesBounds(minoVectors[i])) {
      collided = true;
    }
  }
  if (!collided) {
    m_rotationPoint.y -= 1.0;
    for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
      m_minos[i]->setPosition(minoVectors[i]);
    }
  }
  return collided;
}

void Tetromino::moveForward() {
  Vector3 minoVectors[Tetromino::nBlocks];
  bool collided = false;
  for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
    minoVectors[i] = m_minos[i]->getPosition();
    minoVectors[i].z -= 1.0;
    if (Tetromino::blockField->collidesWithBlock(minoVectors[i])
        || Tetromino::blockField->crossesBounds(minoVectors[i])) {
      collided = true;
    }
  }
  if (!collided) {
    m_rotationPoint.z -= 1.0;
    for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
      m_minos[i]->setPosition(minoVectors[i]);
    }
  }
}

void Tetromino::moveLeft() {
  Vector3 minoVectors[Tetromino::nBlocks];
  bool collided = false;
  for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
    minoVectors[i] = m_minos[i]->getPosition();
    minoVectors[i].x -= 1.0;
    if (Tetromino::blockField->collidesWithBlock(minoVectors[i])
        || Tetromino::blockField->crossesBounds(minoVectors[i])) {
      collided = true;
    }
  }
  if (!collided) {
    m_rotationPoint.x -= 1.0;
    for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
      m_minos[i]->setPosition(minoVectors[i]);
    }
  }
}

void Tetromino::moveRight() {
  Vector3 minoVectors[Tetromino::nBlocks];
  bool collided = false;
  for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
    minoVectors[i] = m_minos[i]->getPosition();
    minoVectors[i].x += 1.0;
    if (Tetromino::blockField->collidesWithBlock(minoVectors[i])
        || Tetromino::blockField->crossesBounds(minoVectors[i])) {
      collided = true;
    }
  }
  if (!collided) {
    m_rotationPoint.x += 1.0;
    for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
      m_minos[i]->setPosition(minoVectors[i]);
    }
  }
}

Vector3 Tetromino::multiplyVectorMatrix(Vector3 a_vector, const GLfloat a_matrix[]) {
  GLfloat vectorMatrix[4];
  vectorMatrix[0] = a_vector.x;
  vectorMatrix[1] = a_vector.y;
  vectorMatrix[2] = a_vector.z;
  vectorMatrix[3] = 1.0;
  GLfloat newVectorMatrix[4];
  newVectorMatrix[0] = vectorMatrix[0] * a_matrix[0]
                       + vectorMatrix[1] * a_matrix[4]
                       + vectorMatrix[2] * a_matrix[8]
                       + vectorMatrix[3] * a_matrix[12];
  newVectorMatrix[1] = vectorMatrix[0] * a_matrix[1]
                       + vectorMatrix[1] * a_matrix[5]
                       + vectorMatrix[2] * a_matrix[9]
                       + vectorMatrix[3] * a_matrix[13];
  newVectorMatrix[2] = vectorMatrix[0] * a_matrix[2]
                       + vectorMatrix[1] * a_matrix[6]
                       + vectorMatrix[2] * a_matrix[10]
                       + vectorMatrix[3] * a_matrix[14];
  newVectorMatrix[3] = vectorMatrix[0] * a_matrix[3]
                       + vectorMatrix[1] * a_matrix[7]
                       + vectorMatrix[2] * a_matrix[11]
                       + vectorMatrix[3] * a_matrix[15];
  Vector3 newVector;
  newVector.x = newVectorMatrix[0];
  newVector.y = newVectorMatrix[1];
  newVector.z = newVectorMatrix[2];
  return newVector;
}

void Tetromino::rotate(const GLfloat a_matrix[]) {
  Vector3 minoVectors[Tetromino::nBlocks];
  bool collided = false;
  for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
    minoVectors[i] = m_minos[i]->getPosition();
    minoVectors[i].x -= m_rotationPoint.x;
    minoVectors[i].y -= m_rotationPoint.y;
    minoVectors[i].z -= m_rotationPoint.z;
    minoVectors[i] = multiplyVectorMatrix(minoVectors[i], a_matrix);
    minoVectors[i].x += m_rotationPoint.x;
    minoVectors[i].y += m_rotationPoint.y;
    minoVectors[i].z += m_rotationPoint.z;
    if (Tetromino::blockField->collidesWithBlock(minoVectors[i])
        || Tetromino::blockField->crossesBounds(minoVectors[i])) {
      collided = true;
    }
  }
  if (!collided) {
    for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
      m_minos[i]->setPosition(minoVectors[i]);
    }
  }
}

void Tetromino::rotateOnXAxis() {
  rotate(X90_ROTATION_MATRIX);
}

void Tetromino::rotateOnYAxis() {
  rotate(Y90_ROTATION_MATRIX);
}

void Tetromino::rotateOnZAxis() {
  rotate(Z90_ROTATION_MATRIX);
}

void Tetromino::transferBlocks() {
  for (unsigned int i = 0; i < Tetromino::nBlocks; i++) {
    Tetromino::blockField->setBlock(m_minos[i]);
    m_minos[i] = 0;
  }
}
