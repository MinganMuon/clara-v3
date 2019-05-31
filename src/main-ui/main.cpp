// main.cpp

#include "ui-framework.h"
#include "game-ui.h"

using namespace UIFramework;

void doMainMenu()
{
	UIBox mainmenubox = UIBox("Clara", 1,1, 16,16);
	UIButton playbutton = UIButton("", "Play", 4,3, 10,5);
	playbutton.selected = true;
	UIButton quitbutton = UIButton("", "Quit", 4,10, 10,5);

	bool exit = false;
	while (!exit) {
		clearscreen();
		mainmenubox.draw();
		playbutton.draw();
		quitbutton.draw();

		int ch = getch();

		switch (ch) {
			case KEY_UP:
			case KEY_DOWN:
				if (playbutton.selected) {
					playbutton.selected = false;
					quitbutton.selected = true;
				} else {
					playbutton.selected = true;
					quitbutton.selected = false;
				}
				break;
			case '\n':
				if (playbutton.selected) {
					doGameSettingsMenu();					
				} else {
					exit = true;
				}
				break;
		}
	}
}

int main()
{
	if (initncurses(50,80))
	{
		doMainMenu();
		endncurses();
	}

	return 0;
}

