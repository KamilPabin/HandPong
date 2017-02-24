#pragma once
#include "Form.h"

#include "Button.h"
#include "Label.h"
class GameMenu :
	public Form
{
public:
	GameMenu();
	~GameMenu();
	ButtonCode Events(Cursor& kursor);
	void UpdateScreen(Mat& obraz);
private:
	Button Button1;
	Button Button2;
	Label SplashScreen;
};

