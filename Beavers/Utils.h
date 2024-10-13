#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
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
    return std::to_string(value);
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

private:
    // Helper methods to format and print messages
    static void PrintMessage(const string& message, const string& type) {
        printf("[%s] %s\n", type.c_str(), message.c_str());
    }
};