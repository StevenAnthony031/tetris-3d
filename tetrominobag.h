#ifndef TETROMINOBAG_H
#define TETROMINOBAG_H

class Tetromino;

class TetrominoBag {
  public:
    TetrominoBag();
    Tetromino* getNext();
    static const unsigned int capacity = 7;
  private:
    void shuffle();
    unsigned int m_currentTetromino;
    unsigned int m_tetrominoSequence[7];
};

#endif
