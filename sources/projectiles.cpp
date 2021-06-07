#include "projectiles.hpp"
#include <SFML/Graphics.hpp>


Projectile::Projectile( float x, float y, int from, Direction direction ):
	m_position({x, y}), m_from(from), m_direction(direction) {
}

void Projectile::update(float delta_time) {
	switch(m_direction) {
		case Direction::UP:
			m_position.y -= delta_time * 16.0f * 12.0f;
			break;
		
		case Direction::DOWN:
			m_position.y += delta_time * 16.0f * 12.0f;
			break;

		case Direction::LEFT:
			m_position.x += delta_time * 16.0f * 12.0f;
			break;

		case Direction::RIGHT:
			m_position.x -= delta_time * 16.0f * 12.0f;
			break;

		default: break;
	}
}

void Projectile::draw(sf::RenderWindow &window) {
	sf::RectangleShape shape ({4.0f, 4.0f});

	shape.setPosition({m_position.x, m_position.y});
	shape.setFillColor(sf::Color::White);

	window.draw(shape);
}

bool Projectile::collideWith(const AABB &aabb) {
	return AABB(m_position.x, m_position.y, 4, 4).collideWith(aabb);
}
