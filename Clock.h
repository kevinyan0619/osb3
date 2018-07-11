/*
 * clock.h
 *
 *  Created on: Jul 11, 2018
 *      Author: kevinyan
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "pager.h"
#include <vector>

using namespace std;

class Clock: public Pager {
public:


	Clock();
	int hand;
	vector<FrameTableEntry*> page_queue;
	FrameTableEntry* get_frame(FrameTable*, vector<Process*>&);

};

#endif /* CLOCK_H_ */
