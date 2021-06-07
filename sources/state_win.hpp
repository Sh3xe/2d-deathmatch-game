#ifndef STATE_WIN_HPP
#define STATE_WIN_HPP

#include "state_base.hpp"
#include <SFML/Graphics.hpp>

class StateWin : public StateBase {
public:
	StateWin(Game& game, std::string winner );
	~StateWin() {}

	void update(Input& input, float delta_time) override;
	void render(sf::RenderWindow& window, float delta_time) override;

private:
	sf::Text m_winner_text;
	float m_clock = 0.0f;

};

#endif