#include "Label.h"


Label::Label()
{
	wsp = Point(0, 0);
	text = "";
	fontScale = 0;
}

Label::Label(int _x, int _y, string _text)
{
	text = _text;
	int cos;
	Size rozmiar = getTextSize(text, CV_FONT_HERSHEY_COMPLEX, 1, 1,&cos);
	wsp = Point(_x-rozmiar.width/2, _y+rozmiar.height/2);
	fontScale = 1;
}

Label::Label(int _x, int _y, string _text, int _fontScale)
{
	text = _text;
	int cos;
	Size rozmiar = getTextSize(text, CV_FONT_HERSHEY_COMPLEX, 1, 1, &cos);
	wsp = Point(_x - rozmiar.width / 2, _y + rozmiar.height / 2);
	fontScale = _fontScale;
}

Label::~Label()
{
}

void Label::Draw(Mat& obraz)
{
	putText(obraz, text, wsp, CV_FONT_HERSHEY_COMPLEX, fontScale, cvScalar(255, 255, 255), 2, CV_AA);
}