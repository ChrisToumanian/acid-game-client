#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "client.h"

class Game
{
public:
	Game();

	std::string user_id = "8df0f74h3h";
	std::string address = "mc.massivedamage.net";
	int port = 25566;
	bool running = false;
	Client* client;
	static std::vector<std::string> message_queue;

	void start();
	void connect();
	void loop();
	void send(std::string message);
	void log(std::string message);
	static void listen(Client* c);
	static void receive(std::string message);
	
};

#endif