#include "client.h"

Client::Client()
{
}

void Client::initialize(std::string address, int port)
{
	// Load socket
	WSADATA wsaData;
	WSAStartup(0x0202, &wsaData);

	// Create first socket
	struct sockaddr_in destination;
	destination.sin_family = AF_INET;
	used_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (used_socket < 0)
	{
		std::cout << "Socket creation failed." << std::endl;
		closesocket(used_socket);
	}

	// Resolve the server address and port
	struct addrinfo* result = NULL, * ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	std::cout << "Connecting...\n";

	int iResult = getaddrinfo(static_cast<LPCTSTR>(address.c_str()), std::to_string(port).c_str(), &hints, &result);
	if (iResult != 0) {
		std::cout << "getaddrinfo() failed with error: " << iResult << std::endl;
		closesocket(used_socket);
		WSACleanup();
		return;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		used_socket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (used_socket == INVALID_SOCKET) {
			std::cout << "socket() failed with error: " << WSAGetLastError() << std::endl;
			WSACleanup();
		}

		// Connect to server.
		iResult = connect(used_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(used_socket);
			used_socket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (used_socket == INVALID_SOCKET) {
		std::cout << "Unable to connect to server!" << std::endl;
		WSACleanup();
		return;
	}
}

std::string Client::send_message(std::string message)
{
	memset(buffer, 0, 1024);
	message += '\r\n';

	// send message
	send(used_socket, message.c_str(), (int)strlen(message.c_str()), 0);

	// receive message
	int result = recv(used_socket, buffer, 1024, 0);
	if (result != SOCKET_ERROR)
	{
		return buffer;
	}

	return "Sent from client.";
}