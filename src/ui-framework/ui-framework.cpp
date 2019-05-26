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
	set_escdelay(0);

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
	// for now, I'll put it in a config or something later
	bool uselinedrawing = false;

	if (selected) 
		attron(A_BOLD);
	if (width <= 2 || height <= 2)
		return;

	// top
	mvaddstr(y,x,"+");
	if (uselinedrawing)
		mvaddch(y,x,ACS_ULCORNER);
	mvaddstr(y,x+1,"-");
	if (uselinedrawing)
		mvaddch(y,x+1,ACS_HLINE);
	if (title.length() > width-3)
	{
		title.erase(width-3);
	}
	mvaddstr(y,x+2, title.c_str());
	mvaddstr(y,x+2+title.length(),std::string(width-3-title.length(),'-').c_str());
	if (uselinedrawing) {
		for (unsigned int i=0; i<=width-3-title.length(); i++)
			mvaddch(y,x+2+title.length()+i,ACS_HLINE);
	}
	mvaddstr(y,x+width-1,"+");
	if (uselinedrawing)
		mvaddch(y,x+width-1,ACS_URCORNER);

	// sides
	for (unsigned int i=y+1; i != y+height-1; i++) {
		mvaddstr(i,x,"|");
		if (uselinedrawing)
			mvaddch(i,x,ACS_VLINE);
		mvaddstr(i,x+width-1,"|");
		if (uselinedrawing)
			mvaddch(i,x+width-1,ACS_VLINE);
	}

	// bottom
	mvaddstr(y+height-1,x,"+");
	if (uselinedrawing)
	mvaddch(y+height-1,x,ACS_LLCORNER);
	for (unsigned int i=x+1; i != x+width-1; i++) {
			mvaddstr(y+height-1,i,"-");
			if (uselinedrawing)
			mvaddch(y+height-1,i,ACS_HLINE);
	}
	mvaddstr(y+height-1,x+width-1,"+");
	if (uselinedrawing)
		mvaddch(y+height-1,x+width-1,ACS_LRCORNER);
	if (selected) 
		attroff(A_BOLD);
}

void UIButton::draw()
{
	UIBox::draw();

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
	if (selected || marked)
		attron(A_BOLD);
	mvaddstr(midY,startX,text.c_str());
	if (selected || marked) 
		attroff(A_BOLD);
}

void UIMarkableSelector::draw()
{
	UIBox::draw();

	unsigned int numtodisplay = height-2;
	if (numtodisplay > m_markables.size())
		numtodisplay = m_markables.size();
	for (unsigned int i = m_topmostdisplayedmarkable; i != m_topmostdisplayedmarkable+numtodisplay; i++)
	{
		if (m_markables[i].length() > width-2)
		{
			// should only run once per markable so perhaps move this to the constructor?
			m_markables[i].erase(width-2);
		}
		if (i == m_markedmarkable || (i == m_cursorposition && selected)) {
		       	attron(A_BOLD);	
			mvaddstr(y+1+(i-m_topmostdisplayedmarkable),x+1,m_markables[i].c_str());
			attroff(A_BOLD);
		} else {
			mvaddstr(y+1+(i-m_topmostdisplayedmarkable),x+1,m_markables[i].c_str());
		}
	}
}

void UIMarkableSelector::movecursordown()
{
	if (m_cursorposition < m_markables.size()-1)
	{
		m_cursorposition++;
		if (m_cursorposition > m_topmostdisplayedmarkable+height-2-1)
			m_topmostdisplayedmarkable++;
	}
}

void UIMarkableSelector::movecursorup()
{
	if (m_cursorposition > 0)
	{
		m_cursorposition--;
		if (m_cursorposition < m_topmostdisplayedmarkable)
			m_topmostdisplayedmarkable--;
	}
}

void UIMarkableSelector::markatcursor()
{
	m_markedmarkable = m_cursorposition;
}

}

