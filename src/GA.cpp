#include "herd.h"

int fitness(string file,string author,bool output){

	FILE *in;
	char buff[512];
	string cmd="./pmars -r 100 ../WilkiesBench/NOBODY.RED "+file;
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

void runGA(int crossover_rate, int mutation_rate) {
	
	herd h = initHerd();

	while(diverse(h)){
		int event = rand() % 100;
	
		if(event <= crossover_rate) {
			if(crossover_type == 1) {
				singlePointCrossover(h);
			}else if (crossover_type == 2) {
				uniformCrossover(h);
			}

		} else if (event <= (mutation_rate + crossover_rate)) {
			mutateHerd(h, add_gene, swap_gene, del_gene, ins_gene, change_gene, mutate_ins, mutate_mode, mutate_addr);
		} else {
			cerr << "Crossover rate and mutation rate add up to less than 100%\n";
			exit(1);
		}
	
		for(int i=0;i<h.size();i++){
			genoToPheno(h.at(i).g_,name);
			int avg_fitness = 0;
		
			for(int n = 0; n < 10; ++n) {
				avg_fitness += fitness(name,author,false);
			}
			cerr << avg_fitness / 10 << endl;
			h.at(i).fitness_ = avg_fitness / 10;
		}
		
		if(selection_type == 0) {
			topHalfSelection(h);
		} else if (selection_type == 1) {
			rouletteSelection(h);
		} else if (selection_type == 2) {
			tournmentSelection(h, TOURNAMENT_SIZE);
		}
	}
	sortHerd(h);
	genoToPheno(h.at(h.size()-1).g_ ,name);
}

int main() {
	runGA(crossover_rate, mutation_rate);
}
