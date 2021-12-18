/*
mivel minden pár mindig ugyanazt az "utódot" fogja hozni.
pl:

a sor: AABC
szabály: AA -> A
		 AB -> C
		 BC -> D
 0. iteráció: 
	AABC

	ez eddig evidens, de elég megszámolni a párokat (és egy unordered_map - ban tárolva elég 
	csak egy számlálót növelni velük)
	
	vagyis:
		AA: 1
		AB: 1
		BC: 1
1. iteráció:
	aAaCbDc

	elég megnézni hogy melyik pár milyen karaktert rakott meguk közé
	és azzal a karakterrel + az 
		elsõ-vel csinálni egy új párt (vagy ha már van
			akkor annak a számlálóját növelni eggyel)

		második-kal csinálni egy új párt (vagy ha már van
			akkor annak a számlálóját növelni eggyel)

	ugyebár, ekkor megszámoltuk milyen új párok keletkeztek, de 
	mivel az alap párt "szétszakítottuk" ezért annak a számlájóját csökkenteni kell egyel.

ha ezt folytatjuk addig amíg kell, meg is vagyunk.

ez win.

(eskü nem ezzel szoptam több órát)
*/

#pragma once  
#include "day14.h"

using namespace std;

const int maxn = 100;

unordered_map<string, char> rules;
unordered_map<string, unsigned long long int> pairs;
string input_line;
char last;

void Day14()
{
	ifstream be;

	be.open("task14.txt");

	//elsõ sor beolvasása, eltárolása
	getline(be, input_line);

	//elsõ soron végig iterál, minden párt betesz a matrixba és növeli a számlálójukat
	for (int i = 1; i < input_line.size(); i++)
	{
		auto pair = pairs.insert({ {input_line[i - 1], input_line[i]}, 1 });

		if (!pair.second)
		{
			pair.first->second++;
		}
	}
	
	last = input_line[input_line.size() - 1];

	//beolassa a szabályokat és letárolja õket
	getline(be, input_line);
	while (getline(be, input_line))
	{
		string pair{ input_line[0], input_line[1] };
		char res = input_line[6];

		rules.insert({ pair, res });
	}


	
	for (int i = 0; i < 40; i++)
	{
		unordered_map<string, unsigned long long int> temp = pairs;

		for (auto& pair : pairs)
		{
			//a temp-ben megkeressük a soron következõ párt, majd csökkentjük a számlálóját
			temp.find(pair.first)->second -= pair.second;

			//a szabály szerint melyik karakter fog bejönni
			char c = rules.find(pair.first)->second;

			//beillesztjük a karaktert a kettõ közé
			auto p1 = temp.insert({ {pair.first[0], c}, pair.second });
			auto p2 = temp.insert({ {c, pair.first[1]}, pair.second });

			//növeljük a számlálókat
			if (!p1.second)
				p1.first->second += pair.second;
			if (!p2.second)
				p2.first->second += pair.second;
		}

		// az eredetit egyenlõvé tesszük az átmenetivel
		pairs = temp;
	}

	//összeszámolás, ez nem lényeg, nem magyaráznám el
	unsigned long long int min = ULLONG_MAX, max = 0;

	unordered_map<char, unsigned long long int> counts;
	for (auto p : pairs)
	{
		auto it_p = counts.insert({ p.first[0], p.second });
		if (!it_p.second)
			it_p.first->second += p.second;
	}

	auto it_p = counts.insert({ last, 1 });
	if (!it_p.second)
		it_p.first->second++;

	for (auto p : counts)
	{
		max = p.second > max ? p.second : max;
		min = p.second < min ? p.second : min;
	}

	cout << max - min << endl;

}