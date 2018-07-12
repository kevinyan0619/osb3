/*
 * fileReader.h
 *
 *  Created on: Jul 8, 2018
 *      Author: kevinyan
 */

#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

string get_token(const vector<string>& list);
void init_token_list(vector<string>& token_list, string file_name);

#endif /* FILEREADER_H_ */
