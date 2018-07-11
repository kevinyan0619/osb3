/*
 * options.cpp
 *
 *  Created on: Jul 10, 2018
 *      Author: kevinyan
 */

#include "options.h"

Options::Options(const string& ops) :
		Oops(false), Pops(false), Fops(false), Sops(false) {

	for (int i = 0; i < ops.length(); i++) {
		switch (ops[i]) {
		case 'O':
			Oops = true;
			break;
		case 'P':
			Pops = true;
			break;
		case 'F':
			Fops = true;
			break;
		case 'S':
			Sops = true;
			break;
		default:
			break;

		}

	}

}
