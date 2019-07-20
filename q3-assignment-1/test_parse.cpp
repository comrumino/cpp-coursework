#include "TestHarness.h"
#include "parse.h"
#include "point.h"
#include "vectorgraphic.h"
#include <iostream>
#include <sstream>
#include <string>

TEST(trim, trim_quote) {
    const std::string trimmables("\"");
    std::string quoted_value("\"value\"");
    trim(quoted_value, trimmables);
    CHECK_EQUAL("value", quoted_value);
}

TEST(trim, trim_empty_quoted) {
    const std::string trimmables("\"");
    std::string quoted_value("");
    trim(quoted_value, trimmables);
    CHECK_EQUAL("", quoted_value);
}

TEST(trim, trim_empty_trimmables) {
    const std::string trimmables("");
    std::string quoted_value("\"value\"");
    trim(quoted_value, trimmables);
    CHECK_EQUAL("\"value\"", quoted_value);
}

TEST(trim, trim_hmmm_bert) {
    const std::string trimmables({-1, '\0'});
    std::string quoted_value({-1, '\0'});
    trim(quoted_value, trimmables);
    CHECK_EQUAL("", quoted_value);
}

TEST(eat, eat_padded_1) {
    const std::string edible(" \t\n");
    std::istringstream padded_string("  string \t\n ");
    std::ostringstream actual;
    eat(padded_string, edible);
    actual << padded_string.rdbuf();
    CHECK_EQUAL("string \t\n ", actual.str());
}
TEST(eat, eat_empty_source) {
    const std::string edible(" \t\n");
    std::istringstream padded_string("");
    std::ostringstream actual;
    eat(padded_string, edible);
    actual << padded_string.rdbuf();
    CHECK_EQUAL("", actual.str());
}
TEST(eat, eat_empty_edible) {
    const std::string edible("");
    std::istringstream padded_string(" string ");
    std::ostringstream actual;
    eat(padded_string, edible);
    actual << padded_string.rdbuf();
    CHECK_EQUAL(" string ", actual.str());
}
TEST(eat, eat_error_istream) {
    const std::string edible({-1, '\0'});
    std::istringstream padded_string({-1, '\0'});
    std::ostringstream actual;

    padded_string.setstate(std::ios::failbit);
    eat(padded_string, edible);
    padded_string.setstate(std::ios::badbit);
    eat(padded_string, edible);
    padded_string.setstate(std::ios::eofbit);
    eat(padded_string, edible);
    actual << padded_string.rdbuf();
    CHECK_EQUAL(padded_string.str(), actual.str());
}

// example unit tests
TEST(trimBeginning, Parse) {
    std::string actual{"  \tHello"};
    trim(actual, " \t\n");

    CHECK_EQUAL("Hello", actual);
}

TEST(trimEnd, Parse) {
    std::string actual{"Hello  \n\n\n\t"};
    trim(actual, " \t\n");

    CHECK_EQUAL("Hello", actual);
}

TEST(trimBeginningAndEnd, Parse) {
    std::string actual{"  Hello\n\t"};
    trim(actual, " \t\n");

    CHECK_EQUAL("Hello", actual);
}

TEST(trimNone, Parse) {
    std::string actual{"Hello"};
    trim(actual);

    CHECK_EQUAL("Hello", actual);
}

TEST(trimEmpty, Parse) {
    std::string actual;
    trim(actual);

    CHECK_EQUAL("", actual);
}

TEST(trimEverything, Parse) {
    std::string actual{"Hello 1234"};
    std::string trimmables{"Hello 0123456789"};
    trim(actual, trimmables);

    CHECK_EQUAL("", actual);
}

TEST(eatNothing, Parse) {
    std::istringstream stream{"Hello"};
    eat(stream, "123456789");

    std::ostringstream actual;
    actual << stream.rdbuf();

    CHECK_EQUAL("Hello", actual.str());
}

TEST(eatSomething, Parse) {
    std::istringstream stream{"4320Hello"};
    eat(stream, "1234567890");

    std::ostringstream actual;
    actual << stream.rdbuf();

    CHECK_EQUAL("Hello", actual.str());
}

TEST(eatSomeLeadingWhitespace, Parse) {
    std::istringstream stream{"   I had leading whitespace"};
    eat(stream);

    std::ostringstream actual;
    actual << stream.rdbuf();

    CHECK_EQUAL("I had leading whitespace", actual.str());
}
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
    /*
    std::string complete_xml = "<VectorGraphic closed=\"true\">"
                               "  <Point x=\"0\" y=\"0\" />\n"
                               "  <Point x=\"10\" y=\"0\"></Point>\n"
                               "  <Point x=\"10\" y='10\'>  \n   </Point>\n"
                               "  <Point x='0\"' y=\"'10\" />\n"
                               "  <Point x='0\"' y=\"null\" />\n"
                               "</VectorGraphic>";
    std::vector<VectorGraphic> vector_graphics;
    CHECK_EQUAL(4, vector_graphics.size());
    parse_xml(complete_xml, vector_graphics);
    std::string empty_element = "<VectorGraphic closed=\"false\"/>";
    parse_xml(empty_element, vector_graphics);
    parse_xml(complete_xml+empty_element, vector_graphics);
    */
}
