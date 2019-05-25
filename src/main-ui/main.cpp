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
				}
				break;
			case '\n':
				if (colorbox.selected) {
					colorwhitebutton.selected = true;
					colorbox.selected = false;
				} else if (colorwhitebutton.selected) {
					colorwhitebutton.toggleMark();
					colorblackbutton.toggleMark();
				} else if (colorblackbutton.selected) {
					colorblackbutton.toggleMark();
					colorwhitebutton.toggleMark();
				} else if (playbutton.selected) {
					exit = true;
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

