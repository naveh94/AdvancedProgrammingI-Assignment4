#ifndef GAME_H
#define GAME_H

#define DEFAULT_HEIGHT 8
#define DEFAULT_WIDTH 8

#include "Board.h"
#include <string>
#include <vector>
#include "Point.h"
#include "Client.h"
#include <stdlib.h>

class Game
{
    public:
        /** Default constructor */
        Game();

        /**
         * Copy constructor
         * @param src source of the copy.
         */
        Game(Game *src);

        /** Default destructor */
        ~Game();

        /**
         * Operator overflow for <<. Will print the board.
         * @param out output
         * @param game input
         * @return out.
         */
        friend ostream& operator <<(ostream& out, const Game &game);


        /**
         * Used by copy constructor for getting current turn.
         * @return current_turn
         */
        int getTurn() { return current_turn; }

        /**
         * Used by AI for calculating best moves.
         * Calculate player score by calculating: player's coins - opposite player's coins
         * @param player the player checked
         * @return player's score.
         */
        int getCurrentScore(int player);

        /**
         * Run all over the board, checking for all available moves for current player.
         * Updates the current_available_moves vector.
         * @return the maximum of coins that can be flipped during this move.
         */
        int updateAvailableMoves();

        /**
         * Used for getting the board by copy constructor only.
         * @return a pointer to the board.
         */
        Board getBoard() const { return *board; }

        /**
         * Check if move (x,y) is a valid move for current player.
         * If it is, will return the sum of enemy blocks taken during this play.
         * @param x parameter x
         * @param y parameter y
         * @return 0 if no valid move. Else will return the amount of coins would be
         * flipped during this play.
         */
        int isValidMove(int x, int y);

        /**
        * Play one turn with given parameters.
        * @param x move parameter
        * @param y move parameter
        * @return 0 if not valid move. 1 if move played.
        */
        int playTurn(int x, int y, int print);

        /**
         * Start a session of gameplay.
         * If is_multiplayer is 1, will let user play both turns.
         * If is_multiplayer is 0, user plays only on Black Player moves, while White Player
         * moves are decided by AI.
         * @param is_multiplayer TRUE/FALSE
         * @return winning player: 1 for White Player, -1 for Black Player, 0 for tie.
         */
        int gamePlay(int is_multiplayer);

        /**
         * Start a new multiplayer session of the game using the server.
         * @return 1 for game won, and 0 for game lost.
         */
        int gameNetworkPlay();

        /**
         * Get available play input from the player.
         * @param availablePlays a vector of available plays.
         * @return a point chosen by player
         */
        Point getPlayerInput();

        /**
         * Return TRUE if point p is in available moves vector.
         * else, returns FALSE/
         * @param p Point
         * @param availablePlays vector of available moves.
         * @return TRUE/FALSE.
         */
        int isPointAvailable(Point p, vector<Point> availablePlays);

        /**
         * Determine winning player by counting coins on board.
         * @return 1 for White Player, -1 for Black Player, 0 for tie.
         */
        int gameOver();

        /**
         * For each of the following functions, check a single direction for available moves.
         * If flip is FALSE, only returns the amount of coins flippable by going in that direction.
         * If flip is TRUE, also flip the coins on available moves.
         * @param x block checked
         * @param y block checked
         * @param flip should flip found coins, or just checking if move available
         * @return the amount of coins flippable (or flipped) found.
         */
        // Check upper direction, in vertical line:
        int checkNorth(int x, int y, int flip);
        // Check upper right direction, in diagonal line:
        int checkNorthEast(int x, int y, int flip);
        // Check right direction, in horizontal line:
        int checkEast(int x, int y, int flip);
        // Check lower-right direction, in diagonal line:
        int checkSouthEast(int x, int y, int flip);
        // Check lower direction, in vertical line:
        int checkSouth(int x, int y, int flip);
        // Check lower-left direction, in diagonal line:
        int checkSouthWest(int x, int y, int flip);
        // Check left direction, in horizontal line:
        int checkWest(int x, int y, int flip);
        // Check upper-left direction, in diagonal line:
        int checkNorthWest(int x, int y, int flip);

    protected:

    private:
        Board *board;
        int current_turn;
        vector<Point> available_moves;
        void printBoard();
        void printAvailableMoves();
        void switchTurn() { this->current_turn *= (-1); }
        int parseInteger(char * str);
};

#endif // GAME_H
