#include <iostream>

using namespace std;

const int BOARDSIZE = 8;
const char EMPTY = '.';
const char BLACK = 'X';
const char WHITE = 'O';


static void initializeBoard(char board[BOARDSIZE][BOARDSIZE])
{
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            board[i][j] = EMPTY;
        }
    }
    int mid = 0;
    mid = BOARDSIZE / 2;
    board[mid - 1][mid - 1] = WHITE;
    board[mid][mid] = WHITE;
    board[mid - 1][mid] = BLACK;
    board[mid][mid - 1] = BLACK;
}

static void printBoard(const char board[BOARDSIZE][BOARDSIZE])
{
    cout << "  A B C D E F G H\n";
    for (int i = 0; i < BOARDSIZE; i++)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < BOARDSIZE; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
static bool isValidMove(const char board[BOARDSIZE][BOARDSIZE], int row, int col, char player)
{
    if (row < 0 || row >= BOARDSIZE || col < 0 || col >= BOARDSIZE || board[row][col] != EMPTY)
        return false;

    char opponent = (player == BLACK) ? WHITE : BLACK;
    bool valid = false;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            int r = row + i, c = col + j;
            bool foundOpponent = false;

            while (r >= 0 && r < BOARDSIZE && c >= 0 && c < BOARDSIZE)
            {
                if (board[r][c] == opponent)
                {
                    foundOpponent = true;
                }
                else if (board[r][c] == player)
                {
                    if (foundOpponent) valid = true;
                    break;
                }
                else
                {
                    break;
                }
                r += i;
                c += j;
            }
        }
    }
    return valid;
}

static void makeMove(char board[BOARDSIZE][BOARDSIZE], int row, int col, char player)
{
    board[row][col] = player;
    char opponent = (player == BLACK) ? WHITE : BLACK;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            int r = row + i, c = col + j;
            char toFlip[BOARDSIZE][2]{};
            int flipCount = 0;

            while (r >= 0 && r < BOARDSIZE && c >= 0 && c < BOARDSIZE)
            {
                if (board[r][c] == opponent)
                {
                    toFlip[flipCount][0] = r;
                    toFlip[flipCount][1] = c;
                    flipCount++;
                }
                else if (board[r][c] == player)
                {
                    for (int i = 0; i < flipCount; ++i)
                    {
                        board[toFlip[i][0]][toFlip[i][1]] = player;
                    }
                    break;
                }
                else
                {
                    break;
                }
                r += i;
                c += j;
            }
        }
    }
}
static bool hasValidMoves(const char board[BOARDSIZE][BOARDSIZE], char player)
{
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            if (isValidMove(board, i, j, player))
                return true;

        }
    }
    return false;
}
static void aiMove(char board[BOARDSIZE][BOARDSIZE], char player)
{
    for (int row = 0; row < BOARDSIZE; ++row)
    {
        for (int col = 0; col < BOARDSIZE; ++col)
        {
            if (isValidMove(board, row, col, player))
            {
                makeMove(board, row, col, player);
                cout << "AI plays at " << endl;
                return;
            }
        }
    }
}

int main() {
    char board[BOARDSIZE][BOARDSIZE];
    initializeBoard(board);
    char currentPlayer = BLACK;

    while (true)
    {
        printBoard(board);
        if (!hasValidMoves(board, currentPlayer))
        {
            cout << "No valid moves for " << currentPlayer << " Game over!" << endl;
            break;
        }

        if (currentPlayer == BLACK)
        {
            int row;
            char colChar;
            cout << "Player " << currentPlayer << endl;
            cin >> colChar >> row;
            int col = colChar - 'A';
            row -= 1;

            if (isValidMove(board, row, col, currentPlayer))
            {
                makeMove(board, row, col, currentPlayer);
                currentPlayer = WHITE;
            }
            else
            {
                cout << "Invalid move. Try again." << endl;
            }
        }
        else
        {
            aiMove(board, currentPlayer);
            currentPlayer = BLACK;
        }
    }

    return 0;
}