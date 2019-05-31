#pragma once
#include "Board.h"
#include "Dictionary.h"
#include "WordFinder.h"
#include "WordGame.h"
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class WordGame {
public:
  WordGame(int numRows, int numCols, int maxWordSizeToLookFor, const string &wordsFile);
  ~WordGame();
  void Run(std::ostream &os=std::cout);

private:
  void PrintWords(const TWordsList &twl, std::ostream &os=std::cout);

  Board *mGameBoard;
  Dictionary mWordsDictionary;
  int mMaxWordSizeToLookFor;
};

