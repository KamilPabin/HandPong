#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"

using namespace cv;

#include "Label.h"
#include "Cursor.h"

class Button
{
public:
	Button();
	Button(int _x1, int _y1, int _x2, int _y2);
	Button(int _x1, int _y1, int _x2, int _y2,string _text);
	~Button();
	void Draw(Mat& obraz);
	bool isPressed(Cursor kursor);
	

private:
	Label text;

	Point wsp1;
	Point wsp2;

	Vec3b Color;

	int deltaTime;

};

