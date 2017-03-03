#ifndef _HERD_H_
#define _HERD_H_

#include "genome.h"

typedef struct Warrior {
	int fitness_;
	genome* g_;

	bool operator<(Warrior w) { return fitness_ < w.fitness_; }
} war_s;

typedef vector<war_s> herd;

herd initHerd() {
	herd h;

	for(int i = 0; i < POPULATION_SIZE; ++i) {
		genome* temp = initGenome();
		h.push_back(temp);
	}

	return h;
}

void sortHerd(herd& h) {
	sort(h.begin(), h.end());
}

void topHalfSelection(herd& h) {
	sortHerd(h);

	for(int i = h.size(); i > h.size()/2; --i) {
		int index = rand()%(h.size()/2) + (h.size()/2);
		
		h.at(i) = h.at(index);
	}

}

void rouletteSelection(herd& h) {
	sortHerd(h);
	
	herd new_herd;
	
	double fitness_sum = 0.0;
	
	for(int i = 0; < h.size(); ++i) {
		fitness_sum += (double)h.at(i).fitness_;
	}

	for(int i = 0; i < h.size(); ++i) {
		double chance = (((double) rand()) / RAND_MAX);
		chance = chance * fitness_sum;
		int index = 0;
		
		while(chance > 0){
			chance -= h.at(index).fitness_;
			index++;
		}

		new_herd.push_back(h.at(index));

	}

	h = new_herd;
}

void tournmentSelection(herd& h, int size) {
	herd new_herd;

	for(int i = 0; i < h.size(); ++i) {
		war_s champion = h.at(rand()%h.size);

		for(int x = 0; x < (size-1); ++x) {
			int index = rand()%h.size();
			
			if(champion.fitness_ < h.at(index)) {
				champion = h.at(index)
			}
		}

		new_herd.push_back(champion);
	}

	h = new_herd;
}

void singlePointCrossover(herd& h) {
	herd new_herd;

	for(int i = 0; i < h.size(); ++i) {
		int index_one = rand()%h.size();
		int index_two = rand()%h.size();

		war_s temp;
		temp.fitness_ = 0;
		temp.g_ = onePointCrossover(h.at(index_one).g_, h.at(index_two).g_);

		new_herd.at(i) = temp;
	}

	h = new_herd;
}

void uniformCrossover(herd& h) {
	herd new_herd;

	for(int i = 0; i < h.size(); ++i) {
		int index_one = rand()%h.size();
		int index_two = rand()%h.size();

		war_s temp;
		temp.fitness_ = 0;
		temp.g_ = uniformCrossover(h.at(index_one).g_, h.at(index_two).g_);

		new_herd.at(i) = temp;
	}

	h = new_herd;
}

void mutateHerd(herd& h,	const int add_gene, 
						 	const int swap_gene, 
							const int del_gene, 
							const int ins_gene, 
							const int change_gene, 
							const int mutate_ins,
							const int mutate_mode,
							const int mutate_addr ) {
	
	for(int i = 0; i < h.size(); ++i) {
	
		mutateGenome(h.at(i).g_ , add_gene, swap_gene, del_gene, ins_gene, change_gene, mutate_ins, mutate_mode, mutate_addr); 	

	}

}
#endif
