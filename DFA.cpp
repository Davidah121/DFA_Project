#include "DFA.h"
DFA::DFA(char* fileName)
{
	quickIO quickBoi = quickIO(fileName, quickIO::READ);
	if (quickBoi.isOpen())
	{
		std::vector<const char*> vectorBoi = quickBoi.readFullFile();
		quickBoi.close();
	}
}


DFA::~DFA()
{
}

void DFA::addState(State state)
{
	dfaStates.push_back(state);
}

State DFA::getState(int index)
{
	return dfaStates[index];
}

bool DFA::processString(char *)
{
	return false;
}
