#ifndef EX2_AI_H
#define EX2_AI_H

#include "Game.h"

class AI {
public:
    /** Default constructor */
    AI(Game *game) : game(game) {}
    /** Default destructor */
    ~AI() {}
    /**
     * Get a vector of available moves, and check for each of them which move
     * will result in other player having less successful moves.
     * Will set x and y to be the best move currently available.
     * @param available_moves vector of available moves.
     * @return 0 if everything went fine. 1 if something went wrong.
     */
    int calculateBestMove(vector<Point> available_moves);
    /** Get the x value of the best play.
     * @return The current value of x
     */
    int getX() const { return x; }
    /** Get the y value of the best play.
     * @return The current value of y
     */
    int getY() const { return y; }

protected:

private:
    Game *game;
    int x;
    int y;
};


#endif //EX2_AI_H
