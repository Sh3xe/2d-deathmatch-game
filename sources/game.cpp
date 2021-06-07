#include "game.hpp"

#include "state_title.hpp"

Game::Game():
	m_window( sf::VideoMode(512, 512), "PacMan Deathmatch REMASTERED" ),
	m_view({ 128, 128 }, { 256, 256 }) {

	m_states.push_back( std::unique_ptr<StateTitle>( new StateTitle(*this) ) );
	m_window.setView( m_view );
}

Game::~Game() {
	m_window.close();
}

void Game::pushstate( std::unique_ptr<StateBase> state ) {
	m_states.push_back( std::move(state) );
}


void Game::handleInput(sf::Event &event) {

	while( m_window.pollEvent(event)) {
		switch(event.type) {
			case sf::Event::Closed:
				m_running = false;
				break;

			case sf::Event::KeyPressed:
				m_input.handleKeyDown(event);
				break;
			
			case sf::Event::KeyReleased:
				m_input.handleKeyUp(event);
				break;

			case sf::Event::Resized: {
				// handle viewport changes
				float a = 0.0f, b = 0.0f;

				if (event.size.width > event.size.height) {
					a = event.size.width;
					b = event.size.height;

					float pos_x = (a - b) * 0.5f / a;
					m_view.setViewport({ pos_x, 0.0f, static_cast<float>(b) / a, 1.0f });

				} else {
					a = event.size.height;
					b = event.size.width;

					float pos_y = (a - b) * 0.5f / a;
					m_view.setViewport({ 0.0f, pos_y, 1.0f, static_cast<float>(b) / a });
				}

				m_window.setView(m_view);
				break;
			}
			
			default: break;
		}
	}

	auto mouse_pos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	m_input.setMousePos({ static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y) });

}

void Game::run() {

	sf::Event event;
	sf::Clock clock;

	float delta_time = 0.0;

	while( m_running  && !m_states.empty()) {
		delta_time = clock.restart().asSeconds();

		if( delta_time < (1.0 / 60.0)) { // sleep to get 60fps
			sf::sleep( sf::seconds((1.0f/60.1f) - delta_time) );
		}

		if (m_states.back()->shouldClose()) {
			m_states.pop_back();
		}

		StateBase &current_state = *m_states.back();

		handleInput(event);
		current_state.update(m_input, delta_time);


		m_window.clear();
		current_state.render(m_window, delta_time);
		m_window.display();

	}

}