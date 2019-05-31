#include "WordFinder.h"
#include "Board.h"
#include "Dictionary.h"
#include <algorithm>
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef std::set<std::string> TWordsList;

TWordsList FragString(const std::string mstr, const int maxFragSize) {
    TWordsList frags;
    std::string frag;
    // i := length of fragment
    // j := offset start
    // i + j := end
    // iterate the set of distances given a supremum of mstr.length
    for (auto i = 0; i < mstr.length(); ++i) {
        for (auto j = i; j < mstr.length(); ++j) {
            frag = mstr.substr(i, j + 1 - i);
            if (maxFragSize != -1 && frag.length() > maxFragSize)
                continue;
            frags.insert(frag);
            std::reverse(frag.begin(), frag.end());
            frags.insert(frag);
        }
    }
    return frags;
}

WordFinder::WordFinder(const Dictionary &dict, const Board &board, int maxFoundWordLength)
    : mWords(dict), mBoard(board), mMaxFoundWordLength(maxFoundWordLength) {}

TWordsList WordFinder::FindWords() {
    TWordsList twl;
    // horizontal
    TWordsList tfrags;
    for (auto i = 0; i < mBoard.NumRows(); ++i) {
        tfrags = FragString(mBoard(i), mMaxFoundWordLength);
        mWords.Intersection(tfrags);
        twl.insert(tfrags.begin(), tfrags.end());
        tfrags.clear();
    }
    // vertical
    std::string tstr;
    for (auto j = 0; j < mBoard.NumCols(); ++j) {
        tstr = "";
        for (auto i = 0; i < mBoard.NumRows(); ++i) {
            tstr += mBoard(i, j);
        }
        tfrags = FragString(tstr, mMaxFoundWordLength);
        mWords.Intersection(tfrags);
        twl.insert(tfrags.begin(), tfrags.end());
        tfrags.clear();
    }
    // diagnol down right
    //        1 2
    //    0 a d d
    //    1 p o t
    //    2 t a b
    // avoid overlap =>
    //    i := [0, nr)
    //    j := [1, nc)
    auto nr = mBoard.NumRows();
    auto nc = mBoard.NumCols();
    // diagnol start zero-th column and find diagnol for all i in [0, NumRows) down right
    for (auto i = 0; i < mBoard.NumRows(); ++i) {
        tstr = "";
        for (auto j = 0; j < std::min(mBoard.NumCols(), mBoard.NumRows() - i); ++j) {
            tstr += mBoard(i + j, j);
        }
        tfrags = FragString(tstr, mMaxFoundWordLength);
        mWords.Intersection(tfrags);
        twl.insert(tfrags.begin(), tfrags.end());
        tfrags.clear();
    }
    // diagnol start zero-th row and find diagnol for all j in [1, NumCols) down right
    for (auto j = 1; j < mBoard.NumCols(); ++j) {
        tstr = "";
        for (auto i = 0; i < std::min(mBoard.NumCols() - j, mBoard.NumRows()); ++i) {
            tstr += mBoard(i, j + i);
        }
        tfrags = FragString(tstr, mMaxFoundWordLength);
        mWords.Intersection(tfrags);
        twl.insert(tfrags.begin(), tfrags.end());
        tfrags.clear();
    }
    // diagnol start zero-th column and find diagnol for all i in [0, NumRows) up right
    for (auto i = 0; i < mBoard.NumRows(); ++i) {
        tstr = "";
        for (auto j = 0; j < 1 + i; ++j) {
            tstr += mBoard(i - j, j);
        }
        tfrags = FragString(tstr, mMaxFoundWordLength);
        mWords.Intersection(tfrags);
        twl.insert(tfrags.begin(), tfrags.end());
        tfrags.clear();
    }
    // diagnol start zero-th row and find diagnol for all j in [1, NumCols) up right
    for (auto j = 1; j < mBoard.NumCols(); ++j) {
        tstr = "";
        for (auto i = 0; i < j; ++i) {
            tstr += mBoard(mBoard.NumCols() + i - j, j);
        }
        tfrags = FragString(tstr, mMaxFoundWordLength);
        mWords.Intersection(tfrags);
        twl.insert(tfrags.begin(), tfrags.end());
        tfrags.clear();
    }
    // then we return words OH MY GERRDDD
    return twl;
}

void WordFinder::AddWord(const std::string &word, TWordsList &wordsFound) {}
