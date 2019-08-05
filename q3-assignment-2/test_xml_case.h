#pragma once
#include <string>

namespace xml_case {
static const std::string play{"<Play/>"};
static const std::string unknown{"<!DOCTYPE PLAY SYSTEM \"play.dtd\">"};
static const std::string declaration{"<?xml version=\"1.0\"?>"};
static const std::string text{"text"};
static const std::string comment{"<!-- comment -->"};
static const std::string point_good{"<Point x=\"1\" y=\"2\"/>"};
static const std::string point_bad{"<Point x=\"-1-1\" y=\"2\"/>"};
static const std::string good_count_1_uncommented{"<Scene width=\"800\" height=\"600\">"
                                                  "    <Layer alias=\"sky\">"
                                                  "        <PlacedGraphic x=\"0\" y=\"0\">"
                                                  "            <VectorGraphic closed=\"true\">"
                                                  "                <Point x=\"1\" y=\"2\"/>"
                                                  "                <Point x=\"3\" y=\"4\"/>"
                                                  "                <Point x=\"5\" y=\"6\"/>"
                                                  "            </VectorGraphic>"
                                                  "        </PlacedGraphic>"
                                                  "    </Layer>"
                                                  "</Scene>"};
static const std::string good_count_2_uncommented{"<Scene width=\"800\" height=\"600\">"
                                                  "    <Layer alias=\"sky\">"
                                                  "        <PlacedGraphic x=\"0\" y=\"0\">"
                                                  "            <VectorGraphic closed=\"true\">"
                                                  "                <Point x=\"1\" y=\"2\"/>"
                                                  "                <Point x=\"3\" y=\"4\"/>"
                                                  "                <Point x=\"5\" y=\"6\"/>"
                                                  "            </VectorGraphic>"
                                                  "        </PlacedGraphic>"
                                                  "        <PlacedGraphic x=\"700\" y=\"0\">"
                                                  "            <VectorGraphic closed=\"false\">"
                                                  "                <Point x=\"7\" y=\"8\"/>"
                                                  "                <Point x=\"9\" y=\"10\"/>"
                                                  "                <Point x=\"11\" y=\"12\"/>"
                                                  "            </VectorGraphic>"
                                                  "        </PlacedGraphic>"
                                                  "    </Layer>"
                                                  "    <Layer alias=\"mountains\">"
                                                  "        <PlacedGraphic x=\"250\" y=\"250\">"
                                                  "            <VectorGraphic closed=\"false\">"
                                                  "                <Point x=\"13\" y=\"14\"/>"
                                                  "                <Point x=\"15\" y=\"16\"/>"
                                                  "                <Point x=\"17\" y=\"18\"/>"
                                                  "            </VectorGraphic>"
                                                  "        </PlacedGraphic>"
                                                  "    </Layer>"
                                                  "</Scene>"};
static const std::string good_count_1_commented{"<!-- comment -->"
                                                "<Scene width=\"800\" height=\"600\">"
                                                "<!-- comment -->"
                                                "    <Layer alias=\"sky\">"
                                                "<!-- comment -->"
                                                "        <PlacedGraphic x=\"0\" y=\"0\">"
                                                "<!-- comment -->"
                                                "            <VectorGraphic closed=\"true\">"
                                                "<!-- comment -->"
                                                "                <Point x=\"1\" y=\"2\"/>"
                                                "                <Point x=\"3\" y=\"4\"/>"
                                                "                <Point x=\"5\" y=\"6\"/>"
                                                "<!-- comment -->"
                                                "            </VectorGraphic>"
                                                "<!-- comment -->"
                                                "        </PlacedGraphic>"
                                                "<!-- comment -->"
                                                "    </Layer>"
                                                "<!-- comment -->"
                                                "</Scene>"
                                                "<!-- comment -->"};
static const std::string bad_count_1_uncommented{"<Scene width=\"800\" height=\"600\""
                                                 "    <Layer alias=\"sky\">"
                                                 "        <PlacedGraphic x=\"0\" y=\"0\">"
                                                 "            <VectorGraphic closed=\"true\">"
                                                 "                <Point x=\"1\" y=\"2\"/>"
                                                 "                <Point x=\"3\" y=\"4\"/>"
                                                 "                <Point x=\"5\" y=\"6\"/>"
                                                 "            </VectorGraphic>"
                                                 "        </PlacedGraphic>"
                                                 "    </Layer>"
                                                 "</Scene>"};
} // namespace xml_case
