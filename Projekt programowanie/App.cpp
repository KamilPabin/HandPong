#include "App.h"


App::App(int _width,int _height)
{
	Kamera.open(0);
	if (!Kamera.isOpened())
	{
		cout << "Nie udalo sie nawiazac polaczenia z kamera.";
		exit(-1);
	}
	width = _width;
	height = _height;
	Kamera.set(CAP_PROP_FRAME_WIDTH, width);
	Kamera.set(CAP_PROP_FRAME_HEIGHT, height);
	forma = new Menu();
	czyKoniec = false;
	Obraz = Mat(_height, _width, CV_8U);
}


App::~App()
{

}

void App::Run()
{
	do
	{
		clock();
		Kamera >> obrazKamery;
		flip(obrazKamery, obrazKamery, 1);
		kursor.findCursor(obrazKamery);
		switch (forma->Events(kursor))
		{
			case Form::GAME_MENU:
			{
				delete forma;
				forma = new GameMenu();
				kursor.setVisible(true);
				break;
			}
			case Form::LEAVE:
			{
				czyKoniec = true;
				break;
			}
			case Form::MENU:
			{
				delete forma;
				forma = new Menu();
				kursor.setVisible(true);
				break;
			}
			case Form::PING_PONG:
			{
				delete forma;
				forma = new PingPong();
				kursor.setVisible(false);
				break;
			}
			case Form::NO_EVENTS:
			{

			}
		};
		forma->UpdateScreen(Obraz);
		if(kursor.isVisible() ) kursor.drawCursor(Obraz);
		imshow("Projekt zaliczenie", Obraz);
	} while ( (waitKey(10) != ' ') && ( !czyKoniec ));
	delete forma;
}