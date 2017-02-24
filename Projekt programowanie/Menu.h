#pragma once
#include "Form.h"
#include "Button.h"
#include "Label.h"

#include "Cursor.h"

#include <iostream>
using namespace std;

class Menu :
	public Form
{
public:
	Menu();
	~Menu();
	ButtonCode Events(Cursor& kursor);
	void UpdateScreen(Mat& obraz);
private:

	Button Button1;
	Button Button2;
	Label SplashScreen;
};

