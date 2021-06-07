#ifndef LEVEL_SELECTOR_HPP
#define LEVEL_SELECTOR_HPP

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "button.hpp"
class Input;

class LevelSelector {
public:
	LevelSelector( const std::string& path );

	std::string selectedLevelPath() { return m_levels[m_selection]; }

	void update(Input& input, float delta_time);
	void render(sf::RenderWindow& window, float delta_time);

private:
	void fetchLevels();

	std::vector< std::string > m_levels;
	float m_mouse_cooldown = 0.0f;
	int m_selection = 0;

	Button m_left, m_right;
	sf::Text m_level_name;

};

#endif