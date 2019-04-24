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

	//returns true if the string is accepted and false if it is rejected.
	bool processString(std::string);

	void errorChecking();

	//returns false if it can not continue.
	bool processStringInteractive(std::string inputString, int indexOfChar);
	void drawDFA();

	void debugStuff();

private:
	bool validDFA = false;
	int startStateIndex = -1;
	std::vector<string> inputs = std::vector<string>();
	std::vector<State> dfaStates = std::vector<State>();
};

