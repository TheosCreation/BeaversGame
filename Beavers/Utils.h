#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>

using std::vector;
using std::string;
using std::map;
using std::shared_ptr;
using std::weak_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;

using sf::Vector2f;
using sf::Vector2u;
using sf::Vector2i;
using sf::Vector3f;

typedef sf::Vector2f Vec2f;
typedef sf::Vector2i Vec2i;
typedef sf::Vector2u Vec2u;

Vec2f normalize(Vec2f& _vec2);
float Length(Vec2f& _vec2);

template <typename T>
std::string ToString(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

template <>
inline std::string ToString(const Vec2f& value) {
    std::ostringstream oss;
    oss << "Vec2f(" << value.x << ", " << value.y << ")";
    return oss.str();
}

template <>
inline std::string ToString(const Vec2i& value) {
    std::ostringstream oss;
    oss << "Vec2i(" << value.x << ", " << value.y << ")";
    return oss.str();
}

template <>
inline std::string ToString(const Vec2u& value) {
    std::ostringstream oss;
    oss << "Vec2u(" << value.x << ", " << value.y << ")";
    return oss.str();
}

class Debug
{
public:
    // Static methods for logging messages
    static void Log(const string& message) {
        PrintMessage(message, "Log");
    };
    static void LogError(const string& message) {
        PrintMessage(message, "Error");
    }
    static void LogWarning(const string& message) {
        PrintMessage(message, "Warning");
    }

    template <typename T>
    static void Log(const T& value) {
        Log(ToString(value));
    }

private:
    // Helper methods to format and print messages
    static void PrintMessage(const string& message, const string& type) {
        printf("[%s] %s\n", type.c_str(), message.c_str());
    }
};