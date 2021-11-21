#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "TrueField.h"

using namespace std;

void TrueField::GenField()
{
	GenMines();

	for (int i = 0; i < trows; i++)
	{
		for (int j = 0; j < tcols; j++)
		{
			if (tField[i][j] != '*')
			{
				tField[i][j]=GenNeighbours(i, j)+ '0';
			}
		}
	}
}

void TrueField::GenMines()
{
	srand(time(NULL));
	vector <pair<int, int>> MineCoords;

	for (int i = 0; i < trows; i++)
	{
		for (int j = 0; j < tcols; j++)
		{
			MineCoords.push_back(make_pair(i, j));
		}
	}

	random_shuffle(MineCoords.begin(), MineCoords.end());

	for (int i = 0; i < tmines; i++)
	{
		tField[MineCoords[i].first][MineCoords[i].second] = '*';
	}
}

int TrueField::GenNeighbours(int rows, int cols)
{
	int neighbours = 0;
	for (int OffsetRow = -1; OffsetRow <= 1; OffsetRow++)
	{
		for (int OffsetCol = -1; OffsetCol <= 1; OffsetCol++)
		{
			int NextRow = rows + OffsetRow;
			int NextCol = cols + OffsetCol;
			if (CheckIfInside(NextRow, NextCol) && tField[NextRow][NextCol]  == '*')
			{
				neighbours++;
			}
		}
	}
	return neighbours;

}

bool TrueField::CheckIfInside(int row, int col)
{
	if (0 <= row && row < trows && 0 <= col && col < tcols)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void TrueField::PrintField()
{
	GenField();
	for (int i = 0; i < trows; i++)
	{
		for (int j = 0; j < tcols; j++)
		{
			cout << tField[i][j] <<"  ";
			if (j == tcols-1)
			{
				cout << "\n";
			}
		}
	}
}