#ifndef _GNM_H_
#define _GNM_H_

#include <string>
#include <vector>
#include "codewars.h"
#include <ctime>
#include <cstdlib>

typedef struct Gene {
	Instructions instruction_;
	addmode arg_mod_one_;
	addmode arg_mod_two_;
	int arg_one_;
	int arg_two_;
} gene_s;

typedef std::vector<Gene> genome;

genome* initGenome() {
	srand(time(NULL));

	return new genome;
}

gene_s createNewGene() {
	gene_s new_gene;

	new_gene.instruction_ = static_cast<Instructions>(rand()%MAX_CODEWARS_INSTRUCTION);
	
	new_gene.arg_mod_one_ = static_cast<addmode>(rand()%MAX_ARGUMENT_MOD);
	new_gene.arg_mod_two_ = static_cast<addmode>(rand()%MAX_ARGUMENT_MOD);

	new_gene.arg_one_ = rand()%MAX_MEMORY;
	new_gene.arg_two_ = rand()%MAX_MEMORY;

	return new_gene;
}

void mutate_instruction(gene_s* g) {
  g->instruction_ = static_cast<Instructions>(rand()%MAX_CODEWARS_INSTRUCTION);
}

void mutate_argument(gene_s* g) {
	if(rand()%2 == 0) {
		g->arg_one_ = rand()%MAX_MEMORY;
	} else {
		g->arg_two_ = rand()%MAX_MEMORY;
	}
}

void mutate_arg_mode(gene_s* g) {
	if(rand()%2 == 0) {
	  g->arg_mod_one_ = static_cast<addmode>(rand()%MAX_ARGUMENT_MOD);
	} else {
		  g->arg_mod_two_ = static_cast<addmode>(rand()%MAX_ARGUMENT_MOD);
	}
}


#endif
