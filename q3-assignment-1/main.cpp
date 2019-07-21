#include "parse.h"
#include "vectorgraphic.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<VectorGraphic> vector_graphics;
    if (argc != 3) {
        std::cout << "Please run this program with two arguments: infile and outfile" << std::endl;
    }
    std::string infile(argv[1]);
    std::string outfile(argv[2]);
    if (!from_file(infile, vector_graphics)) {
        return 1;
    } else if (!to_file(outfile, vector_graphics)) {
        return 1;
    } else {
        return 0;
    }
}
