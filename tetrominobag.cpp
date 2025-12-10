#include "tetrominobag.h"
#include <time.h>
#include "tetrominoi.h"
#include "tetrominoj.h"
#include "tetrominoo.h"
#include "tetrominos.h"
#include "tetrominot.h"
enum TetrominoId {
  TETROMINOID_I = 0,
  TETROMINOID_O = 1,
  TETROMINOID_T = 2,
  TETROMINOID_S = 3,
  TETROMINOID_Z = 4,
  TETROMINOID_J = 5,
  TETROMINOID_L = 6
};


TetrominoBag::TetrominoBag()
  : m_currentTetromino(TetrominoBag::capacity - 1)
{}

Tetromino* TetrominoBag::getNext() {
  if (m_currentTetromino == TetrominoBag::capacity - 1) {
    for (unsigned int i = 0; i < TetrominoBag::capacity; i++) {
      m_tetrominoSequence[i] = i;
    }
    shuffle();
    m_currentTetromino = 0;
  }
  else {
    m_currentTetromino++;
  }
  Tetromino* tetromino;
  switch (m_tetrominoSequence[m_currentTetromino]) {
    case TETROMINOID_I:
      tetromino = new TetrominoI();
      break;
    case TETROMINOID_O:
      tetromino = new TetrominoO();
      break;
    case TETROMINOID_T:
      tetromino = new TetrominoT();
      break;
    case TETROMINOID_S:
      tetromino = new TetrominoS();
      break;
    case TETROMINOID_Z:
      tetromino = new TetrominoS();
      break;
    case TETROMINOID_J:
      tetromino = new TetrominoJ();
      break;
    case TETROMINOID_L:
      tetromino = new TetrominoJ();
      break;
  }
  return tetromino;
}

void TetrominoBag::shuffle() {
  srand(time(0));
  // modern Fisher-Yates shuffle algorithm introduced by Richard Durstenfeld
  for (unsigned int i = TetrominoBag::capacity - 1; i != 0; i--) {
    int j = rand() % i;
    unsigned int temp = m_tetrominoSequence[i];
    m_tetrominoSequence[i] = m_tetrominoSequence[j];
    m_tetrominoSequence[j] = temp;
  }
}
