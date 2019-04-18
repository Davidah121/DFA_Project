#include "DFA.h"
#include "MathExt.h"
#include "Renderer.h"

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