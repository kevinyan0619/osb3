//============================================================================
// Name        : lab3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "fileReader.h"
#include "process.h"
#include "frameTable.h"
#include "vmaEntry.h"
#include "options.h"
#include "totalStats.h"
#include "print_util.h"

#include "FIFO.h"
#include "Second_Chance.h"
#include "Random.h"
#include "NRU.h"
#include "Aging.h"

//#include "frameTable.h"
using namespace std;

int main() {

	vector<string> token_list;
	string file_name = "in1";
	int frame_size = 32;

	Pager* pager;
	pager = new Second_Chance();


	init_token_list(token_list, file_name);
	token_list.push_back("");
	vector<Process*> pro_list;

	Options* ops = new Options("OPFS");
	TotalStats tstats;
//	int i = 0;
//	while (i < token_list.size()) {
//		cout << get_token(token_list) << '\n';
//		i++;
//	}

	int num_pro = stoi(get_token(token_list));
	int num_vma = -1;
	int start_vpage = -1;
	int end_vpage = -1;
	int write_protected = -1;
	int file_Mapped = -1;
	int pid = 0;
	for (int i = 0; i < num_pro; i++) {

		Process* proc = new Process();
		proc->pid = pid;

		num_vma = stoi(get_token(token_list));

		for (int j = 0; j < num_vma; j++) {
			start_vpage = stoi(get_token(token_list));
			end_vpage = stoi(get_token(token_list));
			write_protected = stoi(get_token(token_list));
			file_Mapped = stoi(get_token(token_list));

//			VMAEntry entry = { start_vpage, end_vpage, write_protected,
//					file_Mapped };
			VMAEntry entry;
			entry.start_vpage = start_vpage;
			entry.end_vpage = end_vpage;
			entry.write_protected = write_protected;
			entry.filemapped = file_Mapped;

			proc->vma_table.push_back(entry);

		}

		pro_list.push_back(proc);
		pid++;

	}

//	for (int k = 0; k < pro_list.size(); k++)
//		cout << pro_list[k]->pid << '\n';



	Process* cur_pro;
	FrameTable* frame_table = new FrameTable(frame_size);

	string instr;
	int vpage = -1;
	int pro_swi = -1;

	while ((instr = get_token(token_list)) != "") {

		int operand = stoi(get_token(token_list));

		if (ops->Oops)
			cout << tstats.inst_count << ": ==> " << instr << " " << operand
					<< endl;

		tstats.inst_count++;

		if (instr == "c") { // context switch
			tstats.ctx_switches++;
			tstats.cost += CONTEXT_SWITCH_COST;
			pro_swi = operand;

			cur_pro = pro_list[pro_swi];

			continue;
		}

		tstats.cost += REF_COST;

		vpage = operand;

		PageTableEntry& pte = cur_pro->page_table[vpage];

		Pstats& cur_stats = cur_pro->pstats;

		if (!pte.present) {
			bool valid = false;

			for (int i = 0; i < cur_pro->vma_table.size(); i++) {
				VMAEntry vma_entry = cur_pro->vma_table[i];
				if (vma_entry.start_vpage <= vpage
						&& vma_entry.end_vpage >= vpage) {

					if (vma_entry.write_protected == 1 && instr == "w") {
						// write seg fault

						pte.referenced = 1;
						cur_stats.segprot++;
						tstats.cost += SEGPROT_COST;
						if (ops->Oops) {
							cout << " SEGPROT" << endl;
						}
						continue;
					}

					// the vpage is within the valid VMA range
					valid = true;

					// update pte info according to vma
					pte.write_protect = vma_entry.write_protected;
					pte.file_mapped = vma_entry.filemapped;
					break;
				}
			}

			if (!valid) { // invalid reference, seg falut
				tstats.cost += SEGV_COST;
				cur_stats.segv++;
				if (ops->Oops)
					cout << " SEGV" << endl;

				continue;
			}

			FrameTableEntry* frame = pager->get_frame(frame_table, pro_list);

			if (!(frame->isFree)) {

				// accumulate num of page replacement?

				// unmap UNMAP
				if (ops->Oops)
					cout << " UNMAP " << frame->proid << ":" << frame->vpage
							<< endl;

				PageTableEntry& victim =
						pro_list[frame->proid]->page_table[frame->vpage];

				Pstats& victim_stats = pro_list[frame->proid]->pstats;

				if (victim.modified == 1) { // dirty page
					if (victim.file_mapped == 1) {
						tstats.cost += FILE_OUT_COST;
						victim_stats.fouts++;
						if (ops->Oops)
							cout << " FOUT" << endl;

					}

					else {
						// paged the page out to a swap device
						tstats.cost += PAGE_OUT_COST;
						victim.pagedout = 1;
						victim_stats.outs++;
						if (ops->Oops)
							cout << " OUT" << endl;

					}

					// all changes are made to the local disk
					victim.modified = 0;
				}

				// unmap
				tstats.cost += UNMAP_COST;
				victim_stats.unmaps++;
				victim.present = 0;
				victim.index_to_frame = 0;

			}

			else {
				// the free frame will be used
				frame->isFree = false;
			}

			if (pte.file_mapped) { // file mapped
				tstats.cost += FILE_IN_COST;
				cur_stats.fins++;
				if (ops->Oops)
					cout << " FIN" << endl;

			}

			else { //not file mapped

				if (pte.pagedout) { 	// paged out to swap device before
					tstats.cost += PAGE_IN_COST;
					cur_stats.ins++;
					if (ops->Oops)
						cout << " IN" << endl;
				}

				else { // ZERO
					tstats.cost += ZERO_COST;
					cur_stats.zeros++;
					if (ops->Oops)
						cout << " ZERO" << endl;
				}

			}

			tstats.cost += MAP_COST;
			cur_stats.maps++;
			if (ops->Oops)
				cout << " MAP " << frame->index << endl;

			// update pte
			pte.present = 1;
			pte.index_to_frame = frame->index;

			// update frame table
			frame->proid = cur_pro->pid;
			frame->vpage = vpage;

		} // end of check if pte is present

		pte.referenced = 1;
		if (instr == "w")
			pte.modified = 1;

	} // end of while get instruction

	if (ops->Pops)
		printP(pro_list);
	if (ops->Fops)
		printF(frame_table);
	if (ops->Sops)
		printS(pro_list, tstats);

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

//	for (int i = 0; i < pro_list.size(); i++) {
//		for (int j = 0; j < pro_list[i]->page_table.size(); j++)
//			cout << pro_list[i]->page_table[j].present << " ";
//	}

	return 0;
}
