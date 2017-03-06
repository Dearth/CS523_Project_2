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
			cerr << h.at(i).fitness_ << " ";
		}
		cerr << endl;
	}
}

herd elitism(herd& h){
	herd new_herd;
	new_herd.resize(POPULATION_SIZE);
	sortHerd(h);			
	for(int i=h.size()-1;i>h.size()-ELITE_SIZE;i--){
		new_herd.at(i) = h.at(i);	
	}
	return new_herd;	
}

war_s mutateOrCrossover(war_s w1, war_s w2) {
	war_s new_war;
	new_war.fitness_ = 0;

	int event = rand() % 100;

	if(event <= crossover_rate) {
		if(crossover_type == 0) {
			new_war.g_ = w1.g_;
		} else if(crossover_type == 1) {
			new_war.g_ = singlePointCrossover(w1.g_, w2.g_);
		}else if (crossover_type == 2) {
			new_war.g_ = uniformCrossover(w1.g_, w2.g_);
		}

	} else if (event <= (mutation_rate + crossover_rate)) {
		new_war.g_ = w1.g_;
		mutateGenome(new_war.g_, add_gene, swap_gene, del_gene, ins_gene, change_gene, mutate_ins, mutate_mode, mutate_addr);
	} else {
		cerr << "Crossover rate and mutation rate add up to less than 100%\n";
		exit(1);
	}

	return new_war;
}

void topHalfSelection(herd& h) {
	sortHerd(h);
	int index_one;
	int index_two;

	for(int i = 0; i < h.size()/2; ++i) {
		do {
			index_one = rand() % h.size();
		} while (index_one < h.size()/2);
		
		do {
			index_two = rand() % h.size();
		} while (index_one < h.size()/2);
	
		h.at(i) = mutateOrCrossover(h.at(index_one), h.at(index_two));
	}
}

void rouletteSelection(herd& h) {
	herd new_herd=elitism(h);
	
	int fitness_sum = 0;
	
	for(int i = 0; i < h.size(); ++i) {
		fitness_sum += h.at(i).fitness_;
	}

	if(fitness_sum == 0) {
		return;
	}

	for(int i = 0; i < h.size()-ELITE_SIZE; ++i) {
		int index_one = 0;
		int index_two = 0;
		int chance_one = rand() % fitness_sum;
		int chance_two = rand() % fitness_sum;
		
		for(index_one = 0; index_one < h.size(); ++index_one) {
			chance_one -= h.at(index_one).fitness_;

			if(chance_one <= 0) {
				break;
			}
		}

		for(index_two = 0; index_two < h.size(); ++index_two) {
			chance_two -= h.at(index_two).fitness_;

			if(chance_two <= 0) {
				break;
			}
		}

		new_herd.at(i) = mutateOrCrossover(h.at(index_one), h.at(index_two));
	}

	h = new_herd;
}

void tournmentSelection(herd& h, int size) {

	herd new_herd = elitism(h);

	for(int i = 0; i < h.size()-ELITE_SIZE; ++i) {
		int champ_one = rand() % h.size();
		int champ_two = rand() % h.size();

		for(int x = 0; x < size; ++x) {
			int index = rand() % h.size();
			if(h.at(champ_one).fitness_ < h.at(index).fitness_){
				champ_one = index;
			}
		}

		for(int x = 0; x < size; ++x) {
			int index = rand() % h.size();
			if(h.at(champ_one).fitness_ < h.at(index).fitness_){
				champ_two = index;
			}
		}

		new_herd.at(i) = mutateOrCrossover(h.at(champ_one), h.at(champ_two));
	}

	h = new_herd;
}

void singlePointCrossover(herd& h) {
	herd new_herd=elitism(h);

	for(int i = 0; i < h.size()-ELITE_SIZE; ++i) {
		int index_one = rand()%h.size();
		int index_two = rand()%h.size();

		war_s temp;
		temp.fitness_ = 0;
		temp.g_ = singlePointCrossover(h.at(index_one).g_, h.at(index_two).g_);

		new_herd.at(i) = temp;
	}

	h = new_herd;
}

void uniformCrossover(herd& h) {
  	herd new_herd=elitism(h);

	for(int i = 0; i < h.size()-ELITE_SIZE; ++i) {
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

	for(int i = 0; i < h.size()-ELITE_SIZE; ++i) {
     
		mutateGenome(h.at(i).g_ , add_gene, swap_gene, del_gene, ins_gene, change_gene, mutate_ins, mutate_mode, mutate_addr); 	
    
	}

}
#endif
