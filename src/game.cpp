#include "game.h"

Game::Game()
{
}

void Game::start()
{
	connect();
	running = true;
	loop();
}

void Game::connect()
{
	client = new Client();
	client->initialize("mc.massivedamage.net", 25566);
}

void Game::loop()
{
	int i = 0;
	while (running)
	{
		if (i > -1) running = false;
		std::cout << client->send_message("hi");
		i++;
	}
}

std::string Game::receive(std::string message)
{
	std::cout << "Received: " + message << "\n";
	return "";
}