#pragma once
#include <set>
#include <string>

class Dictionary {
public:
  Dictionary(const std::string &wordsFile);

  bool Contains(const std::string &word) const;

  using citerator = std::set<std::string>::const_iterator;
  void Intersection(std::set<std::string> &twl) const;
  unsigned int Size();
  citerator begin() const;
  citerator end() const;
  citerator &FindNextWord(int size, citerator &iter) const; // to remove

private:
  std::set<std::string> mWords;
};
