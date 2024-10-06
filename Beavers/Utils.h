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

const int TileSize = 64;