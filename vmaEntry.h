/*
 * vmaEntry.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#ifndef VMAENTRY_H_
#define VMAENTRY_H_

#include "constant.h"
#include "constant.h"

typedef struct VMAEntry {
	unsigned int start_vpage : MAX_BITS_VIRTUAL_PAGE;
	unsigned int end_vpage : MAX_BITS_VIRTUAL_PAGE;
	unsigned int write_protected :1;
	unsigned int filemapped :1;

	VMAEntry(unsigned int s = 0, unsigned int e = 0, unsigned int w = 0,
			unsigned int f = 0) :
			start_vpage(s), end_vpage(s), write_protected(w), filemapped(f) {

	}

} VMAEntry;

#endif /* VMAENTRY_H_ */
