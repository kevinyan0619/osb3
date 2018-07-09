/*
 * pager.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#include "frameTable.h"
#include "process.h"
#include <vector>

using namespace std;

class Pager {
public:
	//Pager();

	virtual FrameTableEntry* get_frame(FrameTable*, vector<Process*>&) = 0;
};

