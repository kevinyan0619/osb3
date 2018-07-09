/*
 * Aging.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#ifndef AGING_H_
#define AGING_H_

#include "pager.h"
#include <vector>
#include <bitset>
#include "constant.h"

using namespace std;

class Aging: public Pager {
public:

	Aging(int);
	FrameTableEntry* get_frame(FrameTable*, vector<Process*>&);

	int count;
	vector<bitset<BITSET_SIZE> > counter_list;

};

#endif /* AGING_H_ */
