#include "../include/MatrixGraph.h"

Matrix::Graph::Graph(int n, Type::Graph directed) : M(n), _d(directed) {
}

Matrix::Graph::Graph(const Graph &graph) : M(graph), _d(graph._d) {
}

Matrix::Graph::~Graph() {
}

int Matrix::Graph::size() {
    return M::size().first;
}

void Matrix::Graph::addEdge(int from, int to, int weight) {
    this->set(from, to, 1);
    if (this->_d == Type::Graph::UNDIRECTED) {
        this->set(to, from, 1);
    }
}

void Matrix::Graph::removeEdge(int from, int to) {
    this->set(from, to, 0);
    if (this->_d == Type::Graph::UNDIRECTED) {
        this->set(to, from, 0);
    }
}

void Matrix::Graph::print() {
    M::print();
}

int Matrix::Graph::degres(int vertex) {
    if (vertex < 0 || vertex > this->size()) {
        throw std::invalid_argument("'edge' must be between 0 and the size of the graph !");
    }

    int res = 0;
    for (int i = 0; i < this->size(); i++) {
        if (this->operator()(vertex, i) == 1) {
            res++;
        }
    }

    return res;
}

std::vector<int> Matrix::Graph::BFS() {
    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->size(), -1);
    std::vector<int> res;

    for (int v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            this->BFSVisit(v, color, parent, res);
        }
    }

    return res;
}

void Matrix::Graph::BFSVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res) {
    std::queue<int> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        int w = q.front();
        q.pop();
        for (int z = 0; z < this->size(); z++) {
            if (this->operator()(v, z) == 1) {
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

std::vector<int> Matrix::Graph::DFS(Type::Print type) {
    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->size(), -1);
    std::vector<int> res;

    for (int v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            this->DFSVisit(v, color, parent, res, type);
        }
    }
    return res;
}

void Matrix::Graph::DFSVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res,
                             Type::Print type) {
    color[v] = Color::WHITE;
    if (type == Type::Print::PREORDER) {
        res.push_back(v);
    }
    for (int w = 0; w < this->size(); w++) {
        if (this->operator()(v, w) == 0) {
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

bool Matrix::Graph::isBipartite() {
    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<Color> partie = std::vector<Color>(this->size(), Color::NONE);
    std::vector<int> parent = std::vector<int>(this->size(), -1);

    for (int v = 0; v < this->size(); v++) {
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

bool Matrix::Graph::isBipartiteVisit(int v, std::vector<Color> &color, std::vector<int> &parent,
                                     std::vector<Color> &partie) {
    std::queue<int> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        int w = q.front();
        q.pop();
        Color nextColor = partie[w] == Color::BLUE ? Color::RED : Color::BLUE;
        for (int z = 0; z < this->size(); z++) {
            if (this->operator()(w, z) == 1) {

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

std::optional<std::vector<int>> Matrix::Graph::cycle() {
    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->size(), -1);
    std::vector<int> cycle;

    for (int v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            if (this->cycleVisit(v, color, parent, cycle, -1)) {
                return cycle;
            }
        }
    }
    return std::nullopt;
}

bool Matrix::Graph::cycleVisit(int v, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &cycle,
                               int prev) {
    color[v] = Color::WHITE;
    if (vectorUtils<int>::isInVector(cycle, v)) {
        cycle.push_back(v);
        return true;
    }

    cycle.push_back(v);

    for (int w = 0; w < this->size(); w++) {
        if (this->operator()(v, w) == 1) {
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

    vectorUtils<int>::removeElementsFromVector(cycle, v);

    return false;
}

bool Matrix::Graph::eulerianCycle() {
    for (int j = 0; j < this->size(); j++) {
        int res = 0;
        for (int i = 0; i < this->size(); i++) {
            if (this->operator()(j, i) == 1) {
                res++;
            }
        }

        if (res % 2 != 0) {
            return false;
        }
    }

    return true;
}

std::vector<double> Matrix::Graph::distanceFrom(int v) {
    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->size(), -1);
    std::vector<double> distance = std::vector<double>(this->size());

    this->distanceFromSourceVisit(v, color, parent, distance);

    return distance;
}

void Matrix::Graph::distanceFromSourceVisit(int v, std::vector<Color> &color, std::vector<int> &parent,
                                            std::vector<double> &distance) {
    std::queue<int> q;
    color[v] = Color::WHITE;
    q.push(v);
    while (!q.empty()) {
        int w = q.front();
        q.pop();
        for (int z = 0; z < this->size(); z++) {
            if (this->operator()(w, z) == 1) {
                if (color[z] == Color::BLUE) {
                    color[z] = Color::WHITE;
                    parent[z] = w;
                    distance[z] = distance[w] + 1;
                    q.push(z);
                }
            }
        }
        color[w] = Color::RED;
    }
}

std::vector<double> Matrix::Graph::distanceFromSource() {
    return this->distanceFrom(0);
}

std::pair<int, std::pair<int, int>> Matrix::Graph::longestPath() {
    if (this->_d != Type::DIRECTED) {
        std::cout << "" << std::endl;
        throw std::invalid_argument("The graph must be directed");
    }

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->size(), -1);
    std::pair<int, std::pair<int, int>> lPath = {0, {0, 0}};
    std::pair<int, std::pair<int, int>> actualPath = {0, {0, 0}};

    for (int v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            actualPath = {0, {v, v}};
            this->longestPathVisit(v, color, parent, lPath, actualPath, -1);
        }
    }

    return lPath;
}

void Matrix::Graph::longestPathVisit(int v, std::vector<Color> &color, std::vector<int> &parent,
                                     std::pair<int, std::pair<int, int>> &lPath,
                                     std::pair<int, std::pair<int, int>> actualPath, int previous) {
    color[v] = Color::WHITE;
    actualPath.first += 1;

    for (int w = 0; w < this->size(); w++) {
        if (this->operator()(v, w) == 1) {
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

std::optional<std::pair<int, std::vector<int>>> Matrix::Graph::path(int from, int to) {
    if (from < 0 || from > this->size() || to < 0 || to > this->size()) {
        throw std::invalid_argument("int param have to be between 0 and the _size of the graph");
    }

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->size(), -1);
    std::pair<int, std::vector<int>> path = {0, {from}};
    std::pair<int, int> param = {from, to};

    return this->pathVisit(from, color, parent, path, param);
}

std::optional<std::pair<int, std::vector<int>>>
Matrix::Graph::pathVisit(int v, std::vector<Color> &color, std::vector<int> &parent,
                         std::pair<int, std::vector<int>> path, std::pair<int, int> &param) {
    color[v] = Color::WHITE;
    path.first += 1;
    for (int w = 0; w < this->size(); w++) {
        if (this->operator()(v, w) == 1) {
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

std::optional<int> Matrix::Graph::blackHole() {
    int candidate = 0;
    for (int i = 1; i < this->size(); i++) {
        if (this->_m[candidate][i] == 1) {
            candidate = i;
        }
    }

    bool Ok = true;

    for (int i = 1; i < this->size(); i++) {
        if (this->_m[candidate][i] == 1 || this->_m[i][candidate] == 0) {
            Ok = false;
        }
    }

    return Ok ? std::optional<int>(candidate) : std::nullopt;
}

std::optional<std::pair<double, int>> Matrix::Graph::eccentricity(int v) {
    std::optional<std::pair<double, int>> res;

    auto dist = this->distanceFrom(v);

    for (int i = 0; i < this->size(); i++) {
        if (dist[i] > -1 && (!res.has_value() || res.value().first < dist[i]) && i != v) {
            res = {dist[i], i};
        }
    }

    return res;
}

std::optional<std::pair<double, std::pair<int, int>>> Matrix::Graph::radius() {
    std::optional<std::pair<double, std::pair<int, int>>> minEccentricity;

    for (int i = 0; i < this->size(); i++) {
        auto ecc = this->eccentricity(i);
        if (ecc.has_value() && (!minEccentricity.has_value() || minEccentricity.value().first > ecc.value().first)) {
            minEccentricity = {ecc.value().first, {i, ecc.value().second}};
        }
    }

    return minEccentricity;
}

std::optional<std::pair<double, std::pair<int, int>>> Matrix::Graph::diameter() {
    std::optional<std::pair<double, std::pair<double, int>>> minEccentricity;

    for (int i = 0; i < this->size(); i++) {
        auto ecc = this->eccentricity(i);
        if (ecc.has_value() && (!minEccentricity.has_value() || minEccentricity.value().first < ecc.value().first)) {
            minEccentricity = {ecc.value().first, {i, ecc.value().second}};
        }
    }

    return minEccentricity;
}

Matrix::M Matrix::Graph::matrixPath(int lenght) {
    return this->operator^(lenght);
}

Matrix::M Matrix::Graph::matrixAllPath() {
    Matrix::M temp(this->size());

    for (int i = 1; i < this->size(); i++) {
        temp += this->operator^(i);
    }

    return temp;
}

Matrix::Graph Matrix::Graph::createRandomGraph(int numberOfVertices, Type::Graph directed, double edgeProbability,
                                               bool includeRandomWeight) {
    if (numberOfVertices <= 0 || edgeProbability < 0.0 || edgeProbability > 1.0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> edgeDist(0.0, 1.0);
    std::uniform_int_distribution<int> weightDist(1, 100); // Random weight between 1 and 100

    Matrix::Graph g = Matrix::Graph(numberOfVertices, directed);
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

Type::Graph Matrix::Graph::directed() const {
    return this->_d;
}
