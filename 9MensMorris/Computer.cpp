#include "Computer.h"

Computer::Computer()
{
	random.seed(time(0));
}
int Computer::makeMove(morisGame* Board)
{
	boardSpace* space;
	if (Board->destroyMode == 0)
	{
		if (!Board->isMovingPhase())
		{
			for (int i = 0; i < 24; i++)
			{
				space = Board->boardSpaces[i];
				if (space->isEmpty())
				{
					return i;
				}
			}
		}
		else
		{
			for (int i = 0; i < 24; i++)
			{
				space = Board->boardSpaces[i];
				if (space->isPlayerTwo())
				{
					Board->selected = i;
					for (int j = 0; j < 24; j++)
					{
						if (Board->isAdjacentToSelected(j) && Board->boardSpaces[j]->isEmpty())
						{
							return j;
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 24; i++)
		{
			space = Board->boardSpaces[i];
			if (!space->isEmpty() && space->isPlayerOne() && !Board->isInP1MillArr(i))
			{
				return i;
			}
		}
	}
}