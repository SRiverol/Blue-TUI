#include <ncurses.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

char *choices[] = {
        "Quit",
};
WINDOW *create_newwin(int height, int width, int starty, int startx);
void recalculateWindows(WINDOW **mainWin, WINDOW **logWin, WINDOW **infoWin);
void refreshWindows(WINDOW **mainWin, WINDOW **logWin, WINDOW **infoWin);
void drawWinDetails(WINDOW **mainWin, WINDOW **logWin, WINDOW **infoWin);


int main(int argc, char *argv[]) {
        ITEM **items;
        MENU *menu;
        int choiceNumber, itemNumber;
        ITEM *selectedItem;

	WINDOW *mainWin;
        WINDOW *infoWin;
        WINDOW *logWin;

	int startx, starty, width, height;
	int ch;

	initscr();	
	cbreak();
        noecho();
	keypad(stdscr, TRUE);

        choiceNumber = ARRAY_SIZE(choices);
        items = (ITEM **)calloc(choiceNumber, sizeof(ITEM *));

        for(itemNumber = 0; itemNumber < choiceNumber; itemNumber++) {
                items[itemNumber] = new_item(choices[itemNumber], choices[itemNumber]);
        }
        items[choiceNumber] = (ITEM *)NULL;

        menu = new_menu((ITEM **)items);


        starty = 0;
        startx = 0;
        width = COLS;
        height = LINES - 1;
        mainWin = create_newwin(height, width, starty, startx);
        infoWin = create_newwin(height, width, starty, startx);

        recalculateWindows(&mainWin, &logWin, &infoWin);
        drawWinDetails(&mainWin, &logWin, &infoWin);
        refreshWindows(&mainWin, &logWin, &infoWin);
    
        set_menu_win(menu, mainWin);
        set_menu_sub(menu, derwin(mainWin, 30, 30, 1, 1));
        post_menu(menu);

        set_menu_mark(menu, " * ");
        wrefresh(mainWin);

        curs_set(0);
        refresh();
	
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

                switch (ch) {
                        case KEY_UP:
                                menu_driver(menu, REQ_UP_ITEM);
                                break;
                        case KEY_DOWN:
                                menu_driver(menu, REQ_DOWN_ITEM);
                                break;
                }

                refresh();
	}

        free_item(items[0]);
	free_item(items[1]);
	free_menu(menu);
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
