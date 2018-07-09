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

#include "pager.h"
#include "fileReader.h"
#include "process.h"
#include "frameTable.h"
#include "vmaEntry.h"

//#include "frameTable.h"
using namespace std;

int main() {

	vector<string> token_list;
	string file_name = "in1";
	init_token_list(token_list, file_name);
	token_list.push_back("");
	vector<Process*> pro_list;
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

		Process proc;
		proc.pid = pid;

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

			proc.vma_table.push_back(entry);

		}

		pro_list.push_back(&proc);
		pid++;

	}

	Pager* pager;
	int frame_size = 32;
	Process* cur_pro;
	FrameTable* frame_table = new FrameTable(frame_size);

	string instr;
	int vpage = -1;
	int pro_swi = -1;

	while ((instr = get_token(token_list)) != "") {

		if (instr == "c") { // context switch
			pro_swi = stoi(get_token(token_list));

			cur_pro = pro_list[pro_swi];

			continue;
		}

		vpage = stoi(get_token(token_list));

		PageTableEntry& pte = cur_pro->page_table[vpage];

		if (!pte.present) {
			bool valid = false;

			for (int i = 0; i < cur_pro->vma_table.size(); i++) {
				VMAEntry vma_entry = cur_pro->vma_table[i];
				if (vma_entry.start_vpage <= vpage
						&& vma_entry.end_vpage >= vpage) {

					if (vma_entry.write_protected == 1 && instr == "w") {
						// write seg fault

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
				continue;

			}

			FrameTableEntry* frame = pager->get_frame(frame_table, pro_list);

			if (!frame->isFree) {
				// unmap UNMAP

				PageTableEntry& victim =
						pro_list[frame->proid]->page_table[frame->vpage];

				if (victim.modified == 1) { // dirty page
					if (victim.file_mapped == 1) {
						// fout

					}

					else {
						// paged the page out to a swap device
						victim.pagedout = 1;

					}

					// all changes are made to the local disk
					victim.modified = 0;

				}

				// unmap
				victim.present = 0;
				victim.index_to_frame = 0;

			}

			else {
				// the free frame will be used
				frame->isFree = false;
			}

			if (pte.file_mapped == 1) { // file mapped
				// FIN

			}

			else { //not file mapped

				if (pte.pagedout == 1) { 	// paged out to swap device before

				}

				else { // ZERO

				}

			}

			pte.present = 1;
			pte.index_to_frame = frame->index;

			// update frame info
			frame->proid = cur_pro->pid;
			frame->vpage = vpage;

		} // end of check if pte is present

		pte.referenced = 1;
		if (instr == "w")
			pte.modified = 1;

	}

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
