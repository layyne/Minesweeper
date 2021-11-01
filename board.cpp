// Contains definitions and functions used in creation and generation of boards.

#include "board.hpp"

using namespace std;

// Constructor
Board::Board(int h, int w)
{
    int i, j;
    board.resize(h);
    for (i = 0; i < h; i++)
        board[i].resize(w);

    covered.resize(h);
    for (i = 0; i < h; i++)
    {
        covered[i].resize(w);
        for (j = 0; j < w; j++)
            covered[i][j] = true;
    }

    marked.resize(h);
    for (i = 0; i < h; i++)
        marked[i].resize(w);

    height = h;
    width = w;
    mines = 0;
    failed = false;

    cc = 0;
    cr = 0;
}

// Checks if a given coordinate in the form of (row, col) exists in the board
bool Board::inBounds(int row, int col)
{
    return row >= 0 && row < height && col >= 0 && col < width;
}

// Generates a board, ensuring that the first move is always safe
void Board::generate(int num_mines, int firstmove_row, int firstmove_col)
{
    mines = num_mines;

    reserveFirstMove(firstmove_row, firstmove_col);
    placeMines();
    getNumberTiles();
}

// Marks all of
void Board::reserveFirstMove(int firstmove_row, int firstmove_col)
{
    int i, j, row, col;

    for (i = -1; i < 2; i++)
        for (j = -1; j < 2; j++)
        {
            row = firstmove_row + i;
            col = firstmove_col + j;

            if (inBounds(row, col))
                board[row][col] = 11;
        }
}

void Board::placeMines()
{
    int i, row, col;

    for (i = 0; i < mines; i++)
    {
        row = rand() % height;
        col = rand() % width;

        while (board[row][col] >= 9)
        {
            row = rand() % height;
            col = rand() % width;
        }

        board[row][col] = 9;
    }
}

void Board::getNumberTiles()
{
    int i, j, cur;

    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
        {
            cur = board[i][j];

            if (cur == 11 || cur == 0)
                board[i][j] = countMines(i, j);
            else
                continue;
        }
}

int Board::countMines(int row, int col)
{
    int i, j, count = 0, r, c;

    for (i = -1; i < 2; i++)
        for (j = -1; j < 2; j++)
            if (i || j)
            {
                r = row + i;
                c = col + j;

                if (inBounds(r, c))
                {
                    if (board[r][c] == 11)
                        board[r][c] = 0;
                    else if (board[r][c] == 9)
                        ++count;
                }
            }

    return count;
}

bool Board::isFailed() { return failed; }

void Board::fail() { failed = true; }

void Board::print()
{
    int i, j, cur;

    // cout << "Board size " << height << "x" << width << ", " << mines
    //  << " mines\n\n";

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            cur = board[i][j];

            // if (i == firstmove_row && j == firstmove_col)
            // cout << "\033[94m%\033[m ";
            if (marked[i][j])
                cout << "\033[31mx\033[m ";
            else if (covered[i][j])
                cout << "# ";
            else if (cur == 9)
                cout << "\033[31mM\033[m ";
            else if (cur == 0)
                cout << "\033[35m0\033[m ";
            else
                cout << cur << " ";
        }

        cout << "\n";
    }
}

// void Board::cursesPrint()
// {
//     int i, j, cur;

//     mvprintw(0, 0, "");

//     for (i = 0; i < height; i++)
//     {
//         for (j = 0; j < width; j++)
//         {
//             cur = board[i][j];

//             // if (i == firstmove_row && j == firstmove_col)
//             // cout << "\033[94m%\033[m ";
//             if (i == cr && j == cc)
//                 addstr("% ");
//             else if (marked[i][j])
//                 addstr("x ");
//             else if (covered[i][j])
//                 addstr("# ");
//             else if (cur == 9)
//                 addstr("M ");
//             else
//                 printw("%d ", cur);
//         }

//         addch('\n');
//     }

//     addch('\n');
// }

void Board::printDebug(int firstmove_row, int firstmove_col)
{
    int i, j, cur;

    cout << "Board size " << height << "x" << width << ", " << mines
         << " mines\n\n";

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            cur = board[i][j];

            if (i == firstmove_row && j == firstmove_col)
                cout << "\033[94m%\033[m ";
            else if (cur == 9)
                cout << "\033[31mx\033[m ";
            else if (cur == 0)
                cout << "\033[35m0\033[m ";
            else
                cout << cur << " ";
        }

        cout << "\n";
    }
}

// bool Tile::isClickable()
// {
//     return !(revealed || flagged);
// }
