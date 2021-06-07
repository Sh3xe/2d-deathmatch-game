#include "player_selector.hpp"

#include "resources.hpp"

PlayerSelector::PlayerSelector(sf::Vector2f pos) :
	m_pos(pos),
	m_right(sf::Keyboard::Key::D), m_left(sf::Keyboard::Key::Q) {

}


void PlayerSelector::setKeys(sf::Keyboard::Key left, sf::Keyboard::Key right) {
	m_right = right;
	m_left = left;
}


void PlayerSelector::update(Input& input, float delta_time) {
	m_cooldown += delta_time;

	if (input.isKeyPressed(m_right) && m_cooldown > 0.2f) {
		m_selection = (m_selection + 1) % 8;
		m_cooldown = 0.0f;
	} else if (input.isKeyPressed(m_left) && m_cooldown > 0.2f) {
		m_selection = (m_selection + 7) % 8;
		m_cooldown = 0.0f;
	}
}

void PlayerSelector::render(sf::RenderWindow& window) {
	sf::RectangleShape preview({64, 64});

	preview.setPosition(m_pos);
	preview.setTexture(&Resources::get().spritesheet);
	preview.setTextureRect({16, m_selection * 16 ,16, 16});

	window.draw(preview);

}