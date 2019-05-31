#include "Board.h"
#include "Dictionary.h"
#include "WordFinder.h"
#include "WordGame.h"
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#if 1
int main(int argc, char **argv) {
  int numRows = 4;
  int numCols = numRows;
  string wordsFile("WordsList.txt");

  auto wg = WordGame(numRows, numCols, 0, wordsFile);
  wg.Run();
  return 0;
}
#else
#include "TestHarness.h"

TEST(Dictionary, ctor) { // shouldn't the underlying container be a k-ary tree?
                         // but hey, who cares about data-structures besides SV
  Dictionary dict("WordsList.txt");
  CHECK_EQUAL(168845, dict.Size());
  CHECK_EQUAL(true, dict.Contains("zyzzyva"));
  CHECK_EQUAL(false, dict.Contains("c***candle"));
}

TEST(Board, debug_3x3) {
  const Dictionary dict("WordsList.txt");
  strvector dbg = {"add", "pot",
                   "tab"}; // "add" "pot" "tab" "boa" and then some
  std::stringstream exp;
  std::stringstream act;
  exp << "add" << std::endl << "pot" << std::endl << "tab" << std::endl;
  auto board = Board(3, 3, dict, dbg);
  board.PrintBoard(act);
  CHECK_EQUAL(exp.str(), act.str());
  // call target operator one parameter
  CHECK_EQUAL("add", board(0));
  CHECK_EQUAL("pot", board(1));
  CHECK_EQUAL("tab", board(2));
  // call target operator two parameter
  CHECK_EQUAL('a', board(0, 0));
  CHECK_EQUAL('o', board(1, 1));
  CHECK_EQUAL('b', board(2, 2));
}

TEST(Board, debug_1x3) {
  const Dictionary dict("WordsList.txt");
  strvector dbg = {"add"};
  std::stringstream exp;
  std::stringstream act;
  exp << "add" << std::endl;
  auto board = Board(1, 3, dict, dbg);
  board.PrintBoard(act);
  CHECK_EQUAL(exp.str(), act.str());
  CHECK_EQUAL(1, board.NumRows());
  CHECK_EQUAL(3, board.NumCols());
}

TEST(Board, random_3x3) {
  const Dictionary dict("WordsList.txt");
  std::stringstream exp;
  std::stringstream act;
  exp << "vix" << std::endl << "hcv" << std::endl << "ywk" << std::endl;
  auto board = Board(3, 3, dict);
  board.PrintBoard(act);
  CHECK_EQUAL(exp.str(), act.str());
}

TEST(FragString, result_frags) {
  std::string str = "abc";
  std::stringstream act;
  auto twl = FragString(str);
  // math magic says the result size should be str.length() squared
  CHECK_EQUAL(str.length() * str.length(), twl.size());
  for (auto it = twl.begin(); it != twl.end(); ++it)
    act << *it << " ";
  CHECK_EQUAL("a ab abc b ba bc c cb cba ", act.str());
}

TEST(WordFinder, find_words) {
  const Dictionary dict("WordsList.txt");
  strvector dbg = {"add", "pot",
                   "tab"}; // "add" "pot" "tab" "boa" and then some
  auto board = Board(3, 3, dict, dbg);
  std::stringstream act;
  auto wfr = WordFinder(dict, board, 15);
  auto twl = wfr.FindWords();
  for (auto it = twl.begin(); it != twl.end(); ++it) // already sorted
    act << *it << " ";
  CHECK_EQUAL(
      "a ab ad add apt at ba bat bo boa do ob od pa po pot ta tab to top ",
      act.str());
}

TEST(WordGame, run) {
  auto wg = WordGame(3, 3, 15, "WordsList.txt");
  std::stringstream exp;
  std::stringstream act;
  exp << "Max word length: 15" << std::endl;
  exp << "Number of words found: 6" << std::endl;
  exp << "hy ic iv vc wk xiv " << std::endl;
  wg.Run(act);
  CHECK_EQUAL(exp.str(), act.str());
}
#endif
