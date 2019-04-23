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

	bool processString(std::string);

	void errorChecking();

	//timeToWait in frames
	void processStringInteractive(char* inputString, int timeToWait);
	void drawDFA();

	void debugStuff();

private:
	bool validDFA;
	int framesWaited = 0;
	int startStateIndex = -1;
	std::vector<string> inputs = std::vector<string>();
	std::vector<State> dfaStates = std::vector<State>();
};

