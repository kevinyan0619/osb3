/*
 * Aging.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#include "Aging.h"
#include <limits>

using namespace std;

Aging::Aging(int frame_size) :
		count(0) {
	for (int i = 0; i < frame_size; i++) {

		bitset<32> temp;
		counter_list.push_back(temp);
	}
}

FrameTableEntry* Aging::get_frame(FrameTable* f, vector<Process*>& pro_list) {

	FrameTableEntry* frame = f->get_free_frame();

	unsigned long min = numeric_limits<unsigned long>::max();
	int minIndex = -1;

	if (frame == nullptr) {
		// record page replacement

		// the R bit is reset every 10th page replacement
		if (count == 0) {
			for (int i = 0; i < f->frame_table.size(); i++) {

				FrameTableEntry* fm = &(f->frame_table)[i];
				PageTableEntry* page =
						&(pro_list[fm->proid]->page_table[fm->vpage]);

				if (page->referenced == 1) {
					counter_list[i][BITSET_SIZE - 1] = 1;
				}

				else {
					counter_list[i][BITSET_SIZE - 1] = 0;
				}

			}

			// reset R bit
			for (int i = 0; i < pro_list.size(); i++) {
				for (int j = 0; j < pro_list[i]->page_table.size(); j++)
					pro_list[i]->page_table[j].referenced = 0;
			}

		}

		for (int i = 0; i < f->frame_table.size(); i++) {
			if (counter_list[i].to_ulong() < min) {
				minIndex = i;
				min = counter_list[i].to_ulong();
				frame = &(f->frame_table[i]);
			}

		}

		counter_list[minIndex].reset();

		count++;
		count %= 10;

	}

	return frame;

}
