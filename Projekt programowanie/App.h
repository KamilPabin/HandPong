#pragma once
#include <iostream>
using namespace std;

#include "opencv2\highgui\highgui.hpp"
using namespace cv;

#include "Form.h"
#include "Menu.h"
#include "GameMenu.h"
#include "PingPong.h"

#include "Cursor.h"

class App
{
public:
	App(int width, int height);
	~App();
	void Run();

protected:

	int width;
	int height;
	bool czyKoniec;

	VideoCapture Kamera;
	Mat Obraz;
	Mat obrazKamery;
	Form* forma;
	Cursor kursor;
};

