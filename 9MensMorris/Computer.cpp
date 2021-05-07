#include "Computer.h"

Computer::Computer()
{
}
int Computer::makeMove(morrisGame* Board)
{
	return greedy(Board);
}

int Computer::greedy(morrisGame* Board)
{
	morrisGame* Temp = new morrisGame();
	morrisGame* Temp2 = new morrisGame();
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
					Temp->setBoardPieceP2(j);
					//Temp->turns = Board->turns;
					if (Temp->isNewMillMade(1))
					{
						//// << "stuck";
						value += 10;
					}
					if (adj1[j] != -1) {
						//// << "stuck";
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
					Temp->removePiece(j);
					Temp->isMillBroken(1);
					gameToken* token = new gameToken();
					token->setPlayer(true);
					Temp->toBePlacedP2.push_back(token);

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
							if (Temp->isNewMillMade(1))
							{
								//// << "stuck";
								value += 10;
							}
							if (adj1[j] != -1) {
								//// << "stuck";
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

								if (!Temp->boardSpaces[adj4[j]]->isEmpty() && Temp->boardSpaces[adj4[j]]->isPlayerTwo())
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
						else if (Temp->isAdjacentToSelected(j) && Temp->boardSpaces[j]->isEmpty())
						{
							
							Temp->moveSelectedToPos(j);
							if (Temp->isNewMillMade(1))
							{
								//// << "stuck";
								value += 10;
							}
							if (adj1[j] != -1) {
								//// << "stuck";
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

								if (!Board->boardSpaces[adj4[j]]->isEmpty() && Board->boardSpaces[adj4[j]]->isPlayerTwo())
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
			if (!space->isEmpty() && space->isPlayerOne() && (!Temp->isInP1MillArr(i) || Temp->allActiveP1InMill()))
			{
				value = 1;
				Temp->removePiece(i);
				if (Temp->isMillBroken(Temp->turns % 2))
				{
					//// << "stuck";
					value += 6;
				}
				if (adj1[i] != -1) {
					//// << "stuck";
					if (!Temp->boardSpaces[adj1[i]]->isEmpty() && Temp->boardSpaces[adj1[i]]->isPlayerTwo())
					{
						value += 2;
					}
				}
				if (adj2[i] != -1) {

					if (!Temp->boardSpaces[adj2[i]]->isEmpty() && Temp->boardSpaces[adj2[i]]->isPlayerTwo())
					{
						value += 2;
					}
				}
				if (adj3[i] != -1) {
					if (!Temp->boardSpaces[adj3[i]]->isEmpty() && Temp->boardSpaces[adj3[i]]->isPlayerTwo())
					{
						value += 2;
					}
				}
				if (adj4[i] != -1) {

					if (!Temp->boardSpaces[adj4[i]]->isEmpty() && Temp->boardSpaces[adj4[i]]->isPlayerTwo())
					{
						value += 2;
					}
				}
				Temp->boardSpaces[i]->placedToken = new gameToken();
				Temp->boardSpaces[i]->placedToken->setPlayer(false);
				Temp->activePlayer1.push_back(new gameToken());
				Temp->isNewMillMade(0);
				if (value > bestMove[2])
				{
					bestMove[0] = -1;
					bestMove[1] = i;
					bestMove[2] = value;
				}
			}
		}
	}

	//// << endl <<bestMove[0] << " " << bestMove[1] << endl;
	Board->selected = bestMove[0];
	return bestMove[1];
}
