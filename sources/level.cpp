#include "level.hpp"
#include <fstream>
#include <array>
#include <random>

static constexpr float sprite_scale = 16.0f;

sf::Vector2f interpolate(const sf::Vector2f &v1, const sf::Vector2f &v2, float t) {
	return v1 + (v2 - v1) * t;
}

Level::Level() {
}

Level::Level( const std::string &file_path ) {
	loadFromFile("./resources/levels/" + file_path);
	if(m_valid)
		fillVertexArray();
}

void Level::loadFromFile( const std::string &file_path ) {
	// fetch all level information from a txt file

	/*  Levels are formated the following way:
		TODO 
	*/

	m_valid = false;
	std::ifstream file {file_path};

	if(file) {
		m_valid = true;

		file >> m_spawn_a.x >> m_spawn_a.y;
		file >> m_spawn_b.x >> m_spawn_b.y;

		file >> m_bonus_pos.x >> m_bonus_pos.y;

		m_tiles.clear();
		m_tiles.reserve(width * height);

		int path_size = 0;
		file >> path_size;

		m_ghost_path.clear();
		m_ghost_path.reserve(path_size);

		for(int i = 0; i < path_size; ++i) {
			sf::Vector2f vec;
			file >> vec.x >> vec.y;
			m_ghost_path.push_back(vec);
		}

		for(int i = 0; i < 16 * 16; ++i) {
			Tile tile;
			int id, rotation; // they are going to be casted to char, so using the >> operator can create problems
			file >> id >> rotation >> tile.collidable;

			tile.id = id;
			tile.rotation = rotation;

			m_tiles.push_back(tile);
		}

	}

	if(file.fail())
		m_valid = false;
	file.close();
}

void Level::fillVertexArray() {
	// reset and configure the vertex arary
	m_vertex_array.clear();
	m_vertex_array.setPrimitiveType(sf::Quads);
	m_vertex_array.resize(width * height * 4);

	for(int x = 0; x < width; ++x) // for each tiles
	for(int y = 0; y < height; ++y) {
		// get the current tile
		Tile tile = m_tiles[x + y* width];
		// get the vertex position
		sf::Vertex *vertex = &m_vertex_array[4*(x + y * width)];
		
		// vertex's positions
		vertex[0].position = {(x  ) * sprite_scale, (  y) * sprite_scale};
		vertex[1].position = {(x+1) * sprite_scale, (  y) * sprite_scale};
		vertex[2].position = {(x+1) * sprite_scale, (y+1) * sprite_scale};
		vertex[3].position = {(x  ) * sprite_scale, (y+1) * sprite_scale};

		int tx = tile.id % 8;
		int ty = tile.id / 8;

		// holds the position of each texture coords, adding i % 4 has the effect of rotating the sprite i times
		std::array< sf::Vector2f, 4 > rotations;
		rotations[0] = {(tx  ) * sprite_scale, (  ty) * sprite_scale};
		rotations[1] = {(tx+1) * sprite_scale, (  ty) * sprite_scale};
		rotations[2] = {(tx+1) * sprite_scale, (ty+1) * sprite_scale};
		rotations[3] = {(tx  ) * sprite_scale, (ty+1) * sprite_scale};
		
		// set each textures coords
		vertex[0].texCoords = rotations[(tile.rotation+0) % 4];
		vertex[1].texCoords = rotations[(tile.rotation+1) % 4];
		vertex[2].texCoords = rotations[(tile.rotation+2) % 4];
		vertex[3].texCoords = rotations[(tile.rotation+3) % 4];
	}

}

bool Level::collideWith(const AABB &hitbox) {
	if(hitbox.xmin < 0 || hitbox.ymin < 0 || hitbox.xmax > width * static_cast<int>(sprite_scale) || hitbox.ymax > height * static_cast<int>(sprite_scale))
		return true;

	for(int x = static_cast<int>(hitbox.xmin/16.0); x < static_cast<int>(hitbox.xmax/16.0) + 1; ++x)
	for(int y = static_cast<int>(hitbox.ymin/16.0); y < static_cast<int>(hitbox.ymax/16.0) + 1; ++y) {
		// for each nearby tiles
		Tile tile = m_tiles[x + y* 16];
		AABB aabb {x * 16.0, y * 16.0, 16.0, 16.0};
		// if the tile is collidable and collide,
		if(tile.collidable && hitbox.collideWith(aabb))
			// return true
			return true;
	}
	// else return false
	return false;
}

bool Level::collideWithGhost(const AABB &hitbox) {
	return hitbox.collideWith( {m_ghost_pos.x, m_ghost_pos.y, 16, 16} );
}

bool Level::collideWithBonus(const AABB& hitbox) {
	return hitbox.collideWith({ m_bonus_pos.x, m_bonus_pos.y, 16, 16 }) && m_bonus_active;
}

void Level::update(float delta_time) {
	m_ghost_timer += delta_time;
	if(!m_bonus_active)
		m_bonus_timer += delta_time;

	if(m_ghost_timer > 6.0) m_ghost_timer = 0.0;

	const int path_size = m_ghost_path.size();
	int path_id = static_cast<int>((m_ghost_timer / 6.0) * path_size);

	m_ghost_pos = interpolate( m_ghost_path[path_id], m_ghost_path[(path_id + 1) % path_size], ((m_ghost_timer / 6.0f) * path_size) - path_id);

	static std::default_random_engine e;

	if (m_bonus_timer > 5.0f) {
		m_bonus_timer = 0.0f;
		m_bonus_active = true;
		std::bernoulli_distribution d(0.2);
		m_bonus_type = d(e);
	}

}

void Level::render(sf::RenderWindow &window, sf::Texture &tileset) {
	window.draw(m_vertex_array, &tileset);

	sf::RectangleShape ghost({16, 16});
	ghost.setPosition(m_ghost_pos);
	ghost.setTexture(&tileset);
	ghost.setTextureRect( sf::IntRect({0, 5*16}, {16, 16}) );
	window.draw(ghost);

	if (m_bonus_active) {
		sf::RectangleShape bonus({ 16, 16 });
		bonus.setPosition(m_bonus_pos);
		bonus.setTexture(&tileset);
		bonus.setTextureRect(sf::IntRect({ m_bonus_type * 16, 4 * 16 }, { 16, 16 }));
		window.draw(bonus);
	}


}