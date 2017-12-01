/**
 * @name: Naveh Marchoom
 * @exercise: Ex3
 * @ID: 312275746
 */

#include <iostream>
#include "include/Game.h"

using namespace std;

int main()
{
    int gamemode;
    Game b = Game();
    cout << "Please choose gamemode:" << endl;
    do
    {
        cout << "Choose 1 for Multiplayer mode, or 0 for Single Player mode:" << endl;
        cin >> gamemode;
        if (gamemode != 1 && gamemode != 0)
        {
            cout << "No such gamemode. Please choose again." << endl;
        }
    }
    while (gamemode != 0 && gamemode !=1);
    string mode_name = (gamemode) ? "Multiplayer" : "Single Player";
    cout << "You chose " << mode_name << "mode." << endl;
    b.gamePlay(gamemode);
    return 0;
}
