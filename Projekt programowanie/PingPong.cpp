#include "PingPong.h"


PingPong::PingPong()
{
	gracz = Paletka(320,450,20,420);
	przeciwnik = Paletka(320,30,20,60);
	pilka = Pilka();
	kolor = Vec3b(86,194,54);
	isPlaying = false;
	oczekiwanie = 600;
}


PingPong::~PingPong()
{

}

/* Dokonuje obliczeñ dla aktualnej rozgrywki i dla danego zestawu danych wyznacza odpowiedŸ formy */
Form::ButtonCode PingPong::Events(Cursor& kursor)
{
	if (oczekiwanie>=0)
	{
		oczekiwanie -= (clock() / CLOCKS_PER_SEC);
		if (oczekiwanie < 0)
			isPlaying = true;
	}
	if (isPlaying)
	{
		gracz.Steruj(kursor);
		przeciwnik.Comp(pilka);
		pilka.Move();
		pilka.Bounce(gracz, przeciwnik);
		if (pilka.isOut(gracz,przeciwnik))
		{
			pilka = Pilka();
			gracz.setX(320);
			przeciwnik.setX(320);
			clock();
			oczekiwanie = 600;
			isPlaying = false;
		}
	}
	if (gracz.getPunkty() == 5 || przeciwnik.getPunkty() == 5)
		return GAME_MENU;
	return NO_EVENTS;
}

/* Czyœci i nanosi odpowiednie komponenty na obraz */
void PingPong::UpdateScreen(Mat& obraz)
{
	obraz = Mat(obraz.rows, obraz.cols,CV_8UC3 , kolor);
	gracz.Draw(obraz);
	przeciwnik.Draw(obraz);
	pilka.Draw(obraz);
}

					/* Implementacja klas zagnie¿d¿onych */

/*======================== Implementacja Paletki =========================== */

/* Konstruktor domniemany*/
PingPong::Paletka::Paletka()
{
	width = 100;
	height = 25;
	x = 320;
	y = 480 - height;
	wsp1 = Point(x - width / 2, y - height / 2);
	wsp2 = Point(x + width / 2, y + height / 2);
	kolor = Vec3b(0, 0, 0);
	Punkty = 0;
}

PingPong::Paletka::Paletka(int _x, int _y,int _pktX,int _pktY)
{
	x = _x;
	y = _y;
	pktX = _pktX;
	pktY = _pktY;
	width = 100;
	height = 25;
	wsp1 = Point(x - width / 2, y - height / 2);
	wsp2 = Point(x + width / 2, y + height / 2);
	kolor = Vec3b(164,73,163);
	Punkty = 0;
}

void PingPong::Paletka::Steruj(Cursor kursor)
{
	if ((kursor.getX() - width / 2 > 0) && (kursor.getX()+width/2<640))
	{
		x = kursor.getX();
		wsp1 = Point(x - width / 2, y - height / 2);
		wsp2 = Point(x + width / 2, y + height / 2);
	}
}

void PingPong::Paletka::Draw(Mat& obraz)
{
	rectangle(obraz, Rect(wsp1, wsp2), kolor, -1);
	putText(obraz, string(1, static_cast<char>(Punkty + 48)), Point(pktX, pktY), CV_FONT_HERSHEY_PLAIN, 2, Scalar(11, 11, 227),2);
}

void PingPong::Paletka::Comp(Pilka pilka)
{
	if ( x > pilka.getX())
	{
		x -= 11;
		wsp1.x = x - width / 2;
		wsp2.x = x + width / 2;
	}
	else
	if (x < pilka.getX())
	{
		x += 11 ;
		wsp1.x = x - width / 2;
		wsp2.x = x + width / 2;
	}
}

void PingPong::Paletka::setX(int _x)
{
	x = _x;
	wsp1.x = x - width / 2;
	wsp2.x = x + width / 2;
}

/*============================== Implementacja Pilki ================================ */

PingPong::Pilka::Pilka()
{
	x = 320;
	y = 240;
	r = 20;
	wsp = Point(x, y);
	kolor = Vec3b(255, 255, 255);
	dx = 15 - rand() % 3;
	dy =-8+ rand() % 5;
}

PingPong::Pilka::Pilka(int _x, int _y,int _r)
{
	x = _x;
	y = _y;
	wsp = Point(x, y);
	r = _r;
	kolor = Vec3b();
	dx = 7;
	dy = -7;
}

void PingPong::Pilka::Move()
{
	x += dx;
	y += dy;
	wsp.x = x;
	wsp.y = y;
}

void PingPong::Pilka::Draw(Mat& obraz)
{
	circle(obraz, wsp, r, kolor, -1);
}

bool PingPong::Pilka::isOut(PingPong::Paletka& gracz, PingPong::Paletka& przeciwnik)
{
	if (y + r < 0)
	{
		gracz.dodajPunkty();
		return true;
	}
	else
	if (y - r > 480)
	{
		przeciwnik.dodajPunkty();
		return true;
	}
	return false;
}

void PingPong::Pilka::Bounce(PingPong::Paletka gracz, PingPong::Paletka przeciwnik)
{
	
	if ((y>przeciwnik.getY()) && (x + r > przeciwnik.getP1().x) && (x - r < przeciwnik.getP2().x) && (y - r < przeciwnik.getP2().y)  )
	{
		y = przeciwnik.getP2().y+r;
		dy = -dy;
	}

	if ((y<gracz.getY()) && (x + r > gracz.getP1().x) && (x - r < gracz.getP2().x) && (y + r > gracz.getP1().y)  )
	{
		y = gracz.getP1().y-r;
		dy = -dy;
	}

	if (x - r < 0)
	{
		x = r;
		dx = -dx;
	}

	if (x + r>640)
	{
		x -= r;
		dx = -dx;
	}
}