/*
 * fileReader.cpp
 *
 *  Created on: Jul 8, 2018
 *      Author: kevinyan
 */

#include "fileReader.h"
using namespace std;

string get_token(const vector<string>& list) {
	static int ofs = 0;
	string tk = list[ofs];
	ofs++;
	return tk;
}

void init_token_list(vector<string>& token_list, string file_name) {

	string line = "";
	ifstream myfile(file_name);

	if (!myfile.is_open()) {
		cout << "Error: Unable to open file";
		exit(1);
	}

	while (!myfile.eof()) {
		myfile >> line;
		if (line[0] == '#') {
			myfile.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		else {
			token_list.push_back(line);
		}

	}

}
