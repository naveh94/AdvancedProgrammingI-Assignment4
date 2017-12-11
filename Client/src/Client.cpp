/*
 * Client.cpp
 *
 *  Created on: Dec 11, 2017
 *      Author: naveh
 */

#include "../include/Client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

Client::Client(const char *serverIP, int serverPort) : serverIP(serverIP),
		serverPort(serverPort), clientSocket(0) {
	cout << "Client" << endl;
}

void Client::connectToServer() {
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1) {
		throw "Error opening socket";
	}

	struct in_addr address;
	if (!inet_aton(serverIP, &address)) {
		throw "Can't parse IP address.";
	}

	struct hostent *server;
	server = gethostbyaddr((const void *)&address, sizeof(address), AF_INET);
	if (server == NULL) {
		throw "Host is unreachable";
	}

	struct sockaddr_in serverAddress;
	bzero((char *)&address, sizeof(address));

	serverAddress.sin_family = AF_INET;
	memcpy((char *)&serverAddress.sin_addr.s_addr, (char *)server->h_addr, server->h_length);

	serverAddress.sin_port = htons(serverPort);

	if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
		throw "Error connecting to server";
	}
	cout << "Connected to server.";
}

void Client::sendGamestate(int gamestate) {
	int n = write(clientSocket, &gamestate, sizeof(gamestate));
	if (n == -1) {
		throw "Error writing gamestate to server";
	}
}

void Client::sendMove(Point move) {
	int x = move.getX(), y = move.getY();
	int n = write(clientSocket, &x, sizeof(x));
	if (n == -1) {
		throw "Error writing x to server";
	}
	n = write(clientSocket, &y, sizeof(y));
	if (n == -1) {
		throw "Error writing y to server";
	}
}

Point Client::recieveMove() {
	int x, y, n;
	n = read(clientSocket, &x, sizeof(x));
	if (n == -1) {
		throw "Error reading x from server";
	}
	n = read(clientSocket, &y, sizeof(y));
	if (n == -1) {
		throw "Error reading y from server";
	}
	return Point(x, y);
}

int Client::recievePlayerTurn() {
	int turn, n;
	n = read(clientSocket, &turn, sizeof(turn));
	if (n == -1) {
		throw "Error reading turn from server";
	}
	return turn;
}

int Client::recieveTurnAnnouncement() {
	int announce, n;
	n = read(clientSocket, &announce, sizeof(announce));
	if (n == -1) {
		throw "Error reading turn from server";
	}
	return announce;
}
