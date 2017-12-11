/*
 * main.cpp
 *
 *  Created on: Dec 11, 2017
 *      Author: naveh
 */
#include "include/Server.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
	Server server(9001);
	try {
		server.start();
	} catch (const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		return -1;
	}
	return 0;
}
