#ifndef STATE_TITLE_HPP
#define STATE_TITLE_HPP

#include "state_base.hpp"
#include <SFML/Graphics.hpp>

class StateTitle : public StateBase {
public:
	StateTitle(Game& game);
	~StateTitle() {}

	void update(Input& input, float delta_time) override;
	void render(sf::RenderWindow& window, float delta_time) override;

private:
	float m_clock = 0.0f;

};

#endif