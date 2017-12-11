/*
 * Server.cpp
 *
 *  Created on: Dec 11, 2017
 *      Author: naveh
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "../include/Server.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port) : port(port), serverSocket(0) {
	cout << "Server" << endl;
}

void Server::start() {
	// Create a socket point:
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		throw "Error opening socket";
	}
	// Assign a local address:
	struct sockaddr_in serverAddress;
	bzero((void *)&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);
	if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
		throw "Error on binding";
	}
	// Start listening:
	listen(serverSocket, MAX_CONNECTED_CLIENTS);

	// Define client socket structure:
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen;

	while (true) {
		cout << "Waiting for client connection..." << endl;

		// Accept first player:
		int client1Socket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
		cout << "Client 1 connected!" << endl;
		if (client1Socket == -1) {
			throw "Error on accept first player";
		}

		// Accept second player:
		int client2Socket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
		cout << "Client 2 connected!" << endl;
		if (client2Socket == -1) {
			throw "Error on accept first player";
		}

		// Start the game session.
		handleClients(client1Socket,client2Socket);
	}
}

void Server::handleClients(int player1Socket, int player2Socket) {
	// Sending both players what their turn is, announcing them the game started:
	sendTurn(player1Socket, BLACK_PLAYER);
	sendTurn(player2Socket, WHITE_PLAYER);

	int gamestate, turn = 0;
	int playerSockets[2] = {player1Socket, player2Socket};
	while (true) {
		// Announce a player it his turn and we are waiting for input:
		announceTurn(playerSockets[turn]);

		// Get current game state from player:
		gamestate = getGamestate(playerSockets[turn]);
		if (gamestate == GAMESTATE_NO_MOVES_AVAILABLE) {
			// In case no available moves for player, don't wait for getting a move.
			cout << "No available moves for player." << endl;
			turn = (turn + 1) % 2; // Swap turn;
			continue;
		}
		if (gamestate == GAMESTATE_GAME_OVER) {
			// In case game over, wait for other player to announce too, and d/c players.
			cout << "Game over. Disconnect players" << endl;
			turn = (turn + 1) % 2; // Swap turn;
			announceTurn(playerSockets[turn]);
			gamestate = getGamestate(playerSockets[turn]);
			if (gamestate != GAMESTATE_GAME_OVER) {
				throw "Error, players have different game";
			}
			close(player1Socket);
			close(player2Socket);
			return;
		}
		Point move = getMove(playerSockets[turn]);
		turn = (turn + 1) % 2; // Swap turn;
		// Send given move to player:
		sendMove(playerSockets[turn],move);
	}
}

void Server::sendTurn(int clientSocket, int turn) {
	int n = write(clientSocket, &turn, sizeof(turn));
	if (n == -1) {
		cout << "Error writing turn to socket" << endl;
		return;
	}
}

int Server::getGamestate(int clientSocket) {
	int gamestate, n;
	n = read(clientSocket, &gamestate, sizeof(gamestate));
	if (n == -1) {
		cout << "Error reading current game's state" << endl;
		return -1;
	}
	cout << "Got Game's state: " << gamestate << endl;
	return gamestate;
}

void Server::sendMove(int clientSocket, Point prevMove) {
	int x = prevMove.getX(), y = prevMove.getY(), n;
	n = write(clientSocket, &x, sizeof(x));
	if (n == -1) {
		cout << "Error writing to socket" << endl;
		return;
	}
	n = write(clientSocket, &y, sizeof(y));
	if (n == -1) {
		cout << "Error writing to socket" << endl;
		return;
	}
}

void Server::announceTurn(int clientSocket) {
	int announce = 1;
	int n = write(clientSocket, &announce, sizeof(announce));
	if (n == -1) {
		cout << "Error writing to socket" << endl;
		return;
	}
}

Point Server::getMove(int clientSocket) {
	int x,y,n;
	// Reading current player's move:
	n = read(clientSocket, &x, sizeof(x));
	if (n == -1) {
		cout << "Error reading x value." << endl;
		return Point(0,0);
	}
	if (n == 0) {
		cout << "Client disconnected." << endl;
		return Point(0,0);
	}
	n = read(clientSocket, &y, sizeof(y));
	if (n == -1) {
		cout << "Error reading y value." << endl;
		return Point(0,0);
	}

	// Returning move:
	cout << "Got play (" << x << ", " << y << ")" << endl;
	return Point(x, y);
}

void Server::stop() {
	close(serverSocket);
}
