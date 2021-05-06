#include "Computer.h"

Computer::Computer()
{
}
int Computer::makeMove(morisGame* Board)
{
	return greedy(Board);
}

int Computer::greedy(morisGame* Board)
{
	morisGame* Temp = new morisGame();
	morisGame* Temp2 = new morisGame();
	Temp->setBoard();
	Temp->toBePlacedP1.clear();
	Temp->toBePlacedP2.clear();
	Board->copyBoard(Temp);
	boardSpace* space;
	int depth = 0;
	int bestMove[3] = { 0, 0, 0 };
	int value = 0;

	if (Board->destroyMode == 0)
	{
		if (!Board->isMovingPhase())
		{
			for (int j = 0; j < 24; j++)
			{
				value = 0;
				space = Board->boardSpaces[j];
				if (space->isEmpty())
				{
					if (Temp->isNewMillMade(1))
					{
						//cout << "stuck";
						value += 6;
					}
					if (adj1[j] != -1) {
						//cout << "stuck";
						if (!Temp->boardSpaces[adj1[j]]->isEmpty() && (Temp->boardSpaces[adj1[j]]->isPlayerTwo() || Temp->boardSpaces[adj1[j]]->isPlayerOne()))
						{
							value += 1;
						}
					}
					if (adj2[j] != -1) {

						if (!Temp->boardSpaces[adj2[j]]->isEmpty() && (Temp->boardSpaces[adj2[j]]->isPlayerTwo() || Temp->boardSpaces[adj2[j]]->isPlayerOne()))
						{
							value += 1;
						}
					}
					if (adj3[j] != -1) {
						if (!Temp->boardSpaces[adj3[j]]->isEmpty() && (Temp->boardSpaces[adj3[j]]->isPlayerTwo() || Temp->boardSpaces[adj3[j]]->isPlayerOne()))
						{
							value += 1;
						}
					}
					if (adj4[j] != -1) {

						if (!Temp->boardSpaces[adj4[j]]->isEmpty() && (Temp->boardSpaces[adj3[j]]->isPlayerTwo() || Temp->boardSpaces[adj4[j]]->isPlayerOne()))
						{
							value += 1;
						}
					}
					if (value > bestMove[2])
					{
						bestMove[1] = j;
					}
				}
			}
			return bestMove[1];
		}
		else
		{
			for (int i = 0; i < 24; i++)
			{
				space = Temp->boardSpaces[i];
				if (space->isPlayerTwo() && !Temp->boardSpaces[i]->isEmpty())
				{
					for (int j = 0; j < 24; j++)
					{
						value = 0;
						Temp->selected = i;
						if (Board->activePlayer2.size() < 4 && Temp->boardSpaces[j]->isEmpty())
						{
							Temp->moveSelectedToPos(j);
							Temp->moveSelectedToPos(j);
							if (Temp->isNewMillMade(1))
							{
								//cout << "stuck";
								value += 6;
							}
							if (adj1[j] != -1) {
								//cout << "stuck";
								if (!Temp->boardSpaces[adj1[j]]->isEmpty() && Temp->boardSpaces[adj1[j]]->isPlayerTwo())
								{
									value += 1;
								}
							}
							if (adj2[j] != -1) {

								if (!Temp->boardSpaces[adj2[j]]->isEmpty() && Temp->boardSpaces[adj2[j]]->isPlayerTwo())
								{
									value += 1;
								}
							}
							if (adj3[j] != -1) {
								if (!Temp->boardSpaces[adj3[j]]->isEmpty() && Temp->boardSpaces[adj3[j]]->isPlayerTwo())
								{
									value += 1;
								}
							}
							if (adj4[j] != -1) {

								if (!Temp->boardSpaces[adj4[j]]->isEmpty() && Temp->boardSpaces[adj3[j]]->isPlayerTwo())
								{
									value += 1;
								}
							}
							if (Temp->isMillBroken(1))
							{
								value += 1;
							}
							Temp->selected = j;
							Temp->moveSelectedToPos(i);
							Temp->isMillBroken(1);
							if (value > bestMove[2])
							{
								bestMove[0] = i;
								bestMove[1] = j;
								bestMove[2] = value;
							}
						}
						else if (Temp->isAdjacentToSelected(j) && Temp->boardSpaces[j]->isEmpty() && !Temp->boardSpaces[j]->isPlayerTwo() && !Temp->boardSpaces[j]->isPlayerOne())
						{
							
							Temp->moveSelectedToPos(j);
							if (Temp->isNewMillMade(1))
							{
								//cout << "stuck";
								value += 6;
							}
							if (adj1[j] != -1) {
								//cout << "stuck";
								if (!Board->boardSpaces[adj1[j]]->isEmpty() && Board->boardSpaces[adj1[j]]->isPlayerTwo())
								{
									value += 1;
								}
							}
							if (adj2[j] != -1) {

								if (!Board->boardSpaces[adj2[j]]->isEmpty() && Board->boardSpaces[adj2[j]]->isPlayerTwo())
								{
									value += 1;
								}
							}
							if (adj3[j] != -1) {
								if (!Board->boardSpaces[adj3[j]]->isEmpty() && Board->boardSpaces[adj3[j]]->isPlayerTwo())
								{
									value += 1;
								}
							}
							if (adj4[j] != -1) {

								if (!Board->boardSpaces[adj4[j]]->isEmpty() && Board->boardSpaces[adj3[j]]->isPlayerTwo())
								{
									value += 1;
								}
							}
							if (Temp->isMillBroken(1))
							{
								value += 1;
							}
							Temp->selected = j;
							Temp->moveSelectedToPos(i);
							Temp->isMillBroken(1);
							if (value > bestMove[2])
							{
								bestMove[0] = i;
								bestMove[1] = j;
								bestMove[2] = value;
							}
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
			if (!space->isEmpty() && space->isPlayerOne() && (!Board->isInP1MillArr(i) || Board->allActiveP1InMill()))
			{
				return i;
			}
		}
	}

	//cout << endl <<bestMove[0] << " " << bestMove[1] << endl;
	Board->selected = bestMove[0];
	return bestMove[1];
}
