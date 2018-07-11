/*
 * print_util.cpp
 *
 *  Created on: Jul 10, 2018
 *      Author: kevinyan
 */

#include "print_util.h"

void printP(const vector<Process*>& list) {
	for (int i = 0; i < list.size(); i++) {
		Process* pro = list[i];

		cout << "PT[" << pro->pid << "]:";

		for (int j = 0; j < pro->page_table.size(); j++) {
			PageTableEntry entry = pro->page_table[j];

			if (entry.present == 1) {
				cout << " " << j << ":";
				cout << (entry.referenced ? "R" : "-");
				cout << (entry.modified ? "M" : "-");
				cout << (entry.pagedout ? "S" : "-");
			} else {
				cout << " " << (entry.pagedout ? "#" : "*");
			}
		}
	}
	cout << endl;
}

void printF(const FrameTable* frame) {
	cout << "FT: ";
	for (int i = 0; i < frame->frame_table.size(); i++) {
		FrameTableEntry entry = frame->frame_table[i];
		if (entry.isFree)
			cout << " *";
		else
			cout << " " << entry.proid << ":" << entry.vpage;
	}
	cout << endl;
}

void printS(const vector<Process*>& list, TotalStats tstas) {
	for (int i = 0; i < list.size(); i++) {
		Pstats &sts = list[i]->pstats;

		printf(
				"PROC[%d]: U=%lu M=%lu I=%lu O=%lu FI=%lu FO=%lu Z=%lu SV=%lu SP=%lu\n",
				list[i]->pid, sts.unmaps, sts.maps, sts.ins, sts.outs, sts.fins,
				sts.fouts, sts.zeros, sts.segv, sts.segprot);

	}

	printf("TOTALCOST %lu %lu %llu\n", tstas.ctx_switches, tstas.inst_count,
			tstas.cost);

}
