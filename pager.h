/*
 * pager.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#ifndef PAGER_H_
#define PAGER_H_

#include "frameTable.h"
#include "process.h"
#include <vector>

using namespace std;

class Pager {
public:
	virtual ~Pager() {

	};

	virtual FrameTableEntry* get_frame(FrameTable*, vector<Process*>&) = 0;
};

#endif /* PAGER_H_ */
