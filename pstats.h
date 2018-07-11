/*
 * pstats.h
 *
 *  Created on: Jul 10, 2018
 *      Author: kevinyan
 */

#ifndef PSTATS_H_
#define PSTATS_H_

typedef struct Pstats {
	long unmaps;
	int maps;
	int ins;
	int outs;
	int fins;
	int fouts;
	int zeros;
	int segv;
	int segprot;

	Pstats() :
			unmaps(0), maps(0), ins(0), outs(0), fins(0), fouts(0), zeros(0), segv(
					0), segprot(0) {

	}
};

#endif /* PSTATS_H_ */
