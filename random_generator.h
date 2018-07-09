/*
 * random_generator.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#ifndef RANDOM_GENERATOR_H_
#define RANDOM_GENERATOR_H_

#include <vector>
#include <string>

using namespace std;

class Random_generator {
public:

	Random_generator(const string&);
	int myrandom(int);
	//void init_randvals(const string&);

private:

	vector<int> randvals;


};

#endif /* RANDOM_GENERATOR_H_ */

