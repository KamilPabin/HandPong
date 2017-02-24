#include "Button.h"

Button::Button()
{
	wsp1 = Point(0, 0);
	wsp2 = Point(0, 0);
	Color = Vec3b(0, 0, 0);
	text = Label();
	clock();
}

Button::Button(int _x1,int _y1,int _x2, int _y2)
{
	wsp1 = Point(_x1, _y1);
	wsp2 = Point(_x2, _y2);
	Color = Vec3b(192, 192, 192);
	text = Label( (_x2+_x1)/2,(_y2+_y1)/2, "Button");
}

Button::Button(int _x1, int _y1, int _x2, int _y2,string _text)
{
	wsp1 = Point(_x1, _y1);
	wsp2 = Point(_x2, _y2);
	Color = Vec3b(192, 192, 192);
	text = Label((_x2 + _x1) / 2, (_y2 + _y1) / 2, _text);
}

Button::~Button()
{

}

void Button::Draw(Mat& obraz)
{
	rectangle(obraz, Rect(wsp1, wsp2), Color,-1);
	rectangle(obraz, Rect(wsp1, wsp2), Vec3b(114, 114, 114), 4, CV_AA);
	text.Draw(obraz);

}

bool Button::isPressed(Cursor kursor)
{
	int czas = clock() / CLOCKS_PER_SEC;
	if ((kursor.getX() > wsp1.x) && (kursor.getY() > wsp1.y) && (kursor.getX() < wsp2.x) && (kursor.getY() < wsp2.y))
	{
		deltaTime += czas;
	}
	else
	{
		deltaTime = 0;
	}
	if (deltaTime > 400)
	{
		deltaTime = 0;
		return true;
	}
	else
	{
		return false;
	}
}
