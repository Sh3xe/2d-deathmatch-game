#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "input.hpp"
#include "state_base.hpp"

class Game {
public:
	Game();
	~Game();

	void pushstate( std::unique_ptr<StateBase> state );

	void run();
	void handleInput(sf::Event &event);


private:
	bool m_running = true;

	sf::RenderWindow m_window;
	sf::View m_view;
	std::vector< std::unique_ptr<StateBase>> m_states;
	Input m_input;

};

#endif