// ui-framework.h

#ifndef UI_FRAMEWORK_H
#define UI_FRAMEWORK_H

#include <string>
#include <vector>
#include <ncurses.h>
#include <curses.h>

namespace UIFramework {

bool initncurses(int minrows, int mincols);
void endncurses();

void clearscreen();

class UIObject {
	public:
		UIObject(int thex, int they, int thewidth, int theheight) : x(thex), y(they), height(theheight), width(thewidth), selected(false), selectable(false) {};

		virtual void draw() = 0;

		unsigned int x, y;
		unsigned int height, width;
		bool selected;
		bool selectable;
};

class UIBox : public UIObject {
	public:
		UIBox(std::string thetitle, int thex, int they, int thewidth, int theheight) : UIObject(thex,they,thewidth,theheight), title(thetitle) { selectable = true; selected = false; };

		void draw();

		std::string title;
};

class UIButton : public UIBox {
	public:
		UIButton(std::string thetitle, std::string thetext, int thex, int they, int thewidth, int theheight) : UIBox(thetitle,thex,they,thewidth,theheight), text(thetext) { selectable = true; selected = false; marked = false; };

		void draw();

		bool marked;
		std::string text;
};

class UIMarkableSelector : public UIBox {
	public:
		UIMarkableSelector(std::string thetitle, int thex, int they, int thewidth, int theheight, std::vector<std::string> themarkables) : UIBox(thetitle, thex,they,thewidth,theheight), m_markables(themarkables) { selectable = true; selected = false; m_markedmarkable = 0; m_topmostdisplayedmarkable = 0; m_cursorposition = 0; };

		void draw();
		void movecursordown();
		void movecursorup();
		void markatcursor();
		std::string getmarkedmarkable();
	private:
		std::vector<std::string> m_markables;
		unsigned int m_markedmarkable; // index of marked markable
		unsigned int m_topmostdisplayedmarkable; // index of topmost displayed markable
		unsigned int m_cursorposition; // index of cursor
};

}

#endif

