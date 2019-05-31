#pragma once
#include "Board.h"
#include "Dictionary.h"
#include "WordFinder.h"
#include "WordGame.h"
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

class WordGame {
public:
  WordGame(int numRows, int numCols, int maxWordSizeToLookFor, const string &wordsFile);
  ~WordGame();
  void Run();

  static const int kDefaultBoardSize = 4;
  static const int kMaxBoardSize = 10;
  static const int kDefaultMaxFoundWordLength = 9;
  static const int kMaxMaxFoundWordLength = 15;

private:
  void PrintWords(const TWordsList &);

  Board *mGameBoard;
  Dictionary mWordsDictionary;
  int mMaxWordSizeToLookFor;
};

