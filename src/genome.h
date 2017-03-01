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

//create a genome and seed random generator
genome* initGenome() {
	srand(time(NULL));

	return new genome;
}

//generate a random new gene for genome
gene_s createNewGene() {
	gene_s new_gene;

	new_gene.instruction_ = rand()%MAX_CODEWARS_INSTRUCTION;
	
	new_gene.arg_mod_one_ = rand()%MAX_ARGUMENT_MOD;
	new_gene.arg_mod_two_ = rand()%MAX_ARGUMENT_MOD;

	new_gene.arg_one_ = rand()%MAX_MEMORY;
	new_gene_arg_two_ = rand()%MAX_MEMORY;

	return new_gene;
}

//randomly change the instruction
void mutate_instruction(gene_s* g) {
	g->instruction_ = rand()%MAX_CODEWARS_INSTRUCTION;
}

//randomly change one of the arguments
void mutate_argument(gene_s* g) {
	if(rand()%2 == 0) {
		g->arg_one_ = rand()%MAX_MEMORY;
	} else {
		g->arg_two_ = rand()%MAX_MEMORY;
	}
}

//randomly change one of the argument modes
void mutate_arg_mode(gene_s* g) {
	if(rand()%2 == 0) {
		g->arg_mod_one_ = rand()%MAX_ARGUMENT_MOD;
	} else {
		g->arg_mod_two_ = rand()%MAX_ARGUMENT_MOD;
	}
}


void mutateGenome(genome* g, const int add_g, const int swap_g, const int del_g, const int ins_g, const int change_g) {
	int index = rand()% g->size();

	//choose mutation on % scale
	int mutation = rand()%100;

	//generate cummulative percent chances
	const swap_c = add_g + swap_g;

	if(add_g == mutation) {
		//add new gene
	} else if 
}

#endif
