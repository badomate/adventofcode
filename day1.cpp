#include "day1.h"

void Day1()
{
	std::cout << "1. nap elsõ része" << std::endl;
	std::ifstream file("task1.txt");

	int elso,masodik,harmadik,negyedik;
	file >> elso >> masodik >> harmadik;

	int novekedett = 0;
	while (!file.eof())
	{
		file >> negyedik;
		if (elso < negyedik)
			novekedett++;

		elso = masodik;
		masodik = harmadik;
		harmadik = negyedik;
	}

	std::cout << novekedett << std::endl;


}
