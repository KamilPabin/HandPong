#pragma once

#include "opencv2\highgui\highgui.hpp"
using namespace cv;

#include "Cursor.h"

class Form
{
public:

	enum ButtonCode
	{
		START,
		LEAVE,
		MENU,
		PING_PONG,
		NO_EVENTS,
		GAME_MENU
	};

	Form();
	virtual ~Form();
	virtual ButtonCode Events(Cursor& kursor) = 0;
	/*
		Funkcja sprawdzaj¹ca czy któryœ z przycisków zosta³ naciœniêty(Klasa Button), zwraca odpowiedni ExitCode(ButtonCode)
	*/
	virtual void UpdateScreen(Mat& obraz) = 0;
	/*
		Funkcja rysuj¹ca na ekranie aplikacji komponenty z formy(Klasy Button, Label)
	*/
protected:
	Vec3b backGround;

};

