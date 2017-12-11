#include "../include/Game.h"

#include "../include/AI.h"

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
    this->available_moves.reserve(width * height);
}

Game::Game(Game *src)
{
    board = new Board(src->getBoard());
    current_turn = src->getTurn();
    this->available_moves.reserve(board->getWidth() * board->getHeight());
}

Game::~Game()
{
}

ostream &operator <<(ostream &out, const Game &game)
{
    out << *game.board;
    return out;
}

int Game::isValidMove(int x, int y) {
    int sum = 0,temp;
    if (this->board->getMark(x, y) != BLANK) {
        return 0;
    }
    temp = checkEast(x, y, FALSE);
    if (temp > 0) {
        sum += temp;
    }
    temp = checkSouthEast(x, y, FALSE);
    if (temp > 0) {
        sum += temp;
    }
    temp = checkSouth(x, y, FALSE);
    if (temp > 0) {
        sum += temp;
    }
    temp = checkSouthWest(x, y, FALSE);
    if (temp > 0) {
        sum += temp;
    }
    temp = checkWest(x, y, FALSE);
    if (temp > 0) {
        sum += temp;
    }
    temp = checkNorthWest(x, y, FALSE);
    if (temp > 0) {
        sum += temp;
    }
    temp = checkNorth(x, y, FALSE);
    if (temp > 0) {
        sum += temp;
    }
    temp = checkNorthEast(x, y, FALSE);
    if (temp > 0) {
        sum += temp;
    }
    return sum;
}

int Game::updateAvailableMoves()
{
    vector<Point> temp_v;
    int temp_max = 0, temp;
    for (int i = 1; i < this->board->getHeight() + 1; i++) {
        for (int j = 1; j < this->board->getWidth() + 1; j++) {
        	temp = isValidMove(i, j);
            if (temp) {
                if (temp > temp_max) {
                    temp_max = temp;
                }
			temp_v.push_back(Point(i, j));
            }
        }
    }
    available_moves = temp_v;
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

int Game::playTurn(int x, int y, int print)
{
    if (!this->isValidMove(x, y))
    {
        return FALSE;
    }
    if (print) {
		cout << "Player " << board->markToChar(this->current_turn) << " played:";
		cout << "(" << x << ", " << y << ")" << endl;
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

int Game::gamePlay(int is_multiplayer) {
    AI comp_player = AI(this);
    int players_without_turns = 0;

    while (true) {
    	printBoard();
        updateAvailableMoves(); // Update available moves vector.

        // If both players have no available moves in a row, ends the game:
        if (players_without_turns == 2) {
            break;
        }
        // If no moves available for current player, start counting players without turns
        // and switch to the other player.
        if (available_moves.size() == 0) {
            players_without_turns++;
            cout << "You got no available moves." << endl;
            switchTurn();
            continue;
        }
        // If there are available moves for one of the players, reset counter.
        players_without_turns = 0;

        // For player X on both multiplayer and signleplayer, and for player O on multiplayer:
        if ((is_multiplayer && current_turn == WHITE_PLAYER) || current_turn == BLACK_PLAYER) {
            printAvailableMoves();
            Point move = getPlayerInput();
            playTurn(move.getX(), move.getY(), TRUE);
        } else {
            // For player O on singleplayer:
            if (comp_player.calculateBestMove(available_moves)) {
                cout << "error passing available moves to AI" << endl;
                return 1;
            }
            playTurn(comp_player.getX(), comp_player.getY(), TRUE);
        }

        this->switchTurn();
    }
    cout << "No moves left for both players. Game Over!" << endl;
    return gameOver();
}

int Game::gameNetworkPlay() {
	// 1. Connect to server:
	Client client("127.0.0.1",9001);
	try {
		client.connectToServer();
	} catch (const char *msg) {
		cout << "Failed to connect to server. Reason: " << msg << endl;
		return -1;
	}

	// 2. Get player turn and permission to start game:
	cout << "Waiting for game to start..." << endl;
	int playerTurn = client.recievePlayerTurn();
	cout << "Both players connected! Your mark is " << board->markToChar(playerTurn) << endl;

    // 3. Start game:
    int turns_without_moves = 0;
    while (true) {
    	printBoard();
		updateAvailableMoves();

		// If it's been 2 turns without a move already, the game is over.
		// Tell server we are done, and finish the game.
		if (turns_without_moves >= 2) {
			client.recieveTurnAnnouncement();
			client.sendGamestate(GAMESTATE_GAME_OVER);
			break;
		}

        // If this is current player turn:
        if (current_turn == playerTurn) {
			// Wait for server:
			client.recieveTurnAnnouncement();

			// If no moves available, tell server and skip to opponent turn.
			if (available_moves.size() == 0) {
				turns_without_moves++;
				cout << "You got no available moves." << endl;
				client.sendGamestate(GAMESTATE_NO_MOVES_AVAILABLE);
				switchTurn();
				continue;
			}
			turns_without_moves = 0;
			client.sendGamestate(GAMESTATE_MOVES_AVAILABLE);
			printAvailableMoves();
			Point move = getPlayerInput();
			client.sendMove(move);
			playTurn(move.getX(), move.getY(), TRUE);

        } else {
        	if (available_moves.size() == 0) {
				// If opponent have no available moves, don't wait for receiving a move.
        		turns_without_moves++;
        		switchTurn();
				continue;
        	}
        	turns_without_moves = 0;
        	Point move = client.recieveMove();
        	playTurn(move.getX(), move.getY(), TRUE);
        }
		switchTurn();
    }
    cout << "No moves left for both players. Game Over!" << endl;
    return gameOver();
}

Point Game::getPlayerInput()
{
	int x, y;
	char buffer[16], x_string[16], y_string[16];
	cout << endl << "Enter your move x, y:" << endl;
    while (TRUE)
    {
    	cin.getline(buffer,16);
    	cout << buffer << endl;
    	int i = 0, j = 0;
    	while (buffer[i] >= '0' && buffer[i] <= '9') {
    		x_string[i] = buffer[i];
    		i++;
    	}
    	x_string[i] = '\0';
    	while (buffer[i] <= '0' || buffer[i] >= '9') {
			i++;
		}
    	while (buffer[i] >= '0' && buffer[i] <= '9') {
			y_string[j] = buffer[i];
			i++;
			j++;
		}
    	y_string[j] = '\0';
    	x = parseInteger(x_string);
    	y = parseInteger(y_string);
    	if (!x || !y) {
    		cout << "Input not in right pattern. Please enter input in x, y pattern:" << endl;
    		continue;
    	}
    	Point p = Point(x, y);
    	if (isPointAvailable(p,available_moves))
    	{
    		return p;
        }
    	cout << "Move " << p << " not available. Please enter another move x, y:" << endl;
    }
}

int Game::isPointAvailable(Point p, vector<Point> availablePlays)
{
	for (size_t i = 0; i < availablePlays.size(); i++)
	{
		if (p.getX() == availablePlays.at(i).getX() && p.getY() == availablePlays.at(i).getY())
		{
			return TRUE;
		}
	}
	return FALSE;
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

int Game::getCurrentScore(int player) {
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

void Game::printAvailableMoves() {
	// Prints all available moves:
	cout << "You got " << this->available_moves.size() << " available Moves: " << endl;
	for (size_t i = 0; i < this->available_moves.size(); i++) {
		cout << this->available_moves.at(i);
		if (i < this->available_moves.size() - 1) {
			cout << ", ";
		}
	}
}

void Game::printBoard() {
	cout << "current board:" << endl << *this << endl;
	cout << "Current turn: " << this->board->markToChar(this->current_turn) << endl;
}

int Game::parseInteger(char * str) {
	// If empty string, return 0;
	if (str == NULL || *str == '\0') {
		return 0;
	}
	int integer = 0, index = 0;
	while(str[index]) {
		if (str[index] >= '0' && str[index] <= '9') {
			integer = integer * 10  + (str[index] - '0');
		} else { // If contain non digit characters:
			return 0;
		}
		index++;
	}
	return integer;
}
