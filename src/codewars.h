#ifndef _CODEWARS_H_
#define _CODEWARS_H_

const int MAX_CODEWARS_INSTRUCTION = 20;
const int MAX_ARGUMENT_MOD = 7;
const int MAX_MEMORY = 8000;

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
