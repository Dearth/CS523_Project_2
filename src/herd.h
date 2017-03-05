#ifndef _HERD_H_
#define _HERD_H_

#include "genome.h"

typedef struct Warrior {
	int fitness_;
	genome g_;

	bool operator<(Warrior w) { return fitness_ < w.fitness_; }
} war_s;

typedef vector<war_s> herd;

herd initHerd() {
	herd h;

	srand(time(NULL));

	for(int i = 0; i < POPULATION_SIZE; ++i) {
		war_s temp;
		temp.fitness_ = 0;
		
		h.push_back(temp);
	}

	return h;
}

void sortHerd(herd& h) {
	sort(h.begin(), h.end());
	
	if(DEBUG) {
		for(int i = 0; i < h.size(); ++i) {
			cerr << h.at(i).fitness_;
		}
		cerr << endl;
	}
}

void topHalfSelection(herd& h) {
	sortHerd(h);
	int index;

	for(int i = h.size()-1; i > h.size()/2; --i) {
		do {
			index = rand() % h.size();
		} while(index < (h.size()/2));

		h.at(i) = h.at(index);
	}

}

void rouletteSelection(herd& h) {
	sortHerd(h);
	
	herd new_herd;
	
	int fitness_sum = 0;
	
	for(int i = 0; i < h.size(); ++i) {
		fitness_sum += h.at(i).fitness_;
	}

	if(fitness_sum == 0) {
		return;
	}

	for(int i = 0; i < h.size(); ++i) {
		int index = 0;
		int chance = rand() % fitness_sum;
		
		for(int index = 0; index < h.size(); ++index) {
			chance -= h.at(index).fitness_;

			if(chance <= 0) {
				break;
			}
		}

		new_herd.push_back(h.at(index));

	}

	h = new_herd;
}

void tournmentSelection(herd& h, int size) {
	herd new_herd;

	for(int i = 0; i < h.size(); ++i) {
		war_s champion = h.at(rand()%h.size());

		for(int x = 0; x < (size-1); ++x) {
			int index = rand()%h.size();
			
			if(champion.fitness_ < h.at(index).fitness_) {
				champion = h.at(index);
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

		new_herd.push_back(temp);
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

		new_herd.push_back(temp);
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
