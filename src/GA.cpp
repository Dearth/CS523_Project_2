#include <iostream>
#include <stdio.h>
#include <string.h>
#include <genome.h>
using namespace std;
int fitness(string file,string author){

	FILE *in;
	char buff[512];
	string cmd="./pmars -r 100 WilkiesBench/CANNON.RED "+file;
	author+=" scores";
	if(!(in = popen(cmd.c_str(), "r"))){
		return -1;
	}
	char* results;
	char* point;
	string::size_type sz;
	while(fgets(buff, sizeof(buff), in)!=NULL){
	  if(point=strstr(buff,author.c_str())){
	    strncpy(buff,point+author.length()+1,10);
	    return stoi(buff,&sz);
	    cout << buff;
	  }
	}

	pclose(in);

	return 0;
}
int main() {
  printf("%d\n",fitness("WilkiesBench/IRONGATE.RED","Wayne Sheppard"));
}
