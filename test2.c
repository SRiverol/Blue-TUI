#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void refreshWindows(WINDOW **mainWin, WINDOW **logWin, WINDOW **infoWin);

int main(int argc, char *argv[]) {
    WINDOW *mainWin;
    WINDOW *infoWin;
    WINDOW *logWin;

    int startx, starty, width, height;
    int ch;

    initscr();          /* Start curses mode */
    start_color();
    cbreak();           /* Line buffering disabled, Pass on */
    keypad(stdscr, TRUE); /* I need that nifty F1 */

    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_WHITE);

    refreshWindows(&mainWin, &logWin, &infoWin);

    while ((ch = getch()) != 'q') {
        if (ch == KEY_RESIZE) {
            delwin(mainWin);
            delwin(infoWin);
            delwin(logWin);
            refreshWindows(&mainWin, &logWin, &infoWin);
            refresh();
        }
        refresh();
    }

    endwin(); /* End curses mode */
    return 0;
}

void refreshWindows(WINDOW **mainWin, WINDOW **logWin, WINDOW **infoWin) {
    int height, width, starty, startx;

    // MAIN ATTRIBUTES
    wbkgd(*mainWin, COLOR_PAIR(1));

    // MAIN WINDOW POS MATH
    height = LINES - (LINES / 3);
    width = COLS / 2;
    starty = LINES / 3;
    startx = 0;

    *mainWin = create_newwin(height, width, starty, startx);

    // LOG ATTRIBUTES
    wbkgd(*logWin, COLOR_PAIR(2));

    // LOG WINDOW POS MATH
    height = LINES - (LINES / 3);
    width = COLS - (COLS / 2);
    starty = LINES / 3;
    startx = COLS / 2;

    *logWin = create_newwin(height, width, starty, startx);

    // INFO ATTRIBUTES
    wbkgd(*infoWin, COLOR_PAIR(3));

    // INFO WINDOW POS MATH
    height = LINES / 3;
    width = COLS;
    starty = 0;
    startx = 0;

    *infoWin = create_newwin(height, width, starty, startx);
}

WINDOW *create_newwin(int height, int width, int starty, int startx) {
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);

    box(local_win, 0, 0);
    wrefresh(local_win);

    return local_win;
}

