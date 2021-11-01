#include "board.hpp"

using namespace std;

int Board::countMarked(int row, int col)
{
    int i, j, count = 0, r, c;

    for (i = -1; i < 2; i++)
        for (j = -1; j < 2; j++)
            if (i || j)
            {
                r = row + i;
                c = col + j;

                if (inBounds(r, c) && marked[r][c])
                    ++count;
            }

    return count;
}

void Board::mark(int row, int col)
{
    if (!inBounds(row, col) || !covered[row][col])
        return;

    marked[row][col] = !marked[row][col];
}

void Board::click(int row, int col)
{
    int i, j, r, c;
    if (!inBounds(row, col))
    {
        cout << "out of bounds!\n";
        return;
    }

    if (marked[row][col])
    {
        cout << "marked\n";
        return;
    }

    covered[row][col] = false;

    if (board[row][col] == 9)
        fail();
    else if (board[row][col] == 0)
        for (i = -1; i < 2; i++)
            for (j = -1; j < 2; j++)
                if (i || j)
                {
                    r = row + i;
                    c = col + j;

                    if (inBounds(r, c) && covered[r][c])
                        click(r, c);
                }
}

void Board::bigClick(int row, int col)
{
    int i, j, r, c;

    if (!inBounds(row, col))
    {
        cout << "out of bounds!\n";
        return;
    }

    if (marked[row][col])
    {
        cout << "marked\n";
        return;
    }

    if (covered[row][col])
    {
        cout << "covered\n";
        return;
    }

    if (countMarked(row, col) == board[row][col])
        for (i = -1; i < 2; i++)
            for (j = -1; j < 2; j++)
                if (i || j)
                {
                    r = row + i;
                    c = col + j;

                    if (inBounds(r, c) && covered[r][c])
                        click(r, c);
                }
}

void Board::move(int move)
{
    switch (move)
    {
        case 1:
            if (inBounds(cr - 1, cc))
                --cr;
            break;
        case 2:
            if (inBounds(cr + 1, cc))
                ++cr;
            break;
        case 4:
            if (inBounds(cr, cc - 1))
                --cc;
            break;
        case 8:
            if (inBounds(cr, cc + 1))
                ++cc;
            break;
        default:
            cout << "how\n";
    }
}

int Board::getR() { return cr; }

int Board::getC() { return cc; }
