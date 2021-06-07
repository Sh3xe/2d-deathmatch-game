#include "state_win.hpp"
#include "resources.hpp"

StateWin::StateWin(Game& game, std::string winner): StateBase(game) {

	m_winner_text.setString(winner);
	m_winner_text.setPosition(50.0f, 50.0f);
	m_winner_text.setCharacterSize(24);
	m_winner_text.setFillColor(sf::Color::White);
	m_winner_text.setFont(Resources::get().font);

}

void StateWin::update(Input& input, float delta_time) {
	m_clock += delta_time;

	if (m_clock > 4.0f) m_should_close = true;
}

void StateWin::render(sf::RenderWindow& window, float delta_time) {
	window.draw(m_winner_text);
}

