#include "../include/AI.h"

int AI::calculateBestMove(vector<Point> available_moves)
{
    Game game_copy;
    int best_x, best_y, current_score, worst_score, temp;
    // If given vector has no available moves, something went wrong.
    if (available_moves.size() == 0)
    {
        return 1;
    }
    // Set both best_x and best_y to be first move on the vector. If there is
    // only one move on the vector, it will return those.
    best_x = available_moves.at(0).getX();
    best_y = available_moves.at(0).getY();
    // Create a copy of the game in order to check the result of each move.
    game_copy = new Game(game);
    game_copy.playTurn(available_moves.at(0).getX(),available_moves.at(0).getY(), FALSE);
    current_score = game_copy.getCurrentScore(BLACK_PLAYER);
    // availableMoves() returns the maximum number of coins flipped while calculating
    // available moves for current player. So we set the maximum score of player X to be
    // the sum of Player X's current score, and the maximum of coins flipped on his available
    // moves.
    worst_score = current_score + game_copy.updateAvailableMoves();
    for (size_t i = 1; i < available_moves.size(); i++)
    {
        game_copy = new Game(game);
        game_copy.playTurn(available_moves.at(i).getX(),available_moves.at(i).getY(), FALSE);
        current_score = game_copy.getCurrentScore(BLACK_PLAYER);
        // If on this move, player X's maximum available score is lower than the previous worst
        // score, we would obviously want to keep this move instead.
        temp = current_score + game_copy.updateAvailableMoves();
        if (temp < worst_score)
        {
            worst_score = temp;
            best_x = available_moves.at(i).getX();
            best_y = available_moves.at(i).getY();
        }
    }
    this->x = best_x;
    this->y = best_y;
    return 0;
}
