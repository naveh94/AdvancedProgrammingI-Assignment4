#ifndef GAME_H
#define GAME_H

#define DEFAULT_HEIGHT 8
#define DEFAULT_WIDTH 8


#include "Board.h"
#include <string>
#include <vector>
#include "Point.h"

class Game
{
    public:
        /** Default constructor */
        Game();
        /** Default destructor */
        ~Game();
        friend ostream& operator <<(ostream& out, const Game &game);
        void switchTurn() { this->current_turn *= (-1); }
        int availableMoves();

        // Commands for checking each direction from the block.
        // Will check recursivly for the direction given and will return
        // the number of flippable blocks on the direction given.
        // If flip = 1, will flip the stones on the direction given.
        int checkNorth(int x, int y, int flip);
        int checkNorthEast(int x, int y, int flip);
        int checkEast(int x, int y, int flip);
        int checkSouthEast(int x, int y, int flip);
        int checkSouth(int x, int y, int flip);
        int checkSouthWest(int x, int y, int flip);
        int checkWest(int x, int y, int flip);
        int checkNorthWest(int x, int y, int flip);

        int isValidMove(int x, int y);
        int playTurn(int x, int y);
        int gameOver();
        int gamePlay();

    protected:

    private:
        Board *board;
        int current_turn;
        vector<Point> current_available_moves;
};

#endif // GAME_H
