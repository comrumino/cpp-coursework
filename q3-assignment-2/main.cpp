#include "marshaller.h"
#include "framework.h"
#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <vector>

# if 1
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
    for (auto child : elmnt.getAllChildren()) {
        if (!framework::io::isSaneElement(child, "Scene"))
            continue;
        auto scene = framework::io::readScene(child);
        auto scene_elmnt = framework::io::writeScene(scene);
        auto xml_scene = framework::io::elementToXML(scene_elmnt, doc);
        doc.InsertEndChild(xml_scene);
    }
    auto comment_elmnt = doc.NewComment("My crufty comment!");
    doc.InsertFirstChild(comment_elmnt);
    auto write_code = marshaller::file::write(doc, outfile);
    return write_code;
}
#endif
