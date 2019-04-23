#include "State.h"


State::State(std::string name)
{
	this->name = name;
}

std::string State::getName()
{
	return name;
}

void State::setName(std::string name)
{
	this->name = name;
}

bool State::isAcceptState()
{
	return acceptState;
}

void State::setAcceptState(bool acceptState)
{
	this->acceptState = acceptState;
}

void State::addTransition(Transition trans)
{
	this->trans.push_back(trans);
}

Transition State::getTransition(int index)
{
	return trans[index];
}

int State::getAmountOfTransitions()
{
	return trans.size();
}



State::~State()
{
}

