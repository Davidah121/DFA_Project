#pragma once
#include <vector>

struct Transition
{
	char input;
	void* output;
};


class State
{
public:
	State(std::string);
	~State();
	std::string getName();
	void setName(std::string);
	bool isAcceptState();
	void setAcceptState(bool);
	void addTransition(Transition);
	Transition getTransition(int index);
	int getAmountOfTransitions();

private:
	bool acceptState = false;
	bool finalState = false;
	std::string name;
	std::vector<Transition> trans = std::vector<Transition>();
	


};

