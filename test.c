
#include <signal.h>
#include <stdio.h>
#include <curses.h>
#include <ncurses.h>
#include <strings.h>
#include <stdlib.h> // Added for memory allocation

typedef union _win_border_struct {
    chtype leftSide, rightSide, topSide, bottomSide,
           topLeft, topRight, bottomLeft, bottomRight;
} BORDER;

typedef struct _win_struct {
    BORDER border;
} WIN;

void renderMainWindow(WIN *win);
void initUnion(BORDER *border);

int main() {
    /* Initialize curses */
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    WIN *win = malloc(sizeof(WIN)); // Allocate memory for WIN
    BORDER *border = malloc(sizeof(BORDER)); // Allocate memory for BORDER

    if (win == NULL || border == NULL) {
        // Handle memory allocation failure
        perror("Memory allocation failed");
        endwin(); // End curses mode
        return 1; // Exit with an error code
    }

    initUnion(border);
    win->border = *border; // Copy the BORDER structure into the WIN structure

    renderMainWindow(win);
    refresh();

    int c;
    while ((c = getch()) != 'q') {
        // Your code here
    }

    free(win); // Free allocated memory for WIN
    free(border); // Free allocated memory for BORDER

    endwin(); // End curses mode
    return 0;
}

void initUnion(BORDER *border) {
    border->leftSide = '|';
    border->rightSide = '|';
    border->topSide = '-';
    border->bottomSide = '-';
    border->topLeft = '+';
    border->topRight = 'o';
    border->bottomLeft = '[';
    border->bottomRight = ']';
}

void renderMainWindow(WIN *win) {
    int x, y, width, height;
    x = 10;
    y = 10;
    width = 10;
    height = 10;

    mvaddch(y, x, win->border.topLeft);
    mvaddch(y, x + width, win->border.topRight);
    mvaddch(y + height, x, win->border.bottomLeft);
    mvaddch(y + height, x + width, win->border.bottomRight);
}
