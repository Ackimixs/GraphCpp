#include <gtest/gtest.h>
#include "../include/Graph.h"

struct SimpleGraph : public ::testing::Test {
    List::Graph g;
    SimpleGraph() : g(4) {
        g.addEdge(0, 1);
        g.addEdge(1, 2);
        g.addEdge(2, 3);
    }
};

struct ComplexGraph : public ::testing::Test {
    List::Graph g;
    ComplexGraph() : g(18) {
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(0, 4);
        g.addEdge(0, 9);
        g.addEdge(4, 3);
        g.addEdge(4, 5);
        g.addEdge(4, 6);
        g.addEdge(6, 7);
        g.addEdge(9, 8);
        g.addEdge(9, 10);
        g.addEdge(10, 11);
        g.addEdge(11, 12);
        g.addEdge(13, 0);
        g.addEdge(14, 13);
        g.addEdge(15, 0);
        g.addEdge(16, 15);
        g.addEdge(17, 16);
    }
};

struct SimpleGraphDirected : public ::testing::Test {
    List::Graph g;
    SimpleGraphDirected() : g(4, Type::DIRECTED) {
        g.addEdge(0, 1);
        g.addEdge(1, 2);
        g.addEdge(2, 3);
    }
};

struct RandomGraph : public ::testing::Test {
    List::Graph g;
    RandomGraph() : g(List::Graph::createRandomGraph(350, Type::UNDIRECTED, .2)) {}
};


// ----------------- TESTING BFS --------------

TEST_F(SimpleGraph, GrapBFS) {

    std::vector<int> res = {0, 1, 2, 3};

    ASSERT_EQ(g.BFS(), res);
}

TEST_F(RandomGraph, GraphBFS_allEdge) {

    auto res = g.BFS();

    ASSERT_EQ(res.size(), g.size());
}


TEST_F(ComplexGraph, GraphBFS_Length) {

    auto res = g.BFS();

    ASSERT_EQ(res.size(), g.size());
}

// ----------------- TESTING DFS --------------

TEST_F(SimpleGraph, GraphDFS) {

    std::vector<int> res = {0, 1, 2, 3};

    ASSERT_EQ(g.BFS(), res);
}

TEST_F(SimpleGraph, GraphDFS_Stack) {

    std::vector<int> res = {0, 1, 2, 3};

    ASSERT_EQ(g.BFS(), res);
}

TEST_F(RandomGraph, GraphDFS_allEdge) {

    auto res = g.BFS();

    ASSERT_EQ(res.size(), g.size());
}

TEST_F(RandomGraph, GraphDFS_Stack_allEdge) {

    auto res = g.BFS();

    ASSERT_EQ(res.size(), g.size());
}


// ----------------- TESTING PATH --------------

TEST_F(RandomGraph, GraphPath) {
    auto res = g.path(0, 3);

    ASSERT_TRUE(res.has_value());
}

TEST_F(SimpleGraph, GraphPath) {
    auto res = g.path(0, 3);

    ASSERT_EQ(res.value().first, 3);
    ASSERT_EQ(res.value().second, std::vector<int>({0, 1, 2, 3}));
}

TEST_F(SimpleGraph, GraphNoPath) {
    g.removeEdge(1, 2);

    auto res = g.path(0, 3);

    ASSERT_FALSE(res.has_value());
}

TEST_F(ComplexGraph, GraphNotPath) {

    g.removeEdge(10, 11);

    auto res = g.path(17, 12);

    ASSERT_TRUE(res.has_value());
}

TEST_F(SimpleGraphDirected, GraphLongestPath) {

    auto res = g.longestPath();

    ASSERT_EQ(res.first, 3);
    ASSERT_EQ(res.second.first, 0);
    ASSERT_EQ(res.second.second, 3);
}

TEST_F(SimpleGraph, GraphDistanceFromSource) {
    auto res = g.distanceFromSource();

    ASSERT_EQ(res, std::vector<double>({0, 1, 2, 3}));
}


// ----------------- TESTING CYCLE --------------

TEST_F(SimpleGraph, GraphNoCycle) {

    auto res = g.cycle();

    ASSERT_FALSE(res.has_value());
}

TEST_F(ComplexGraph, GrophNoCycle) {
    auto res = g.cycle();

    ASSERT_FALSE(res.has_value());
}

TEST(Graph, GraphCycle) {
    List::Graph g(6);

    g.addEdge(0,1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 4);
    g.addEdge(4, 5);
    g.addEdge(2, 3);

    auto cycle = g.cycle();

    ASSERT_TRUE(cycle.has_value());
}


// ----------------- TESTING BIPARTITE --------------

TEST_F(SimpleGraph, GraphIsBipartite) {
    ASSERT_TRUE(g.isBipartite());
}

TEST_F(SimpleGraph, GraphIsNotBipartite) {
    g.addEdge(1, 3);

    g.addEdge(0, 2);

    ASSERT_FALSE(g.isBipartite());
}

// ----------------- TESTING EULERIAN CYCLE --------------
TEST(Graph, GraphEulerianCycle) {
    List::Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 4);
    g.addEdge(0, 5);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 5);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    ASSERT_TRUE(g.eulerianCycle());
}

TEST(Graph, GraphEulerianCycleNot) {
    List::Graph g(6);

    g.addEdge(0,1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 4);
    g.addEdge(4, 5);

    ASSERT_FALSE(g.eulerianCycle());
}

// ----------------- TESTING BLACK HOLE --------------
TEST(Graph, GraphBlackHole) {
    List::Graph g(6, Type::Graph::DIRECTED);

    g.addEdge(1, 0);
    g.addEdge(2, 0);
    g.addEdge(3, 0);
    g.addEdge(4, 0);
    g.addEdge(1, 4);

    ASSERT_EQ(g.blackHole().value(), 0);
}

// ----------------- TESTING ECCENTRICITY / RADIUS / DIAMETER --------------

TEST_F(SimpleGraph, GraphEccentricity) {
    auto res = g.eccentricity(0);

    ASSERT_TRUE(res.has_value());
    ASSERT_EQ(res.value().first, 3);
    ASSERT_EQ(res.value().second, 3);
}

TEST_F(SimpleGraph, GraphRadius) {
    auto res = g.radius();

    ASSERT_TRUE(res.has_value());
    ASSERT_EQ(res.value().first, 2);
}

TEST_F(SimpleGraph, GraphDiameter) {
    auto res = g.diameter();

    ASSERT_TRUE(res.has_value());
    ASSERT_EQ(res.value().first, 3);
}

TEST_F(ComplexGraph, GraphEccentricity) {
    auto res = g.eccentricity(0);

    ASSERT_TRUE(res.has_value());
    ASSERT_EQ(res.value().first, 4);
    ASSERT_EQ(res.value().second, 12);
}

TEST_F(ComplexGraph, GraphRadius) {
    auto res = g.radius();

    ASSERT_TRUE(res.has_value());
    ASSERT_EQ(res.value().first, 4);
    ASSERT_EQ(res.value().second.first, 0);
    ASSERT_EQ(res.value().second.second, 12);
}

TEST_F(ComplexGraph, GraphDiameter) {
    auto res = g.diameter();

    ASSERT_TRUE(res.has_value());
    ASSERT_EQ(res.value().first, 7);
    ASSERT_EQ(res.value().second.first, 7);
    ASSERT_EQ(res.value().second.second, 12);
}