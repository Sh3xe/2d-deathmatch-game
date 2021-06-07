#include "input.hpp"

Input::Input() {

}

void Input::handleKeyDown( sf::Event &event ) {
	m_keys[event.key.code] = true;
}

void Input::handleKeyUp( sf::Event &event ) {
	m_keys[event.key.code] = false;
}
