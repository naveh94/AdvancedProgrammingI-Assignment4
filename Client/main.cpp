/**
 * @name: Naveh Marchoom
 * @exercise: Ex3
 * @ID: 312275746
 */

#include <iostream>
#include "include/Game.h"
#define LOCAL_MULTIPLAYER 1
#define AI_SINGLEPLAYER 0

using namespace std;

int main()
{
    int gamemode = 0;
    Game game = Game();
    cout << "Choose an opponent type:" << endl;
	cout << "1. a human local player" << endl;
	cout << "2. An AI player" << endl;
	cout << "3. a remote player" << endl;
    do {
        cin >> gamemode;
        if (gamemode < 1 || gamemode > 3)
        {
            cout << "No such gamemode. Please choose again:" << endl;
        }
    } while (gamemode < 1 && gamemode > 3);
    cin.ignore(1,'\n');
    switch (gamemode) {
    case 1:
    	game.gamePlay(LOCAL_MULTIPLAYER);
    	break;
    case 2:
    	game.gamePlay(AI_SINGLEPLAYER);
    	break;
    case 3:
		game.gameNetworkPlay();
		break;
    default:
    	break;
    }
    return 0;
}
