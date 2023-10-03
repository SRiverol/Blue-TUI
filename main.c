#include <ncurses.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <menu.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void recalculateWindows(WINDOW **mainWin, WINDOW **logWin, WINDOW **infoWin);
void refreshWindows(WINDOW **mainWin, WINDOW **logWin, WINDOW **infoWin);
void drawWinDetails(WINDOW **mainWin, WINDOW **logWin, WINDOW **infoWin);


int main(int argc, char *argv[]) {
	WINDOW *mainWin;
        WINDOW *infoWin;
        WINDOW *logWin;

	int startx, starty, width, height;
	int ch;

	initscr();	
	cbreak();
	keypad(stdscr, TRUE);

        recalculateWindows(&mainWin, &logWin, &infoWin);
        drawWinDetails(&mainWin, &logWin, &infoWin);
        refreshWindows(&mainWin, &logWin, &infoWin);
	
	while((ch = getch()) != 'q') {	
                if(ch == KEY_RESIZE) {

                        // TURN THIS INTO A FUNCTION LATER
                        endwin();
                        refresh();
                        clear();

                        if(mainWin != NULL && logWin != NULL && infoWin != NULL) {
                                delwin(mainWin);
                                delwin(infoWin);
                                delwin(logWin);
                        }

                        if(COLS > 80 && LINES > 30) {
                                recalculateWindows(&mainWin, &logWin, &infoWin);
                                drawWinDetails(&mainWin, &logWin, &infoWin);
                                refreshWindows(&mainWin, &logWin, &infoWin);

                        } else {
                                addstr("Not enough space");
                        }
                        
                        refresh();
                }

                refresh();
	}
	endwin();			/* End curses mode		  */
	return 0;
}


void drawWinDetails(WINDOW **mainWin, WINDOW **logWin, WINDOW **infoWin) {
        mvwaddstr(*mainWin, 0, 1, "|Devices|");
        mvwaddstr(*logWin, 0, 1, "|BluetoothCTL Log|");
        mvwaddstr(*infoWin, 0, 1, "|Device Information|");
}
void refreshWindows(WINDOW **mainWin, WINDOW **logWin, WINDOW **infoWin) {
        refresh();
        wrefresh(*mainWin);
        wrefresh(*logWin);
        wrefresh(*infoWin);
}
void recalculateWindows(WINDOW **mainWin, WINDOW **logWin, WINDOW **infoWin) { 
        int height, width, starty, startx;
       
        //MAIN ATTRIBUTES

        //MAIN WINDOW POS MATH
	height = LINES - (LINES / 3);
	width = COLS / 2;
	starty = LINES / 3;	
	startx = 0;
        
	refresh();
	*mainWin = create_newwin(height, width, starty, startx);
        
        //LOG ATTRIBUTES
        wbkgd(*logWin, COLOR_PAIR(2));
        //LOG WINDOW POS MATH

        height = LINES - (LINES / 3);
        width = COLS - (COLS / 2);
        starty =  LINES / 3;	
        startx = COLS / 2;    
	
        refresh();
	*logWin = create_newwin(height, width, starty, startx);
        
        //INFO ATTRIBUTES

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
