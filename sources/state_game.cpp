#include "state_game.hpp"
#include "state_win.hpp"
#include "resources.hpp"

#include "input.hpp"
#include "game.hpp"

StateGame::StateGame( Game &game, const std::string& level_name, int player_a_id, int player_b_id): StateBase(game),
	m_level(level_name),
	m_player_a( {500, -500}, player_a_id, 0),
	m_player_b( {1000, -1000}, player_b_id, 1) {

	m_player_a.setKeys(
		sf::Keyboard::Key::Z,
		sf::Keyboard::Key::S,
		sf::Keyboard::Key::Q,
		sf::Keyboard::Key::D,
		sf::Keyboard::Key::Space );

	m_player_a.setPosition(m_level.getSpawnA().x, m_level.getSpawnA().y);
	m_player_b.setPosition(m_level.getSpawnB().x, m_level.getSpawnB().y);

	// TODO: probably do that in a "onInit" function with error handling, works fine for now

	// set text properties
	m_timer_txt.setPosition(112.0f, 1.0f);
	m_timer_txt.setCharacterSize(32);
	m_timer_txt.setScale(0.4f, 0.4f);
	m_timer_txt.setFillColor(sf::Color::White);
	m_timer_txt.setFont(Resources::get().font);

	m_score_a.setPosition(10.0f, 1.0f);
	m_score_a.setCharacterSize(32);
	m_score_a.setScale(0.4f, 0.4f);
	m_score_a.setFillColor(sf::Color::White);
	m_score_a.setFont(Resources::get().font);

	m_score_b.setPosition(230.0f, 1.0f);
	m_score_b.setCharacterSize(32);
	m_score_b.setScale(0.4f, 0.4f);
	m_score_b.setFillColor(sf::Color::White);
	m_score_b.setFont(Resources::get().font);
}

void StateGame::update(Input &input, float delta_time) {

	if (input.isKeyPressed(sf::Keyboard::Key::Escape)) m_should_close = true;

	m_round_time += delta_time;
	const int count_down = static_cast<int>(60*1.3 - m_round_time);

	int seconds = count_down % 60;

	m_timer_txt.setString( std::to_string( static_cast<int>(count_down / 60) ) + ( seconds < 10 ? ":0": ":") + std::to_string(seconds) );
	m_score_b.setString( std::to_string(m_player_a.getDeaths()) );
	m_score_a.setString( std::to_string(m_player_b.getDeaths()) );

	m_player_a.update(input, m_level, m_projectiles, delta_time);
	m_player_b.update(input, m_level, m_projectiles, delta_time);

	// handling projectiles
	for(auto it = m_projectiles.begin(); it != m_projectiles.end();) {
		Projectile &projectile = *it;

		projectile.update(delta_time);

		// check player_a's collision
		if(projectile.collideWith( m_player_a.getAABB() ) && projectile.getPlayer() != m_player_a.getId()&& ! m_player_a.isDead()) { // if the projectile from player_b hit player_a
			// increment death counter
			m_player_a.kill();
			// set position
			m_player_a.setPosition( m_level.getSpawnA().x, m_level.getSpawnA().y );
		}

		// check player_b's collision
		if(projectile.collideWith( m_player_b.getAABB() ) && projectile.getPlayer() != m_player_b.getId() && ! m_player_b.isDead()) {
			m_player_b.kill();
			m_player_b.setPosition( m_level.getSpawnB().x, m_level.getSpawnB().y );
		}

		auto pos = projectile.getPosition();

		if(pos.x < 0 || pos.y < 0 || pos.x > Level::width * 16 || pos.y > Level::height * 16) {
			m_projectiles.erase(it++);
		} else ++it;

	}

	if( m_level.collideWithGhost(m_player_a.getAABB())) {
		m_player_a.kill();
		m_player_a.setPosition( m_level.getSpawnA().x, m_level.getSpawnA().y );

	} if( m_level.collideWithGhost(m_player_b.getAABB())) {
		m_player_b.kill();
		m_player_b.setPosition( m_level.getSpawnB().x, m_level.getSpawnB().y );
	}

	m_level.update(delta_time);

	if (count_down <= 0) {
		m_should_close = true;
		std::string msg = "";

		if (m_player_a.getDeaths() > m_player_b.getDeaths())
			msg = "Player B\nwon!";
		else if (m_player_a.getDeaths() == m_player_b.getDeaths())
			msg = "Tie!";
		else
			msg = "Player A\nwon!";

		m_game.pushstate(std::unique_ptr<StateWin>(new StateWin(m_game, msg)));
		m_round_time = 0.0f;
	}

}

void StateGame::render(sf::RenderWindow &window, float delta_time) {
	m_level.render(window, Resources::get().tileset);

	window.draw(m_timer_txt);
	window.draw(m_score_a);
	window.draw(m_score_b);

	m_player_a.render(window, Resources::get().spritesheet, delta_time);
	m_player_b.render(window, Resources::get().spritesheet, delta_time);

	for(auto& projectile: m_projectiles)
		projectile.draw(window);
}
