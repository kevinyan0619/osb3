/*
 * Second-Chance.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#ifndef SECOND_CHANCE_H_
#define SECOND_CHANCE_H_

#include "pager.h"
#include <queue>

using namespace std;

class Second_Chance: Pager {
public:
	queue<FrameTableEntry*> page_queue;

	Second_Chance();
	FrameTableEntry* get_frame(FrameTable*, vector<Process*>&);

};

#endif /* SECOND_CHANCE_H_ */
