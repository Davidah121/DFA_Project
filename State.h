#pragma once
#include <vector>

struct Transition
{
	char input;
	State output;
};


class State
{
public:
	State(char);
	~State();
	char getName();
	char setName(char);
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

