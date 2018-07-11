/*
 * pstats.h
 *
 *  Created on: Jul 10, 2018
 *      Author: kevinyan
 */

#ifndef PSTATS_H_
#define PSTATS_H_

typedef struct Pstats {
	unsigned long unmaps;
	unsigned long maps;
	unsigned long ins;
	unsigned long outs;
	unsigned long fins;
	unsigned long fouts;
	unsigned long zeros;
	unsigned long segv;
	unsigned long segprot;

	Pstats() :
			unmaps(0), maps(0), ins(0), outs(0), fins(0), fouts(0), zeros(0), segv(
					0), segprot(0) {

	}
} Pstats;

#endif /* PSTATS_H_ */
