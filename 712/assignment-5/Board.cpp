#include "Board.h"
#include "Dictionary.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// std::vector<std::string>	mBoard;

Board::Board(const unsigned int numRows, const unsigned int numCols, const Dictionary &dict, const strvector &debug)
    : mNumRows(numRows), mNumCols(numCols) {
    if (debug.empty())
        initializeRandomBoard();
    else
        mBoard = debug;
}

const unsigned int Board::NumRows() const { return mNumRows; }

const unsigned int Board::NumCols() const { return mNumCols; }

void Board::initializeRandomBoard() {
    std::srand(mNumRows * mNumCols);
    int r = 0;
    char c = 'a';
    for (auto i = 0; i < mNumRows * mNumCols; ++i) {
        if (mBoard.size() < (i / mNumRows) + 1)
            mBoard.push_back("");
        r = rand() % 26;
        c = 'a' + r;
        mBoard[i / mNumCols] = mBoard[i / mNumCols] + c;
    }
}

char Board::operator()(unsigned int row, unsigned int col) const { return mBoard[row][col]; }

const std::string &Board::operator()(unsigned int row) const { return mBoard[row]; }

void Board::PrintBoard(std::ostream &os) const {
    for (auto it = mBoard.begin(); it != mBoard.end(); ++it)
        os << *it << std::endl;
}
