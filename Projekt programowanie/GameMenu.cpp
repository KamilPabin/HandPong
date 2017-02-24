#include "GameMenu.h"


GameMenu::GameMenu()
{
	backGround = Vec3b(94, 217, 234);
	Button1 = Button(10, 100, 210, 150, "Ping Pong");
	Button2 = Button(400, 100, 600, 150, "Powrot");
	SplashScreen = Label(110, 70, "Wybierz gre", 1);
}


GameMenu::~GameMenu()
{
}

Form::ButtonCode GameMenu::Events(Cursor& kursor)
{
	if (Button1.isPressed(kursor))
	{
		return PING_PONG;
	}
	else
	if (Button2.isPressed(kursor))
	{
		return MENU;
	}
	else
		return NO_EVENTS;
}

void GameMenu::UpdateScreen(Mat& obraz)
{
	obraz = Mat(obraz.rows, obraz.cols, CV_8UC3 ,backGround);
	Button1.Draw(obraz);
	Button2.Draw(obraz);
	SplashScreen.Draw(obraz);
}