/*
 * pageTableEntry.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#ifndef PAGETABLEENTRY_H_
#define PAGETABLEENTRY_H_

#include "constant.h"

typedef struct PageTableEntry {
	unsigned int present :1;
	unsigned int write_protect :1;
	unsigned int modified :1;
	unsigned int referenced :1;
	unsigned int pagedout :1;
	unsigned int file_mapped :1;
	unsigned int index_to_frame :MAX_BITS_FRAME_TABLE;

	PageTableEntry(unsigned int p = 0, unsigned int w = 0, unsigned int m = 0,
			unsigned int r = 0, unsigned int pout = 0, unsigned int map = 0,
			unsigned int index = 0) :
			present(p), write_protect(w), modified(m), referenced(r), pagedout(
					pout), file_mapped(map), index_to_frame(index) {

	}

} PageTableEntry;

#endif /* PAGETABLEENTRY_H_ */
