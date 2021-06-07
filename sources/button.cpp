#include "button.hpp"
#include "resources.hpp"

Button::Button(sf::Vector2f pos, sf::Vector2f size, const std::string &str):
	m_position(pos), m_size(size) {

	m_text.setPosition(pos.x, pos.y);
	m_text.setCharacterSize(32);
	m_text.setString(str);
	m_text.setScale(0.4f, 0.4f);
	m_text.setFillColor(sf::Color::White);
	m_text.setFont(Resources::get().font);
}

void Button::update(Input& input) {
	auto mouse_pos = input.getMousePos();

	m_pressed = false;
	m_hover = false;

	if ( mouse_pos.x >= m_position.x && mouse_pos.x <= m_position.x + m_size.x &&
		mouse_pos.y >= m_position.y && mouse_pos.y <= m_position.y + m_size.y )
		m_hover = true;

	if (m_hover && sf::Mouse::isButtonPressed(sf::Mouse::Left)) m_pressed = true;
}

void Button::render(sf::RenderWindow& window) {
	sf::RectangleShape shape({m_size.x, m_size.y});

	shape.setPosition(m_position);
	shape.setFillColor( m_hover ? sf::Color::Blue: sf::Color::Black );
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(2);

	window.draw(shape);
	window.draw(m_text);
}