#include "Menu.h"


Menu::Menu()
{
	backGround = Vec3b(225, 64, 101);
	Button1 = Button(225, 100, 450, 150,"Start!");
	Button2 = Button(225, 175, 450, 225,"Koniec Gry");
	SplashScreen = Label(250, 70,"MultiGame",2);
}


Menu::~Menu()
{

}


Menu::ButtonCode Menu::Events(Cursor& kursor)
{
	if (Button1.isPressed(kursor))
	{
		return GAME_MENU;
	}
	else
	if (Button2.isPressed(kursor))
	{
		return LEAVE;
	}
	else
	{
		return NO_EVENTS;
	}
}

void Menu::UpdateScreen(Mat& obraz)
{
	obraz = Mat(obraz.rows, obraz.cols, CV_8UC3, backGround);
	Button1.Draw(obraz);
	Button2.Draw(obraz);
	SplashScreen.Draw(obraz);
}