#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "TrueField.h"

using namespace std;
//user board
void TrueField::GenField()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			tField[i][j] = '+';
		}
	}
}

void TrueField::GenMines()
{
	srand(time(NULL));
	vector <pair<int, int>> MineCoords;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			MineCoords.push_back(make_pair(rows, cols));
		}
	}
	random_shuffle(MineCoords.begin(), MineCoords.end());
	for (int i = 0; i < mines; i++)
	{
		tField[MineCoords[i].first][MineCoords[i].second] = '*';
	}
}

void TrueField::GenNeighbours()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (tField[i][j] != '*')
			{
				for (int m = i - 1; m < i + 1; m++)
				{
					for (int n = j - 1; n < j + 1; n++)
					{
						if (tField[m][n] == '*' && (m != i) && (n != j))
						{
							neighbours++;
						}

					}
				}
				tField[i][j] = neighbours;
			}
		}
	}
}

void TrueField::PrintField()
{
	GenField();
	GenMines();
	GenNeighbours();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << tField[i][j] <<"\t";
		}
	}
}