/*
 * frameTableEntry.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#ifndef FRAMETABLEENTRY_H_
#define FRAMETABLEENTRY_H_

typedef struct FrameTableEntry {
	int index;
	int proid;
	int vpage;
	bool isFree;

	FrameTableEntry(int i = -1, int p = -1, int v = -1, bool is = true) :
			index(i), proid(p), vpage(v), isFree(is) {

	}

} FrameTableEntry;

#endif /* FRAMETABLEENTRY_H_ */
