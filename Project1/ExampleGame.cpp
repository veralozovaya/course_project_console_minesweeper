#include "ExampleGame.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;


void Fields::GenField()
{
	GenMines();

	for (int i = 0; i < trows; i++)
	{
		for (int j = 0; j < tcols; j++)
		{
			if (tField[i][j] != '*')
			{
				tField[i][j] = GenNeighbours(i, j) + '0';
			}
		}
	}
}

void Fields::GenMines()
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

int Fields::GenNeighbours(int rows, int cols)
{
	int neighbours = 0;
	for (int OffsetRow = -1; OffsetRow <= 1; OffsetRow++)
	{
		for (int OffsetCol = -1; OffsetCol <= 1; OffsetCol++)
		{
			int NextRow = rows + OffsetRow;
			int NextCol = cols + OffsetCol;
			if (CheckIfInside(NextRow, NextCol) && tField[NextRow][NextCol] == '*')
			{
				neighbours++;
			}
		}
	}
	return neighbours;
}

bool Fields::CheckIfInside(int row, int col)
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


void Fields::uGenField()
{
	GenField();
	for (int i = 0; i < urows; i++)
	{
		for (int j = 0; j < ucols; j++)
		{
			uField[i][j] = '+';
		}
	}
	uPrintField(UserPos);
}

void Fields::uPrintField(int userpos[2])
{
	uField[userpos[0]][userpos[1]] = '$';
	for (int i = 0; i < urows; i++)
	{
		for (int j = 0; j < ucols; j++)
		{
			cout << uField[i][j] << "  ";
			if (j == ucols-1)
			{
				cout << "\n";
			}
			
		}
	}
}

void Fields::OpenBox(int row, int col)
{
	if (tField[row][col] != '*')
	{
		uField[row][col] = tField[row][col];
	}
	else
	{
		EndGame();
	}
	
}

void Fields::FlagBox(int row, int col)
{
	uField[row][col] = 'f';
}

bool Fields::EndGame()
{
	return 0;
}

ExampleGame::ExampleGame() {
	Fields game;

	game.uGenField();

	track_key(VK_SPACE); //открыть
	track_key(VK_LEFT);
	track_key(VK_RIGHT);
	track_key(VK_UP);
	track_key(VK_DOWN);
	track_key(0x46); //флаг


}

void ExampleGame::on_button_press(const int button) {

	switch (button)
	{
	case VK_LEFT:
	{
		system("cls");
		user_col++;
		uPrintField(UserPos);
	}

	case VK_RIGHT:
	{
		system("cls");
		user_col--;
		uPrintField(UserPos);

	}
	case VK_UP:
	{
		system("cls");
		user_col--;
		uPrintField(UserPos);

	}

	case VK_DOWN:
	{
		system("cls");
		user_row++;
		uPrintField(UserPos);

	}
	case VK_SPACE:
	{
		system("cls");
		OpenBox(user_row, user_col);
		uPrintField(UserPos);

	}

	case 0x46:
	{
		system("cls");
		FlagBox(user_row, user_col);
		uPrintField(UserPos);
	}
	default:
		break;
	}
}
void ExampleGame::track_key(const int key) {
	m_TrackedKeys.insert(key);
}

void ExampleGame::untrack_key(const int key) {
	const std::set<int>::const_iterator keyItr = m_TrackedKeys.find(key);
	if (keyItr != m_TrackedKeys.end())
	{
		m_TrackedKeys.erase(keyItr);
	}
}