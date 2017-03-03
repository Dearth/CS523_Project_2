#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "herd.h"
using namespace std;
const string author="God";
const string name="Neo.RED";
const double tolerance = 0.01;

int crossover_type = 0; //0 = no crossover, 1 = single point, 2 = uniform
int selection_type = 0; //0 = topHalf, 1 = roulette, 2 = tournment

int add_gene = 20;
int swap_gene = 20;
int del_gene = 20;
int ins_gene = 20;
int change_gene = 20;

int mutate_ins = 33;
int mutate mode = 33;
int mutate_addr = 34;

void genoToPheno(genome* _genome,String name){

	ofstream outfile (name);
	
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

int fitness(string file,string author,bool output){

	FILE *in;
	char buff[512];
	string cmd="./pmars -r 100 ../WilkiesBench/NOBODY.RED "+file;
	author+=" scores";
	//cout<<author;
	if(!(in = popen(cmd.c_str(), "r"))){
		return -1;
	}
	char* results;
	char* point;
	string::size_type sz;
	while(fgets(buff, sizeof(buff), in)!=NULL){
	  if(output) printf("%s",buff);
	  if(point=strstr(buff,author.c_str())){
	    strncpy(buff,point+author.length()+1,10);
	    return stoi(buff,&sz);
	    
	  }
	}

	pclose(in);

	return 0;
}

bool diverse(herd h){
	int sum=0;
	for(int i=0;i<h.size();i++){
		sum+=h.at(i).fittness_;
	}
	sum/=h.size();
	if(sum==0) {
		return true;
	}

	for(int i=0;i<h.size();i++){
		x=h.at(i).fittness/sum;
		double upper_bound = 1.0 + tolerance;
		double lower_bound = 1.0 - tolerance

		if(!(x>=lower_bound*sum && x<=upper_bound*sum)) {
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
		} else if (event <= mutation_rate + crossover_rate) {
			mutateHerd(h, add_gene, swap_gene, del_gene, ins_gene, change_gene, mutate_ins, mutate_mode, mutate_addr);
		} else {
			cerr << "Crossover rate and mutation rate add up to less than 100%\n";
			exit(1);
		}
	
		for(int i=0;i<h.size();i++){
		  genoToPheno(h.at(i).g_,name);
		  h.at(i).fittness_=fittness(name,author,false);
		}
		
		if(selection_type == 0) {
			topHalfSelection(h);
		} else if (selection_type == 1) {
			rouletteSelection(h);
		} else if (selection_type == 2) {
			tournmentSelection(h);
		}
	}
	sortHerd(h);
	genoToPheno(h.at(h.size-1),name);
}

int main() {
	//srand (time(NULL));
	genome* _genome = initGenome();
	_genome->push_back(createNewGene());
	_genome->push_back(createNewGene());
	_genome->push_back(createNewGene());
	_genome->push_back(createNewGene());
	genoToPheno(_genome);

	printf("%d\n",fitness(name,author,false));
}
