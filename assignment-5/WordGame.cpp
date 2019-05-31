#include "Board.h"
#include "Dictionary.h"
#include "WordFinder.h"
#include "WordGame.h"
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

/* 
 * static const int kDefaultBoardSize = 4;
 * static const int kMaxBoardSize = 10;
 * static const int kDefaultMaxFoundWordLength = 9;
 * static const int kMaxMaxFoundWordLength = 15;
 * Board *mGameBoard;
 * Dictionary mWordsDictionary;
 * int mMaxWordSizeToLookFor;
 */
WordGame::WordGame(int numRows, int numCols, int maxWordSizeToLookFor, const string &wordsFile)
    :mWordsDictionary(wordsFile), mMaxWordSizeToLookFor(maxWordSizeToLookFor),
    mGameBoard(new Board(numRows, numCols, mWordsDictionary)) {}

WordGame::~WordGame() {
    if (mGameBoard != nullptr)
        delete mGameBoard;
}
void WordGame::Run() {
}
void WordGame::PrintWords(const TWordsList &) {
}
