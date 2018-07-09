/*
 * Random_generator.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#include <iostream>
#include <fstream>

#include "Random_generator.h"

Random_generator::Random_generator(const string& randfile) {
	ifstream myfile(randfile);
	string line;

	if (!myfile.is_open()) {
		cout << "Error: Unable to open random file";
		exit(1);
	}

	getline(myfile, line);
	randvals.reserve(stoi(line));
	while (getline(myfile, line)) {
		randvals.push_back(stoi(line));

	}

	myfile.close();
}

int Random_generator::myrandom(int num) {
	static int ofs = 0;
	int sum = 1 + (randvals[ofs] % num);
	ofs++;
	if (ofs == randvals.size())
		ofs = 0;
	return sum;
}

