/*
 * Second_Chance.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#include "Second_Chance.h"

Second_Chance::Second_Chance() {

}

FrameTableEntry* Second_Chance::get_frame(FrameTable* f,
		vector<Process*>& pro_list) {

	FrameTableEntry* frame = f->get_free_frame();

	if (frame == nullptr) {

		frame = page_queue.front();
		PageTableEntry* pte =
				&((pro_list[frame->proid])->page_table[frame->vpage]);

		while (pte->referenced == 1) {
			pte->referenced = 0;
			page_queue.pop();
			page_queue.push(frame);

			frame = page_queue.front();
			pte = &((pro_list[frame->proid])->page_table[frame->vpage]);
		}

		page_queue.pop();
		page_queue.push(frame);

	}

	else {
		page_queue.push(frame);
	}
	return frame;

}

