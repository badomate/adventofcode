/*
mivel minden p�r mindig ugyanazt az "ut�dot" fogja hozni.
pl:

a sor: AABC
szab�ly: AA -> A
		 AB -> C
		 BC -> D
 0. iter�ci�: 
	AABC

	ez eddig evidens, de el�g megsz�molni a p�rokat (�s egy unordered_map - ban t�rolva el�g 
	csak egy sz�ml�l�t n�velni vel�k)
	
	vagyis:
		AA: 1
		AB: 1
		BC: 1
1. iter�ci�:
	aAaCbDc

	el�g megn�zni hogy melyik p�r milyen karaktert rakott meguk k�z�
	�s azzal a karakterrel + az 
		els�-vel csin�lni egy �j p�rt (vagy ha m�r van
			akkor annak a sz�ml�l�j�t n�velni eggyel)

		m�sodik-kal csin�lni egy �j p�rt (vagy ha m�r van
			akkor annak a sz�ml�l�j�t n�velni eggyel)

	ugyeb�r, ekkor megsz�moltuk milyen �j p�rok keletkeztek, de 
	mivel az alap p�rt "sz�tszak�tottuk" ez�rt annak a sz�ml�j�j�t cs�kkenteni kell egyel.

ha ezt folytatjuk addig am�g kell, meg is vagyunk.

ez win.

(esk� nem ezzel szoptam t�bb �r�t)
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

	//els� sor beolvas�sa, elt�rol�sa
	getline(be, input_line);

	//els� soron v�gig iter�l, minden p�rt betesz a matrixba �s n�veli a sz�ml�l�jukat
	for (int i = 1; i < input_line.size(); i++)
	{
		auto pair = pairs.insert({ {input_line[i - 1], input_line[i]}, 1 });

		if (!pair.second)
		{
			pair.first->second++;
		}
	}
	
	last = input_line[input_line.size() - 1];

	//beolassa a szab�lyokat �s let�rolja �ket
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
			//a temp-ben megkeress�k a soron k�vetkez� p�rt, majd cs�kkentj�k a sz�ml�l�j�t
			temp.find(pair.first)->second -= pair.second;

			//a szab�ly szerint melyik karakter fog bej�nni
			char c = rules.find(pair.first)->second;

			//beillesztj�k a karaktert a kett� k�z�
			auto p1 = temp.insert({ {pair.first[0], c}, pair.second });
			auto p2 = temp.insert({ {c, pair.first[1]}, pair.second });

			//n�velj�k a sz�ml�l�kat
			if (!p1.second)
				p1.first->second += pair.second;
			if (!p2.second)
				p2.first->second += pair.second;
		}

		// az eredetit egyenl�v� tessz�k az �tmenetivel
		pairs = temp;
	}

	//�sszesz�mol�s, ez nem l�nyeg, nem magyar�zn�m el
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