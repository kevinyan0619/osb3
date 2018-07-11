/*
 * constant.h
 *
 *  Created on: Jul 7, 2018
 *      Author: kevinyan
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_


#define PAGE_TABLE_SIZE 64
#define MAX_BITS_FRAME_TABLE 7
#define MAX_SIZE_FRAME_TABLE 128
#define MAX_BITS_VIRTUAL_PAGE 6
#define NRU_CLASS 4
#define BITSET_SIZE 32

#define MAP_COST 400
#define UNMAP_COST 400

#define PAGE_IN_COST 3000
#define PAGE_OUT_COST 3000

#define FILE_IN_COST 2500
#define FILE_OUT_COST 2500

#define ZERO_COST 150
#define SEGV_COST 240
#define SEGPROT_COST 300
#define REF_COST 1
#define CONTEXT_SWITCH_COST 121

#endif /* CONSTANT_H_ */
