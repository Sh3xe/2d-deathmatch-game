#include "player.hpp"
#include "input.hpp"
#include "level.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>

static std::unordered_map<Direction, int> sprite_direction_id = {
	{ Direction::NONE, 0  },
	{ Direction::UP, 3    },
	{ Direction::DOWN, 4  },
	{ Direction::LEFT, 1  },
	{ Direction::RIGHT, 2 }
};

Player::Player():
	m_position({0 ,0}),
	m_keys{sf::Keyboard::Key::Up, sf::Keyboard::Key::Down, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right, sf::Keyboard::Key::RControl} {
}

Player::Player( sf::Vector2f pos, int sprite, int id ):
	m_position(pos), m_selected_sprite(sprite), m_id(id),
	m_keys{sf::Keyboard::Key::Up, sf::Keyboard::Key::Down, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right, sf::Keyboard::Key::RControl} {
}

void Player::setSpriteId(int id) {
	m_selected_sprite = id;
}

void Player::setKeys(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key fire) {
	m_keys = {up, down, left, right, fire};
}

AABB Player::getAABB() {
	return AABB(m_position.x, m_position.y, 16.0, 16.0);
}

void Player::setPosition(float x, float y) {
	m_position.x = x;
	m_position.y = y;
}

void Player::kill() {
	m_is_dead = true;
	m_death_timer = 0.0;
	++m_deaths;
}


void Player::update(Input &input, Level &level, std::list<Projectile> &projectiles_lst, float delta_time) {
	m_bonus_timer -= delta_time;
	m_cooldown += delta_time;

	// don't update the position if the player is dead
	if(m_is_dead) {
		// just update the death timer
		m_death_timer += delta_time;

		// if he is stil dead, stop, if he is not, mark it that way and continue
		if(m_death_timer > 2)
			m_is_dead = false;
		else
			return;
	}

	if(input.isKeyPressed(m_keys[4]) && m_cooldown > 0.3 && m_direction != Direction::NONE) {
		m_cooldown = 0.0;
		projectiles_lst.emplace_back(m_position.x + 8, m_position.y + 8, m_id, m_direction);
	}

	if(input.isKeyPressed(m_keys[0]))
		m_direction = Direction::UP;

	if(input.isKeyPressed(m_keys[1]))
		m_direction = Direction::DOWN;

	if(input.isKeyPressed(m_keys[2]))
		m_direction = Direction::RIGHT;

	if(input.isKeyPressed(m_keys[3]))
		m_direction = Direction::LEFT;

	sf::Vector2f vel = {0, 0};

	switch(m_direction) {
		case Direction::UP:
			vel.y -= m_speed * delta_time;
			break;

		case Direction::DOWN:
			vel.y += m_speed * delta_time;
			break;

		case Direction::LEFT:
			vel.x += m_speed * delta_time;
			break;

		case Direction::RIGHT:
			vel.x -= m_speed * delta_time;
			break;

		default: break;
	}

	m_position += vel;

	AABB aabb {m_position.x, m_position.y, 16.0, 16.0};

	if( level.collideWith(aabb) ) {
		m_position -= vel;
		m_direction = Direction::NONE;
	}

	if (level.collideWithBonus(aabb)) {
		level.disableBonus();
		m_bonus_type = level.getBonusType();
		m_bonus_timer = 3.0f;

		if (m_bonus_type == 0)
			m_speed = 90.0f;
		else
			m_speed = 120.0f;
	}

	if (m_bonus_timer < 0.0f) m_speed = 60.0f;

}

void Player::render(sf::RenderWindow &window, sf::Texture &spritesheet, float delta_time) {

	if (!m_is_dead) {
		sf::RectangleShape player_overlay({ 18, 18 });
		sf::Vector2i pos{ 6 * 16, 0 };

		if (m_animation_timer > (10.0 / 60.0) && m_animation_timer < (20.0 / 60.0))
			pos.y = sprite_direction_id[m_direction] * 18;

		player_overlay.setPosition(m_position - sf::Vector2f(1, 1) );
		player_overlay.setTexture(&spritesheet);
		player_overlay.setTextureRect(sf::IntRect(pos, { 18, 18 }));

		window.draw(player_overlay);

	}

	sf::RectangleShape player_shape ({16, 16});

	// set rectangle's position and sprite
	player_shape.setPosition(m_position);
	player_shape.setTexture(&spritesheet);
	
	// calculate the texture rect from the time and all
	sf::Vector2i pos {0, 16*m_selected_sprite};

	m_death_timer += delta_time;
	m_animation_timer += delta_time;

	// handle animation
	if(m_is_dead) {
		pos.x = 5 * 16;

		int animation_y = static_cast<int>( (m_death_timer / 1.7) * 4 );
		if( animation_y > 4 ) animation_y = 4;
		
		pos.y = animation_y * 16;

	} else if (m_animation_timer > (10.0/60.0) && m_animation_timer < (20.0/60.0))
		pos.x = sprite_direction_id[m_direction] * 16;
	else if (m_animation_timer > (10.0/60.0))
		m_animation_timer = 0.0;

	player_shape.setTextureRect( sf::IntRect(pos, {16, 16}) );

	// draw the shape
	window.draw(player_shape);

}
