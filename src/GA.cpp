#include "herd.h"

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
	ofstream outfile;
	ofstream best_war;
	ofstream bester_war;

	best_war.open("Best_war.RED");
	if(best_war.fail()){
		cerr << "Error opening best file" << endl;
		exit(1);
	}
	
	bester_war.open("Bester_war.RED");
	if(bester_war.fail()){
		cerr << "Error opening bester file" << endl;
		exit(1);
	}

	//logging expiermental data
	if(DEBUG) {
		outfile.open("fitness_over_time.csv");
		if(outfile.fail()){
			cerr << "Error opening fitness log" << endl;
			exit(1);
		}
	}

	for(int i = 0; i < NUMBER_OF_ISLANDS; ++i) {
		herd h = initHerd();
		islands.push_back(h);
	}

	int current_generation = 1;

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
				
				for(int n = 0; n < 11; ++n) {
				  avg_fitness += fitness(name,author,false,static_cast<wilkies>(n));
				}
				islands.at(i).at(x).fitness_ = avg_fitness;
			}
		
			if(DEBUG){ 
				sortHerd(islands.at(i));
				cerr << wilkiesBench[i] << ": ";
				for(int j = 0; j < islands.at(i).size(); ++j) {
					cerr << islands.at(i).at(j).fitness_ << ", ";
					outfile << islands.at(i).at(j).fitness_ << ", ";
				}
				outfile << endl;
				cerr << endl;
			}
		
			auto best_warr = islands[0].end()-1;
			auto bester_warr = islands[0].end()-1;
			for(int index = 0; index < islands.size(); ++index) {
				if(best_warr->fitness_ < (islands[index].end()-1)->fitness_) {
					bester_warr = best_warr;
					best_warr = islands[index].end()-1;
				}
			}

			genoToPheno(best_warr->g_, "Best_Neo.RED");
			genoToPheno(bester_warr->g_, "Bester_Neo.RED");
			

			if(selection_type == 0) {
				topHalfSelection(islands.at(i));
			} else if (selection_type == 1) {
				rouletteSelection(islands.at(i));
			} else if (selection_type == 2) {
				tournmentSelection(islands.at(i), TOURNAMENT_SIZE);
			}
		}
		
		if(!EXIT_ON_TOLERANCE && MAX_GENERATION == current_generation) {
			break;
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
	if(DEBUG) {
		outfile.close();
	}
	best_war.close();
	bester_war.close();
}

void usage() {
	cout << "Running the GA without input will default to 50/50 crossover/mutation rate" << endl;
	cout << "Defaults: no crossover, bottom half replacement" << endl << endl;
	cout << fixed;
	cout << setw(20) << left << "-h, --help" << setw(20) << left << "Print usage" << endl;
	cout << setw(20) << left << "-d, --debug" << setw(20) << left << "Turn debugging on" << endl;
	cout << setw(20) << left << "-cr [value]" << setw(20) << left << "Crossover Rate" << endl;
	cout << setw(20) << left << "-mr [value]" << setw(20) << left << "Mutation Rate" << endl;
	cout << setw(20) << left << "-ct [0-2]" << setw(20) << left << "Crossover Type" << endl;
	cout << setw(20) << left << "" << setw(20) << left << "	0 = No crossover" << endl;
	cout << setw(20) << left << "" << setw(20) << left << "	1 = Single point Crossover" << endl;
	cout << setw(20) << left << "" << setw(20) << left << "	2 = Uniform Crossover" << endl << endl;
	cout << setw(20) << left << "-st [0-2]" << setw(20) << left << "Selection Type" << endl;
	cout << setw(20) << left << "" << setw(20) << left << "	0 = Botton Half Replace" << endl;
	cout << setw(20) << left << "" << setw(20) << left << "	1 = Roullette" << endl;
	cout << setw(20) << left << "" << setw(20) << left << "	2 = Tournament" << endl;

}


int main(int argc, char** argv) {
	for(int i = 1; i < argc; ++i) {
		if(!strncmp(argv[i], "-cr", 3)) {
			crossover_rate = atoi(argv[i+1]);
			++i;
		} else if (!strncmp(argv[i], "-mr", 3)) {
			mutation_rate = atoi(argv[i+1]);
			++i;
		} else if (!strncmp(argv[i], "-ct", 3)) {
			crossover_type = atoi(argv[i+1]);
			if((0 > crossover_type) || (crossover_type > 2)) {
				cout << "Incorrect Crossover Type" << endl;
				usage();
				exit(1);
			}
			++i;
		} else if (!strncmp(argv[i], "-st", 3)) {
			selection_type = atoi(argv[i+1]);
			if((0 > selection_type) || (selection_type > 2)) {
				cout << "Incorrect Selection Type" << endl;
				usage();
				exit(1);
			}
			++i;
		} else if (!strncmp(argv[i], "-h", 2)) {
			usage();
			return 0;
		} else if (!strncmp(argv[i], "--help", 6)) {
			usage();
			return 0;
		} else if (!strncmp(argv[i], "--debug", 7)) {
			DEBUG = true;
		} else if (!strncmp(argv[i], "-d", 2)) {
			DEBUG = true;
		} else {
			cout << "Unknown option" << argv[i] << endl;
			usage();
			exit(1);
		}
	}

	if(100 != (crossover_rate + mutation_rate)) {
		cout << "Mutation and Crossover Rates need to add up to 100" << endl;
		exit(1);
	}

	if(DEBUG) {
		cout << "Crossover Rate: " << crossover_rate << endl;
		cout << "Mutation Rate: " << mutation_rate << endl;
		cout << "Crossover Type: " << crossover_type << endl;
		cout << "Selection Type: " << selection_type << endl;
	}

	runGA(crossover_rate, mutation_rate);

	return 0;
}
