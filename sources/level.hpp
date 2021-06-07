#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>
#include <stdint.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>

#include "utils.hpp"

namespace sf { class RenderWindow; };

struct Tile {
	Tile(std::uint8_t id, std::uint8_t rotation, bool collidable):
		id(id), rotation(rotation),
		collidable(collidable){
	}
	
	Tile(): Tile(0, 0, false){}

	std::uint8_t id;
	std::uint8_t rotation;
	bool collidable;
};

class Level {
public:
	static constexpr int width = 16;
	static constexpr int height = 16;

	Level( const std::string &file_path );
	Level();

	inline sf::Vector2f getSpawnA() const { return m_spawn_a; }
	inline sf::Vector2f getSpawnB() const { return m_spawn_b; }
	int getBonusType() const { return m_bonus_type; }

	void disableBonus() { 
		m_bonus_active = false;
		m_bonus_timer = 0.0f;
	}

	void fillVertexArray();
	void loadFromFile( const std::string &file_path );

	void update(float delta_time);
	void render(sf::RenderWindow &window, sf::Texture &tileset);

	bool collideWith(const AABB &hitbox);
	bool collideWithGhost(const AABB &hitbox);
	bool collideWithBonus(const AABB& hitbox);

	operator bool() { return m_valid; }

private:
	std::vector<Tile> m_tiles;
	sf::VertexArray m_vertex_array;

	std::vector<sf::Vector2f> m_ghost_path;

	float m_ghost_timer = 0.0f;
	float m_bonus_timer = 0.0f;

	int m_bonus_type = 0;
	bool m_bonus_active = false;

	sf::Vector2f m_ghost_pos{ -200.0f, -200.0f };
	sf::Vector2f m_bonus_pos{ -200.0f, -200.0f };

	sf::Vector2f m_spawn_a = {0.0f, 0.0f};
	sf::Vector2f m_spawn_b = {0.0f, 0.0f};


	bool m_valid = false;

};

#endif