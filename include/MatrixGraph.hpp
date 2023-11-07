#pragma once

#include "Matrix.hpp"
#include "Logger.hpp"

#include <optional>
#include <random>
#include <iostream>
#include <queue>

namespace Matrix {
    template<typename T>
    class Graph : public adjacentMatrix<T> {
    private:
        Type::Graph _d;
        size_t _size;

    protected:
        void BFSVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &res);

        void DFSVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &res, Type::Print type);

        bool cycleVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &cycle, T prev);

        void distanceFromSourceVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &distance);

        bool isBipartiteVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<Color> &partie);

        void longestPathVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::pair<T, std::pair<T, T>> &lPath, std::pair<T, std::pair<T, T>> actualPath, T previous);

        std::optional<std::pair<T, std::vector<T>>> pathVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::pair<T, std::vector<T>> path, std::pair<T, T> &param);

    public:
        Graph();

        /**
         * @brief Create a graph
         * @param n -> the size of the graph
         * @param directed -> the type of the graph DIRECTED or UNDIRECTED, default UNDIRECTED
         */
        Graph(int size, Type::Graph directed = Type::Graph::UNDIRECTED);

        /**
         * @brief Create a graph from a matrix
         * @param graph -> graph to copie
         */
        Graph(const Graph& graph);

        /**
         * @brief Create a random graph
         * @param numberOfVertices -> the number of vertices
         * @param directed -> the type of the graph DIRECTED or UNDIRECTED, default UNDIRECTED
         * @param edgeProbability -> the probability of an edge to be created, default 0.5
         * @param includeRandomWeight -> if true the weight of the edge will be random, default false
         * @return the random graph
         */
        static Graph createRandomGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, double edgeProbability = 0.5, bool includeRandomWeight = false);

        static Graph<T> createCycleGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, bool includeRandomWeight = false);

        static Graph<T> createBlackHoleGraph(int numberOfVertices, Type::Graph directed = Type::Graph::DIRECTED, bool includeRandomWeight = false, T blackHole = 0);

        static Graph<T> createCompleteGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, bool includeRandomWeight = false);

        static Graph<T> createBipartiteGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, bool includeRandomWeight = false);

        static Graph<T> createStarGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, bool includeRandomWeight = false);

        ~Graph();

        size_t size() const;

        [[nodiscard]] Type::Graph directed() const;

        /**
         * @brief Add an edge to the graph
         * @param from -> the starting point
         * @param to -> the ending point
         * @param weight -> the weight of the edge
         */
        void addEdge(T from, T to, T weight = 1);

        /**
         * @brief Remove an edge from the graph (hard complexity so use it carefully)
         * @param from -> the starting point
         * @param to -> the ending point
         */
        void removeEdge(T from, T to);

        /**
         * @brief Get the degres of a vertex
         * @param vertex -> the vertex
         * @return the degres of the vertex
         */
        T degres(T vertex);

        /**
         * @brief Get the BFS of the graph
         * @return a vector of the BFS
         */
        std::vector<T> BFS(T start = 0);

        /**
         * @brief Get the DFS of the graph
         * @param type PREORDER or POSTORDER
         * @return a vector of the DFS
         */
        std::vector<T> DFS(T start = 0, Type::Print type = Type::Print::PREORDER);

        /**
         * @brief Check if the graph is bipartite
         * @return true if the graph is bipartite else false
         */
        bool isBipartite();

        /**
         * @brief Check if the graph has a cycle
         * @return a vector of edges of the cycle if exist else nothing
         */
        std::optional<std::vector<T>> cycle();

        /**
         * @brief Check if the graph is eulerian
         * @return true if the graph is eulerian else false
         */
        bool eulerianCycle();

        /**
         * @brief distance from any vertex
         * @param v -> the vertex
         * @return a vector of the distance from v
         */
        std::vector<T> distanceFrom(T v);

        /**
         * @brief Distance from 0
         * @return a vector of the distance from 0
         */
        std::vector<T> distanceFromSource();

        /**
         * @brief Return the longest path
         * @return std::pair(length of the path, std::pair(from, to))
         * work with a directed graph without cycle (DAG)
         */
        std::pair<T, std::pair<T, T>> longestPath();

        /**
         * @brief Return the longest path
         * @param from -> the starting point
         * @param to -> the ending point
         * @return std::pair(length of the path, std::vector(vertices of the path))
         */
        std::optional<std::pair<T, std::vector<T>>> path(T from, T to);

        /**
         * @brief Check if any vertex is a black hole
         * @return the black hole vertex or nothing
         */
        std::optional<T> blackHole();

        /**
         * @brief Get the eccentricity of a vertex
         * @param v -> the vertex
         * @return std::pair(distance, longest vertex)
         */
        std::optional<std::pair<T, T>> eccentricity(T v);

        /**
         * @brief Get the radius of the graph
         * @return std::pair(distance, std::pair(from, to))
         * NOT linear complexity
         */
        std::optional<std::pair<T, std::pair<T, T>>> radius();

        /**
         * @brief Get the diameter of the graph
         * @return std::pair(distance, std::pair(from, to))
         * NOT linear complexity
         */
        std::optional<std::pair<T, std::pair<T, T>>> diameter();

        M<T> matrixPath(T lenght);

        M<T> matrixAllPath();

        std::vector<std::pair<T, T>> operator[](T vertex) const;
    };
}

template<typename T>
Matrix::Graph<T>::Graph() : adjacentMatrix<T>(size_t(0)), _size(0), _d(Type::Graph::UNDIRECTED) {}

template<typename T>
Matrix::Graph<T>::Graph(int size, Type::Graph directed) : adjacentMatrix<T>(size), _d(directed), _size(size) {
    Logger::debug("Create a graph of size " + std::to_string(size) + " and type " + std::to_string(directed));
}

template<typename T>
Matrix::Graph<T>::Graph(const Graph &graph) : adjacentMatrix<T>(graph), _d(graph._d), _size(graph._size) {
    Logger::debug("Create a graph from copy");
}

template<typename T>
Matrix::Graph<T>::~Graph() {
    Logger::debug("Delete a graph");
}

template<typename T>
void Matrix::Graph<T>::addEdge(T from, T to, T weight) {
    this->set(from, to, std::make_pair(1, weight));
    if (this->_d == Type::Graph::UNDIRECTED) {
        this->set(to, from, std::make_pair(1, weight));
    }
}

template<typename T>
void Matrix::Graph<T>::removeEdge(T from, T to) {
    Logger::debug("Remove edge from " + std::to_string(from) + " to " + std::to_string(to));
    this->set(from, to, std::make_pair(0, 0));
    if (this->_d == Type::Graph::UNDIRECTED) {
        this->set(to, from, std::make_pair(0, 0));
    }
}

template<typename T>
T Matrix::Graph<T>::degres(T vertex) {
    if (vertex < 0 || vertex > this->size()) {
        throw std::invalid_argument("'edge' must be between 0 and the size of the graph !");
    }

    T res = 0;
    for (size_t i = 0; i < this->size(); i++) {
        if (this->operator()(vertex, i).first == 1) {
            res++;
        }
    }

    return res;
}

template<typename T>
std::vector<T> Matrix::Graph<T>::BFS(T start) {
    Logger::debug("BFS algorithm starting...");

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);
    std::vector<T> res;

    this->BFSVisit(start, color, parent, res);
    for (size_t v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            this->BFSVisit(v, color, parent, res);
        }
    }

    return res;
}

template<typename T>
void Matrix::Graph<T>::BFSVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &res) {
    std::queue<T> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        int w = q.front();
        q.pop();
        for (size_t z = 0; z < this->size(); z++) {
            if (this->at(v, z).first == 1) {
                if (color[z] == Color::BLUE) {
                    color[z] = Color::WHITE;
                    parent[z] = w;
                    q.push(z);
                }
            }
        }
        color[w] = Color::RED;
        res.push_back(w);
    }
}

template<typename T>
std::vector<T> Matrix::Graph<T>::DFS(T start, Type::Print type) {
    Logger::debug("DFS algorithm starting...");

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);
    std::vector<T> res;

    this->DFSVisit(start, color, parent, res, type);
    for (size_t v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            this->DFSVisit(v, color, parent, res, type);
        }
    }
    return res;
}

template<typename T>
void Matrix::Graph<T>::DFSVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &res,
                                Type::Print type) {
    color[v] = Color::WHITE;
    if (type == Type::Print::PREORDER) {
        res.push_back(v);
    }
    for (size_t w = 0; w < this->size(); w++) {
        if (this->operator()(v, w).first == 0) {
            if (color[w] == Color::BLUE) {
                parent[w] = v;
                this->DFSVisit(w, color, parent, res, type);
            }
        }
    }
    color[v] = Color::RED;
    if (type == Type::Print::POSTORDER) {
        res.push_back(v);
    }
}

template<typename T>
bool Matrix::Graph<T>::isBipartite() {
    Logger::debug("Check if the graph is bipartite...");

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<Color> partie = std::vector<Color>(this->size(), Color::NONE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);

    for (size_t v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            partie[v] = Color::BLUE;
            bool res = this->isBipartiteVisit(v, color, parent, partie);
            if (!res) {
                return false;
            }
        }
    }
    return true;
}

template<typename T>
bool Matrix::Graph<T>::isBipartiteVisit(T v, std::vector<Color> &color, std::vector<T> &parent,
                                        std::vector<Color> &partie) {
    std::queue<int> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        int w = q.front();
        q.pop();
        Color nextColor = partie[w] == Color::BLUE ? Color::RED : Color::BLUE;
        for (size_t z = 0; z < this->size(); z++) {
            if (this->operator()(w, z).first == 1) {

                // PART TO CHECK IF THE GRAPH IS BIPARTITE
                if (partie[z] != Color::NONE) {
                    if (partie[z] == partie[w]) {
                        return false;
                    }
                } else {
                    partie[z] = nextColor;
                }

                if (color[z] == Color::BLUE) {
                    color[z] = Color::WHITE;
                    parent[z] = w;
                    q.push(z);
                }
            }
        }
        color[w] = Color::RED;
    }
    return true;
}

template<typename T>
std::optional<std::vector<T>> Matrix::Graph<T>::cycle() {
    Logger::debug("Check if the graph has a cycle...");

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);
    std::vector<T> cycle;

    for (size_t v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            if (this->cycleVisit(v, color, parent, cycle, -1)) {
                return cycle;
            }
        }
    }
    return std::nullopt;
}

template<typename T>
bool Matrix::Graph<T>::cycleVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &cycle,
                                  T prev) {
    color[v] = Color::WHITE;
    if (vectorUtils<T>::isInVector(cycle, v)) {
        cycle.push_back(v);
        return true;
    }

    cycle.push_back(v);

    for (size_t w = 0; w < this->size(); w++) {
        if (this->operator()(v, w).first == 1) {
            if (color[w] == Color::BLUE) {
                parent[w] = v;
                if (this->cycleVisit(w, color, parent, cycle, v)) {
                    return true;
                }
            } else if (w != prev) {
                cycle.push_back(w);
                return true;
            }

        }
    }

    color[v] = Color::RED;

    vectorUtils<T>::removeElementsFromVector(cycle, v);

    return false;
}

template<typename T>
bool Matrix::Graph<T>::eulerianCycle() {
    Logger::debug("Check if the graph is eulerian...");

    for (size_t j = 0; j < this->size(); j++) {
        T res = 0;
        for (size_t i = 0; i < this->size(); i++) {
            if (this->operator()(j, i).first == 1) {
                res++;
            }
        }

        if (static_cast<int>(res) % 2 != 0) {
            return false;
        }
    }

    return true;
}

template<typename T>
std::vector<T> Matrix::Graph<T>::distanceFrom(T v) {
    Logger::debug("Distance from " + std::to_string(v) + " algorithm starting...");
    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);
    std::vector<T> distance = std::vector<T>(this->size());

    this->distanceFromSourceVisit(v, color, parent, distance);

    return distance;
}

template<typename T>
void Matrix::Graph<T>::distanceFromSourceVisit(T v, std::vector<Color> &color, std::vector<T> &parent,
                                               std::vector<T> &distance) {
    std::queue<T> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        T w = q.front();
        q.pop();
        for (size_t z = 0; z < this->size(); z++) {
            if (this->operator()(w, z).first == 1) {
                if (color[z] == Color::BLUE) {
                    color[z] = Color::WHITE;
                    parent[z] = w;
                    distance[z] = distance[w] + this->at(w, z).second;
                    q.push(z);
                }
            }
        }
        color[w] = Color::RED;
    }
}

template<typename T>
std::vector<T> Matrix::Graph<T>::distanceFromSource() {
    return this->distanceFrom(0);
}

template<typename T>
std::pair<T, std::pair<T, T>> Matrix::Graph<T>::longestPath() {
    Logger::debug("Longest path algorithm starting...");
    if (this->_d != Type::DIRECTED) {
        std::cout << "" << std::endl;
        throw std::invalid_argument("The graph must be directed");
    }

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);
    std::pair<T, std::pair<T, T>> lPath = {0, {0, 0}};
    std::pair<T, std::pair<T, T>> actualPath = {0, {0, 0}};

    for (size_t v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            actualPath = {0, {v, v}};
            this->longestPathVisit(v, color, parent, lPath, actualPath, -1);
        }
    }

    return lPath;
}

template<typename T>
void Matrix::Graph<T>::longestPathVisit(T v, std::vector<Color> &color, std::vector<T> &parent,
                                        std::pair<T, std::pair<T, T>> &lPath,
                                        std::pair<T, std::pair<T, T>> actualPath, T previous) {
    color[v] = Color::WHITE;
    actualPath.first += 1;

    for (size_t w = 0; w < this->size(); w++) {
        if (this->operator()(v, w).first == 1) {
            if (w != previous) {
                actualPath.second.second = w;

                if (actualPath.first > lPath.first) {
                    lPath = actualPath;
                }
            }

            if (w != previous) {
                parent[w] = v;
                this->longestPathVisit(w, color, parent, lPath, actualPath, v);
            }
        }
    }
    color[v] = Color::RED;
}

template<typename T>
std::optional<std::pair<T, std::vector<T>>> Matrix::Graph<T>::path(T from, T to) {
    Logger::debug("Path algorithm starting...");
    if (from < 0 || from > this->size() || to < 0 || to > this->size()) {
        throw std::invalid_argument("int param have to be between 0 and the _size of the graph");
    }

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);
    std::pair<T, std::vector<T>> path = {0, {from}};
    std::pair<T, T> param = {from, to};

    return this->pathVisit(from, color, parent, path, param);
}

template<typename T>
std::optional<std::pair<T, std::vector<T>>>
Matrix::Graph<T>::pathVisit(T v, std::vector<Color> &color, std::vector<T> &parent,
                            std::pair<T, std::vector<T>> path, std::pair<T, T> &param) {
    color[v] = Color::WHITE;
    path.first += 1;
    for (size_t w = 0; w < this->size(); w++) {
        if (this->operator()(v, w).first == 1) {
            if (color[w] == Color::BLUE) {
                parent[w] = v;
                path.second.push_back(w);

                if (w == param.second) {
                    return path;
                }

                auto newPath = this->pathVisit(w, color, parent, path, param);
                if (newPath.has_value()) {
                    return newPath;
                } else {
                    path.second.pop_back();
                }
            }
        }
    }

    color[v] = Color::RED;
    return std::nullopt;
}

template<typename T>
std::optional<T> Matrix::Graph<T>::blackHole() {
    Logger::debug("Black hole algorithm starting...");
    int candidate = 0;
    for (size_t i = 1; i < this->size(); i++) {
        if (this->_m[candidate * this->size() + i].first == 1) {
            Logger::debug("New candidate : " + std::to_string(i) + " with " + std::to_string(this->_m[candidate * this->size() + i].first) + " edge(s)");
            candidate = i;
        }
    }

    bool Ok = true;

    for (size_t i = 1; i < this->size(); i++) {
        if (this->_m[candidate * this->size() + i].first == 1 || this->_m[i * this->size() + candidate].first == 0) {
            Logger::debug("Candidate " + std::to_string(candidate) + " is not a black hole");
            Ok = false;
        }
    }

    return Ok ? std::optional<T>(candidate) : std::nullopt;
}

template<typename T>
std::optional<std::pair<T, T>> Matrix::Graph<T>::eccentricity(T v) {
    std::optional<std::pair<T, T>> res;

    auto dist = this->distanceFrom(v);

    for (size_t i = 0; i < this->size(); i++) {
        if (dist[i] > -1 && (!res.has_value() || res.value().first < dist[i]) && i != v) {
            res = {dist[i], i};
        }
    }

    return res;
}

template<typename T>
std::optional<std::pair<T, std::pair<T, T>>> Matrix::Graph<T>::radius() {
    std::optional<std::pair<T, std::pair<T, T>>> minEccentricity;

    for (size_t i = 0; i < this->size(); i++) {
        auto ecc = this->eccentricity(i);
        if (ecc.has_value() && (!minEccentricity.has_value() || minEccentricity.value().first > ecc.value().first)) {
            minEccentricity = {ecc.value().first, {i, ecc.value().second}};
        }
    }

    return minEccentricity;
}

template<typename T>
std::optional<std::pair<T, std::pair<T, T>>> Matrix::Graph<T>::diameter() {
    std::optional<std::pair<T, std::pair<T, T>>> minEccentricity;

    for (size_t i = 0; i < this->size(); i++) {
        auto ecc = this->eccentricity(i);
        if (ecc.has_value() && (!minEccentricity.has_value() || minEccentricity.value().first < ecc.value().first)) {
            minEccentricity = {ecc.value().first, {i, ecc.value().second}};
        }
    }

    return minEccentricity;
}

template<typename T>
Matrix::M<T> Matrix::Graph<T>::matrixPath(T lenght) {
    M<T> res(size(), size());

    res = (*this);

    return res^lenght;
}

template<typename T>
Matrix::M<T> Matrix::Graph<T>::matrixAllPath() {
    M temp(*this);

    for (size_t i = 1; i < this->size(); i++) {
        temp += this->operator^(i);
    }

    return temp;
}

template<typename T>
Matrix::Graph<T> Matrix::Graph<T>::createRandomGraph(int numberOfVertices, Type::Graph directed, double edgeProbability,
                                                     bool includeRandomWeight) {
    Logger::debug("Creating random graph with " + std::to_string(numberOfVertices) + " vertices.");

    if (numberOfVertices <= 0 || edgeProbability < 0.0 || edgeProbability > 1.0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> edgeDist(0.0, 1.0);
    std::uniform_int_distribution<int> weightDist(1, 100); // Random weight between 1 and 100

    Matrix::Graph<T> g = Matrix::Graph<T>(numberOfVertices, directed);
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = i + 1; j < numberOfVertices; j++) {
            if (edgeDist(gen) < edgeProbability) {
                int w = 1;
                if (includeRandomWeight) {
                    w = weightDist(gen);
                }

                g.addEdge(i, j, w);
            }
        }
    }
    return g;
}

template<typename T>
Matrix::Graph<T> Matrix::Graph<T>::createCycleGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight) {
    Logger::debug("Creating cycle graph with " + std::to_string(numberOfVertices) + " vertices.");

    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> weightDist(1, 100); // Random weight between 1 and 100


    Matrix::Graph<T> g = Matrix::Graph<T>(numberOfVertices, directed);
    for (int i = 0; i < numberOfVertices; i++) {
        g.addEdge(i, (i + 1) % numberOfVertices, includeRandomWeight ? weightDist(gen) : 1);
    }
    return g;
}

template<typename T>
Matrix::Graph<T> Matrix::Graph<T>::createBlackHoleGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight, T blackHole) {
    Logger::debug("Creating black hole graph with " + std::to_string(numberOfVertices) + " vertices.\nStarting black hole at " + std::to_string(blackHole));

    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> weightDist(1, 100); // Random weight between 1 and 100

    Matrix::Graph<T> g = Matrix::Graph<T>(numberOfVertices, directed);
    for (T i = 0; i < numberOfVertices; i++) {
        if (i != blackHole) {
            g.addEdge(i, blackHole, includeRandomWeight ? weightDist(gen) : 1);
        }
    }
    return g;
}

template<typename T>
Matrix::Graph<T> Matrix::Graph<T>::createCompleteGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight) {
    Logger::debug("Creating complete graph with " + std::to_string(numberOfVertices) + " vertices.");

    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> weightDist(1, 100); // Random weight between 1 and 100

    Matrix::Graph<T> g = Matrix::Graph<T>(numberOfVertices, directed);
    for (T i = 0; i < numberOfVertices; i++) {
        for (T j = i + 1; j < numberOfVertices; j++) {
            g.addEdge(i, j, includeRandomWeight ? weightDist(gen) : 1);
        }
    }
    return g;
}

template<typename T>
Matrix::Graph<T> Matrix::Graph<T>::createBipartiteGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight) {
    Logger::debug("Creating bipartite graph with " + std::to_string(numberOfVertices) + " vertices");

    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> weightDist(1, 100); // Random weight between 1 and 100

    Matrix::Graph<T> g = Matrix::Graph<T>(numberOfVertices, directed);
    for (T i = 0; i < numberOfVertices / 2; i++) {
        for (T j = numberOfVertices / 2; j < numberOfVertices; j++) {
            g.addEdge(i, j, includeRandomWeight ? weightDist(gen) : 1);
        }
    }
    return g;
}

template<typename T>
Matrix::Graph<T> Matrix::Graph<T>::createStarGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight) {
    Logger::debug("Creating star graph with " + std::to_string(numberOfVertices) + " vertices");

    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> weightDist(1, 100); // Random weight between 1 and 100

    Matrix::Graph<T> g = Matrix::Graph<T>(numberOfVertices, directed);
    for (T i = 1; i < numberOfVertices; i++) {
        g.addEdge(0, i, includeRandomWeight ? weightDist(gen) : 1);
    }
    return g;
}

template<typename T>
Type::Graph Matrix::Graph<T>::directed() const {
    return this->_d;
}

template<typename T>
size_t Matrix::Graph<T>::size() const {
    return this->_size;
}

template<typename T>
std::vector<std::pair<T, T>> Matrix::Graph<T>::operator[](T vertex) const {
    std::vector<std::pair<T, T>> res;

    for (size_t i = 0; i < this->size(); i++) {
        if (this->at(vertex, i).first == 1) {
            res.push_back(std::make_pair(i ,this->at(vertex, i).second));
        }
    }

    return res;
}