#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <array>
#include <list>

#include "input.hpp"
#include "projectiles.hpp"

class Level;
namespace sf { class RenderWindow; class Texture; };

class Player {
public:
	Player();
	Player( sf::Vector2f pos, int sprite, int id );

	inline int getId() const { return m_id; }
	inline bool isDead() const { return m_is_dead; }
	AABB getAABB();
	inline int getDeaths() const { return m_deaths; }

	void setKeys(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key fire);
	void setSpriteId(int id);
	void setPosition(float x, float y);

	void kill();

	void update(Input &input, Level &level, std::list<Projectile> &projectiles_lst, float delta_time);
	void render(sf::RenderWindow &window, sf::Texture &spritesheet, float delta_time);


private:
	int m_id = 0, m_deaths = 0, m_bonus_type = 0;
	bool m_is_dead = false;

	std::array<sf::Keyboard::Key, 5> m_keys;
	int m_selected_sprite = 0;

	Direction m_direction = Direction::NONE;
	sf::Vector2f m_position = {0, 0};

	float m_speed = 60.0f;

	float m_animation_timer = 0.0f;
	float m_cooldown = 0.0f;
	float m_death_timer = 0.0f;
	float m_bonus_timer = 0.0f;

};

#endif