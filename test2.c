#include <signal.h>
#include <stdio.h>
#include <curses.h>
#include <ncurses.h>
#include <strings.h>
#include <stdlib.h>

typedef struct _win_border_struct {
	chtype 	leftSide, rightSide, topSide, bottomSide,  
	 	topLeft, topRight, bottomLeft, bottomRight;

}BORDER;

typedef struct _win_struct {
	BORDER border;
}WIN;

void renderMainWindow(WIN *win);
void initUnion(BORDER *border);

int main() {
        /* Stuff We Will Need*/
        WIN *win = malloc(sizeof(WIN));
        BORDER *border = malloc(sizeof(BORDER));
        int c;


        /* Initialize curses */
	initscr();
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);


        initUnion(border);
        renderMainWindow(win);
        refresh();

        while((c = getch()) != 'q') {

        }
        free(win);
        free(border);

        endwin();
        return 0;
}

void initUnion(BORDER *border) {
        border->leftSide = '|';
        border->rightSide = '|';
        border->topSide = '-';
        border->bottomSide = '-';
        border->topLeft = '+';
        border->topRight = '+';
        border->bottomLeft = '+';
        border->bottomRight = '+';
}
void renderMainWindow(WIN *win) {
        int x, y, width, height;
        x = 2;
        y = 2;
        width = COLS / 2;
        height = LINES / 2;

        mvaddch(y,x, win->border.topLeft);
        mvaddch(y, x + width, win->border.topRight);
        mvaddch(y - height, x, win->border.topSide);
        mvaddch(y - height, x + width, win->border.rightSide);

}
