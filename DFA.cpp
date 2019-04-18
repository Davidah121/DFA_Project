#include "DFA.h"
#include "MathExt.h"
#include "Renderer.h"
#include "stringTools.h"

DFA::DFA(char* fileName)
{
	quickIO quickBoi = quickIO(fileName, quickIO::READ);
	if (quickBoi.isOpen())
	{
		std::vector<string> vectorBoi = quickBoi.readFullFileString();
		quickBoi.close();
		int startIndex = 0;
		int endIndex = 0;
		startIndex = vectorBoi[0].find('{', 0);
		endIndex = vectorBoi[0].find('}', 0);
		string stringBoi = vectorBoi[0].substr(startIndex, endIndex - startIndex);
		inputs = stringTools::splitString(stringBoi, ',');

		startIndex = vectorBoi[1].find('{', 0);
		endIndex = vectorBoi[1].find('}', 0);
		stringBoi = vectorBoi[1].substr(startIndex, endIndex - startIndex);
		std::vector<string> states = stringTools::splitString(stringBoi, ',');

		startIndex = vectorBoi[3].find('{', 0);
		endIndex = vectorBoi[3].find('}', 0);
		stringBoi = vectorBoi[3].substr(startIndex, endIndex - startIndex);
		std::vector<string> endState = stringTools::splitString(stringBoi, ',');

		for (int i = 0; i < states.size(); i++)
		{
			State m = State((char*)states[i].c_str());
			dfaStates.push_back(m);
			if (states[i] == vectorBoi[2])
			{
				startStateIndex = i;				
			}
			for (int j = 0; j < endState.size(); j++)
			{
				if (states[i] == endState[j])
				{
					m.setAcceptState(true);
				}
			}
		}
		
		for (int i = 4; i < vectorBoi.size(); i++)
		{
			int commaLocation = vectorBoi[i].find(',', 0);
			string stateName = vectorBoi[i].substr(1, commaLocation - 1);
			
			int parenthLocation = vectorBoi[i].find(')', commaLocation);
			string input = vectorBoi[i].substr(commaLocation, parenthLocation - commaLocation);

			int arrowLocation = vectorBoi[i].find("->", 0);
			string toStateName = vectorBoi[i].substr(arrowLocation, vectorBoi[i].size() - arrowLocation);
			//Process next thing
			//Format
			//(state,input)->state
			State *firstState;
			State *secondState;
			for (int j = 0; j < dfaStates.size(); j++)
			{
				if (dfaStates[j].getName() == stateName)
				{
					firstState = &dfaStates[j];
				}
				if (dfaStates[j].getName() == toStateName)
				{
					secondState = &dfaStates[j];
				}
			}
			
			firstState->addTransition(Transition{(char*)input.c_str(), (void*)secondState});
		}

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

void DFA::drawDFA()
{
	double dirChange = 360.0 / dfaStates.size();

	for (int i = 0; i < dfaStates.size(); i++)
	{
		int x = 128 + MathExt::cos(MathExt::toRadians(dirChange * i)) * 128;
		int y = 128 + MathExt::sin(MathExt::toRadians(dirChange * i)) * 128;

		Renderer::setDrawColor({ 255,255,255 });
		Renderer::drawCircle(x, y, 16);
		Renderer::setDrawColor({ 0,0,0 });
		Renderer::drawText(dfaStates[i].getName(), x, y);
	}
}