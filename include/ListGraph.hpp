#pragma once

#include "Utils.hpp"
#include "Logger.hpp"

#include <queue>
#include <stack>
#include <optional>
#include <exception>
#include <iostream>
#include <random>

namespace List {
    template<typename T>
    class Graph {
    private:
        std::vector<std::vector<std::pair<T, T>>> adjList;
        size_t _size;

    protected:
        Type::Graph _d;

        void BFSVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &res);

        void DFSVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &res, Type::Print type);

        void DFSVisitStack(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &res, Type::Print type);

        bool cycleVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &cycle, T prev);

        void distanceFromSourceVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &distance);

        bool isBipartiteVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<Color> &partie);

        void longestPathVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::pair<T, std::pair<T, T>> &lPath, std::pair<T, std::pair<T, T>> actualPath, T previous);

        std::optional<std::pair<T, std::vector<T>>> pathVisitBFS(T v, std::vector<Color> &color, std::vector<T> &parent, std::pair<T, std::vector<T>> path, std::pair<T, T> &param);

    public:
        Graph();

        /**
         * @brief Create a graph
         * @param directed -> the type of the graph DIRECTED or UNDIRECTED, default UNDIRECTED
         */
        Graph(int size, Type::Graph directed = Type::UNDIRECTED);

        /**
         * @brief Create a graph from a matrix
         * @param matrix -> the matrix
         * @param directed -> the type of the graph DIRECTED or UNDIRECTED, default UNDIRECTED
         */
        Graph(const Graph& graph);

        ~Graph();

        /**
         * @brief Create a random graph
         * @param numberOfVertices -> the number of vertices
         * @param directed -> the type of the graph DIRECTED or UNDIRECTED, default UNDIRECTED
         * @param edgeProbability -> the probability of an edge to be created, default 0.5
         * @param includeRandomWeight -> if true the weight of the edge will be random, default false
         * @return the random graph
         */

        static List::Graph<T> createRandomGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, double edgeProbability = 0.5, bool includeRandomWeight = false);

        static List::Graph<T> createCycleGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, bool includeRandomWeight = false);

        static List::Graph<T> createBlackHoleGraph(int numberOfVertices, Type::Graph directed = Type::Graph::DIRECTED, bool includeRandomWeight = false, T blackHole = 0);

        static List::Graph<T> createCompleteGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, bool includeRandomWeight = false);

        static List::Graph<T> createBipartiteGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, bool includeRandomWeight = false);

        static List::Graph<T> createStarGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, bool includeRandomWeight = false);

        [[nodiscard]] size_t size() const;

        [[nodiscard]] Type::Graph directed() const;

        std::vector<std::pair<T, T>> operator[](T vertex) const;

        /**
         * @brief Add an edge to the graph
         * @param from -> the starting point
         * @param to -> the ending point
         * @param weight -> the weight of the edge
         */
        void addEdge(T from, T to, T weight = 1.0);

        /**
         * @brief Remove an edge from the graph (hard complexity so use it carefully)
         * @param from -> the starting point
         * @param to -> the ending point
         * @return true if the edge is removed else false
         */
        bool removeEdge(T from, T to);

        bool isEdge(T from, T to);

        /**
         * @brief Get the degres of a vertex
         * @param vertex -> the vertex
         * @return the degres of the vertex
         */
        int degres(T vertex);

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
         * @brief Get the DFS of the graph using a stack
         * @param type PREORDER or POSTORDER
         * @return a vector of the DFS
         */
        std::vector<T> DFS_stack(Type::Print type = Type::Print::PREORDER);

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

        void print();
    };

};

template<typename T>
List::Graph<T>::Graph() : _d(Type::Graph::UNDIRECTED), _size(0) {}

template<typename T>
List::Graph<T>::Graph(int size, Type::Graph directed) :  _d(directed), _size(size) {
    Logger::debug("Creating graph of size " + std::to_string(size) + " and type ...");

    this->adjList = std::vector<std::vector<std::pair<T, T>>>(size);
}

template<typename T>
List::Graph<T>::~Graph() {
    Logger::debug("Deleting graph...");
}

template<typename T>
List::Graph<T>::Graph(const List::Graph<T> &graph) : _size(graph._size), _d(graph._d) {
    Logger::debug("Creating graph from copy...");

    this->adjList = graph.adjList;
}

template<typename T>
void List::Graph<T>::addEdge(T from, T to, T weight) {
    if (from < 0 || from > this->size() - 1) {
        throw std::invalid_argument("'from' need to be between 0 and the _size of the graph - 1");
    } else if (to < 0 || to > this->size() - 1) {
        throw std::invalid_argument("'to' need to be between 0 and the _size of the graph - 1");
    }

    this->adjList[from].emplace_back(to, weight);
    if (this->_d == Type::UNDIRECTED) {
        this->adjList[to].emplace_back(from, weight);
    }
}

template<typename T>
void List::Graph<T>::print() {
    for (int i = 0; i < this->size(); i++) {
        std::cout << i << " : ";
        for (std::pair<T, T> j : this->adjList[i]) {
            std::cout << j.first << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
size_t List::Graph<T>::size() const {
    return this->_size;
}


template<typename T>
std::vector<T> List::Graph<T>::BFS(T start) {
    Logger::debug("BFS algorithm starting...");

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);
    std::vector<T> res;

    this->BFSVisit(start, color, parent, res);
    for (T v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            this->BFSVisit(v, color, parent, res);
        }
    }

    return res;
}

template<typename T>
void List::Graph<T>::BFSVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &res) {
    std::queue<T> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        T w = q.front();
        q.pop();
        for (std::pair<T, T> z : this->adjList[w]) {
            if (color[z.first] == Color::BLUE) {
                color[z.first] = Color::WHITE;
                parent[z.first] = w;
                q.push(z.first);
            }
        }
        color[w] = Color::RED;
        res.push_back(w);
    }
}

template<typename T>
std::vector<T> List::Graph<T>::DFS(T start, Type::Print type) {
    Logger::debug("DFS algorithm starting...");

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);
    std::vector<T> res;

    this->DFSVisit(start, color, parent, res, type);
    for (T v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            this->DFSVisit(v, color, parent, res, type);
        }
    }
    return res;
}

template<typename T>
void List::Graph<T>::DFSVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &res, Type::Print type) {
    color[v] = Color::WHITE;
    if (type == Type::Print::PREORDER) {
        res.push_back(v);
    }
    for (std::pair<T, T> w : this->adjList[v]) {
        if (color[w.first] == Color::BLUE) {
            parent[w.first] = v;
            this->DFSVisit(w.first, color, parent, res, type);
        }
    }
    color[v] = Color::RED;
    if (type == Type::Print::POSTORDER) {
        res.push_back(v);
    }
}

template<typename T>
std::vector<T> List::Graph<T>::DFS_stack(Type::Print type) {
    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);
    std::vector<T> res;

    for (T v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            DFSVisitStack(v, color, parent, res, type);
        }
    }

    return res;
}

template<typename T>
void List::Graph<T>::DFSVisitStack(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &res, Type::Print type) {
    std::stack<T> s;
    color[v] = Color::WHITE;
    s.push(v);
    while (!s.empty()) {
        T w = s.top();
        s.pop();
        if (color[w] == Color::RED) {
            continue;
        }
        for (T i = (T(this->adjList[w].size()) - 1); i >= 0; i--) {
            std::pair<T, T> z = this->adjList[w][i];
            if (color[z.first] != Color::RED) {
                color[z.first] = Color::WHITE;
                parent[z.first] = w;
                s.push(z.first);
            }
        }
        color[w] = Color::RED;
        res.push_back(w);
    }
}

template<typename T>
List::Graph<T> List::Graph<T>::createRandomGraph(int numberOfVertices, Type::Graph directed, double edgeProbability, bool includeRandomWeight) {
    Logger::debug("Creating random graph with " + std::to_string(numberOfVertices) + " vertices and edge probability " + std::to_string(edgeProbability) + "...");

    if (numberOfVertices <= 0 || edgeProbability < 0.0 || edgeProbability > 1.0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> edgeDist(0.0, 1.0);
    std::uniform_int_distribution<T> weightDist(1, 100); // Random weight between 1 and 100

    List::Graph g = List::Graph<T>(numberOfVertices, directed);
    for (T i = 0; i < numberOfVertices; i++) {
        for (T j = i + 1; j < numberOfVertices; j++) {
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
std::optional<std::vector<T>> List::Graph<T>::cycle() {
    Logger::debug("Cycle algorithm starting...");
    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);
    std::vector<T> cycle;

    for (T v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            if (this->cycleVisit(v, color, parent, cycle, -1)) {
                return cycle;
            }
        }
    }
    return std::nullopt;
}

template<typename T>
bool List::Graph<T>::cycleVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<T> &cycle, T prev) {
    color[v] = Color::WHITE;
    if (vectorUtils<T>::isInVector(cycle, v)) {
        cycle.push_back(v);
        return true;
    }

    cycle.push_back(v);

    for (std::pair<T, T> w : this->adjList[v]) {
        if (color[w.first] == Color::BLUE) {
            parent[w.first] = v;
            if (this->cycleVisit(w.first, color, parent, cycle, v)) {
                return true;
            }
        } else if (w.first != prev) {
            cycle.push_back(w.first);
            return true;
        }
    }

    color[v] = Color::RED;

    vectorUtils<T>::removeElementsFromVector(cycle, v);

    return false;
}

template<typename T>
std::vector<T> List::Graph<T>::distanceFrom(T v) {
    Logger::debug("Distance from " + std::to_string(v) + " algorithm starting...");
    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);
    std::vector<T> distance = std::vector<T>(this->size());

    this->distanceFromSourceVisit(v, color, parent, distance);

    return distance;
}

template<typename T>
std::vector<T> List::Graph<T>::distanceFromSource() {
    return this->distanceFrom(0);
}

template<typename T>
void List::Graph<T>::distanceFromSourceVisit(T v, std::vector<Color> &color, std::vector<T> &parent,
                                          std::vector<T> &distance) {
    std::queue<T> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        T w = q.front();
        q.pop();
        for (std::pair<T, T> z : this->adjList[w]) {
            if (color[z.first] == Color::BLUE) {
                color[z.first] = Color::WHITE;
                parent[z.first] = w;
                distance[z.first] = distance[w] + z.second;
                q.push(z.first);
            }
        }
        color[w] = Color::RED;
    }
}

template<typename T>
bool List::Graph<T>::isBipartite() {
    Logger::debug("Bipartite algorithm starting...");
    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<Color> partie = std::vector<Color>(this->size(), Color::NONE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);

    for (T v = 0; v < this->size(); v++) {
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
bool List::Graph<T>::isBipartiteVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::vector<Color> &partie) {
    std::queue<T> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        T w = q.front();
        q.pop();
        Color nextColor = partie[w] == Color::BLUE ? Color::RED : Color::BLUE;
        for (std::pair<T, T> z : this->adjList[w]) {

            // PART TO CHECK IF THE GRAPH IS BIPARTITE
            if (partie[z.first] != Color::NONE) {
                if (partie[z.first] == partie[w]) {
                    Logger::debug("The graph is not bipartite");
                    return false;
                }
            } else {
                partie[z.first] = nextColor;
            }

            if (color[z.first] == Color::BLUE) {
                color[z.first] = Color::WHITE;
                parent[z.first] = w;
                q.push(z.first);
            }
        }
        color[w] = Color::RED;
    }
    return true;
}

template<typename T>
std::pair<T, std::pair<T, T>> List::Graph<T>::longestPath() {
    Logger::debug("Longest path algorithm starting...");
    if (this->_d != Type::DIRECTED) {
        std::cout << "" << std::endl;
        throw std::invalid_argument("The graph must be directed");
    }

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);
    std::pair<T, std::pair<T, T>> lPath = {0, {0, 0}};
    std::pair<T, std::pair<T, T>> actualPath = {0, {0, 0}};

    for (T v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            actualPath = {0, {v, v}};
            this->longestPathVisit(v, color, parent, lPath, actualPath, -1);
        }
    }

    return lPath;
}

template<typename T>
void List::Graph<T>::longestPathVisit(T v, std::vector<Color> &color, std::vector<T> &parent, std::pair<T, std::pair<T, T>> &lPath, std::pair<T, std::pair<T, T>> actualPath, T previous) {
    color[v] = Color::WHITE;
    actualPath.first += 1;

    for (std::pair<T, T> w : this->adjList[v]) {
        if (w.first != previous) {
            Logger::debug("New path found : " + std::to_string(actualPath.first) + " from " + std::to_string(actualPath.second.first) + " to " + std::to_string(actualPath.second.second));
            actualPath.second.second = w.first;

            if (actualPath.first > lPath.first) {
                lPath = actualPath;
            }
        }

        if (w.first != previous) {
            Logger::debug("New path found : " + std::to_string(actualPath.first) + " from " + std::to_string(actualPath.second.first) + " to " + std::to_string(actualPath.second.second));
            parent[w.first] = v;
            this->longestPathVisit(w.first, color, parent, lPath, actualPath, v);
        }
    }
    color[v] = Color::RED;
}

template<typename T>
std::optional<std::pair<T, std::vector<T>>> List::Graph<T>::path(T from, T to) {
    Logger::debug("Path algorithm starting...");
    if (from < 0 || from > this->size() || to < 0 || to > this->size()) {
        throw std::invalid_argument("int param have to be between 0 and the _size of the graph");
    }

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<T> parent = std::vector<T>(this->size(), -1);
    std::pair<T, std::vector<T>> path = {0, {from}};
    std::pair<T, T> param = {from, to};

    return this->pathVisitBFS(from, color, parent, path, param);
}

template<typename T>
std::optional<std::pair<T, std::vector<T>>> List::Graph<T>::pathVisitBFS(T v, std::vector<Color> &color, std::vector<T> &parent, std::pair<T, std::vector<T>> path, std::pair<T, T> &param) {

    std::vector<T> distance = std::vector<T>(this->size());
    std::queue<T> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        T w = q.front();
        q.pop();
        for (std::pair<T, T> z : this->adjList[w]) {
            if (color[z.first] == Color::BLUE) {
                color[z.first] = Color::WHITE;
                parent[z.first] = w;
                distance[z.first] = distance[w] + z.second;
                q.push(z.first);

                if (z.first == param.second) {
                    Logger::debug("Path found !");
                    path.second = {};
                    T tmp = z.first;
                    while (tmp != -1) {
                        path.second.insert(path.second.begin(), tmp);
                        tmp = parent[tmp];
                    }

                    path.first = distance[z.first];
                    return path;
                }
            }
        }
        color[w] = Color::RED;
    }

    return std::nullopt;
}


template<typename T>
bool List::Graph<T>::removeEdge(T from, T to) {
    Logger::debug("Removing edge " + std::to_string(from) + " -> " + std::to_string(to));
    if (from < 0 || from > this->size() - 1) {
        throw std::invalid_argument("'from' need to be between 0 and the _size of the graph - 1");
    } else if (to < 0 || to > this->size() - 1) {
        throw std::invalid_argument("'to' need to be between 0 and the _size of the graph - 1");
    }

    bool res = false;
    for (T i = 0; i < this->adjList[from].size(); i++) {
        if (this->adjList[from][i].first == to) {
            this->adjList[from].erase(this->adjList[from].begin() + i);
            res = true;
        }
    }

    if (!res) {
        Logger::debug("Edge " + std::to_string(from) + " -> " + std::to_string(to) + " not found");
        return false;
    }

    if (this->_d == Type::UNDIRECTED) {
        res = false;

        for (T i = 0; i < this->adjList[to].size(); i++) {
            if (this->adjList[to][i].first == from) {
                this->adjList[to].erase(this->adjList[to].begin() + i);
                res = true;
            }
        }
    }

    return res;
}

template<typename T>
bool List::Graph<T>::eulerianCycle() {
    Logger::debug("Eulerian cycle algorithm starting...");
    for (const auto& u : this->adjList) {
        if (u.size() % 2 != 0) {
            Logger::debug("The graph is not eulerian");
            return false;
        }
    }

    return true;
}

template<typename T>
std::optional<T> List::Graph<T>::blackHole() {
    Logger::debug("Black hole algorithm starting...");
    T candidate = 0;
    for (T i = 1; i < this->size(); i++) {
        for (T u : this->adjList[candidate]) {
            if (u.first == i) {
                Logger::debug("New candidate : " + std::to_string(i));
                candidate = i;
            }
        }
    }

    bool Ok = true;

    if (!this->adjList[candidate].empty()) {
        return std::nullopt;
    }

    for (T i = 0; i < this->size(); i++) {
        if (i != candidate) {
            bool find = false;
            for (auto u : this->adjList[i]) {
                if (u.first == candidate) {
                    Logger::debug("Candidate " + std::to_string(candidate) + " is connected to " + std::to_string(i));
                    find = true;
                }
            }
            if (!find) {
                Ok = false;
                Logger::debug("Candidate " + std::to_string(candidate) + " is not connected to " + std::to_string(i));
                break;
            }
        }
    }

    return Ok ? std::optional<T>(candidate) : std::nullopt;
}

template<typename T>
std::optional<std::pair<T, T>> List::Graph< T>::eccentricity(T v) {
    std::optional<std::pair<T, T>> res;

    std::vector<T> dist = this->distanceFrom(v);

    for (T i = 0; i < this->size(); i++) {
        if (dist[i] > -1 && (!res.has_value() || res.value().first < dist[i]) && i != v) {
            res = {dist[i], i};
        }
    }

    return res;
}

template<typename T>
std::optional<std::pair<T, std::pair<T, T>>> List::Graph<T>::radius() {
    std::optional<std::pair<T, std::pair<T, T>>> minEccentricity;

    for (T i = 0; i < this->size(); i++) {
        auto ecc = this->eccentricity(i);
        if (ecc.has_value() && (!minEccentricity.has_value() || minEccentricity.value().first > ecc.value().first)) {
            minEccentricity = {ecc.value().first, {i, ecc.value().second}};
        }
    }

    return minEccentricity;
}

template<typename T>
std::optional<std::pair<T, std::pair<T, T>>> List::Graph<T>::diameter() {
    std::optional<std::pair<T, std::pair<T, T>>> minEccentricity;

    for (T i = 0; i < this->size(); i++) {
        auto ecc = this->eccentricity(i);
        if (ecc.has_value() && (!minEccentricity.has_value() || minEccentricity.value().first < ecc.value().first)) {
            minEccentricity = {ecc.value().first, {i, ecc.value().second}};
        }
    }

    return minEccentricity;
}

template<typename T>
int List::Graph<T>::degres(T vertex) {
    if (vertex < 0 || vertex > this->size()) {
        throw std::invalid_argument("'edge' must be between 0 and the size of the graph !");
    }

    return int(this->adjList[vertex].size());
}

template<typename T>
Type::Graph List::Graph<T>::directed() const {
    return _d;
}

template<typename T>
std::vector<std::pair<T, T>> List::Graph<T>::operator[](T vertex) const {
    return this->adjList[vertex];
}

template<typename T>
bool List::Graph<T>::isEdge(T from, T to) {
    std::ranges::any_of(this->adjList[from], [to](std::pair<T, T> u) {
        return u.first == to;
    });
    return false;
}

template<typename T>
List::Graph<T> List::Graph<T>::createCycleGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight) {
    Logger::debug("Creating cycle graph with " + std::to_string(numberOfVertices) + " vertices.");

    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> weightDist(1, 100); // Random weight between 1 and 100


    List::Graph g = List::Graph<T>(numberOfVertices, directed);
    for (int i = 0; i < numberOfVertices; i++) {
        g.addEdge(i, (i + 1) % numberOfVertices, includeRandomWeight ? weightDist(gen) : 1);
    }
    return g;
}

template<typename T>
List::Graph<T> List::Graph<T>::createBlackHoleGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight, T blackHole) {
    Logger::debug("Creating black hole graph with " + std::to_string(numberOfVertices) + " vertices.\nStarting black hole at " + std::to_string(blackHole));

    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> weightDist(1, 100); // Random weight between 1 and 100

    List::Graph g = List::Graph<T>(numberOfVertices, directed);
    for (T i = 0; i < numberOfVertices; i++) {
        if (i != blackHole) {
            g.addEdge(i, blackHole, includeRandomWeight ? weightDist(gen) : 1);
        }
    }
    return g;
}

template<typename T>
List::Graph<T> List::Graph<T>::createCompleteGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight) {
    Logger::debug("Creating complete graph with " + std::to_string(numberOfVertices) + " vertices.");

    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> weightDist(1, 100); // Random weight between 1 and 100

    List::Graph g = List::Graph<T>(numberOfVertices, directed);
    for (T i = 0; i < numberOfVertices; i++) {
        for (T j = i + 1; j < numberOfVertices; j++) {
            g.addEdge(i, j, includeRandomWeight ? weightDist(gen) : 1);
        }
    }
    return g;
}

template<typename T>
List::Graph<T> List::Graph<T>::createBipartiteGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight) {
    Logger::debug("Creating bipartite graph with " + std::to_string(numberOfVertices) + " vertices");

    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> weightDist(1, 100); // Random weight between 1 and 100

    List::Graph g = List::Graph<T>(numberOfVertices, directed);
    for (T i = 0; i < numberOfVertices / 2; i++) {
        for (T j = numberOfVertices / 2; j < numberOfVertices; j++) {
            g.addEdge(i, j, includeRandomWeight ? weightDist(gen) : 1);
        }
    }
    return g;
}

template<typename T>
List::Graph<T> List::Graph<T>::createStarGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight) {
    Logger::debug("Creating star graph with " + std::to_string(numberOfVertices) + " vertices");

    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> weightDist(1, 100); // Random weight between 1 and 100

    List::Graph g = List::Graph<T>(numberOfVertices, directed);
    for (T i = 1; i < numberOfVertices; i++) {
        g.addEdge(0, i, includeRandomWeight ? weightDist(gen) : 1);
    }
    return g;
}
