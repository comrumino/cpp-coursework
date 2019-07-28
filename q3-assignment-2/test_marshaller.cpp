#include "TestHarness.h"
#include "test_xml_case.h"
#include "tinyxml2.h"
#include "vectorgraphic.h"
#include "framework.h"



TEST(marshaller, file_write_xml) {
    // to writable location
    std::string fname = "test_parse.xml";
    tinyxml2::XMLDocument doc;
    doc.Parse(xml_case::good_count_1_uncommented.c_str());
    CHECK_EQUAL(0, marshaller::file::write(doc, fname));
    // to non-writable location
    CHECK_EQUAL(1, marshaller::file::write(doc, "/path/that/does/not/exist" + fname));

}
TEST(marshaller, file_read_xml) {
    // to writable location
    std::string fname = "test_parse.xml";
    tinyxml2::XMLDocument doc;
    CHECK_EQUAL(0, marshaller::file::read(doc, fname));
    doc.Parse(xml_case::bad_count_1_uncommented.c_str());
    // to non-writable location
    CHECK_EQUAL(1, marshaller::file::read(doc, "/path/that/does/not/exist" + fname));
}


/*
TEST(xml, xml_to_file) {
    tinyxml2::XMLDocument doc;
    doc.Parse(xml_case::good_count_1_uncommented
}
*/
/*
TEST(xml, xml_point_good) {
    std::string complete_xml = "<VectorGraphic closed=\"true\">"
                               "  <Point x=\"0\" y=\"0\" />\n"
                               "  <Point x=\"10\" y=\"0\"></Point>\n"
                               "  <Point x=\"10\" y='10\'>  \n   </Point>\n"
                               "     </VectorGraphic>";
    std::vector<VectorGraphic> vector_graphics;
    std::string empty_element = "<VectorGraphic closed=\"false\"/>";
    parse_xml(complete_xml, vector_graphics);
    CHECK_EQUAL(1, vector_graphics.size());
    parse_xml(complete_xml + empty_element, vector_graphics);
    CHECK_EQUAL(3, vector_graphics.size());
    parse_xml(empty_element, vector_graphics);
    CHECK_EQUAL(4, vector_graphics.size());
    if (vector_graphics.size() == 4) {
        // given vector graphic example
        CHECK_EQUAL(3, vector_graphics[0].getPointCount());
        CHECK_EQUAL(true, vector_graphics[0].isClosed());
        CHECK_EQUAL(false, vector_graphics[0].isOpen());
        CHECK_EQUAL(10, vector_graphics[0].getWidth());
        CHECK_EQUAL(10, vector_graphics[0].getHeight());
        // empty element
        CHECK_EQUAL(0, vector_graphics[3].getPointCount());
        CHECK_EQUAL(false, vector_graphics[3].isClosed());
        CHECK_EQUAL(true, vector_graphics[3].isOpen());
        CHECK_EQUAL(0, vector_graphics[3].getWidth());
        CHECK_EQUAL(0, vector_graphics[3].getHeight());
        // the combined is assumed correct since size is correct
    }
}
TEST(xml, xml_point_bad) {
    std::string vg_start = "<VectorGraphic closed=\"true\">";
    std::string vg_end = "</VectorGraphic>";
    std::vector<std::string> bad_points{"  <Point x=\"10\" y='-1-0-'>  \n   </Point>\n",
                                        "  <Point x='0\"' y=\"'10\" />\n", "  <Point x='0\"' y=\"null\" />\n"};
    std::string complete_xml = "";
    std::vector<VectorGraphic> vector_graphics;
    for (auto bad_point : bad_points) {
        complete_xml = vg_start + bad_point + vg_end;
        parse_xml(complete_xml, vector_graphics);
        CHECK_EQUAL(0, vector_graphics.size());
        vector_graphics.clear();
    }
}
*/

