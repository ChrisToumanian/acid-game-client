#include "game.h"

std::vector<std::string> Game::message_queue;

Game::Game()
{
}

void Game::start()
{
	connect();
	running = true;
	std::thread t(Game::listen, client);
	t.detach();

	send("/uid " + user_id);
	loop();
}

void Game::connect()
{
	client = new Client();
	client->initialize(address, port);
}

void Game::loop()
{
	int i = 0;
	while (running)
	{
		// receive messages
		for (int i = 0; i < message_queue.size(); i++)
		{
			// handle message
			log(message_queue[i]);

			// erase message
			message_queue.erase(message_queue.begin() + i);
		}
	}
}

void Game::send(std::string message)
{
	client->send_message(message);
}

void Game::receive(std::string message)
{
	message_queue.push_back(message);
}

void Game::listen(Client* c)
{
	c->listen(receive);
}

void Game::log(std::string message)
{
	std::cout << message << "\r\n";
}