#include "day3.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <bitset>

#define SIZE 12 // change to 5 for example

void Day3() {

	std::ifstream input("task3.txt");


	/* --- Part 1 --- */

	int count_zeros[SIZE];
	std::vector<std::bitset<SIZE>> data;

	std::string line;

	while (std::getline(input, line)) {
		std::bitset<SIZE> b(line);
		data.push_back(b);

		for (int i = 0; i < SIZE; i++) {
			count_zeros[i] += b[i] ^ 1; // if zero : counter++
		}

	}

	std::bitset<SIZE> gamma;
	int size = data.size();
	for (int i = 0; i < SIZE; i++) {
		gamma[i] = (count_zeros[i] > size / 2) ? 0 : 1;
	}


	std::bitset<SIZE> epsilon = gamma;
	epsilon.flip();

	std::cout << "Part1: " << gamma.to_ulong() * epsilon.to_ulong() << std::endl;

	/* --- Part 2 --- */

	/* oxygen generator rating */

	std::vector<std::bitset<SIZE>> oxygen = data;

	for (int i = SIZE - 1; i >= 0; i--) {

		int count_zeros = 0;
		for (auto b : oxygen) {
			count_zeros += b[i] ^ 1;
		}
		int oxygen_rate = (count_zeros > oxygen.size() / 2) ? 0 : 1;

		if (oxygen.size() > 1) {
			auto end = std::remove_if(oxygen.begin(), oxygen.end(), [&oxygen_rate, &i](std::bitset<SIZE>& bs) { return bs[i] != oxygen_rate; });
			oxygen.erase(end, oxygen.end());
		}
		else {
			break;
		}
	}

	/* CO2 scrubber rating */


	std::vector<std::bitset<SIZE>> co2_scrubber = data;

	for (int i = SIZE - 1; i >= 0; i--) {

		int count_zeros = 0;
		for (auto b : co2_scrubber) {
			count_zeros += b[i] ^ 1;
		}
		int co2_scrubber_rate = (count_zeros <= co2_scrubber.size() / 2) ? 0 : 1;

		if (co2_scrubber.size() > 1) {
			auto end = std::remove_if(co2_scrubber.begin(), co2_scrubber.end(), [&co2_scrubber_rate, &i](std::bitset<SIZE>& bs) { return bs[i] != co2_scrubber_rate; });
			co2_scrubber.erase(end, co2_scrubber.end());
		}
		else {
			break;
		}
	}

	std::cout << "Part2: " << oxygen[0].to_ulong() * co2_scrubber[0].to_ulong() << std::endl;

}