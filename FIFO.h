/*
 * FIFO.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "pager.h"
#include <queue>

using namespace std;

class FIFO: public Pager {
public:
	queue<FrameTableEntry*> page_queue;

	FIFO();
	FrameTableEntry* get_frame(FrameTable*, vector<Process*>&);

};

#endif /* FIFO_H_ */
