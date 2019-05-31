#pragma once
#include "Board.h"
#include "Dictionary.h"
#include <set>
#include <string>
#include <vector>
#include <sstream>


typedef std::set<std::string> TWordsList;

TWordsList FragString(const std::string mstr);

class WordFinder {
public:

  WordFinder(const Dictionary &dict, const Board &board, int maxFoundWordLength);
  TWordsList FindWords();

private:
  void AddWord(const std::string &word, TWordsList &wordsFound);

  const Dictionary &mWords;
  const Board &mBoard;
  int mMaxFoundWordLength;
};
