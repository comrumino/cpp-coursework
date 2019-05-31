#pragma once
#include "Dictionary.h"
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::string> strvector;

class Board {
  public:
    Board(const unsigned int numRows, const unsigned int numCols, const Dictionary &dict,
          const strvector &debug = strvector());

    const unsigned int NumRows() const;
    const unsigned int NumCols() const;
    void initializeRandomBoard();
    char operator()(unsigned int row, unsigned int col) const;
    const std::string &operator()(unsigned int row) const;
    void PrintBoard(std::ostream &os = std::cout) const;

  private:
    strvector mBoard;
    const unsigned int mNumRows = 0;
    const unsigned int mNumCols = 0;
};
