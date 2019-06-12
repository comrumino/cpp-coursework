#pragma once
#include <iostream>
#include <string>

class SimpleClass {
  public:
    SimpleClass(std::string sc_id = "default sc") : id{sc_id} { std::cout << "  Constructed: " << id << std::endl; }

    SimpleClass(const SimpleClass &src) : id{src.id + " copy"} { std::cout << "  Copied: " << id << std::endl; }

    ~SimpleClass() { std::cout << "  Deconstructed: " << id << std::endl; }

  private:
    const std::string id;
};

void f1(SimpleClass aSimpleClass);

void f2(SimpleClass aSimpleClass);

void f3(SimpleClass &aSimpleClass);

void f4(SimpleClass *aSimpleClass);
