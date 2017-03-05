#ifndef _CODEWARS_H_
#define _CODEWARS_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const bool DEBUG = true;

const int MAX_CODEWARS_INSTRUCTION = 19;
const int MAX_ARGUMENT_MOD = 8;
const int MAX_MEMORY = 8000;

const int POPULATION_SIZE = 100;

const string author="God";
const string name="Neo.RED";
const double tolerance = 0.01;

const int ELITE_SIZE=10;

int crossover_rate = 50;
int mutation_rate = 50;

int crossover_type = 2; //0 = no crossover, 1 = single point, 2 = uniform
int selection_type = 1; //0 = topHalf, 1 = roulette, 2 = tournment
const int TOURNAMENT_SIZE = 2;

int add_gene = 3;
int swap_gene = 23;
int del_gene = 6;
int ins_gene = 3;
int change_gene = 65;

int mutate_ins = 33;
int mutate_mode = 33;
int mutate_addr = 34;

const std::string instructions[]={"DAT","MOV","ADD","SUB","MUL","DIV","MOD","JMP","JMZ","JMN","DJN","SPL","CMP","SEQ","SNE","SLT","LDP","STP","NOP"};

enum Instructions {
	DAT = 0,
	MOV,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	JMP,
	JMZ,
	JMN,
	DJN,
	SPL,
	CMP,
	SEQ,
	SNE,
	SLT,
	LDP,
	STP,
	NOP
};

const std::string addressMode[]={"", "#","$","@","<","*","{","}"};
typedef enum AddressModes {
	NORMAL = 0,
	IMMEDIATE,
	DIRECT,
	INDIRECT,
	INDIR_PREDEC,
	INDIR_A,
	INDIR_PREDEC_A,
	INDIR_POSDEC_A
} addmode;

#endif
