#ifndef _CODEWARS_H_
#define _CODEWARS_H_

#include <iomanip>
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

bool DEBUG = false;
const bool EXIT_ON_TOLERANCE = false;

const int NUMBER_OF_ISLANDS = 1;
const int MAX_GENERATION = 100;
const int FITNESS_TRIALS = 20;
const int MAX_CODEWARS_INSTRUCTION = 19;
const int MAX_ARGUMENT_MOD = 8;
const int MAX_MEMORY = 8000;

const int POPULATION_SIZE = 50;
const int ELITE_SIZE=10;

const string author="God";
const string name="Neo.RED";

const double tolerance = 0.01;


int crossover_rate = 50;
int mutation_rate = 50;

int crossover_type = 0; //0 = no crossover, 1 = single point, 2 = uniform
int selection_type = 0; //0 = topHalf, 1 = roulette, 2 = tournment
const int TOURNAMENT_SIZE = 3;

int add_gene = 6;
int swap_gene = 30;
int del_gene = 1;
int ins_gene = 3;
int change_gene = 60;

int mutate_ins = 50;
int mutate_mode = 15;
int mutate_addr = 35;

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

const std::string wilkiesBench[]={"BLUEFUNK.RED","CANNON.RED","FSTORM.RED","IRONGATE.RED","MARCIA13.RED","NOBODY.RED","PAPERONE.RED","PSWING.RED","THERMITE.RED","TIME.RED","TORNADO.RED"};
typedef enum WilkiesBench{
  BLUEFUNK =0,
  CANNON,
  FSTORM,
  IRONGATE,
  MARCIA13,
  NOBODY,
  PAPERONE,
  PSWING,
  THERMITE,
  TIME,
  TORNADO
} wilkies;
#endif
