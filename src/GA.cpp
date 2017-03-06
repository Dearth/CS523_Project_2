#include "herd.h"
const wilkies BENCH=BLUEFUNK;
int fitness(string file,string author,bool output,wilkies benchMark){

	FILE *in;
	char buff[512];
	string cmd="./pmars -r 100 ../WilkiesBench/"+wilkiesBench[benchMark]  +" "+ file + " 2>&1";
	author+=" scores";
	string error = "error";
	//cout<<author;
	if(!(in = popen(cmd.c_str(), "r"))){
		return -1;
	}
	char* results;
	char* point;
	string::size_type sz;
	while(fgets(buff, sizeof(buff), in)!=NULL){
		if(output) {
	  		printf("%s",buff);
		}
	
		if(NULL != (point=strstr(buff,author.c_str()))){
			strncpy(buff,point+author.length()+1,10);
			pclose(in);
	    	return stoi(buff,&sz);
		}
		
		if(NULL != (point=strstr(buff,error.c_str()))){
			pclose(in);
			return -1;
		}
	}

	pclose(in);

	return 0;
}

bool diverse(herd h){
	int sum=0;
	for(int i=0;i<h.size();i++){
		sum+=h.at(i).fitness_;
	}
	sum /= (double)h.size();
	if(sum==0) {
		return true;
	}

	for(int i=0;i<h.size();i++){
		double x = (double)h.at(i).fitness_ / sum;
		double upper_bound = 1.0 + tolerance;
		double lower_bound = 1.0 - tolerance;

		if(!((x >= lower_bound*sum) && (x <= upper_bound*sum))) {
			return true;
		}
	}
	return false;
}

bool islandDiverse(vector<herd>& i) {
	bool ret = true;

	for(int x = 0; x < i.size(); ++x) {
		ret = ret && diverse(i.at(x));
	}

	return ret;
}

void runGA(int crossover_rate, int mutation_rate) {
	
	vector<herd> islands;

	for(int i = 0; i < NUMBER_OF_ISLANDS; ++i) {
		herd h = initHerd();
		islands.push_back(h);
	}

	int current_generation = 0;

	while(islandDiverse){
		for(int i = 0; i < islands.size(); ++i) {
			int event = rand() % 100;
		
			if(event <= crossover_rate) {
				if(crossover_type == 1) {
					singlePointCrossover(islands.at(i));
				}else if (crossover_type == 2) {
					uniformCrossover(islands.at(i));
				}
	
			} else if (event <= (mutation_rate + crossover_rate)) {
				mutateHerd(islands.at(i), add_gene, swap_gene, del_gene, ins_gene, change_gene, mutate_ins, mutate_mode, mutate_addr);
			} else {
				cerr << "Crossover rate and mutation rate add up to less than 100%\n";
				exit(1);
			}
		
			for(int x = 0; x < islands.at(i).size(); x++){
				genoToPheno(islands.at(i).at(x).g_,name);
				int avg_fitness = 0;
			
				for(int n = 0; n < FITNESS_TRIALS; ++n) {
				  avg_fitness += fitness(name,author,false,BENCH);
				}
			//	h.at(i).fitness_ = avg_fitness / FITNESS_TRIALS;
				islands.at(i).at(x).fitness_ = avg_fitness;
			}
			
			if(selection_type == 0) {
				topHalfSelection(islands.at(i));
			} else if (selection_type == 1) {
				rouletteSelection(islands.at(i));
			} else if (selection_type == 2) {
				tournmentSelection(islands.at(i), TOURNAMENT_SIZE);
			}
	
			if(!EXIT_ON_TOLERANCE && MAX_GENERATION == current_generation) {
				break;
			}
		}

		++current_generation;
	}

	for(int i = 0; i < islands.size(); ++i) {
		sortHerd(islands.at(i));
	
		cout << "Printing final populations fitness:" << endl;
		for(int x = 0; x < islands.at(i).size(); x++){
		  cout << islands.at(i).at(x).fitness_ << ", ";
		}
		cout << endl;
		
		war_s best_warrior = islands.at(i).at(POPULATION_SIZE-1);
		for(int i = 1; i < islands.size(); ++i) {
			if(best_warrior < islands.at(i).at(POPULATION_SIZE-1)) {
				best_warrior = islands.at(i).at(POPULATION_SIZE-1);
			}
		}

		genoToPheno(best_warrior.g_ ,name);
	}
}

int main() {
	runGA(crossover_rate, mutation_rate);
}
