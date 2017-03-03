#ifndef _GNM_H_
#define _GNM_H_

#include "codewars.h"

typedef struct Gene {
	Instructions instruction_;
	addmode arg_mod_one_;
	addmode arg_mod_two_;
	int arg_one_;
	int arg_two_;
} gene_s;

typedef std::vector<Gene> genome;

//create a genome and seed random generator
genome* initGenome() {
	srand(time(NULL));

	return new genome;
}

void genoToPheno(genome* _genome,string name){

	ofstream outfile (name);
	if(outfile.fail()) {
		cerr << "Error opening up file: " << name << endl;
		exit(1);
	}

	outfile << ";redcode-94" << std::endl;
	outfile << ";name " << name	<< std::endl;
	outfile << ";author " << author	<< std::endl;
	outfile << ";assert CORESIZE==8000" << std::endl;
	for(Gene gene: *_genome) {
		outfile << instructions[gene.instruction_]<<" "
			<<addressMode[gene.arg_mod_one_]<<gene.arg_one_<<", "
			<<addressMode[gene.arg_mod_two_]<<gene.arg_two_<<endl;;
	}
	
	outfile.close();
  
}

//generate a random new gene for genome
gene_s createNewGene() {
	gene_s new_gene;

	new_gene.instruction_ = static_cast<Instructions>(rand()%MAX_CODEWARS_INSTRUCTION);
	
	new_gene.arg_mod_one_ = static_cast<addmode>(rand()%MAX_ARGUMENT_MOD);
	new_gene.arg_mod_two_ = static_cast<addmode>(rand()%MAX_ARGUMENT_MOD);

	new_gene.arg_one_ = rand()%MAX_MEMORY;
	new_gene.arg_two_ = rand()%MAX_MEMORY;

	return new_gene;
}

//randomly change the instruction
void mutate_instruction(gene_s* g) {
  g->instruction_ = static_cast<Instructions>(rand()%MAX_CODEWARS_INSTRUCTION);
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
		g->arg_mod_one_ = static_cast<addmode>(rand()%MAX_ARGUMENT_MOD);
	} else {
		g->arg_mod_two_ = static_cast<addmode>(rand()%MAX_ARGUMENT_MOD);
	}
}

/*
	add_gene: integer percent chance of adding a new gene (adds are appends to current program)
	swap_gene: integer percent chance of swaping two genes
	del_gene: integer percent chance of deleting an existing gene
	ins_gene: integer percent chance of inserting a new gene
	change_gene: integer percent chance of mutating a random gene
	mutate_ins: integer percent chance of mutating a genes instruction
	mutate_mode: integer percent chance of mutating a genes address mode (equal probability of changing mode 1 or mode 2)
	mutate_addr: integer percent chance of mutating a genes address (equal probability of changing addr 1 or 2)

	sum(*_gene) == 100 and sum(mutate_*) == 100 to be valid percentages

	Values should be given as raw percents, cummulative percentage is calculated internally for control
	flow.

	ex:
		if( RANDOM <= add_gene) {
			//add gene
		} else if ( RANDOM <= add_gene+swap_gene ) {
			//swap_gene
		} 
		.
		.
		.
*/

void mutateGenome(genome* g, 	const int add_gene, 
								const int swap_gene, 
								const int del_gene, 
								const int ins_gene, 
								const int change_gene, 
								const int mutate_ins,
								const int mutate_mode,
								const int mutate_addr ) {
	
	//choose mutation on % scale
	int mutation = (rand()%100) + 1;
	int index_one, index_two;

	if(g->size() != 0) {
		index_one = rand()%g->size();
		index_two = rand()%g->size();
	}

	//generate cummulative percent chances for gene mutation
	const int swap_percent = add_gene + swap_gene;
	const int del_percent = swap_percent + del_gene;
	const int ins_percent = del_percent + ins_gene;
	const int change_percent = ins_percent + change_gene;

	if(mutation <= mutation) {
		//append a new gene
		g->push_back(createNewGene());

	} else if (mutation <= swap_percent) {
		//swap genes at two locations
		if(g->size() < 2) {
			return;
		}

		auto first = g->begin() + index_one;
		auto second = g->begin() + index_two;

		iter_swap(first, second);
	
	} else if (mutation <= del_percent) {
		//delete gene
		if(g->size() == 0) {
			return;
		}

		auto loc = g->begin() + index_one;

		g->erase(loc);

	} else if (mutation <= ins_percent) {
		//insert gene
		auto loc = g->begin() + index_one;

		g->insert(loc, createNewGene());

	} else if (mutation <= change_percent) {
		//change gene
		//calculate cummulative percentages for mutate
		if(g->size() == 0) {
			return;
		}

		const int mode_percent = mutate_ins + mutate_mode;
		const int addr_percent = mode_percent + mutate_addr;

		mutation = (rand()%100) + 1;
		
		if(mutation <= mutate_ins) {
			//change instruction
			//mutute the gene pointed to by the begin iterator offset by index
			//dereference the iterator to get the memory location of the gene
			//instead of memory location of iterator
			mutate_instruction(&(*(g->begin()+index_one)));

		} else if (mutation <= mode_percent) {
			//change mode
			mutate_arg_mode(&(*(g->begin()+index_one)));

		} else if (mutation <= addr_percent) {
			//change address
			mutate_argument(&(*(g->begin()+index_one)));

		} else {
			cerr << "Gene mutation percentages add up to less than 100%" << endl; 
		}	
	} else {
		cerr << "Genome mutation percentatges add up to less than 100%" << endl;
		exit(1);
	}
}

genome* onePointCrossover(genome* g1, genome* g2) {
	int s1 = g1->size();
	int s2 = g2->size();
	int pivot = 0;

	genome* g = new genome;

	if(s1 == 0) {
		*g = *g2;
	} else if (s2 == 0) {
		*g = *g1;
	} else {

		//use smaller vector for pivot point
		if(s1 < s2) {
			pivot = rand()%s1;
		} else {
			pivot = rand()%s2;
		}

		if(rand()%2 == 0) {
			for(int i = 0; i < pivot; ++i) {
				g->push_back(g1->at(i));
			}
	
			for(int i = pivot + 1; i < s2; ++i) {
				g->push_back(g2->at(i));
			}
		} else {
			for(int i = 0; i < pivot; ++i) {
				g->push_back(g2->at(i));
			}

			for(int i = pivot + 1; i < s1; ++i) {
				g->push_back(g1->at(i));
			}
		}
	}
	return g;
}

genome* uniformCrossover(genome* g1, genome* g2) {
	int s1 = g1->size();
	int s2 = g2->size();
	int pivot = 0;

	genome* g = new genome;

	if(s1 == 0) {
		*g = *g2;
	} else if (s2 == 0) {
		*g = *g1;
	} else {
		if (s1 < s2) {
			for(int i = 0; i < s1; ++i) {
				if(rand()%2) {
					g->push_back(g1->at(i));
				} else {
					g->push_back(g2->at(i));
				}
			}
	
			for(int i = s1; i < s2; ++i) {
				g->push_back(g2->at(i));
			}

		} else {
			for(int i = 0; i < s2; ++i) {
				if(rand()%2) {
					g->push_back(g1->at(i));
				} else {
					g->push_back(g2->at(i));
				}
			}
	
			for(int i = s2; i < s1; ++i) {
				g->push_back(g1->at(i));
			}
		}
	}
	return g;
}
#endif


































