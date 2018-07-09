/*
 * NRU.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#ifndef NRU_H_
#define NRU_H_

#include "pager.h"
#include "random_generator.h"
#include "constant.h"

#include <array>
#include <string>

using namespace std;

class NRU: public Pager {
public:
	NRU(const string&);

	Random_generator grt;
	int count;

	FrameTableEntry* get_frame(FrameTable*, vector<Process*>&);

	array<vector<FrameTableEntry*>, NRU_CLASS> nru_class;

};

#endif /* NRU_H_ */
