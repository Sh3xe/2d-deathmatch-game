#include "state_title.hpp"
#include "game.hpp"
#include "state_menu.hpp"
#include "resources.hpp"


StateTitle::StateTitle(Game& game): StateBase(game) {
}

void StateTitle::update(Input& input, float delta_time)  {
	m_clock += delta_time;

	if (m_clock > 4.0f) {
		m_should_close = true;
		m_game.pushstate(std::unique_ptr<StateBase>(new StateMenu(m_game)));
	}
}

void StateTitle::render(sf::RenderWindow& window, float delta_time)  {
	sf::RectangleShape title({ 256.0f, 256.0f });

	title.setPosition({ 0.0f, 0.0f });
	title.setTextureRect(sf::IntRect(0, 0, 256, 256));
	title.setTexture(&Resources::get().title_texture);

	window.draw(title);

	sf::RectangleShape fade({ 256.0f, 256.0f });
	sf::Color fade_color;

	if (m_clock < 1.0f)
		fade_color.a = static_cast<sf::Uint8>( (1.0f - m_clock) * 255 );
	else if (m_clock > 3.0f)
		fade_color.a = static_cast<sf::Uint8>( 255 - (4.0f - m_clock) * 255 );
	else
		fade_color.a = static_cast<sf::Uint8>(0);

	fade.setFillColor(fade_color);

	window.draw(fade);
}
