#include "../include/Game.h"
#include "../include/Ai.h"

Game::Game()
{
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    board = new Board(width,height);
    board->setMark(width / 2 , height / 2 + 1, BLACK_PLAYER);
    board->setMark(width / 2 + 1, height / 2, BLACK_PLAYER);
    board->setMark(width / 2 , height / 2, WHITE_PLAYER);
    board->setMark(width / 2  + 1, height / 2 + 1, WHITE_PLAYER);
    current_turn = BLACK_PLAYER;
    this->current_available_moves.reserve(width * height);
}

Game::Game(Game *src)
{
    board = new Board(src->getBoard());
    current_turn = src->getTurn();
    this->current_available_moves.reserve(board->getWidth() * board->getHeight());
}

Game::~Game()
{
}

ostream &operator <<(ostream &out, const Game &game)
{
    out << *game.board;
    return out;
}

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

int Game::gamePlay(int is_multiplayer)
{
    Ai comp_player = Ai(this);
    int max_flippable, x, y, is_move_played, players_without_turns = 0;
    if (!is_multiplayer)
    {

    }
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
        players_without_turns = 0;

        // For player X on both multiplayer and signleplayer, and for player O on multiplayer:
        if ((is_multiplayer && this->current_turn == WHITE_PLAYER) || this->current_turn == BLACK_PLAYER)
        {
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
        }
            // For player O on singleplayer:
        else
        {
            if (comp_player.calculateBestMove(this->current_available_moves))
            {
                cout << "error passing available moves to AI" << endl;
                return 1;
            }
            playTurn(comp_player.getX(), comp_player.getY());
            cout << "Player O played " << Point(comp_player.getX(), comp_player.getY()) << "." << endl;
        }

        this->switchTurn();
    }
    cout << "No moves left for both players. Game Over!" << endl;
    return gameOver();
}

int Game::gameOver()
{
    int player_O = 0, player_X = 0;
    for (int i = 1; i <= board->getHeight(); i++)
    {
        for (int j = 1; j <= board->getWidth(); j++)
        {
            if (board->getMark(i,j) == WHITE_PLAYER)
            {
                player_O++;
            }
            if (board->getMark(i,j)== BLACK_PLAYER)
            {
                player_X++;
            }
        }
    }
    if (player_O > player_X)
    {
        cout << "Player O wins with " << player_O << " squares taken!" << endl;
        return WHITE_PLAYER;
    }
    if (player_X > player_O)
    {
        cout << "Player X wins with " << player_X << " squares taken!" << endl;
        return BLACK_PLAYER;
    }
    cout << "The game ends with a tie. Both players got " << player_O << " squares taken." << endl;
    return 0;
}

int Game::getCurrentScore(int player)
{
    int white_player_coins = 0, black_player_coins = 0, white_player_score, black_player_score;
    for (int i = 1; i <= board->getHeight(); i++)
    {
        for (int j = 1; j <= board->getWidth(); j++)
        {
            if (board->getMark(i,j) == WHITE_PLAYER)
            {
                white_player_coins++;
            }
            if (board->getMark(i,j)== BLACK_PLAYER)
            {
                black_player_coins++;
            }
        }
    }
    black_player_score = black_player_coins - white_player_coins;
    white_player_score = white_player_coins - black_player_coins;
    // If given player is Black Player, returns his score, else returns white player score.
    return (player == BLACK_PLAYER) ? black_player_score : white_player_score;
}

