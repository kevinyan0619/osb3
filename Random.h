/*
 * Random.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include "pager.h"
#include "string"
#include "random_generator.h"
using namespace std;

class Random: public Pager {
public:
	Random_generator grt;

	Random(const string&);

	FrameTableEntry* get_frame(FrameTable*, vector<Process*>&);

};

#endif /* RANDOM_H_ */
