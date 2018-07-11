/*
 * print_util.h
 *
 *  Created on: Jul 10, 2018
 *      Author: kevinyan
 */

#ifndef PRINT_UTIL_H_
#define PRINT_UTIL_H_


#include <vector>
#include "process.h"
#include "frametable.h"
#include "totalStats.h"
#include <iostream>
using namespace std;

void printP (const vector<Process*>& list);
void printF (const FrameTable* frame);
void printS (const vector<Process*>& list, TotalStats sta);



#endif /* PRINT_UTIL_H_ */
