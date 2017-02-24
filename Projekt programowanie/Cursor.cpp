#include "Cursor.h"


Cursor::Cursor()
{
	x = 0;
	y = 0;
	wartoscGraniczna =220;
	MINIMALNY_ROZMIAR_KONTURU = 100;
	Kolor = Vec3b(0, 0, 255);
	visibility = true;
}


Cursor::~Cursor()
{
}

Mat Cursor::wybierzPiksele(Mat& obraz)
{
	Scalar szukanaBarwa = wyliczBarwe(Kolor);
	obraz.copyTo(wybierzPikseleBarwa);
	konwertujNaBarwe(wybierzPikseleBarwa);
	//imshow("Barwa", wybierzPikseleBarwa);
	absdiff(wybierzPikseleBarwa, szukanaBarwa, wybierzPikseleRoznica);
	wybierzPikseleWynik = Mat(wybierzPikseleRoznica.size(), CV_8U);
	for (int i = 0; i < wybierzPikseleWynik.rows; i++)
	{
		for (int j = 0; j < wybierzPikseleWynik.cols; j++)
		{
			Vec3b piksel = wybierzPikseleRoznica.at<Vec3b>(i, j);
			wybierzPikseleWynik.at<uchar>(i, j) = saturate_cast<uchar>((int)piksel.val[0] + piksel.val[1] + piksel.val[2]);
		}
	}
	threshold(wybierzPikseleWynik, wybierzPikseleWynik, wartoscGraniczna, 255, THRESH_BINARY_INV);
	imshow("Wybrane", wybierzPikseleWynik);
	return wybierzPikseleWynik;
}

Kontur Cursor::filtruj(Mat& wybrane)
{
	vector<Kontur> filtrujKonturty;
	findContours(wybrane, filtrujKonturty, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	double najwiekszyObszar = 0;
	int nrNajwiekszego = 0;
	for (int i = 0; i < filtrujKonturty.size(); i++)
	{
		double rozmiar =abs(contourArea(filtrujKonturty[i]));
		if (rozmiar > najwiekszyObszar)
		{
			najwiekszyObszar = rozmiar;
			nrNajwiekszego = i;
		}
	}
	return najwiekszyObszar > 0 ? filtrujKonturty[nrNajwiekszego] : Kontur();	
	//return Kontur();
}

Point Cursor::wyznaczPolozenie(Kontur kontur)
{
	if ((kontur.size() == 0) || (abs(contourArea(kontur)) < MINIMALNY_ROZMIAR_KONTURU))
	{
		return Point();
	}
	else
	{
		Moments momenty = moments(kontur);
		return Point(momenty.m10 / momenty.m00, momenty.m01 / momenty.m00);
	}
	//return Point(100, 100);
}

Vec3b Cursor::wyliczBarwe(Vec3b piksel)
{
	int suma = (int)piksel.val[0] + piksel.val[1] + piksel.val[2];
	if (suma != 0)
	{
		piksel.val[0] = piksel.val[0] * 255 / suma;
		piksel.val[1] = piksel.val[1] * 255 / suma;
		piksel.val[2] = 255 - piksel.val[0] - piksel.val[1];
	}
	return piksel;
}

void Cursor::konwertujNaBarwe(Mat& obraz)
{
	for (int i = 0; i < obraz.rows; i++)
	{
		for (int j = 0; j < obraz.cols; j++)
		{
			obraz.at<Vec3b>(i, j) = wyliczBarwe(obraz.at<Vec3b>(i, j));
		}
	}
}

void Cursor::findCursor(Mat& obraz)
{
	Mat piksele = wybierzPiksele(obraz);
	Kontur wybranyKontur = filtruj(piksele);
	polozenie = wyznaczPolozenie(wybranyKontur);
	x = polozenie.x;
	y = polozenie.y;
}

void Cursor::drawCursor(Mat& ekran)
{
	circle(ekran, Point(x, y), 20, Kolor, -1);
}
