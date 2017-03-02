#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "genome.h"
#include "codewars.h"
using namespace std;
const string author="God";
const string name="Neo.RED";
  
void genoToPheno(genome* _genome){

  ofstream outfile (name);
  
  outfile << ";redcode-94" << std::endl;
  outfile << ";name " << name  << std::endl;
  outfile << ";author " << author  << std::endl;
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
