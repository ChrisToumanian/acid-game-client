#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include "client.h"

class Game
{
public:
	Game();

	bool running = false;
	Client* client;

	void start();
	void connect();
	void loop();
	std::string receive(std::string message);
};

#endif