/*
 * totalStats.h
 *
 *  Created on: Jul 11, 2018
 *      Author: kevinyan
 */

#ifndef TOTALSTATS_H_
#define TOTALSTATS_H_

typedef struct TotalStats {

	unsigned long ctx_switches;
	unsigned long inst_count;
	unsigned long long cost;

	TotalStats() :
			ctx_switches(0), inst_count(0), cost(0) {

	}
} TotalStats;

#endif /* TOTALSTATS_H_ */
