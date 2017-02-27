#ifndef _CODEWARS_H_
#define _CODEWARS_H_

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
