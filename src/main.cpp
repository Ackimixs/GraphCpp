#include "../include/ListGraph.hpp"
#include "../include/MatrixGraph.hpp"
#include "../include/GmlFile.hpp"
#include "../include/Args.hpp"

int main(int argv, char **argc) {

    // Convert argv to map
    std::map<std::string, std::vector<std::string>> args;

    for (int i = 0; i < argv; i++) {
        auto arg = std::string(argc[i]);
        if (arg[0] == '-') {
            args[arg] = std::vector<std::string>();
            for (int j = i + 1; j < argv; j++) {
                std::string arg2 = argc[j];
                if (arg2[0] == '-') {
                    break;
                } else {
                    args[arg].push_back(arg2);
                }
            }
        }
    }

    checkArgs(args);

    Logger::debug("Graph v" + std::string(GRAPH_VERSION) + " started !");

    std::string graphType = argc[1];

    if (graphType == "list") {
        runGraphArgs<List::Graph<int>>(args);
    } else if (graphType == "matrix") {
        runGraphArgs<Matrix::Graph<int>>(args);
    } else {
        if (argv == 1) {
            Logger::error("Please provide a graph type as first argument, see --help for more informations");
        } else if (argc[1][0] == '-') {
            Logger::error("Please provide a graph type as first argument, see --help for more informations");
        } else {
            Logger::error("Unknown graph type : " + graphType);
        }
        exit(1);
    }

//    List::Graph g(6);
//
//    g.addEdge(0, 1);
//    g.addEdge(1, 2);
//    g.addEdge(2, 3);
//    g.addEdge(3, 4);
//    g.addEdge(0, 5);
//    g.addEdge(4, 5);

//    auto path = g.path(0, 4, false);
//
//    auto path2 = g.path(0, 3, false);
//
//    auto path3 = g.path(0, 4, true);
//
//    auto path4 = g.path(0, 3, true);
//
//    auto distanceFromS = g.distanceFromSource();
//
//    for (auto i : distanceFromS) {
//        std::cout << i << ", ";
//    }

//    List::Graph g = List::Graph::createRandomGraph(200, Type::UNDIRECTED, .01);

//    // BIPARTITE TESTER
//    List::Graph g = List::Graph(4, Type::UNDIRECTED);
//
//    g.addEdge(0, 1);
//    g.addEdge(1, 2);
//    g.addEdge(2, 3);
//    g.addEdge(3, 0);

////    CHECK LONGEST PATH => 5
//    List::Graph g = List::Graph(18, Type::DIRECTED);
//
//    g.addEdge(0, 1);
//    g.addEdge(0, 2);
//    g.addEdge(0, 4);
//    g.addEdge(0, 9);
//    g.addEdge(4, 3);
//    g.addEdge(4, 5);
//    g.addEdge(4, 6);
//    g.addEdge(6, 7);
//    g.addEdge(9, 8);
//    g.addEdge(9, 10);
//    g.addEdge(10, 11);
//    g.addEdge(11, 12);
//    g.addEdge(13, 0);
//    g.addEdge(14, 13);
//    g.addEdge(15, 0);
//    g.addEdge(16, 15);
//    g.addEdge(17, 16);

//    List::Graph g(6);
//
//    g.addEdge(0,1);
//    g.addEdge(0, 2);
//    g.addEdge(1, 2);
//    g.addEdge(1, 4);
//    g.addEdge(4, 5);
//    g.addEdge(2, 3);

//    List::Graph g(5);
//
//    g.addEdge(0, 1);
//    g.addEdge(0, 2);
//    g.addEdge(2, 3);
//    g.addEdge(1, 3);
//    g.addEdge(1, 4);
//
//    g.print();
//
//    auto v = g.eccentricity(3);
//
//    if (v.has_value()) {
//        std::cout << v.value().first << ", " << v.value().second << std::endl;
//    }
//
//    for (int i = 0; i < g.size(); i++) {
//        auto v = g.eccentricity(i);
//        if (v.has_value()) {
//            std::cout << i << ", " << v.value().first << ", " << v.value().second << std::endl;
//        }
//    }
//
//    auto r = g.radius();
//
//    if (r.has_value()) {
//        std::cout << r.value().first << " : " << r.value().second.first << " -> " << r.value().second.second << std::endl;
//    }
//
//    auto d = g.diameter();
//
//    if (d.has_value()) {
//        std::cout << d.value().first << " : " << d.value().second.first << " -> " << d.value().second.second << std::endl;
//    }


//
//    auto cycle = g.cycle();
//
//    if (cycle.has_value()) {
//        for (auto i : cycle.value()) {
//            std::cout << i << ", ";
//        }
//        std::cout << std::endl;
//    } else {
//        std::cout << "No cycle !" << std::endl;
//    }

//
//    auto distanceFromSource = g.distanceFromSource();
//
//    for (auto i : distanceFromSource) {
//        std::cout << i << ", ";
//    }
//    std::cout << std::endl;
//
//    g.BFS();
//
//    g.DFS(printType::PREORDER);
//    g.DFS(printType::POSTORDER);
//
//    g.DFS_stack();

//    bool isB = g.isBipartite();
//    std::cout << (isB ? "true" : "false") << std::endl;


//    auto path = g.longestPath();
//
//    std::cout << "longest path : " << path.first << ", from " << path.second.first << " to " << path.second.second << std::endl;

//    auto res = g.path(0, 100);
//
//    if (res) {
//        std::cout << res.value().first << std::endl;
//        for (int i : res.value().second) {
//            std::cout << i << ", ";
//        }
//        std::cout << std::endl;
//    } else {
//        std::cout << "no path" << std::endl;
//    }

//    Matrix ide = Matrix::identityMatrix(5);
//
//    ide.print();

    return 0;
}
