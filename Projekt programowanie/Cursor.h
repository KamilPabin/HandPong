#pragma once
#include <vector>
using namespace std;

#include"opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
using namespace cv;

typedef vector<Point> Kontur;

class Cursor
{
public:


	Cursor();
	~Cursor();
	int getX(){ return x; };
	int getY(){ return y; };
	Point getPosition(){ return polozenie; };
	void findCursor(Mat& obrazKamery);
	void drawCursor(Mat& ekran);

	bool isVisible(){ return visibility; };
	void setVisible(bool _visibility){ visibility = _visibility; };
private:

	int x;
	int y;
	Point polozenie;

	Vec3b Kolor;
	Point wyznaczPolozenie(Kontur kontur);
	Mat wybierzPiksele(Mat& obraz);
	Kontur filtruj(Mat& obraz);

	static Vec3b wyliczBarwe(Vec3b piksel);
	static void konwertujNaBarwe(Mat& obraz);

	Mat wybierzPikseleBarwa;
	Mat wybierzPikseleRoznica;
	Mat wybierzPikseleWynik;

	 int wartoscGraniczna;
	 int MINIMALNY_ROZMIAR_KONTURU;

	 bool visibility;
};

