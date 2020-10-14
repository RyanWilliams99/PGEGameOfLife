#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"


int gol[256][240];



// Override base class with your custom functionality
class PGEGameOfLife : public olc::PixelGameEngine
{

	bool IsAlive(int x, int y)
	{

		if (gol[x][y] == 1)
			return true;
		else
			return false;
	}


	int NumberOfLiveMembers(int x, int y)
	{
		int liveMembers = 0;

		if (gol[x + 1][y] == 1)
			liveMembers += 1;

		if (gol[x + 1][y - 1] == 1)
			liveMembers += 1;

		if (gol[x][y - 1] == 1)
			liveMembers += 1;

		if (gol[x - 1][y - 1] == 1)
			liveMembers += 1;

		if (gol[x - 1][y] == 1)
			liveMembers += 1;

		if (gol[x - 1][y + 1] == 1)
			liveMembers += 1;

		if (gol[x + 1][y + 1] == 1)
			liveMembers += 1;

		return liveMembers;
	}

public:
	PGEGameOfLife()
	{
		// Name you application
		sAppName = "PGEGameOfLife";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		Clear(olc::BLACK);

		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
			{
				int v = rand() % 10;
				if (v == 1)
					gol[x][y] = 1;
			}
				
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame, draws random coloured pixels

		//Actually Draw
		for (int x = 0; x < ScreenWidth(); x++)
		{
			for (int y = 0; y < ScreenHeight(); y++)
			{
				if (gol[x][y] == 1)
				{
					Draw(x, y, olc::Pixel(olc::WHITE));
				}
					
			}
				
		}
			

		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
			{
				//Rule 1
				if (IsAlive(x, y))
				{
					if (NumberOfLiveMembers(x, y) < 2)
					gol[x][y] = 0; //die

					std::cout << "killed a value at x - " << x << " y -  " << y << "\n";

				}
			}

		return true;
	}

};



int main()
{
	PGEGameOfLife demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}
