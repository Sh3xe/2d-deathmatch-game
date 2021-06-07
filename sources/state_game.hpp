#ifndef STATE_GAME_HPP
#define STATE_GAME_HPP

#include <list>

#include "state_base.hpp"
#include "level.hpp"
#include "player.hpp"
#include "projectiles.hpp"


class StateGame: public StateBase {
public:
	StateGame( Game &game, const std::string &level_name, int player_a_id, int player_b_id );
	~StateGame() {}

	void update(Input &input, float delta_time) override;
	void render(sf::RenderWindow &window, float delta_time) override;

private:
	Level m_level;
	Player m_player_a;
	Player m_player_b;

	std::list<Projectile> m_projectiles;

	float m_round_time = 0.0;

	sf::Text m_timer_txt;
	sf::Text m_score_a;
	sf::Text m_score_b;

};

#endif