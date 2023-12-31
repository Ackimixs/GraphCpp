#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP

#include <utility>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>

namespace Utils {
    bool isNumber(const std::string& s);

    bool isDouble(const std::string& s);

    std::string getCurrentDateTime();
}

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
    static bool isInVector(std::vector<T>& vec, const T& value) {
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

#endif // UTILS_HPP