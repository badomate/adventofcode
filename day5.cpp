#include "day5.h"

struct point {
	int X, Y;

	point(int x, int y)
	{
		X = x;
		Y = y;
	}

	point() {};

	bool operator==(const point& std) const noexcept
	{
		return this->X == std.X && this->Y == std.Y;
	};

	bool operator<(const point& std) const noexcept {
		return this->X < std.X;
	};
};

struct line {
	point Kezd;
	point Veg;

	vector<point> Egesz;

	line(point kezd, point veg)
	{
		Kezd = kezd;
		Veg = veg;
	};
	line() {};
	bool operator==(const line& std) const noexcept
	{
		return this->Kezd == std.Kezd && this->Veg == std.Veg;
	};

	void makeLine() {

		

		if (Kezd.X == Veg.X)
		{
			Egesz.push_back(Kezd);
			for (int i = 1; i <= abs(Kezd.Y - Veg.Y); i++)
				if (Kezd.Y < Veg.Y)
					Egesz.push_back(point(Kezd.X, Kezd.Y + i));
				else
					Egesz.push_back(point(Kezd.X, Kezd.Y - i));

			return;
		}

		else if (Kezd.Y == Veg.Y)
		{
			Egesz.push_back(Kezd);
			for (int i = 1; i <= abs(Kezd.X - Veg.X); i++)
				Egesz.push_back(point(Kezd.X + i, Kezd.Y));

			return;
		}/*

		else
		{
			if (Kezd.Y < Veg.Y)
			{
				for (int i = 1; i <= abs(Kezd.X - Veg.X); i++)
					Egesz.push_back(point(Kezd.X + i, Kezd.Y + i));
			}
			else
			{
				for (int i = 1; i <= abs(Kezd.X - Veg.X); i++)
					Egesz.push_back(point(Kezd.X + i, Kezd.Y - i));
			}
		}*/


	}
};



void Day5()
{
	ifstream file("task5.txt");

	vector<line> lines;

	for (int i = 0; i < 500; i++)
	{
		line nextLine;

		point first;
		point second;

		file >> first.X >> first.Y;
		file >> second.X >> second.Y;

		if (first.X < second.X)
		{
			nextLine.Kezd = first;
			nextLine.Veg = second;
		}
		else {
			nextLine.Kezd = second;
			nextLine.Veg = first;
		}

		nextLine.makeLine();

		lines.push_back(nextLine);
	}
	int count = 0;

	for(int x = 0; x < 1000; x++)
		for (int y = 0; y < 1000; y++)
		{
			int found = 0;
			for (auto next : lines)
			{
				vector<point>::iterator it = find(next.Egesz.begin(), next.Egesz.end(), point(x, y));

				if (it != next.Egesz.end())
				{
					if (found == 2)
						break;
					found++;
				}

			}

			if (found >= 2)
			{
				count++;
				break;
			}
		}

	cout << count;
}