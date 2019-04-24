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
		startIndex = vectorBoi[0].find('{', 0)+1;
		endIndex = vectorBoi[0].find('}', 0);
		string stringBoi = vectorBoi[0].substr(startIndex, endIndex - startIndex);
		inputs = stringTools::splitString(stringBoi, ',');

		startIndex = vectorBoi[1].find('{', 0)+1;
		endIndex = vectorBoi[1].find('}', 0);
		stringBoi = vectorBoi[1].substr(startIndex, endIndex - startIndex);
		std::vector<string> states = stringTools::splitString(stringBoi, ',');

		startIndex = vectorBoi[3].find('{', 0)+1;
		endIndex = vectorBoi[3].find('}', 0);
		stringBoi = vectorBoi[3].substr(startIndex, endIndex - startIndex);
		std::vector<string> endState = stringTools::splitString(stringBoi, ',');

		for (int i = 0; i < states.size(); i++)
		{
			State m = State(states[i]);
			
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
			dfaStates.push_back(m);
		}
		
		for (int i = 4; i < vectorBoi.size(); i++)
		{
			int commaLocation = vectorBoi[i].find(',', 0);
			string stateName = vectorBoi[i].substr(1, commaLocation - 1);

			
			
			int parenthLocation = vectorBoi[i].find(')', commaLocation);
			string input = vectorBoi[i].substr(commaLocation+1, parenthLocation - commaLocation-1);

			int arrowLocation;
			string toStateName;

			if (i < vectorBoi.size()-1)
			{
				arrowLocation = vectorBoi[i].find("->", 0) + 2;
				toStateName = vectorBoi[i].substr(arrowLocation, vectorBoi[i].size() - arrowLocation);
			}
			else
			{
				arrowLocation = vectorBoi[i].find("->", 0) + 2;
				toStateName = vectorBoi[i].substr(arrowLocation, vectorBoi[i].size() - arrowLocation-1);
			}

			//Process next thing
			//Format
			//(state,input)->state
			State *firstState = nullptr;
			State *secondState = nullptr;

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
			
			if (firstState != nullptr)
			{
				firstState->addTransition(Transition{ input[0], (void*)secondState });
			}
		}

	}
	errorChecking();
	
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

bool DFA::processString(std::string c)
{
	State *currentState = &dfaStates[startStateIndex];

	bool invalidString = false;
	for (int i = 0; i < c.size(); i++)
	{
		char currentChar = c[i];
		State *next=nullptr;
		for (int j = 0; j < currentState->getAmountOfTransitions(); j++)
		{
			Transition transition = currentState->getTransition(j);			
			if (transition.input == currentChar)
			{
				next = (State*)transition.output;
			}
		}

		if (next == nullptr)
		{
			std::cout << "Invalid String" << std::endl;
			invalidString = true;
			break;
		}
		currentState = next;
	}

	if (invalidString == false)
	{
		if (currentState->isAcceptState())
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void DFA::errorChecking()
{
	int shouldHaveInputs = inputs.size();
	bool hasStart = false;
	bool hasEnd = false;

	validDFA = true;

	if (shouldHaveInputs == 0)
	{
		validDFA = false;
		std::cout << "INPUTS" << std::endl;
	}
	if (startStateIndex == -1)
	{
		validDFA = false;
		std::cout << "START" << std::endl;
	}

	for (int i = 0; i < dfaStates.size(); i++)
	{
		if (dfaStates[i].isAcceptState())
		{
			hasEnd = true;
		}

		if (dfaStates[i].getAmountOfTransitions() != shouldHaveInputs)
		{
			//Invalid DFA
			std::cout << "NOT ENOUGH TRANSITIONS ON " << i << std::endl;
			validDFA = false;
			break;
		}

		for (int j = 0; j < dfaStates[i].getAmountOfTransitions(); j++)
		{
			if (dfaStates[i].getTransition(j).output == nullptr)
			{
				std::cout << "Invalid transition at " << i << "," << j << std::endl;
				validDFA = false;
				break;
			}
		}

		if (validDFA == false)
		{
			break;
		}
	}

	if (hasEnd == false)
	{
		validDFA = false;
		std::cout << "NO END" << std::endl;
	}
	if (validDFA == false)
	{
		MessageBox(NULL, "This DFA is invalid.", "ERROR", MB_ICONERROR);
	}
}

void DFA::drawDFA()
{
	if (validDFA == true)
	{
		double dirChange = 360.0 / dfaStates.size();

		for (int i = 0; i < dfaStates.size(); i++)
		{
			int x = 128 - MathExt::cos(MathExt::toRadians(dirChange * i)) * 128;
			int y = 128 - MathExt::sin(MathExt::toRadians(dirChange * i)) * 128;

			for (int j = 0; j < dfaStates[i].getAmountOfTransitions(); j++)
			{
				State* tempState = (State*)dfaStates[i].getTransition(j).output;
				int index = -1;

				for (int k = 0; k < dfaStates.size(); k++)
				{
					if (tempState->getName() == dfaStates[k].getName())
					{
						index = k;
						break;
					}
				}

				int x2 = 128 - MathExt::cos(MathExt::toRadians(dirChange * index)) * 128;
				int y2 = 128 - MathExt::sin(MathExt::toRadians(dirChange * index)) * 128;

				float midX = (x + x2) / 2;
				float midY = (y + y2) / 2;

				if (i==index)
				{
					//same point, do loop.
					x = 128 - MathExt::cos(MathExt::toRadians(dirChange * i + 8)) * 128;
					y = 128 - MathExt::sin(MathExt::toRadians(dirChange * i + 8)) * 128;

					x2 = 128 - MathExt::cos(MathExt::toRadians(dirChange * i - 8)) * 128;
					y2 = 128 - MathExt::sin(MathExt::toRadians(dirChange * i - 8)) * 128;
					
					midX = 128 - MathExt::cos(MathExt::toRadians(dirChange * i)) * 224;
					midY = 128 - MathExt::sin(MathExt::toRadians(dirChange * i)) * 224;
				}

				float yChange = y2 - y;
				float xChange = x2 - x;

				bool incr = true;
				if (xChange > 0)
				{
					midY += 16;
					incr = true;
				}
				else if(xChange<0)
				{
					midY -= 16;
					incr = false;
				}

				if (yChange > 0)
				{
					midX -= 16;
					incr = true;
				}
				else if(yChange<0)
				{
					midX += 16;
					incr = false;
				}

				BezierCurve temp = BezierCurve();

				temp.addPoint(Vec2f(160 + x, 120 + y));
				temp.addPoint(Vec2f(160 + midX, 120 + midY));
				temp.addPoint(Vec2f(160 + x2, 120 + y2));

				Renderer::setDrawColor(Color{ 255, 255, 255 });
				Renderer::drawBezierCurve(temp);

				Vec2f midOfCurve = temp.evaluate(0.5);

				if (xChange > 0)
				{
					if (yChange < 0)
					{
						Renderer::setDrawColor({ 255, 255, 255 });
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x - 16, (int)midOfCurve.y);
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x, (int)midOfCurve.y + 16);

						Renderer::setDrawColor({ 0, 0, 0 });
						int y2v = 0;
						for (int k = 0; k < dfaStates[i].getAmountOfTransitions(); k++)
						{
							if (tempState == (State*)dfaStates[i].getTransition(k).output)
							{
								std::string text = "";
								text += dfaStates[i].getTransition(k).input;
								Renderer::drawText(text, (int)midOfCurve.x + 12, (int)midOfCurve.y + y2v);
								y2v -= 16;
							}
						}
					}
					else
					{
						Renderer::setDrawColor({ 255, 255, 255 });
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x - 16, (int)midOfCurve.y);
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x, (int)midOfCurve.y - 16);

						Renderer::setDrawColor({ 0, 0, 0 });
						int y2v = -32;
						for (int k = 0; k < dfaStates[i].getAmountOfTransitions(); k++)
						{
							if (tempState == (State*)dfaStates[i].getTransition(k).output)
							{
								std::string text = "";
								text += dfaStates[i].getTransition(k).input;
								Renderer::drawText(text, (int)midOfCurve.x + 12, (int)midOfCurve.y + y2v);
								y2v += 16;
							}
						}
					}
				}
				else
				{
					if (yChange < 0)
					{
						Renderer::setDrawColor({ 255, 255, 255 });
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x + 16, (int)midOfCurve.y);
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x, (int)midOfCurve.y + 16);

						Renderer::setDrawColor({ 0, 0, 0 });
						int y2v = 0;
						for (int k = 0; k < dfaStates[i].getAmountOfTransitions(); k++)
						{
							if (tempState == (State*)dfaStates[i].getTransition(k).output)
							{
								std::string text = "";
								text += dfaStates[i].getTransition(k).input;
								Renderer::drawText(text, (int)midOfCurve.x - 12, (int)midOfCurve.y + y2v);
								y2v -= 16;
							}
						}
					}
					else
					{
						Renderer::setDrawColor({ 255, 255, 255 });
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x + 16, (int)midOfCurve.y);
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x, (int)midOfCurve.y - 16);

						Renderer::setDrawColor({ 0, 0, 0 });
						int y2v = -32;
						for (int k = 0; k < dfaStates[i].getAmountOfTransitions(); k++)
						{
							if (tempState == (State*)dfaStates[i].getTransition(k).output)
							{
								std::string text = "";
								text += dfaStates[i].getTransition(k).input;
								Renderer::drawText(text, (int)midOfCurve.x - 12, (int)midOfCurve.y + y2v);
								y2v += 16;
							}
						}
					}
				}
			}
			
		}

		for (int i = 0; i<dfaStates.size(); i++)
		{
			int x = 128 - MathExt::cos(MathExt::toRadians(dirChange * i)) * 128;
			int y = 128 - MathExt::sin(MathExt::toRadians(dirChange * i)) * 128;

			Renderer::setDrawColor({ 0,0,0 });
			
			if (dfaStates[i].isAcceptState())
			{
				Renderer::drawCircle(160 + x, 120 + y, 30);

				Renderer::setDrawColor({ 180,180,180 });
				Renderer::drawCircle(160 + x, 120 + y, 28);

				Renderer::setDrawColor({ 0,0,0 });
				Renderer::drawCircle(160 + x, 120 + y, 26);
			}
			else
			{
				Renderer::drawCircle(160 + x, 120 + y, 26);
			}

			Renderer::setDrawColor({ 180,180,180 });
			Renderer::drawCircle(160 + x, 120 + y, 24);
			Renderer::setDrawColor({ 0,0,0 });
			Renderer::drawText(dfaStates[i].getName(), 160 + x - 12, 120 + y - 12);
		}
	}
}

bool DFA::processStringInteractive(std::string input, int indexOfChar)
{
	
	if (validDFA == true)
	{
		State* currentState = &dfaStates[startStateIndex];
		for (int i = 0; i < indexOfChar; i++)
		{
			char currentChar = input[i];
			State* next = nullptr;
			for (int j = 0; j < currentState->getAmountOfTransitions(); j++)
			{
				Transition transition = currentState->getTransition(j);
				if (transition.input == currentChar)
				{
					next = (State*)transition.output;
					break;
				}
			}

			if (next != nullptr)
			{
				currentState = next;
			}
			else
			{
				std::cout << "Invalid Input String" << std::endl;
				return false;
			}
		}

		double dirChange = 360.0 / dfaStates.size();

		for (int i = 0; i < dfaStates.size(); i++)
		{
			int x = 128 - MathExt::cos(MathExt::toRadians(dirChange * i)) * 128;
			int y = 128 - MathExt::sin(MathExt::toRadians(dirChange * i)) * 128;

			for (int j = 0; j < dfaStates[i].getAmountOfTransitions(); j++)
			{
				State* tempState = (State*)dfaStates[i].getTransition(j).output;
				int index = -1;

				for (int k = 0; k < dfaStates.size(); k++)
				{
					if (tempState->getName() == dfaStates[k].getName())
					{
						index = k;
						break;
					}
				}

				int x2 = 128 - MathExt::cos(MathExt::toRadians(dirChange * index)) * 128;
				int y2 = 128 - MathExt::sin(MathExt::toRadians(dirChange * index)) * 128;

				float midX = (x + x2) / 2;
				float midY = (y + y2) / 2;

				if (i == index)
				{
					//same point, do loop.
					x = 128 - MathExt::cos(MathExt::toRadians(dirChange * i + 8)) * 128;
					y = 128 - MathExt::sin(MathExt::toRadians(dirChange * i + 8)) * 128;

					x2 = 128 - MathExt::cos(MathExt::toRadians(dirChange * i - 8)) * 128;
					y2 = 128 - MathExt::sin(MathExt::toRadians(dirChange * i - 8)) * 128;

					midX = 128 - MathExt::cos(MathExt::toRadians(dirChange * i)) * 224;
					midY = 128 - MathExt::sin(MathExt::toRadians(dirChange * i)) * 224;
				}

				float yChange = y2 - y;
				float xChange = x2 - x;

				bool incr = true;
				if (xChange > 0)
				{
					midY += 16;
					incr = true;
				}
				else if (xChange < 0)
				{
					midY -= 16;
					incr = false;
				}

				if (yChange > 0)
				{
					midX -= 16;
					incr = true;
				}
				else if (yChange < 0)
				{
					midX += 16;
					incr = false;
				}

				BezierCurve temp = BezierCurve();

				temp.addPoint(Vec2f(160 + x, 120 + y));
				temp.addPoint(Vec2f(160 + midX, 120 + midY));
				temp.addPoint(Vec2f(160 + x2, 120 + y2));

				Renderer::setDrawColor(Color{ 255, 255, 255 });
				Renderer::drawBezierCurve(temp);

				Vec2f midOfCurve = temp.evaluate(0.5);

				if (xChange > 0)
				{
					if (yChange < 0)
					{
						Renderer::setDrawColor({ 255, 255, 255 });
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x - 16, (int)midOfCurve.y);
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x, (int)midOfCurve.y + 16);

						Renderer::setDrawColor({ 0, 0, 0 });
						int y2v = 0;
						for (int k = 0; k < dfaStates[i].getAmountOfTransitions(); k++)
						{
							if (tempState == (State*)dfaStates[i].getTransition(k).output)
							{
								std::string text = "";
								text += dfaStates[i].getTransition(k).input;
								Renderer::drawText(text, (int)midOfCurve.x + 12, (int)midOfCurve.y + y2v);
								y2v -= 16;
							}
						}
					}
					else
					{
						Renderer::setDrawColor({ 255, 255, 255 });
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x - 16, (int)midOfCurve.y);
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x, (int)midOfCurve.y - 16);

						Renderer::setDrawColor({ 0, 0, 0 });
						int y2v = -32;
						for (int k = 0; k < dfaStates[i].getAmountOfTransitions(); k++)
						{
							if (tempState == (State*)dfaStates[i].getTransition(k).output)
							{
								std::string text = "";
								text += dfaStates[i].getTransition(k).input;
								Renderer::drawText(text, (int)midOfCurve.x + 12, (int)midOfCurve.y + y2v);
								y2v += 16;
							}
						}
					}
				}
				else
				{
					if (yChange < 0)
					{
						Renderer::setDrawColor({ 255, 255, 255 });
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x + 16, (int)midOfCurve.y);
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x, (int)midOfCurve.y + 16);

						Renderer::setDrawColor({ 0, 0, 0 });
						int y2v = 0;
						for (int k = 0; k < dfaStates[i].getAmountOfTransitions(); k++)
						{
							if (tempState == (State*)dfaStates[i].getTransition(k).output)
							{
								std::string text = "";
								text += dfaStates[i].getTransition(k).input;
								Renderer::drawText(text, (int)midOfCurve.x - 12, (int)midOfCurve.y + y2v);
								y2v -= 16;
							}
						}
					}
					else
					{
						Renderer::setDrawColor({ 255, 255, 255 });
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x + 16, (int)midOfCurve.y);
						Renderer::drawLine((int)midOfCurve.x, (int)midOfCurve.y, (int)midOfCurve.x, (int)midOfCurve.y - 16);

						Renderer::setDrawColor({ 0, 0, 0 });
						int y2v = -32;
						for (int k = 0; k < dfaStates[i].getAmountOfTransitions(); k++)
						{
							if (tempState == (State*)dfaStates[i].getTransition(k).output)
							{
								std::string text = "";
								text += dfaStates[i].getTransition(k).input;
								Renderer::drawText(text, (int)midOfCurve.x - 12, (int)midOfCurve.y + y2v);
								y2v += 16;
							}
						}
					}
				}

			}

		}

		for (int i = 0; i < dfaStates.size(); i++)
		{
			int x = 128 - MathExt::cos(MathExt::toRadians(dirChange * i)) * 128;
			int y = 128 - MathExt::sin(MathExt::toRadians(dirChange * i)) * 128;

			Renderer::setDrawColor({ 0,0,0 });

			if (dfaStates[i].isAcceptState())
			{
				Renderer::drawCircle(160 + x, 120 + y, 30);

				Renderer::setDrawColor({ 180,180,180 });
				Renderer::drawCircle(160 + x, 120 + y, 28);

				Renderer::setDrawColor({ 0,0,0 });
				Renderer::drawCircle(160 + x, 120 + y, 26);
			}
			else
			{
				Renderer::drawCircle(160 + x, 120 + y, 26);
			}

			if (&dfaStates[i] == currentState)
			{
				if (indexOfChar == input.size())
				{
					if (dfaStates[i].isAcceptState())
					{
						Renderer::setDrawColor({ 0,255,0 });
					}
					else
					{
						Renderer::setDrawColor({ 0,0,255 });
					}
				}
				else
				{
					Renderer::setDrawColor({ 120,255,255 });
				}
			}
			else
			{
				Renderer::setDrawColor({ 180,180,180 });
			}
			
			Renderer::drawCircle(160 + x, 120 + y, 24);
			Renderer::setDrawColor({ 0,0,0 });
			Renderer::drawText(dfaStates[i].getName(), 160 + x - 12, 120 + y - 12);
		}

		return true;
	}

	return false;
}

void DFA::debugStuff()
{
	if (validDFA)
	{
		std::cout << "Start State: " << dfaStates[startStateIndex].getName() << std::endl;

		std::cout << "____INPUT____" << std::endl;
		for (int i = 0; i < inputs.size(); i++)
		{
			
			std::cout << inputs[i] << ",";
		}
		std::cout << std::endl;
		for (int i = 0; i < dfaStates.size(); i++)
		{
			std::cout << "____STATE____" << std::endl;
			std::cout << dfaStates[i].getName() << std::endl;
			std::cout << "IS accept: " << dfaStates[i].isAcceptState() << std::endl;

			std::cout << "Transtions" << std::endl;
			for (int j = 0; j < dfaStates[i].getAmountOfTransitions(); j++)
			{
				std::cout << "input: " << dfaStates[i].getTransition(j).input << std::endl;
				if (dfaStates[i].getTransition(j).output != nullptr)
				{
					std::cout << "to state: " << ((State*)dfaStates[i].getTransition(j).output)->getName() << std::endl;
				}
			}
		}
		
	}
	

}