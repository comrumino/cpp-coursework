#pragma once
#include "Board.h"
#include "Dictionary.h"
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef std::set<std::string> TWordsList;

TWordsList FragString(const std::string mstr, const int maxFragSize = -1);

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
