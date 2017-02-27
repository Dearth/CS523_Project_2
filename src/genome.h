#ifndef _GNM_H_
#define _GNM_H_

#include <string>
#include <vector>
#include "codewars.h"
#include <ctime>
#include <cstdlib>

typedef struct Gene {
	Instruction instruction_;
	addmode arg_mod_one_;
	addmode arg_mod_two_;
	int arg_one_;
	int arg_two_;
} gene_s;

typedef vector<Gene> genome;

genome* initGenome() {
	srand(time(NULL));

	return new genome;
}

void add_instruction(genome* g) {
	

#endif
