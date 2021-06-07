#include "level_selector.hpp"
#include "resources.hpp"

#include <filesystem>

namespace fs = std::filesystem;

LevelSelector::LevelSelector(const std::string& path) :
	m_left({ 32.0f, 32.0f }, {32.0f, 32.0f }, "<"), m_right({ 12 * 16.0f, 32.0f }, { 32.0f, 32.0f }, ">") {

	m_level_name.setPosition(5 * 16.0f, 32.0f);
	m_level_name.setCharacterSize(32);
	m_level_name.setScale(0.4f, 0.4f);
	m_level_name.setFillColor(sf::Color::White);
	m_level_name.setFont(Resources::get().font);

	fetchLevels();
}

void LevelSelector::fetchLevels() {
	const fs::path dir{ "resources/levels/" };
	m_levels.clear();

	for (const auto& entry : fs::directory_iterator(dir)) {
		m_levels.push_back( entry.path().filename().string() );
	}
}

void LevelSelector::update(Input& input, float delta_time) {
	m_mouse_cooldown += delta_time;

	m_left.update(input);
	m_right.update(input);

	if (m_left.isPressed() && m_mouse_cooldown > 0.2f) {
		m_mouse_cooldown = 0.0f;
		m_selection = (m_selection + m_levels.size() - 1) % m_levels.size();

	} else if (m_right.isPressed() && m_mouse_cooldown > 0.2f) {
		m_mouse_cooldown = 0.0f;
		m_selection = (m_selection + 1) % m_levels.size();

	}

	m_level_name.setString(m_levels[m_selection]);
}


void LevelSelector::render(sf::RenderWindow& window, float delta_time) {
	m_left.render(window);
	m_right.render(window);
	window.draw(m_level_name);
}