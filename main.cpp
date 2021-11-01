// Main source file used to parse command-line arguments and begin game.

#include "board.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    if (argc != 4)
    {
        cerr << "Usage: ./a.out <height> <width> <mines>\n";
        return 1;
    }

    int moveR, moveC;

    int height = atoi(argv[1]);
    int width = atoi(argv[2]);
    int mines = atoi(argv[3]);

    // int action;
    char action;
    char buff[64];

    Board b{height, width};

    // initscr();
    // raw();
    // keypad(stdscr, TRUE);
    // noecho();

    scanf("%d", &moveR);
    scanf("%d", &moveC);

    // clock_t start = clock();
    b.generate(mines, moveR, moveC);
    b.click(moveR, moveC);
    // clock_t stop = clock();

    // double elapsed = (double)(stop - start) / CLOCKS_PER_SEC * 1000;

    // cout.precision(5);

    // b.printDebug(moveR, moveC);

    b.print();

    while (!b.isFailed())
    {
        scanf(" %c", &action);
        scanf("%d", &moveR);
        scanf("%d", &moveC);

        // action = getch();

        // switch (action)
        // {
        //     case KEY_UP:
        //         b.move(1);
        //         break;
        //     case KEY_DOWN:
        //         b.move(2);
        //         break;
        //     case KEY_LEFT:
        //         b.move(4);
        //         break;
        //     case KEY_RIGHT:
        //         b.move(8);
        //         break;
        //     case 'c':
        //         b.click(b.getR(), b.getC());
        //         break;
        //     case 'b':
        //         b.bigClick(b.getR(), b.getC());
        //         break;
        //     case 'm':
        //         b.mark(b.getR(), b.getC());
        //         break;
        //     default:
        //         cout << "dumbfuck\n";
        // }

        switch (action)
        {
            case 'c':
                b.click(moveR, moveC);
                break;
            case 'b':
                b.bigClick(moveR, moveC);
                break;
            case 'm':
                b.mark(moveR, moveC);
                break;
            default:
                cout << "dumb";
                scanf("%s", buff);
        }

        b.print();
        // b.cursesPrint();
    }

    // refresh();
    // getch();
    // endwin();

    // b.printDebug(firstmove_row, firstmove_col);

    // cout << "Board generated in " << elapsed << "ms\n\n";

    return 0;
}
