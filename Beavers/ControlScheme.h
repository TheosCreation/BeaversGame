#pragma once
#include <SFML/Graphics.hpp>

struct ControlScheme
{
	sf::Keyboard::Key Left		= sf::Keyboard::Key::A;
	sf::Keyboard::Key Right		= sf::Keyboard::Key::D;
	sf::Keyboard::Key Up		= sf::Keyboard::Key::W;
	sf::Keyboard::Key Down		= sf::Keyboard::Key::S;
	sf::Keyboard::Key Interact	= sf::Keyboard::Key::F;
	sf::Keyboard::Key Hint	= sf::Keyboard::Key::H;
	sf::Keyboard::Key Pause = sf::Keyboard::Key::Escape;
};