/*
 * frameTable.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#ifndef FRAMETABLE_H_
#define FRAMETABLE_H_

#include "frameTableEntry.h"

#include <vector>

using namespace std;

class FrameTable {
public:

	vector<FrameTableEntry> frame_table;

	FrameTable(int);
	FrameTableEntry* get_free_frame();

};

#endif /* FRAMETABLE_H_ */
