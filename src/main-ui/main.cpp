// main.cpp

#include "ui-framework.h"

using namespace UIFramework;

void doGameSettingsMenu()
{
	UIBox gamesettingsbox = UIBox("Game Settings", 1,1, 48,26);
	UIBox colorbox = UIBox("Your Color", 4,3, 16,16);
	colorbox.selected = true;
	UIBox aiselectorbox = UIBox("Opposing AI", 22,3, 24,16);
	UIButton playbutton = UIButton("", "Play!", 4,20, 42,5);

	UIButton colorwhitebutton = UIButton("", "Black", 7,6, 10,5);
	colorwhitebutton.marked = true;
	UIButton colorblackbutton = UIButton("", "White", 7,13, 10,5);

	UIMarkableSelector aiselector = UIMarkableSelector("AI Selection", 23,4, 22,14, std::vector<std::string>{"Random","random 2", "this ai is random", "this ai has a very very long name that it is using to test things", "12ply random", "Random 1", "Random 2", "Random 3", "Random 4", "Random 5", "Random 6", "Random 7", "Random 8", "Random 9", "Random 10", "Random 11", "Random 12", "Random 13"});

	bool wascolorboxlast = true;
	bool exit = false;
	while (!exit) {
		clearscreen();
		gamesettingsbox.draw();
		colorbox.draw();
		aiselectorbox.draw();
		playbutton.draw();
		colorwhitebutton.draw();
		colorblackbutton.draw();
		aiselector.draw();

		int ch = getch();

		switch (ch) {
			case KEY_UP:
				if (playbutton.selected) {
					playbutton.selected = false;
					if (wascolorboxlast) {
						colorbox.selected = true;
					} else {
						aiselectorbox.selected = true;
					}
				} else if (colorblackbutton.selected) {
					colorblackbutton.selected = false;
					colorwhitebutton.selected = true;
				} else if (aiselector.selected) {
					aiselector.movecursorup();
				}
				break;
			case KEY_DOWN:
				if (colorbox.selected) {
					wascolorboxlast = true;
					colorbox.selected = false;
					playbutton.selected = true;
				} else if (aiselectorbox.selected) {
					wascolorboxlast = false;
					aiselectorbox.selected = false;
					playbutton.selected = true;
				} else if (colorwhitebutton.selected) {
					colorblackbutton.selected = true;
					colorwhitebutton.selected = false;
				} else if (aiselector.selected) {
					aiselector.movecursordown();
				}
				break;
			case KEY_RIGHT:
				if (colorbox.selected) {
					colorbox.selected = false;
					aiselectorbox.selected = true;
				}
				break;
			case KEY_LEFT:
				if (aiselectorbox.selected) {
					colorbox.selected = true;
					aiselectorbox.selected = false;
				}
				break;
			case 27: // escape key
				if (colorwhitebutton.selected) {
					colorwhitebutton.selected = false;
					colorbox.selected = true;
				} else if (colorblackbutton.selected) {
					colorblackbutton.selected = false;
					colorbox.selected = true;
				} else if (aiselector.selected) {
					aiselector.selected = false;
					aiselectorbox.selected = true;
				}
				break;
			case '\n':
				if (colorbox.selected) {
					colorwhitebutton.selected = true;
					colorbox.selected = false;
				} else if (colorwhitebutton.selected) {
					colorwhitebutton.marked = true;
					colorblackbutton.marked = false;
				} else if (colorblackbutton.selected) {
					colorwhitebutton.marked = false;
					colorblackbutton.marked = true;
				} else if (playbutton.selected) {
					exit = true;
				} else if (aiselectorbox.selected) {
					aiselector.selected = true;
					aiselectorbox.selected = false;
				} else if (aiselector.selected) {
					aiselector.markatcursor();
				}
				break;
		}
	}
}

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

