#include "marshaller.h"
#include "framework.h"
#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <vector>

# if 0
int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Please run this program with two arguments: infile and outfile" << std::endl;
    }
    std::string infile(argv[1]);
    std::string outfile(argv[2]);
    tinyxml2::XMLDocument doc;
    auto read_code = marshaller::file::read(doc, infile);
    if (read_code != 0) {
        return read_code;
    }
    auto elmnt = framework::io::elementFromXML(doc.ToDocument());
    doc.Clear();
    static_cast<void>(framework::io::elementToXML(elmnt, doc));  // cast to void since doc is referenced and updated 
    auto comment_elmnt = doc.NewComment("My crufty comment!");
    doc.InsertFirstChild(comment_elmnt);
    auto write_code = marshaller::file::write(doc, outfile);
    return write_code;
}
#endif
