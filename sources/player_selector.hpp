#ifndef PLAYER_SELECTOR_HPP
#define PLAYER_SELECTOR_HPP

#include "SFML/Graphics.hpp"

#include "input.hpp"

class PlayerSelector {
public:
	PlayerSelector(sf::Vector2f pos);

	void setKeys(sf::Keyboard::Key left, sf::Keyboard::Key right);

	inline int getSelection() const { return m_selection; }

	void update(Input& input, float delta_time);
	void render(sf::RenderWindow& window);

private:
	sf::Vector2f m_pos;
	sf::Keyboard::Key m_right, m_left;
	int m_selection = 0;
	float m_cooldown = 0.0f;

};

#endif