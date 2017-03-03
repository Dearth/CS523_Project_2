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
using namespace std;

const int MAX_CODEWARS_INSTRUCTION = 20;
const int MAX_ARGUMENT_MOD = 7;
const int MAX_MEMORY = 8000;

const int POPULATION_SIZE = 100;

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

const std::string addressMode[]={"#","$","@","<","*","{","}"};
typedef enum AddressModes {
	IMMEDIATE = 0,
	DIRECT,
	INDIRECT,
	INDIR_PREDEC,
	INDIR_A,
	INDIR_PREDEC_A,
	INDIR_POSDEC_A
} addmode;

#endif
