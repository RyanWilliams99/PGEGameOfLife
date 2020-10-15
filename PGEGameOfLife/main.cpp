#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

using namespace std;

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

		if (gol[x][y + 1] == 1) //N
			liveMembers += 1;

		if (gol[x + 1][y + 1] == 1) //NE
			liveMembers += 1;

		if (gol[x + 1][y] == 1) //E
			liveMembers += 1;

		if (gol[x + 1][y - 1] == 1) //SE
			liveMembers += 1;

		if (gol[x][y - 1] == 1) //S
			liveMembers += 1;

		if (gol[x - 1][y - 1] == 1) //SW
			liveMembers += 1;

		if (gol[x + 1][y] == 1) //W
			liveMembers += 1;

		if (gol[x - 1][y + 1] == 1) //NW
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
		Clear(olc::BLACK);
		// called once per frame, draws random coloured pixels
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
			{
				 
				if (IsAlive(x, y)) //Live Cell
				{
					if (NumberOfLiveMembers(x, y) < 2) //Rule 1
					{
						gol[x][y] = 0; //die
						cout << "x - " << x << "y - " << y << " DIE - less than 2 members" << endl;
					}
					if (NumberOfLiveMembers(x, y) == 2) //Rule 2 
					{
						gol[x][y] = 1; //live
						cout << "x - " << x << "y - " << y << " LIVE -  2 members so live" << endl;

					}
					if (NumberOfLiveMembers(x, y) == 3) //Rule 3 
					{
						gol[x][y] = 1; //live
						cout << "x - " << x << "y - " << y << " LIVE -  3 members so live" << endl;

					}
					if (NumberOfLiveMembers(x, y) > 3) //Rule 3
					{
						gol[x][y] = 0; //die
						cout << "x - " << x << "y - " << y << " DIE -  more than 3 members so die" << endl;

					}
				
				}
				else
				{
					if (NumberOfLiveMembers(x, y) == 3) //Rule 3
					{
						gol[x][y] = 1; //live
						cout << "x - " << x << "y - " << y << " LIVE dead but has 3 memebers" << endl;

					}
				}



				//Actually Draw
				if (gol[x][y] == 1)
				{
					Draw(x, y, olc::Pixel(olc::WHITE));
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
