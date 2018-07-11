//============================================================================
// Name        : lab3.cpp
// Author      : Shucheng Yan
// Version     :
// Copyright   : Shucheng Yan sy1253
// Description : MMU
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
#include "Clock.h"

#include "frameTable.h"
using namespace std;

int main(int argc, char **argv) {

	vector<string> token_list;
	//string file_name = "in10";
	int frame_size = 32;
	//Options* ops = new Options("OPFS");
	//FrameTable* frame_table = new FrameTable(frame_size);

	Options* ops;
	string file_name = argv[argc - 2];
	string rand_file = argv[argc - 1];


	init_token_list(token_list, file_name);
	token_list.push_back("");
	vector<Process*> pro_list;
	TotalStats tstats;


	Pager* pager;
	FrameTable* frame_table;
	//pager = new Second_Chance();
	//pager = new FIFO();
	//pager = new Random("rfile");
	//pager = new NRU("rfile");
	//pager = new Aging(frame_size);
	//pager = new Clock();

	string opt;
	int c = 0;

	while ((c = getopt(argc, argv, "a:o:f:")) != -1) {
		switch (c) {
		case 'a':
			opt = optarg;

			if (opt == "f")
				pager = new FIFO();
			else if (opt == "s")
				pager = new Second_Chance();
			else if (opt == "r")
				pager = new Random(rand_file);
			else if (opt == "n")
				pager = new NRU(rand_file);
			else if (opt == "c")
				pager = new Clock();
			else if (opt == "a")
				pager = new Aging(frame_size);
			else {
				fprintf(stderr,
						"Option -a requires an valid MMU algo choice.\n");
				exit(1);
			}

			break;

		case 'o':
			opt = optarg;

//			for (int i = 0; i < opt.size(); i++) {
//				char op = opt[i];
//				if (op != 'O' && op != 'P' && op != 'F' && op != 'S') {
//					fprintf(stderr,
//							"Option -o requires an valid option set.\n");
//					exit(1);
//
//				}
//			}

			ops = new Options(optarg);

			break;

		case 'f':
			opt = optarg;

			frame_table = new FrameTable(stoi(opt));

			break;

		case '?':
			if (optopt == 'c' || optopt == 'o' || optopt == 'f')
				fprintf(stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint(optopt))
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
			exit(1);

		default:
			exit(1);
		}
	}


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

	string instr;
	int operand = -1;
	int vpage = -1;
	int pro_swi = -1;

	while ((instr = get_token(token_list)) != "") {

		operand = stoi(get_token(token_list));

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

		// get the corresponding vpage for read/write
		vpage = operand;
		PageTableEntry& pte = cur_pro->page_table[vpage];
		Pstats& cur_stats = cur_pro->pstats;

		if (!pte.present) { // handle page fault

			bool valid = false;
			for (int i = 0; i < cur_pro->vma_table.size(); i++) {
				const VMAEntry& vma_entry = cur_pro->vma_table[i];
				if (vpage >= vma_entry.start_vpage
						&& vpage <= vma_entry.end_vpage) {

					// the vpage is within the valid VMA range
					valid = true;

					// update pte info according to vma
					pte.write_protect = vma_entry.write_protected;
					pte.file_mapped = vma_entry.filemapped;
					break;
				}

			}

//
//			if (instr == "w" && pte.write_protect) { // write seg fault
//
//				pte.referenced = 1;
//				cur_stats.segprot++;
//				tstats.cost += SEGPROT_COST;
//				if (ops->Oops) {
//					cout << " SEGPROT" << endl;
//				}
//				//continue;
//			} else{
//				pte.modified = 1;
//			}

			if (!valid) { // invalid reference, seg falut
				tstats.cost += SEGV_COST;
				cur_stats.segv++;
				if (ops->Oops)
					cout << " SEGV" << endl;

				continue;
			}

			// get a frame for the pte
			FrameTableEntry* frame = pager->get_frame(frame_table, pro_list);

			// page replacement is needed
			if (!(frame->isFree)) {

				// unmap UNMAP
				if (ops->Oops)
					cout << " UNMAP " << frame->proid << ":" << frame->vpage
							<< endl;

				// locate the victim page table
				PageTableEntry& victim =
						pro_list[frame->proid]->page_table[frame->vpage];

				Pstats& victim_stats = pro_list[frame->proid]->pstats;

				if (victim.modified == 1) { // dirty page

					if (victim.file_mapped == 1) { // file mapped page
						tstats.cost += FILE_OUT_COST;
						victim_stats.fouts++;
						if (ops->Oops)
							cout << " FOUT" << endl;

					}

					else {
						// page victim out to a swap device
						tstats.cost += PAGE_OUT_COST;
						victim.pagedout = 1;
						victim_stats.outs++;
						if (ops->Oops)
							cout << " OUT" << endl;
					}

					// all changes are made to the local disk
					victim.modified = 0;
					victim.index_to_frame = 0;
				}

				// update victim page table info
				tstats.cost += UNMAP_COST;
				victim_stats.unmaps++;

				victim.present = 0;
				//victim.index_to_frame = 0;
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

				if (pte.pagedout) { // previously paged out to swap device before
					tstats.cost += PAGE_IN_COST;
					cur_stats.ins++;
					if (ops->Oops)
						cout << " IN" << endl;
				}

				else { // ZERO
					pte.present = 0;
					pte.referenced = 0;
					pte.modified = 0;
					pte.pagedout = 0;
					pte.index_to_frame = 0;

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

		if (instr == "w") { // write seg fault

			if (pte.write_protect) {
				pte.referenced = 1;
				cur_stats.segprot++;
				tstats.cost += SEGPROT_COST;
				if (ops->Oops)
					cout << " SEGPROT" << endl;

			}
			//continue;
			else {
				pte.modified = 1;
			}
		}

//		if (instr == "w")
//			pte.modified = 1;

	} // end of while get instruction

	if (ops->Pops)
		printP(pro_list);
	if (ops->Fops)
		printF(frame_table);
	if (ops->Sops)
		printS(pro_list, tstats);

//	for (int i = 0; i < pro_list.size(); i++) {
//		for (int j = 0; j < pro_list[i]->page_table.size(); j++)
//			cout << pro_list[i]->page_table[j].present << " ";
//	}

	return 0;
}

