// ui-framework.cpp

#include "ui-framework.h"

namespace UIFramework {

bool initncurses(int minrows, int mincols)
{
	initscr();
	keypad(stdscr, TRUE); 
	noecho();
	curs_set(FALSE);
	cbreak();

	if (LINES < minrows || COLS < mincols) {
		clear();
		mvaddstr(0, 0, "Error: the console isn't big enough!");
		mvaddstr(2, 0, "Press any key to quit.");
		move(3, 0);
		getch();
		endwin();
		return false;
	}

	clear();
	refresh();
	
	return true;
}

void endncurses()
{
	endwin();
}

void clearscreen()
{
	clear();
	refresh();
}

// note: draw functions require ncurses to be already initialized

void UIBox::draw()
{
	if (width <= 2 || height <= 2)
		return;

	// top
	mvaddstr(y,x,"+");
	mvaddstr(y,x+1,"-");
	if (title.length() > width-3)
	{
		title.erase(width-3);
	}
	mvaddstr(y,x+2, title.c_str());
	mvaddstr(y,x+2+title.length(),std::string(width-3-title.length(),'-').c_str());
	mvaddstr(y,x+width-1,"+");

	// sides
	for (unsigned int i=y+1; i != y+height-1; i++) {
		mvaddstr(i,x,"|");
		mvaddstr(i,x+width-1,"|");
	}

	// bottom
	mvaddstr(y+height-1,x,"+");
	for (unsigned int i=x+1; i != x+width-1; i++) {
		mvaddstr(y+height-1,i,"-");
	}
	mvaddstr(y+height-1,x+width-1,"+");
}

void UIButton::draw()
{
	if (selected) 
		attron(A_BOLD);
	UIBox::draw();
	if (selected) 
		attroff(A_BOLD);

	unsigned int inH = height-2;
	unsigned int inW = width-2;
	unsigned int midY;
	if (inH % 2) {
		midY = y+1+inH/2;
	} else {
		midY = y+1+(inH-1)/2;
	}
	unsigned int startX;
	if (inW % 2)
	{
		startX = x+inW/2;
	} else {
		startX = x+(inW-1)/2;
	}
	if (text.length() > inW)
	{
		text.erase(inW);
	}
	if (text.length() % 2)
	{
		startX = startX - text.length()/2 + 1;
	} else {
		startX = startX - (text.length()-1)/2 + 1;
	}
	if (selected) 
		attron(A_BOLD);
	mvaddstr(midY,startX,text.c_str());
	if (selected) 
		attroff(A_BOLD);
}

}

