#pragma once
#include "Form.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

#include "Button.h"

class PingPong :
	public Form
{
public:
	PingPong();
	~PingPong();

	ButtonCode Events(Cursor& kursor);
	void UpdateScreen(Mat& obraz);

	/*					 Zagnie¿d¿one klasy do obs³ugi tej formy. Paletka oraz pi³ka.						*/
	/*======================================================================================================*/

private:

	class Pilka;	// Deklaracja zapowiadaj¹ca

	class Paletka
	{
	public:
		Paletka();
		Paletka(int _x, int _y,int _pktX,int _pktY);

		void Steruj(Cursor kursor);
		void Draw(Mat& obraz);
		void Comp(Pilka pilka);
		int getX(){ return x; };
		int getY(){ return y; };
		Point getP1(){ return wsp1; };
		Point getP2(){ return wsp2; };

		void setX(int _x);
		void dodajPunkty(){ Punkty++; };
		int getPunkty(){ return Punkty; };
	private:
		int x;
		int y;

		int width;
		int height;

		Point wsp1;
		Point wsp2;
		Vec3b kolor;

		int  Punkty;
		int pktX;
		int pktY;
	};

	class Pilka
	{
	public:
		Pilka();
		Pilka(int _x, int _y,int _r);

		void Move();
		void Bounce(Paletka gracz, Paletka przeciwnik);
		void Draw(Mat& obraz);

		int getX(){ return x; };
		int getY(){ return y; };
		int getR(){ return r; };

		void setX(int _x){ x = _x; };
		void setY(int _y){ y = _y; };

		bool isOut(Paletka& gracz, Paletka& przeciwnik);
	private:
		int x;
		int dx;
		int y;
		int dy;
		int r;

		Vec3b kolor;
		Point wsp;
	};

	/*								 Koniec definicji klas zagnie¿d¿onych									 */
	/*=======================================================================================================*/

	Paletka gracz;
	Paletka przeciwnik;

	Pilka pilka;
	Vec3b kolor;

	bool isPlaying;
	int oczekiwanie;
};

