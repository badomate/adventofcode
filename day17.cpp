#include "day17.h"

struct cord {
	int X;
	int Y;

	cord(int x, int y)
	{
		X = x;
		Y = y;
	}

	cord() {};

	bool operator==(const cord& std) const noexcept {
		return this->X == std.X && this->Y == std.Y;
	}
};

void visualize(int steps, cord velocity, cord bottomLeft, cord topRight)
{
	vector<cord> path;
	path.push_back(cord(0, 0));
	int max_height = 0;

	for (int i = 0; i < steps; i++)
	{
		cord newStep;
		newStep.X = path[path.size() - 1].X + velocity.X;
		newStep.Y = path[path.size() - 1].Y + velocity.Y;

		if (newStep.Y > max_height)
			max_height = newStep.Y;

		if (velocity.X > 0)
			velocity.X -= 1;

		velocity.Y -= 1;

		path.push_back(newStep);
	}

	for (int y = max_height; y >= path[path.size() - 1].Y - 1; y--)
	{
		for (int x = 0; x <= path[path.size() - 1].X + 4; x++)
		{
			char betu = '.';

			if ((bottomLeft.X <= x && x <= topRight.X) && (bottomLeft.Y <= y && y <= topRight.Y))
				betu = 'T';

			vector<cord>::iterator it = find(path.begin(), path.end(), cord(x, y));
			if (it != path.end())
			{
				//if (betu == 'T')
					//cout << x << " " << y;
				betu = '#';
			}
			if (x == 0 && y == 0)
				betu = 'S';

			cout << betu;
		}
		cout << endl;
	}
}


void Day17()
{
	cord bottomLeft = cord(185, -122);
	cord topRight = cord(221, -74);
	cord velocity = cord(20, 121);
	int steps = 500;

	//visualize(steps, velocity, bottomLeft, topRight);

	//part one
	cout << bottomLeft.Y * (bottomLeft.Y + 1) / 2 << endl;

	//part 2
	/*
	int maxStep = abs(bottomLeft.Y * 2 + 1);
	int cc = 0;
	for (int step = 2; step <= maxStep; step++)
	{
		//x tengely
		
		for (int i = bottomLeft.X; i <= topRight.X; i++)
		{
			if ((i + sumIntegers(step - 1)) % step == 0)
			{
				for (int y = topRight.Y; y >= bottomLeft.Y; y--)
				{
					if ((y + sumIntegers(step - 1)) % step == 0)
					{
						cc++;
					}
				}
			}
		}
	}
	cout << cc + (topRight.X - bottomLeft.X + 1) * abs(-topRight.Y + bottomLeft.Y - 1) << endl; 
	*/

	//brute force stuff
	int minx = 185, maxx = 221, miny = -122, maxy = -74;
	int counter = 0;
	int maxt = max(-2 * miny + 1, maxx);

	for (int vyo = miny; vyo <= -miny; vyo++)
		for (int vxo = 1; vxo <= maxx; vxo++)
			for (int t = 1; t <= maxt; t++)
			{
				int y = vyo * t - t * (t - 1) / 2;
				int x;
				if (t < vxo)
					x = vxo * t - t * (t - 1) / 2;
				else
					x = vxo * (vxo + 1) / 2;
				if (miny <= y && y <= maxy && minx <= x && x <= maxx)
				{
					counter++;
					break;
				}
			}

	cout << counter << endl;
}


