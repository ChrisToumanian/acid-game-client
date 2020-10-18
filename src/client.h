#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

class Client
{
public:
	Client();

	int used_socket;
	char buffer[1024];

	void initialize(std::string _address, int _port);
	std::string send_message(std::string message);
};

#endif: