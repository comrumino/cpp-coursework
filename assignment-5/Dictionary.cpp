#include "Dictionary.h"
#include <algorithm>
#include <set>
#include <string>
#include <fstream>
#include <iostream>

// std::set<std::string>		mWords;
Dictionary::Dictionary(const std::string &wordsFile) {
    //std::set<std::string> mWords;
    std::ifstream inFile(wordsFile);
    std::string word;
    while (inFile >> word) {
        mWords.insert(word);
    }
}

unsigned int Dictionary::Size(){
    return mWords.size();
}

bool Dictionary::Contains(const std::string &word) const {
    return mWords.find(word) != mWords.end();
}

void Dictionary::Intersection(std::set<std::string> &twl) const {
    std::set<std::string> intr;
    std::set_intersection(mWords.begin(), mWords.end(), twl.begin(), twl.end(), std::inserter(intr, intr.begin()));
    twl = intr;
}

using citerator = std::set<std::string>::const_iterator;

citerator Dictionary::begin() const {
    return mWords.cbegin();
}

citerator Dictionary::end() const {
    return mWords.cend();
}

citerator &Dictionary::FindNextWord(int size, citerator &iter) const {
    return iter;
}
