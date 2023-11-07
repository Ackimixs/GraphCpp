#pragma once

#include "ListGraph.hpp"
#include "Logger.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template<typename G>
void toGmlFile(const std::string& filename, const G& graph) {

    Logger::debug("Writing graph to " + filename);

    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {
        outputFile << "graph\n";
        outputFile << "[\n";


        for (int i = 0; i < graph.size(); i++) {
            outputFile << "node\n[\n";

            outputFile << "id " << std::to_string(i) << "\n";

            outputFile << "Label " << "\"Node "<< std::to_string(i) << "\"";

            outputFile << "graphics\n[\n";

            outputFile << "x " << std::to_string(std::rand() % 10001) << "\n";
            outputFile << "y " << std::to_string(std::rand() % 10001) << "\n";

            outputFile << "]\n";

            outputFile << "]\n";
        }


        for (int i = 0; i < graph.size(); i++) {
            for (auto v : graph[i]) {
                outputFile << "edge\n[\n";

                outputFile << "source " << std::to_string(i) << "\n";
                outputFile << "target " << std::to_string(v.first) << "\n";
                outputFile << "label " << "\"" << std::to_string(v.second) << "\"" << "\n";

                outputFile << "]\n";
            }
        }


        outputFile << "]\n";
        outputFile.close();
    } else {
        Logger::error("Unable to open file " + filename);
    }
}