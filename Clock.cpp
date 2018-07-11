/*
 * clock.cpp
 *
 *  Created on: Jul 11, 2018
 *      Author: kevinyan
 */

#include "clock.h"

Clock::Clock() :
		hand(0) {

}

FrameTableEntry* Clock::get_frame(FrameTable* f, vector<Process*>& pro_list) {

	FrameTableEntry* frame = f->get_free_frame();

	if (frame == nullptr) {

		frame = page_queue[hand];
		PageTableEntry* pte =
				&((pro_list[frame->proid])->page_table[frame->vpage]);

		while (pte->referenced == 1) {
			pte->referenced = 0;

			hand++;
			hand %= page_queue.size();

			frame = page_queue[hand];
			pte = &((pro_list[frame->proid])->page_table[frame->vpage]);

		}

		hand++;
		hand %= page_queue.size();

	}

	else {
		page_queue.push_back(frame);
	}

	return frame;

}
