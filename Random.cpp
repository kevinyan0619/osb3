/*
 * Random.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#include "Random.h"
#include "random_generator.h"

#include <string>
#include <iostream>
#include <fstream>

Random::Random(const string& randfile) :
		grt(randfile) {
}

FrameTableEntry* Random::get_frame(FrameTable* f, vector<Process*>& pro_list) {
	FrameTableEntry* frame = f->get_free_frame();

	if (f == nullptr) {
		int rand = grt.myrandom(f->frame_table.size());
		frame = &((f->frame_table)[rand]);
	}

	return frame;

}

