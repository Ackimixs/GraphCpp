#pragma once

#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <iostream>
#include <chrono>
#include <random>
#include <optional>
#include "Matrix.h"

namespace Type {
    enum Graph {
        UNDIRECTED,
        DIRECTED
    };

    enum Print {
        PREORDER,
        POSTORDER
    };
};

enum Color {
    NONE,
    BLUE,
    WHITE,
    RED
};


typedef std::pair<int, double> edge;

namespace List {
    class Graph {
    private:
        std::vector<std::vector<edge>> adjList;
        int _size;

    protected:
        Type::Graph directed;

        void BFSVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res);

        void DFSVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res, Type::Print type);

        void DFSVisitStack(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res, Type::Print type);

        bool cycleVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &cycle, int prev);

        void distanceFromSourceVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<double> &distance);

        bool isBipartiteVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<Color> &partie);

        void longestPathVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::pair<int, std::pair<int, int>> &lPath, std::pair<int, std::pair<int, int>> actualPath, int previous);

        std::optional<std::pair<int, std::vector<int>>> pathVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::pair<int, std::vector<int>> path, std::pair<int, int> &param);

    public:
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

        /**
         * @brief Get the size of the graph
         * @return the size of the graph
         */
        [[nodiscard]] int size() const;

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
        std::vector<int> BFS();

        /**
         * @brief Get the DFS of the graph
         * @param type PREORDER or POSTORDER
         * @return a vector of the DFS
         */
        std::vector<int> DFS(Type::Print type = Type::Print::PREORDER);

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
        std::optional<std::pair<int, std::vector<int>>> path(int from, int to);

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

namespace Matrix {
    class Graph : public M {
    private:
        Type::Graph directed;

    protected:
        void BFSVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res);

        void DFSVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res, Type::Print type);

        bool cycleVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &cycle, int prev);

        void distanceFromSourceVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<double> &distance);

        bool isBipartiteVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<Color> &partie);

        void longestPathVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::pair<int, std::pair<int, int>> &lPath, std::pair<int, std::pair<int, int>> actualPath, int previous);

        std::optional<std::pair<int, std::vector<int>>> pathVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::pair<int, std::vector<int>> path, std::pair<int, int> &param);

    public:
        /**
         * @brief Create a graph
         * @param n -> the size of the graph
         * @param directed -> the type of the graph DIRECTED or UNDIRECTED, default UNDIRECTED
         */
        Graph(int n, Type::Graph directed = Type::Graph::UNDIRECTED);

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
        static Matrix::Graph createRandomGraph(int numberOfVertices, Type::Graph directed = Type::Graph::UNDIRECTED, double edgeProbability = 0.5, bool includeRandomWeight = false);

        ~Graph();

        int size();

        /**
         * @brief Add an edge to the graph
         * @param from -> the starting point
         * @param to -> the ending point
         * @param weight -> the weight of the edge
         */
        void addEdge(int from, int to, int weight = 1);

        /**
         * @brief Remove an edge from the graph (hard complexity so use it carefully)
         * @param from -> the starting point
         * @param to -> the ending point
         */
        void removeEdge(int from, int to);

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
        std::vector<int> BFS();

        /**
         * @brief Get the DFS of the graph
         * @param type PREORDER or POSTORDER
         * @return a vector of the DFS
         */
        std::vector<int> DFS(Type::Print type = Type::Print::PREORDER);

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
        std::optional<std::pair<int, std::vector<int>>> path(int from, int to);

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

        M matrixPath(int lenght);

        M matrixAllPath();
    };
}


template <typename T>
class vectorUtils {
public:
    /**
     * @brief Remove an element from a vector
     * @param vec -> the vector
     * @param value -> the value to remove
     */
    static void removeElementsFromVector(std::vector<T>& vec, const T& value) {
        vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end());
    }

    /**
     * @brief Remove every element from a vector until a value
     * @param vec -> the vector
     * @param value -> the value to stop
     */
    static void removeElementsUntilValue(std::vector<T>& vec, const T& value) {
        for (typename std::vector<T>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it) {
            if (*it == value) {
                vec.pop_back();
                break;
            }
            vec.pop_back();
        }
    }

    /**
     * @brief Check if a value is in a vector
     * @param vec -> the vector
     * @param value -> the value to check
     * @return true if the value is in the vector else false
     */
    static bool isInVector(std::vector<T> vec, T value) {
        return std::count(vec.begin(), vec.end(), value);
    }

    static T sumOfVector(std::vector<T> vec) {
        int sum = 0;
        for (auto i : vec) {
            sum += i;
        }
        return sum;
    }
};
