#ifndef _GNM_H_
#define _GNM_H_

#include <string>
#include <vector>
#include "codewars.h"

typedef struct Genome {
	string instruction_;
	char arg_mod_one_;
	char arg_mod_two_;
	char arg_one_;
	char arg_two_;
} genome_s;

vector<genome_s>* initGenome() {
	genome = new vector<genome_s>;

	return genome;

}



#endif
