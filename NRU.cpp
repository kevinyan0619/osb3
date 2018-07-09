/*
 * NRU.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#include "NRU.h"

using namespace std;

NRU::NRU(const string& randfile) :
		grt(randfile), count(0) {

}

FrameTableEntry* NRU::get_frame(FrameTable* f, vector<Process*>& pro_list) {

	FrameTableEntry* frame = f->get_free_frame();

	if (frame == nullptr) {

		// record page replacement

		// R bit is reset every 10th page replacement
//		if (count == 0) {
		for (int i = 0; i < f->frame_table.size(); i++) {

			FrameTableEntry* fm = &(f->frame_table)[i];
			PageTableEntry* page = &(pro_list[fm->proid]->page_table[fm->vpage]);

			int rank = 2 * (page->referenced) + (page->modified);

			nru_class[rank].push_back(fm);

//			}

// reset R bit
//			for (int i = 0; i < pro_list.size(); i++) {
//				for (int j = 0; j < pro_list[i]->page_table.size(); j++)
//					pro_list[i]->page_table[j].referenced = 0;
//			}

		}

		// get frame with the lowest priority
		for (int i = 0; i < nru_class.size(); i++) {
			if (!nru_class[i].empty()) {
				int randnum = grt.myrandom(nru_class[i].size());
				frame = nru_class[i][randnum];
				break;
			}

		}

		// clear ranking
		for (int i = 0; i < nru_class.size(); i++)
			nru_class[i].clear();

//		count++;
//		count %= 10;

	}

	return frame;
}

