#include "TestHarness.h"
#include "framework.h"
#include "test_xml_case.h"
#include "tinyxml2.h"
#include "vectorgraphic.h"

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
