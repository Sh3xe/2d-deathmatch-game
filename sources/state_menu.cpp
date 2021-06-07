#include "state_menu.hpp"
#include "state_game.hpp"

#include "input.hpp"
#include "game.hpp"

StateMenu::StateMenu( Game &game ):
	StateBase(game),
	m_button({ 4*16.0f, 12*16.0f }, { 128.0f, 32.0f }, "START"),
	m_level_selector("resources/levels"),
	m_player_a_selection({ 32.0f, 6 * 16.0f }),
	m_player_b_selection({ 10 * 16.0f, 6 * 16.0f }) {

	m_player_b_selection.setKeys(sf::Keyboard::Key::Left, sf::Keyboard::Key::Right);
}

void StateMenu::update(Input &input, float delta_time)  {
	m_button.update(input);
	m_level_selector.update(input, delta_time);
	m_player_a_selection.update(input, delta_time);
	m_player_b_selection.update(input, delta_time);

	if(m_button.isPressed())
		m_game.pushstate( std::unique_ptr<StateGame>( new StateGame(
			m_game, m_level_selector.selectedLevelPath(),
			m_player_a_selection.getSelection(),
			m_player_b_selection.getSelection()) ) );

}

void StateMenu::render(sf::RenderWindow &window, float delta_time) {
	m_button.render(window);
	m_level_selector.render(window, delta_time);
	m_player_a_selection.render(window);
	m_player_b_selection.render(window);
}