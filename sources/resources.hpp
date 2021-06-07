#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "SFML/Graphics.hpp"

class Resources {
public:
	Resources(const Resources&) = delete;

	static Resources& get() {
		static Resources* instance = nullptr;

		if (!instance) {
			instance = new Resources();
			instance->init();
		}

		return *instance;
	}

	sf::Font font;
	sf::Texture tileset;
	sf::Texture spritesheet;
	sf::Texture title_texture;


private:

	void init() {
		tileset.loadFromFile("resources/images/tileset.png");
		spritesheet.loadFromFile("resources/images/players.png");
		font.loadFromFile("resources/fonts/joystick.ttf");
		title_texture.loadFromFile("./resources/images/titlescreen.png");
	}

	Resources() {}
};


#endif