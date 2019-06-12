#include "word-game.h"
#include "board.h"
#include "dictionary.h"
#include "word-finder.h"
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

WordGame::WordGame(int numRows, int numCols, int maxWordSizeToLookFor, const string &wordsFile)
    : mWordsDictionary(wordsFile), mMaxWordSizeToLookFor(maxWordSizeToLookFor),
      mGameBoard(new Board(numRows, numCols, mWordsDictionary)) {}

WordGame::~WordGame() {
    if (mGameBoard != nullptr)
        delete mGameBoard;
}

void WordGame::Run(std::ostream &os) {
    auto wfr = WordFinder(mWordsDictionary, *mGameBoard, mMaxWordSizeToLookFor);
    auto twl = wfr.FindWords();
    os << "Max word length: " << mMaxWordSizeToLookFor << std::endl;
    os << "Number of words found: " << twl.size() << std::endl;
    PrintWords(twl, os);
}

void WordGame::PrintWords(const TWordsList &twl, std::ostream &os) {
    for (auto it = twl.begin(); it != twl.end(); ++it) // already sorted
        os << *it << " ";
    os << std::endl;
}
