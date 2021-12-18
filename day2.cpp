#include "day2.h"

void Day2() {

	//part 1
	std::ifstream file("task2.txt");

	int depth = 0, horizontal = 0;

	std::string dir;

	while (getline(file, dir))
	{
		switch (dir[0])
		{
		case 'u':
			depth -= dir[3] - '0';
			break;
		case 'f':
			horizontal += dir[8] - '0';
			break;
		case 'd':
			depth += dir[5] - '0';
		}
	}


	std::cout << depth * horizontal << std::endl;
	file.close();
	//part 2
	file.open("task2.txt");
	depth = 0, horizontal = 0;
	int aim = 0;

	while (getline(file, dir))
	{
		switch (dir[0])
		{
		case 'u':
			aim -= dir[3] - '0';
			break;
		case 'f':
			horizontal += dir[8] - '0';
			depth += (dir[8] - '0') * aim;
			break;
		case 'd':
			aim += dir[5] - '0';
		}
	}

	std::cout << depth * horizontal << std::endl;




}