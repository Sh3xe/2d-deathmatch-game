#ifndef PROJECTILES_HPP
#define PROJECTILES_HPP

#include "utils.hpp"
#include <SFML/System/Vector2.hpp>

namespace sf { class RenderWindow; };

class Projectile {
public:
	Projectile( float x, float y, int from, Direction direction );

	void update(float delta_time);
	void draw(sf::RenderWindow &window);
	inline sf::Vector2f getPosition() const { return m_position; }

	inline int getPlayer() { return m_from; }

	bool collideWith(const AABB &aabb);

private:
	sf::Vector2f m_position;
	Direction m_direction;
	int m_from;

};

#endif