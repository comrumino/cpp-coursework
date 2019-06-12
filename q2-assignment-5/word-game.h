#pragma once
#include "board.h"
#include "dictionary.h"
#include "word-finder.h"
#include "word-game.h"
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class WordGame {
  public:
    WordGame(int numRows, int numCols, int maxWordSizeToLookFor, const string &wordsFile);
    ~WordGame();
    void Run(std::ostream &os = std::cout);

  private:
    void PrintWords(const TWordsList &twl, std::ostream &os = std::cout);

    Board *mGameBoard;
    Dictionary mWordsDictionary;
    int mMaxWordSizeToLookFor;
};
