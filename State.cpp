#include "State.h"

State::State()
{
}

State::State(char name)
{
	this->name = name;
}

char State::getName()
{
	return name;
}

void State::setName(char name)
{
	this->name = name;
}

bool State::isFinalState()
{
	return finalState;
}

void State::setFinalState(bool finalState)
{
	this->finalState = finalState;
}

bool State::isAcceptState()
{
	return false;
}

void State::setAcceptState(bool acceptState)
{
	this->acceptState = acceptState;
}

void State::addTransition(Transition trans)
{
	this->trans.push_back(trans);
}

State::~State()
{
}

