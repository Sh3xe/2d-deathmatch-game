#ifndef INPUT_HPP
#define INPUT_HPP

#include <unordered_map>
#include <SFML/Window/Event.hpp>


class Input {
public:
	Input();

	void handleKeyDown( sf::Event &event );
	void handleKeyUp( sf::Event &event );

	sf::Vector2i getMousePos() { return m_mouse_pos; }
	void setMousePos(sf::Vector2i pos) { m_mouse_pos = pos; }

	inline bool isKeyPressed( sf::Keyboard::Key key) {
		return m_keys[key];
	}

private:
	std::unordered_map<sf::Keyboard::Key, bool> m_keys;
	sf::Vector2i m_mouse_pos;

};

#endif