
#ifndef STATE_MENU_HPP
#define STATE_MENU_HPP

#include "state_base.hpp"
#include "level_selector.hpp"
#include "player_selector.hpp"
#include "button.hpp"

class StateMenu: public StateBase {
public:
	StateMenu( Game &game );
	~StateMenu() {}

	void update(Input &input, float delta_time) override;
	void render(sf::RenderWindow &window, float delta_time) override;

private:
	Button m_button;
	LevelSelector m_level_selector;
	PlayerSelector m_player_a_selection, m_player_b_selection;

};

#endif