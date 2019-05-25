// main.cpp

#include "ui-framework.h"

using namespace UIFramework;

int main()
{
	if (initncurses(50,80))
	{
		clearscreen();
		UIBox box1 = UIBox("Test", 1,1, 10,10);
		box1.draw();
		UIButton button1 = UIButton("", "Test", 20,20, 10,5);
		button1.draw();
		UIButton button2 = UIButton("", "Testing", 15,15, 15,5);
		button2.selected = true;
		button2.draw();
		getch();

		endncurses();
	}

	return 0;
}

