#include "game.hpp"

#ifdef WIN32
#include <Windows.h>
#endif

int main() {

#ifdef WIN32
	// hide the console
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif

	Game game;
	game.run();
}