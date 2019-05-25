// ui-framework.h

#ifndef UI_FRAMEWORK_H
#define UI_FRAMEWORK_H

#include <string>
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
		void toggleMark() { if (marked) { marked = false; } else { marked = true; } };

		bool marked;
		std::string text;
};

}

#endif

