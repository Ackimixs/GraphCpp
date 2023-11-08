#pragma once

#include "ListGraph.hpp"
#include "GmlFile.hpp"
#include "Constants.hpp"
#include "Logger.hpp"
#include "LogColor.hpp"

#include <vector>
#include <string>
#include <map>
#include <chrono>

void checkArgs(std::map<std::string, std::vector<std::string>> args) {
    if (args.contains("-h") || args.contains("--help")) {
        std::cout << "./ggraph [matrix | list] [-a | --algo, -n | --nodes, -v | --version, --debug, -p | --probability, -t | --templates]" << std::endl;
        exit(0);
    }

    if (args.contains("-v") || args.contains("--version")) {
        std::cout << "Graph v" << GRAPH_VERSION << std::endl;
        exit(0);
    }

    if (args.contains("--debug")) {
        Logger::setLogLevel(LogLevel::DEBUG);
    } else {
        Logger::setLogLevel(LogLevel::INFO);
    }
}

template<typename G>
void runGraphArgs(std::map<std::string, std::vector<std::string>> args) {
    Logger::debug("Running graph args");

    int n = 1000;
    double p = .01;
    G g;

    if (args.contains("-n") || args.contains("--nodes")) {
        std::vector<std::string> nArgs = args.contains("-n") ? args["-n"] : args["--nodes"];
        if (nArgs.size() > 1) {
            Logger::error("Too many arguments for -n");
            exit(1);
        }
        if (Utils::isDouble(nArgs[0])) {
            n = std::stoi(nArgs[0]);
        } else {
            Logger::error("Argument for -n | --nodes is not a number");
            exit(1);
        }
    }

    if (args.contains("-p") || args.contains("--probability")) {
        std::vector<std::string> pArgs = args.contains("-p") ? args["-p"] : args["--probability"];
        if (pArgs.size() > 1) {
            Logger::error("Too many arguments for -p");
            exit(1);
        }
        if (Utils::isDouble(pArgs[0])) {
            p = std::stod(pArgs[0]);
        } else {
            Logger::error("Argument for -p | --probability is not a number");
            exit(1);
        }
    }

    if (args.contains("-t") || args.contains("--template")) {
        std::vector<std::string> templateArgs = args.contains("-t") ? args["-t"] : args["--template"];

        if (templateArgs[0] == "cycle") {
            g = G::createCycleGraph(n, Type::Graph::UNDIRECTED, true);
        } else if (templateArgs[0] == "complete") {
            g = G::createCompleteGraph(n, Type::Graph::UNDIRECTED, true);
        } else if (templateArgs[0] == "bipartite") {
            g = G::createBipartiteGraph(n, Type::Graph::UNDIRECTED, true);
        } else if (templateArgs[0] == "black-hole") {
            int startIndex = templateArgs.size() > 1 ? Utils::isNumber(templateArgs[1]) ? std::stoi(templateArgs[1]) : 0 : 0;

            g = G::createBlackHoleGraph(n, Type::Graph::UNDIRECTED, true, startIndex);
        } else if (templateArgs[0] == "star") {
            g = G::createStarGraph(n, Type::Graph::UNDIRECTED, true);
        } else if (templateArgs[0] == "random") {
            g = G::createRandomGraph(n, Type::Graph::UNDIRECTED, p, true);
        } else {
            Logger::error("Unknown template");
            exit(1);
        }
    } else {
        g = G::createRandomGraph(n, Type::Graph::UNDIRECTED, p, true);
    }

    if (args.contains("-o") || args.contains("--output")) {
        std::string filename = args.contains("-o") ? args["-o"][0] : args["--output"][0];

        if (filename.find(".gml") == std::string::npos) {
            filename += ".gml";
        }

        toGmlFile<G>(filename, g);
    }

    if (args.contains("-a") || args.contains("--algo")) {
        std::vector<std::string> algoArg = args.contains("-a") ? args["-a"] : args["--algo"];

        if (algoArg[0] == "bfs") {

            int startIndex = 0;
            if (algoArg.size() > 1) {
                if (Utils::isNumber(algoArg[1])) {
                    startIndex = std::stoi(algoArg[1]);
                } else {
                    Logger::error("Second Argument for -a | --algo is not a number");
                    exit(1);
                }
            }

            auto start = std::chrono::high_resolution_clock::now();

            auto vec = g.BFS(startIndex);

            auto end = std::chrono::high_resolution_clock::now();

            std::stringstream ss;

            for (auto i : vec) {
                ss << i << ", ";
            }

            Logger::debug(ss.str());

            ss.str("");

            ss << "Time to execute BFS : ";

            ss << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds";

            Logger::info(ss.str());

        } else if (algoArg[0] == "dfs") {

            int startIndex = 0;
            if (algoArg.size() > 1) {
                if (Utils::isNumber(algoArg[1])) {
                    startIndex = std::stoi(algoArg[1]);
                } else {
                    Logger::error("Second Argument for -a | --algo is not a number");
                    exit(1);
                }
            }

            auto start = std::chrono::high_resolution_clock::now();

            auto vec = g.DFS(startIndex);

            auto end = std::chrono::high_resolution_clock::now();

            std::stringstream ss;

            for (auto i: vec) {
                ss << i << ", ";
            }

            Logger::debug(ss.str());

            ss.str("");

            ss << "Time to execute DFS : ";

            ss << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds";

            Logger::info(ss.str());

        } else if (algoArg[0] == "bipartite") {
            auto start = std::chrono::high_resolution_clock::now();

            auto vec = g.isBipartite();

            auto end = std::chrono::high_resolution_clock::now();

            std::stringstream ss;

            ss << "Time to execute Bipartite : ";

            ss << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds";

            ss << " | Graph is : " << LogColor::fgRed << (vec ? "Bipartite" : "not Bipartite") << LogColor::reset;

            Logger::info(ss.str());

        } else {
            Logger::error("Unknown algorithm");
            exit(1);
        }
    }
}