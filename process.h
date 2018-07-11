/*
 * process.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include "vmaEntry.h"
#include "pageTableEntry.h"
#include "pstats.h"
#include <array>
#include <vector>

using namespace std;

typedef struct Process {
	int pid;

	vector<VMAEntry> vma_table;

	array<PageTableEntry, PAGE_TABLE_SIZE> page_table;

	Pstats pstats;

} Process;

#endif /* PROCESS_H_ */
