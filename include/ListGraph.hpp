#pragma once

#include "Utils.hpp"

#include <queue>
#include <stack>
#include <optional>
#include <exception>
#include <iostream>
#include <random>

namespace List {
    class Graph {
    private:
        std::vector<std::vector<edge>> adjList;
        int _size;

    protected:
        Type::Graph _d;

        void BFSVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res);

        void DFSVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res, Type::Print type);

        void DFSVisitStack(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res, Type::Print type);

        bool cycleVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &cycle, int prev);

        void distanceFromSourceVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<double> &distance);

        bool isBipartiteVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<Color> &partie);

        void longestPathVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::pair<int, std::pair<int, int>> &lPath, std::pair<int, std::pair<int, int>> actualPath, int previous);

        std::optional<std::pair<int, std::vector<int>>> pathVisitDFS(int v, std::vector<Color> &color, std::vector<int> &parent, std::pair<int, std::vector<int>> path, std::pair<int, int> &param);

        std::optional<std::pair<int, std::vector<int>>> pathVisitBFS(int v, std::vector<Color> &color, std::vector<int> &parent, std::pair<int, std::vector<int>> path, std::pair<int, int> &param);

    public:
        Graph();

        /**
         * @brief Create a graph
         * @param size -> the size of the graph
         * @param directed -> the type of the graph DIRECTED or UNDIRECTED, default UNDIRECTED
         */
        Graph(int size, Type::Graph directed = Type::UNDIRECTED);

        /**
         * @brief Create a graph from a matrix
         * @param matrix -> the matrix
         * @param directed -> the type of the graph DIRECTED or UNDIRECTED, default UNDIRECTED
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
        static List::Graph createRandomGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, double edgeProbability = 0.5, bool includeRandomWeight = false);

        static List::Graph createCycleGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, bool includeRandomWeight = false);

        static List::Graph createBlackHoleGraph(int numberOfVertices, Type::Graph directed = Type::Graph::DIRECTED, bool includeRandomWeight = false, int blackHole = 0);

        static List::Graph createCompleteGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, bool includeRandomWeight = false);

        static List::Graph createBipartiteGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, bool includeRandomWeight = false);

        /**
         * @brief Get the size of the graph
         * @return the size of the graph
         */
        [[nodiscard]] int size() const;

        [[nodiscard]] Type::Graph directed() const;

        std::vector<edge> operator[](int vertex) const;

        /**
         * @brief Add an edge to the graph
         * @param from -> the starting point
         * @param to -> the ending point
         * @param weight -> the weight of the edge
         */
        void addEdge(int from, int to, double weight = 1.0);

        /**
         * @brief Remove an edge from the graph (hard complexity so use it carefully)
         * @param from -> the starting point
         * @param to -> the ending point
         * @return true if the edge is removed else false
         */
        bool removeEdge(int from, int to);

        bool isEdge(int from, int to);

        /**
         * @brief Get the degres of a vertex
         * @param vertex -> the vertex
         * @return the degres of the vertex
         */
        int degres(int vertex);

        /**
         * @brief Get the BFS of the graph
         * @return a vector of the BFS
         */
        std::vector<int> BFS(int start = 0);

        /**
         * @brief Get the DFS of the graph
         * @param type PREORDER or POSTORDER
         * @return a vector of the DFS
         */
        std::vector<int> DFS(int start = 0, Type::Print type = Type::Print::PREORDER);

        /**
         * @brief Get the DFS of the graph using a stack
         * @param type PREORDER or POSTORDER
         * @return a vector of the DFS
         */
        std::vector<int> DFS_stack(Type::Print type = Type::Print::PREORDER);

        /**
         * @brief Check if the graph is bipartite
         * @return true if the graph is bipartite else false
         */
        bool isBipartite();

        /**
         * @brief Check if the graph has a cycle
         * @return a vector of edges of the cycle if exist else nothing
         */
        std::optional<std::vector<int>> cycle();

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
        std::vector<double> distanceFrom(int v);

        /**
         * @brief Distance from 0
         * @return a vector of the distance from 0
         */
        std::vector<double> distanceFromSource();

        /**
         * @brief Return the longest path
         * @return std::pair(length of the path, std::pair(from, to))
         * work with a directed graph without cycle (DAG)
         */
        std::pair<int, std::pair<int, int>> longestPath();

        /**
         * @brief Return the longest path
         * @param from -> the starting point
         * @param to -> the ending point
         * @return std::pair(length of the path, std::vector(vertices of the path))
         */
        std::optional<std::pair<int, std::vector<int>>> path(int from, int to, bool bfs = true);

        /**
         * @brief Check if any vertex is a black hole
         * @return the black hole vertex or nothing
         */
        std::optional<int> blackHole();

        /**
         * @brief Get the eccentricity of a vertex
         * @param v -> the vertex
         * @return std::pair(distance, longest vertex)
         */
        std::optional<std::pair<double, int>> eccentricity(int v);

        /**
         * @brief Get the radius of the graph
         * @return std::pair(distance, std::pair(from, to))
         * NOT linear complexity
         */
        std::optional<std::pair<double, std::pair<int, int>>> radius();

        /**
         * @brief Get the diameter of the graph
         * @return std::pair(distance, std::pair(from, to))
         * NOT linear complexity
         */
        std::optional<std::pair<double, std::pair<int, int>>> diameter();

        void print();
    };
};


List::Graph::Graph() : _size(0), _d(Type::Graph::UNDIRECTED) {}

List::Graph::Graph(int size, Type::Graph directed) : _size(size), _d(directed) {
    this->adjList = std::vector<std::vector<edge>>(size);
}

List::Graph::Graph(const List::Graph &graph) {
    this->_size = graph._size;
    this->_d = graph._d;
    this->adjList = graph.adjList;
}

void List::Graph::addEdge(int from, int to, double weight) {
    if (from < 0 || from > this->_size - 1) {
        throw std::invalid_argument("'from' need to be between 0 and the _size of the graph - 1");
    } else if (to < 0 || to > this->_size - 1) {
        throw std::invalid_argument("'to' need to be between 0 and the _size of the graph - 1");
    }

    this->adjList[from].emplace_back(to, weight);
    if (this->_d == Type::UNDIRECTED) {
        this->adjList[to].emplace_back(from, weight);
    }
}

void List::Graph::print() {
    for (int i = 0; i < this->_size; i++) {
        std::cout << i << " : ";
        for (std::pair<int, int> j : this->adjList[i]) {
            std::cout << j.first << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<int> List::Graph::BFS(int start) {
    std::vector<Color> color = std::vector<Color>(this->_size, Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->_size, -1);
    std::vector<int> res;

    this->BFSVisit(start, color, parent, res);
    for (int v = 0; v < this->_size; v++) {
        if (color[v] == Color::BLUE) {
            this->BFSVisit(v, color, parent, res);
        }
    }

    return res;
}

void List::Graph::BFSVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res) {
    std::queue<int> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        int w = q.front();
        q.pop();
        for (std::pair<int, int> z : this->adjList[w]) {
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

std::vector<int> List::Graph::DFS(int start, Type::Print type) {
    std::vector<Color> color = std::vector<Color>(this->_size, Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->_size, -1);
    std::vector<int> res;

    this->DFSVisit(start, color, parent, res, type);
    for (int v = 0; v < this->_size; v++) {
        if (color[v] == Color::BLUE) {
            this->DFSVisit(v, color, parent, res, type);
        }
    }
    return res;
}

void List::Graph::DFSVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res, Type::Print type) {
    color[v] = Color::WHITE;
    if (type == Type::Print::PREORDER) {
        res.push_back(v);
    }
    for (edge w : this->adjList[v]) {
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

std::vector<int> List::Graph::DFS_stack(Type::Print type) {
    std::vector<Color> color = std::vector<Color>(this->_size, Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->_size, -1);
    std::vector<int> res;

    for (int v = 0; v < this->_size; v++) {
        if (color[v] == Color::BLUE) {
            DFSVisitStack(v, color, parent, res, type);
        }
    }

    return res;
}

void List::Graph::DFSVisitStack(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res, Type::Print type) {
    std::stack<int> s;
    color[v] = Color::WHITE;
    s.push(v);
    while (!s.empty()) {
        int w = s.top();
        s.pop();
        if (color[w] == Color::RED) {
            continue;
        }
        for (int i = (int(this->adjList[w].size()) - 1); i >= 0; i--) {
            edge z = this->adjList[w][i];
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

List::Graph List::Graph::createRandomGraph(int numberOfVertices, Type::Graph directed, double edgeProbability, bool includeRandomWeight) {
    if (numberOfVertices <= 0 || edgeProbability < 0.0 || edgeProbability > 1.0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> edgeDist(0.0, 1.0);
    std::uniform_int_distribution<int> weightDist(1, 100); // Random weight between 1 and 100

    List::Graph g = List::Graph(numberOfVertices, directed);
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

std::optional<std::vector<int>> List::Graph::cycle() {
    std::vector<Color> color = std::vector<Color>(this->_size, Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->_size, -1);
    std::vector<int> cycle;

    for (int v = 0; v < this->_size; v++) {
        if (color[v] == Color::BLUE) {
            if (this->cycleVisit(v, color, parent, cycle, -1)) {
                return cycle;
            }
        }
    }
    return std::nullopt;
}

bool List::Graph::cycleVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &cycle, int prev) {
    color[v] = Color::WHITE;
    if (vectorUtils<int>::isInVector(cycle, v)) {
        cycle.push_back(v);
        return true;
    }

    cycle.push_back(v);

    for (edge w : this->adjList[v]) {
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

    vectorUtils<int>::removeElementsFromVector(cycle, v);

    return false;
}

std::vector<double> List::Graph::distanceFrom(int v) {
    std::vector<Color> color = std::vector<Color>(this->_size, Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->_size, -1);
    std::vector<double> distance = std::vector<double>(this->_size);

    this->distanceFromSourceVisit(v, color, parent, distance);

    return distance;
}

std::vector<double> List::Graph::distanceFromSource() {
    return this->distanceFrom(0);
}

void List::Graph::distanceFromSourceVisit(int v, std::vector<Color> &color, std::vector<int> &parent,
                                          std::vector<double> &distance) {
    std::queue<int> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        int w = q.front();
        q.pop();
        for (edge z : this->adjList[w]) {
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

bool List::Graph::isBipartite() {
    std::vector<Color> color = std::vector<Color>(this->_size, Color::BLUE);
    std::vector<Color> partie = std::vector<Color>(this->_size, Color::NONE);
    std::vector<int> parent = std::vector<int>(this->_size, -1);

    for (int v = 0; v < this->_size; v++) {
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

bool List::Graph::isBipartiteVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<Color> &partie) {
    std::queue<int> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        int w = q.front();
        q.pop();
        Color nextColor = partie[w] == Color::BLUE ? Color::RED : Color::BLUE;
        for (edge z : this->adjList[w]) {

            // PART TO CHECK IF THE GRAPH IS BIPARTITE
            if (partie[z.first] != Color::NONE) {
                if (partie[z.first] == partie[w]) {
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

std::pair<int, std::pair<int, int>> List::Graph::longestPath() {
    if (this->_d != Type::DIRECTED) {
        std::cout << "" << std::endl;
        throw std::invalid_argument("The graph must be directed");
    }

    std::vector<Color> color = std::vector<Color>(this->_size, Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->_size, -1);
    std::pair<int, std::pair<int, int>> lPath = {0, {0, 0}};
    std::pair<int, std::pair<int, int>> actualPath = {0, {0, 0}};

    for (int v = 0; v < this->_size; v++) {
        if (color[v] == Color::BLUE) {
            actualPath = {0, {v, v}};
            this->longestPathVisit(v, color, parent, lPath, actualPath, -1);
        }
    }

    return lPath;
}

void List::Graph::longestPathVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::pair<int, std::pair<int, int>> &lPath, std::pair<int, std::pair<int, int>> actualPath, int previous) {
    color[v] = Color::WHITE;
    actualPath.first += 1;

    for (edge w : this->adjList[v]) {
        if (w.first != previous) {
            actualPath.second.second = w.first;

            if (actualPath.first > lPath.first) {
                lPath = actualPath;
            }
        }

        if (w.first != previous) {
            parent[w.first] = v;
            this->longestPathVisit(w.first, color, parent, lPath, actualPath, v);
        }
    }
    color[v] = Color::RED;
}

std::optional<std::pair<int, std::vector<int>>> List::Graph::path(int from, int to, bool bfs) {
    if (from < 0 || from > this->_size || to < 0 || to > this->_size) {
        throw std::invalid_argument("int param have to be between 0 and the _size of the graph");
    }

    std::vector<Color> color = std::vector<Color>(this->_size, Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->_size, -1);
    std::pair<int, std::vector<int>> path = {0, {from}};
    std::pair<int, int> param = {from, to};

    if (bfs) {
        return this->pathVisitBFS(from, color, parent, path, param);
    } else {
        return this->pathVisitDFS(from, color, parent, path, param);
    }
}

std::optional<std::pair<int, std::vector<int>>> List::Graph::pathVisitDFS(int v, std::vector<Color> &color, std::vector<int> &parent, std::pair<int, std::vector<int>> path, std::pair<int, int> &param) {

    color[v] = Color::WHITE;
    path.first += 1;
    for (edge w : this->adjList[v]) {
        if (color[w.first] == Color::BLUE) {
            parent[w.first] = v;
            path.second.push_back(w.first);

            if (w.first == param.second) {
                return path;
            }

            auto newPath = this->pathVisitDFS(w.first, color, parent, path, param);
            if (newPath.has_value()) {
                return newPath;
            } else {
                path.second.pop_back();
            }
        }
    }
    color[v] = Color::RED;
    return std::nullopt;
}

std::optional<std::pair<int, std::vector<int>>> List::Graph::pathVisitBFS(int v, std::vector<Color> &color, std::vector<int> &parent, std::pair<int, std::vector<int>> path, std::pair<int, int> &param) {

    std::vector<double> distance = std::vector<double>(this->_size);
    std::queue<int> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        int w = q.front();
        q.pop();
        for (edge z : this->adjList[w]) {
            if (color[z.first] == Color::BLUE) {
                color[z.first] = Color::WHITE;
                parent[z.first] = w;
                distance[z.first] = distance[w] + z.second;
                q.push(z.first);

                if (z.first == param.second) {
                    path.second = {};
                    auto tmp = z.first;
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

int List::Graph::size() const {
    return _size;
}

bool List::Graph::removeEdge(int from, int to) {
    if (from < 0 || from > this->_size - 1) {
        throw std::invalid_argument("'from' need to be between 0 and the _size of the graph - 1");
    } else if (to < 0 || to > this->_size - 1) {
        throw std::invalid_argument("'to' need to be between 0 and the _size of the graph - 1");
    }

    bool res = false;
    for (int i = 0; i < this->adjList[from].size(); i++) {
        if (this->adjList[from][i].first == to) {
            this->adjList[from].erase(this->adjList[from].begin() + i);
            res = true;
        }
    }
    if (!res) return false;

    if (this->_d == Type::UNDIRECTED) {
        res = false;

        for (int i = 0; i < this->adjList[to].size(); i++) {
            if (this->adjList[to][i].first == from) {
                this->adjList[to].erase(this->adjList[to].begin() + i);
                res = true;
            }
        }
    }

    return res;
}

bool List::Graph::eulerianCycle() {
    for (const auto& u : this->adjList) {
        if (u.size() % 2 != 0) {
            return false;
        }
    }

    return true;
}

std::optional<int> List::Graph::blackHole() {
    int candidate = 0;
    for (int i = 1; i < this->size(); i++) {
        for (auto u : this->adjList[candidate]) {
            if (u.first == i) {
                candidate = i;
            }
        }
    }

    bool Ok = true;

    if (!this->adjList[candidate].empty()) {
        return std::nullopt;
    }

    for (int i = 0; i < this->size(); i++) {
        if (i != candidate) {
            bool find = false;
            for (auto u : this->adjList[i]) {
                if (u.first == candidate) {
                    find = true;
                }
            }
            if (!find) {
                Ok = false;
            }
        }
    }

    return Ok ? std::optional<int>(candidate) : std::nullopt;
}

std::optional<std::pair<double, int>> List::Graph::eccentricity(int v) {
    std::optional<std::pair<double, int>> res;

    auto dist = this->distanceFrom(v);

    for (int i = 0; i < this->size(); i++) {
        if (dist[i] > -1 && (!res.has_value() || res.value().first < dist[i]) && i != v) {
            res = {dist[i], i};
        }
    }

    return res;
}

std::optional<std::pair<double, std::pair<int, int>>> List::Graph::radius() {
    std::optional<std::pair<double, std::pair<int, int>>> minEccentricity;

    for (int i = 0; i < this->size(); i++) {
        auto ecc = this->eccentricity(i);
        if (ecc.has_value() && (!minEccentricity.has_value() || minEccentricity.value().first > ecc.value().first)) {
            minEccentricity = {ecc.value().first, {i, ecc.value().second}};
        }
    }

    return minEccentricity;
}

std::optional<std::pair<double, std::pair<int, int>>> List::Graph::diameter() {
    std::optional<std::pair<double, std::pair<double, int>>> minEccentricity;

    for (int i = 0; i < this->size(); i++) {
        auto ecc = this->eccentricity(i);
        if (ecc.has_value() && (!minEccentricity.has_value() || minEccentricity.value().first < ecc.value().first)) {
            minEccentricity = {ecc.value().first, {i, ecc.value().second}};
        }
    }

    return minEccentricity;
}

int List::Graph::degres(int vertex) {
    if (vertex < 0 || vertex > this->size()) {
        throw std::invalid_argument("'edge' must be between 0 and the size of the graph !");
    }

    return int(this->adjList[vertex].size());
}

Type::Graph List::Graph::directed() const {
    return _d;
}

std::vector<edge> List::Graph::operator[](int vertex) const {
    return this->adjList[vertex];
}

bool List::Graph::isEdge(int from, int to) {
    std::ranges::any_of(this->adjList[from], [to](edge u) {
        return u.first == to;
    });
    return false;
}

List::Graph List::Graph::createCycleGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight) {
    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> weightDist(1, 100); // Random weight between 1 and 100


    List::Graph g = List::Graph(numberOfVertices, directed);
    for (int i = 0; i < numberOfVertices; i++) {
        g.addEdge(i, (i + 1) % numberOfVertices, includeRandomWeight ? weightDist(gen) : 1);
    }
    return g;
}

List::Graph List::Graph::createBlackHoleGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight, int blackHole) {
    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> weightDist(1, 100); // Random weight between 1 and 100

    List::Graph g = List::Graph(numberOfVertices, directed);
    for (int i = 0; i < numberOfVertices; i++) {
        if (i != blackHole) {
            g.addEdge(i, blackHole, includeRandomWeight ? weightDist(gen) : 1);
        }
    }
    return g;
}

List::Graph List::Graph::createCompleteGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight) {
    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> weightDist(1, 100); // Random weight between 1 and 100

    List::Graph g = List::Graph(numberOfVertices, directed);
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = i + 1; j < numberOfVertices; j++) {
            g.addEdge(i, j, includeRandomWeight ? weightDist(gen) : 1);
        }
    }
    return g;
}

List::Graph List::Graph::createBipartiteGraph(int numberOfVertices, Type::Graph directed, bool includeRandomWeight) {
    if (numberOfVertices <= 0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> weightDist(1, 100); // Random weight between 1 and 100

    List::Graph g = List::Graph(numberOfVertices, directed);
    for (int i = 0; i < numberOfVertices / 2; i++) {
        for (int j = numberOfVertices / 2; j < numberOfVertices; j++) {
            g.addEdge(i, j, includeRandomWeight ? weightDist(gen) : 1);
        }
    }
    return g;
}