#include "../include/Game.h"

Game::Game()
{
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    board = new Board(width,height);
    board->setMark(width / 2 , height / 2 + 1, PLAYER_X);
    board->setMark(width / 2 + 1, height / 2, PLAYER_X);
    board->setMark(width / 2 , height / 2, PLAYER_O);
    board->setMark(width / 2  + 1, height / 2 + 1, PLAYER_O);
    current_turn = PLAYER_X;
    this->current_available_moves.reserve(width * height);
}

Game::~Game()
{
}

ostream &operator <<(ostream &out, const Game &game)
{
    out << *game.board;
    return out;
}

/**
 * Check if move (x,y) is a valid move for current player.
 * If it is, will return the sum of enemy blocks taken during this play.
 * @param x parameter x
 * @param y parameter y
 * @return 0 if no valid move. Else will return the amount of coins would be
 * flipped during this play.
 */
int Game::isValidMove(int x, int y)
{
    int sum = 0,temp;
    if (this->board->getMark(x, y) != BLANK)
    {
        return 0;
    }
    if (temp = this->checkEast(x, y, FALSE) > 0)
    {
        sum += temp;
    }
    if (temp = this->checkSouthEast(x, y, FALSE) > 0)
    {
        sum += temp;
    }
    if (temp = this->checkSouth(x, y, FALSE) > 0)
    {
        sum += temp;
    }
    if (temp = this->checkSouthWest(x, y, FALSE) > 0)
    {
        sum += temp;
    }
    if (temp = this->checkWest(x, y, FALSE) > 0)
    {
        sum += temp;
    }
    if (temp = this->checkNorthWest(x, y, FALSE) > 0)
    {
        sum += temp;
    }
    if (temp = this->checkNorth(x, y, FALSE) > 0)
    {
        sum += temp;
    }
    if (temp = this->checkNorthEast(x, y, FALSE) > 0)
    {
        sum += temp;
    }
    return sum;
}

/**
 * Run all over the board, checking for all available moves for current player.
 * Updates the current_available_moves vector.
 * @return the maximum of coins that can be flipped during this move.
 */
int Game::availableMoves()
{
    vector<Point> temp_v;
    int temp_max = 0, temp;
    for (int i = 1; i < this->board->getHeight() + 1; i++)
    {
        for (int j = 1; j < this->board->getWidth() + 1; j++)
        {
            if (temp = this->isValidMove(i, j))
            {
                if (temp > temp_max)
                {
                    temp_max = temp;
                }
                temp_v.push_back(Point(i, j));
            }
        }
    }
    this->current_available_moves = temp_v;
    return temp_max;
}

/**
 * Check upper direction, in vertical line.
 * @param x block checked
 * @param y block checked
 * @param flip should flip found coins, or just checking if move available
 * @return the amount of coins flippable (or flipped) found.
 */
int Game::checkNorth(int x, int y, int flip)
{
    // If there is a blank block or border block on the side checked:
    if (board->getMark(x, y - 1) == BLANK || board->getMark(x, y - 1) == BORDER)
    {
        return -99;
    }
    int flippables = 0;
    // If there is a frendly block on the side checked:
    if (board->getMark(x, y - 1) != current_turn)
    {
        // There is an enemy block on the side checked,
        // we add one and check how many emeny blocks are there:
        flippables = 1 + checkNorth(x, y - 1, flip);
    }
    // If there is a positive greater than 0 number of flippables, it means
    // we got a line of enemy blocks that end with a friendly blocks.
    if (flippables > 0 && flip == TRUE)
    {
        // if flippables > 0 and flip is 1, we flip current block to our.
        board->setMark(x, y - 1, current_turn);
    }
    return flippables;
}

/**
 * Check upper right direction, in diagonal line.
 * @param x block checked
 * @param y block checked
 * @param flip should flip found coins, or just checking if move available
 * @return the amount of coins flippable (or flipped) found.
 */
int Game::checkNorthEast(int x, int y, int flip)
{
    if (board->getMark(x + 1, y - 1) == BLANK || board->getMark(x + 1, y - 1) == BORDER)
    {
        return -99;
    }
    int flippables = 0;
    if (board->getMark(x + 1, y - 1) != current_turn)
    {
        flippables = 1 + checkNorthEast(x + 1, y - 1, flip);
    }
    if (flippables > 0 && flip == TRUE)
    {
        board->setMark(x + 1, y - 1, current_turn);
    }
    return flippables;
}

/**
 * Check right direction, in horizontal line.
 * @param x block checked
 * @param y block checked
 * @param flip should flip found coins, or just checking if move available
 * @return the amount of coins flippable (or flipped) found.
 */
int Game::checkEast(int x, int y, int flip)
{
    if (board->getMark(x + 1, y) == BLANK || board->getMark(x + 1, y) == BORDER)
    {
        return -99;
    }
    int flippables = 0;
    if (board->getMark(x + 1, y) != current_turn)
    {
        flippables = 1 + checkEast(x + 1, y, flip);
    }
    if (flippables > 0 && flip == TRUE)
    {
        board->setMark(x + 1 , y, current_turn);
    }
    return flippables;
}

/**
 * Check lower-right direction, in diagonal line.
 * @param x block checked
 * @param y block checked
 * @param flip should flip found coins, or just checking if move available
 * @return the amount of coins flippable (or flipped) found.
 */
int Game::checkSouthEast(int x, int y, int flip)
{
    if (board->getMark(x + 1, y + 1) == BLANK || board->getMark(x + 1, y + 1) == BORDER)
    {
        return -99;
    }
    int flippables = 0;
    if (board->getMark(x + 1, y + 1) != current_turn)
    {
        flippables = 1 + checkSouthEast(x + 1, y + 1, flip);
    }
    if (flippables > 0 && flip == TRUE)
    {
        board->setMark(x + 1, y + 1, current_turn);
    }
    return flippables;
}

/**
 * Check lower direction, in vertical line.
 * @param x block checked
 * @param y block checked
 * @param flip should flip found coins, or just checking if move available
 * @return the amount of coins flippable (or flipped) found.
 */
int Game::checkSouth(int x, int y, int flip)
{
    if (board->getMark(x, y + 1) == BLANK || board->getMark(x, y + 1) == BORDER)
    {
        return -99;
    }
    int flippables = 0;
    if (board->getMark(x, y + 1) != current_turn)
    {
        flippables = 1 + checkSouth(x, y + 1, flip);
    }
        if (flippables > 0 && flip == TRUE)
    {
        board->setMark(x, y, current_turn);
    }
    return flippables;
}

/**
 * Check lower-left direction, in diagonal line.
 * @param x block checked
 * @param y block checked
 * @param flip should flip found coins, or just checking if move available
 * @return the amount of coins flippable (or flipped) found.
 */
int Game::checkSouthWest(int x, int y, int flip)
{
    if (board->getMark(x - 1, y + 1) == BLANK || board->getMark(x - 1, y + 1) == BORDER)
    {
        return -99;
    }
    int flippables = 0;
    if (board->getMark(x - 1, y + 1) != current_turn)
    {
        flippables = 1 + checkSouthWest(x - 1, y + 1, flip);
    }
    if (flippables > 0 && flip == TRUE)
    {
        board->setMark(x - 1, y + 1, current_turn);
    }
    return flippables;
}

/**
 * Check left direction, in horizontal line.
 * @param x block checked
 * @param y block checked
 * @param flip should flip found coins, or just checking if move available
 * @return the amount of coins flippable (or flipped) found.
 */
int Game::checkWest(int x, int y, int flip)
{
    if (board->getMark(x - 1, y) == BLANK || board->getMark(x - 1, y) == BORDER)
    {
        return -99;
    }
    int flippables = 0;
    if (board->getMark(x - 1, y) != current_turn)
    {
        flippables = 1 + checkWest(x - 1, y, flip);
    }
    if (flippables > 0 && flip == TRUE)
    {
        board->setMark(x - 1, y, current_turn);
    }
    return flippables;
}

/**
 * Check upper-left direction, in diagonal line.
 * @param x block checked
 * @param y block checked
 * @param flip should flip found coins, or just checking if move available
 * @return the amount of coins flippable (or flipped) found.
 */
int Game::checkNorthWest(int x, int y, int flip)
{
    if (board->getMark(x - 1, y - 1) == BLANK || board->getMark(x - 1, y - 1) == BORDER)
    {
        return -99;
    }
    int flippables = 0;
    if (board->getMark(x - 1, y - 1) != current_turn)
    {
        flippables = 1 + checkNorthWest(x - 1, y - 1, flip);
    }
    if (flippables > 0 && flip == TRUE)
    {
        board->setMark(x - 1, y - 1, current_turn);
    }
    return flippables;
}

/**
 * Play one turn with given parameters. If given parameters are not a valid move,
 * returns 0.
 * @param x
 * @param y
 * @return
 */
int Game::playTurn(int x, int y)
{
    if (!this->isValidMove(x, y))
    {
        return FALSE;
    }
    this->board->setMark(x, y, current_turn);
    this->checkEast(x, y, TRUE);
    this->checkNorth(x, y, TRUE);
    this->checkNorthEast(x, y, TRUE);
    this->checkNorthWest(x, y, TRUE);
    this->checkSouth(x, y, TRUE);
    this->checkSouthEast(x, y, TRUE);
    this->checkSouthWest(x, y, TRUE);
    this->checkWest(x, y, TRUE);
    return TRUE;
}

/**
 * Start a session of gameplay, which ends when both players don't have any moves left.
 * @return 1 if player O won, -1 if player X won, and 0 if there is a tie.
 */
int Game::gamePlay()
{
    int max_flippable, x, y, is_move_played, players_without_turns = 0;
    while (TRUE)
    {
        cout << "current board:" << endl << *this << endl;
        cout << "Current turn: " << this->board->markToChar(this->current_turn) << endl;
        max_flippable = this->availableMoves();
        // If both players have no available moves in a row, ends the game:
        if (players_without_turns == 2)
        {
            break;
        }
        // If no moves available for current player, start counting players without turns
        // and switch to the other player.
        if (this->current_available_moves.size() == 0)
        {
            players_without_turns++;
            cout << "You got no available moves." << endl;
            this->switchTurn();
            continue;
        }
        // If there are available moves for one of the players, reset counter.
        players_without_turns == 0;
        // Prints all available moves:
        cout << "You got " << this->current_available_moves.size() << " available Moves: " << endl;
        for (int i = 0; i < this->current_available_moves.size(); i++)
        {
            cout << this->current_available_moves.at(i);
            if (i < this->current_available_moves.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << endl << "Enter your move x,y:" << endl;
        do
        {
            cin >> x >> y;
            is_move_played = this->playTurn(x,y);
            if (is_move_played == FALSE)
            {
                cout << "Move not available. Please enter another move x,y:" << endl;
            }
        } while (is_move_played == FALSE);
        this->switchTurn();
    }
    cout << "No moves left for both players. Game Over!" << endl;
    return gameOver();
}


/**
 * Determine who won by counting all the blocks on the board,
 * and announce it.
 * @return 1 if Player O won, -1 if Player X won, and 0 if there is a tie.
 */
int Game::gameOver()
{
    int player_O = 0, player_X = 0;
    for (int i = 1; i <= board->getHeight(); i++)
    {
        for (int j = 1; j <= board->getWidth(); j++)
        {
            if (board->getMark(i,j) == PLAYER_O)
            {
                player_O++;
            }
            if (board->getMark(i,j)== PLAYER_X)
            {
                player_X++;
            }
        }
    }
    if (player_O > player_X)
    {
        cout << "Player O wins with " << player_O << " squares taken!" << endl;
        return PLAYER_O;
    }
    if (player_X > player_O)
    {
        cout << "Player X wins with " << player_X << " squares taken!" << endl;
        return PLAYER_X;
    }
    cout << "The game ends with a tie. Both players got " << player_O << " squares taken." << endl;
    return 0;
}


