#pragma once
#include <vector>

struct Transition
{
	char input;
	void* output; //Can't have a State*
};

class State
{
public:
	State();
	State(char);
	~State();
	char getName();
	void setName(char);
	bool isFinalState();
	void setFinalState(bool);
	bool isAcceptState();
	void setAcceptState(bool);
	void addTransition(Transition);

private:
	bool acceptState = false;
	bool finalState = false;
	char name;
	std::vector<Transition> trans = std::vector<Transition>();
	
};
