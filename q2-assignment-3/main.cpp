#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>
using namespace std;

// All potential parenthesis
static const std::unordered_map<char, char> bracket_open_close = {{'[', ']'}, {'{', '}'}, {'(', ')'}};
class ParenthesisChecker {
  public:
    static bool CheckAndPrint(const std::string &str, std::ostream &os);

    static bool IsOpenParen(char ch);
    static bool IsCloseParen(char ch);
    static bool IsMatchingCloseParen(char openParen, char closeParen);

  private:
    static bool IsWellFormed(const std::string &str);
};

bool ParenthesisChecker::CheckAndPrint(const string &str, ostream &os) {
    bool valid = ParenthesisChecker::IsWellFormed(str);
    os << "\"" << str << "\":" << (valid ? "" : " not") << " well formed." << std::endl;
    return valid;
}

bool ParenthesisChecker::IsWellFormed(const string &str) {
    bool valid = true;
    std::stack<char> pstack;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {

        if (*it == '[' || *it == '{' || *it == '(') { // is open, set expectation
            pstack.push(bracket_open_close.find(*it)->second);
        } else if (*it == ']' || *it == '}' || *it == ')') { // is it close, then check if it does not expectations
            if (pstack.empty() || pstack.top() != *it)       // if empty or not as expected, no good
                valid = false;
            else
                pstack.pop();
        }
        if (!valid)
            break;
    }
    return valid && pstack.empty(); // check valid upto this point and that no extra bracks are in stack
}

void TestWellFormed(ostream &os) {
    bool chk = false;
    std::vector<string> cases{"(())", "(())[2][ ]", "(())[[]]", "(()) [[ {{ (()) }} ]] [][] () {} {{}}",
                              "(()) Foo(2,3) Bar(arr[1][2], arr[2][2])"};
    os << "TestWellFormed:" << std::endl;
    for (auto c : cases) {
        os << "  ";
        chk = ParenthesisChecker::CheckAndPrint(c, os);
    }
}

void TestNotWellFormed(ostream &os) {
    bool chk = false;
    std::vector<string> cases{"(()) )",
                              "(())[2][ ] [",
                              "(())[[]] }",
                              "(()) [[ {{ (()) }} ]] [][] () {} {{}} ())",
                              "(()) Foo(2,3) Bar(arr[1][2], arr[2][2]) )(",
                              ")("};
    os << "TestNotWellFormed:" << std::endl;
    for (auto c : cases) {
        os << "  ";
        chk = ParenthesisChecker::CheckAndPrint(c, os);
    }
}

#include "TestHarness.h"
TEST(WellFormed, given) {
    std::stringstream os;
    TestWellFormed(os);
    std::cout << os.str() << std::endl;
}

TEST(NotWellFormed, given) {
    std::stringstream os;
    TestNotWellFormed(os);
    std::cout << os.str() << std::endl;
}
