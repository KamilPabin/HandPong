#pragma once

#include <string>
using namespace std;

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
using namespace cv;
class Label
{
public:
	Label();
	Label(int _x,int _y, string _text);
	Label(int _x, int _y, string _text, int _fontSize);
		~Label();
	void Draw(Mat& obraz);

private:
	string text;
	Point wsp;
	int fontScale;
};

