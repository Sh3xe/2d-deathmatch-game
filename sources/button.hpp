#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "input.hpp"

class Button {
public:
	Button(sf::Vector2f pos, sf::Vector2f size, const std::string &str = "");

	bool isPressed() { return m_pressed;  }

	void update(Input& input);
	void render(sf::RenderWindow& window);

private:
	bool m_pressed = false;
	bool m_hover = false;

	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Text m_text;

};

#endif