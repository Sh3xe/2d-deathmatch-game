#ifndef STATE_BASE_HPP
#define STATE_BASE_HPP

class Input;
class Game;
namespace sf { class RenderWindow; };

class StateBase {
public:
	StateBase( Game &game ): m_game(game) {}
	virtual ~StateBase() {}

	virtual void update(Input &input, float delta_time) = 0;
	virtual void render(sf::RenderWindow &window, float delta_time) = 0;

	inline bool shouldClose() const { return m_should_close; }

protected:
	Game &m_game;
	bool m_should_close = false;
};

#endif