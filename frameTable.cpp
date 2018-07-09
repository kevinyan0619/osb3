/*
 * frameTable.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#include "frameTable.h"

FrameTable::FrameTable(int size) {
	for (int i = 0; i < size; i++) {
		FrameTableEntry entry;
		entry.index = i;
		frame_table.push_back(entry);
	}
}

FrameTableEntry* FrameTable::get_free_frame() {
	for (int i = 0; i < frame_table.size(); i++) {
		if (frame_table[i].isFree) {
			FrameTableEntry* entry_ptr = &(frame_table[i]);
			return entry_ptr;
		}
	}
	return nullptr;
}
