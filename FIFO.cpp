/*
 * FIFO.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#include "FIFO.h"
using namespace std;

FIFO::FIFO() {

}

FrameTableEntry* FIFO::get_frame(FrameTable* f, vector<Process*>& pro_list) {

	FrameTableEntry* frame = f->get_free_frame();

	if (frame == nullptr) {
		frame = page_queue.front();
		page_queue.pop();
		page_queue.push(frame);
	}

	else
		page_queue.push(frame);

	return frame;

}
