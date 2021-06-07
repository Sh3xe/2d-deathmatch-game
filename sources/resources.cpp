#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "SFML/Graphics.hpp"

class Resources {
public:
	static sf::Font font;
	static sf::Texture tileset;
	static sf::Texture spritesheet;
	static sf::Texture title_texture;


private:
	Resources() {}

};


#endif