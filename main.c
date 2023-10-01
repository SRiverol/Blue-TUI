#include <ncurses.h>
#include <curses.h>
#include <string.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void refreshWindows(WINDOW **mainWin, WINDOW **logWin, WINDOW **infoWin);

int main(int argc, char *argv[]) {
{	WINDOW *mainWin;
        WINDOW *infoWin;
        WINDOW *logWin;

	int startx, starty, width, height;
	int ch;

	initscr();			/* Start curses mode 		*/
	cbreak();			/* Line buffering disabled, Pass on*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/

        refreshWindows(&mainWin, &logWin, &infoWin);

	refresh();
        wrefresh(mainWin);
	attroff(COLOR_PAIR(1));
	
	while((ch = getch()) != 'q') {	
                if(getch() == KEY_RESIZE) {
                        refreshWindows(&mainWin, &logWin, &infoWin);
                }
	}
	endwin();			/* End curses mode		  */
	return 0;
}
}

void refreshWindows(WINDOW **mainWin, WINDOW **logWin, WINDOW **infoWin) {
        int height, width, starty, startx;

        //MAIN WINDOW POS MATH
	height = LINES - (LINES / 3);
	width = COLS / 2;
	starty = LINES / 3;	
	startx = 0;

	refresh();
	*mainWin = create_newwin(height, width, starty, startx);

        //LOG WINDOW POS MATH
        height = LINES - (LINES / 3);
        width = COLS - (COLS / 2);
        starty =  LINES / 3;	
        startx = COLS / 2;    

	refresh();
	*logWin = create_newwin(height, width, starty, startx);

        //INFO WINDOW POS MATH
        height = LINES / 3;
        width = COLS;
        starty =  0;	
        startx = 0;

        refresh();
        *infoWin = create_newwin(height, width, starty, startx);
}
WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}
