#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "State.h"
#include "quickIO.h"

class DFA
{
public:
	DFA(char* fileName);
	~DFA();

	void addState(State);
	State getState(int);

	bool processString(char*);
private:
	
	std::vector<State> dfaStates = std::vector<State>();
};

