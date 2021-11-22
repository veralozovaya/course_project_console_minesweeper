#include "ExampleGame.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <chrono>

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

	for (int i = 0; i < trows; i++)
	{
		for (int j = 0; j < tcols; j++)
		{
			cout << tField[i][j] << "  ";
			if (j == ucols - 1)
			{
				cout << "\n";
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

void Fields::FieldPrint()
{
	for (int i = 0; i < urows; i++)
	{
		for (int j = 0; j < ucols; j++)
		{
			
				uField[i][j] = '+';

		}
	}
	for (int i = 0; i < urows; i++)
	{
		for (int j = 0; j < ucols; j++)
		{
			for (int k = 0; k < FlagCoords.size(); k++)
			{
				if (i == FlagCoords[k].first && j == FlagCoords[k].second)
				{
					uField[i][j] = 'f';
				}
			}

		}
		uField[user_row][user_col] = '$';

	}

	/*for (int i = 0; i < urows; i++)
	{
		for (int j = 0; j < ucols; j++)
		{
			for (int k = 0; k < FlagCoords.size(); k++)
			{
				if (i == BoxCoords[k].first && j == BoxCoords[k].second)
				{
					uField[i][j] = tField[i][j];
				}
			}

		}
	}*/

	for (int i = 0; i < urows; i++)
	{
		for (int j = 0; j < ucols; j++)
		{
			cout << uField[i][j] << "  ";
			if (j == ucols - 1)
			{
				cout << "\n";
			}

		}
	}
}

void Fields::OpenBox()
{
	if (count == 0)
	{
		GenField();
		if (tField[user_row][user_col] != '*')
		{
			BoxCoords.push_back(make_pair(user_row, user_col));
			FieldPrint();
		}
		else
		{
			cout << "///////";
		}
		count++;
	}
	else
	{
		if (tField[user_row][user_col] != '*')
		{
			BoxCoords.push_back(make_pair(user_row, user_col));
			FieldPrint();
		}
		else
		{
			cout << "///////";
		}
	}
	
}

void Fields::FlagBox()
{
	FlagCoords.push_back(make_pair(user_row, user_col));
	
}

void Fields::UnFlagBox()
{
	for (int k = 0; k < FlagCoords.size(); k++)
	{
		if (user_row == FlagCoords[k].first && user_col == FlagCoords[k].second)
		{
			FlagCoords.erase(FlagCoords.begin() + k);
		}

	}
	//FlagCoords.pop_back();
}

bool Fields::EndGame()
{
	return 0;
}

ExampleGame::ExampleGame() {
	Fields game;
	//game.GenField();
	game.FieldPrint();
	
	track_key(VK_SPACE); //открыть
	track_key(VK_LEFT);
	track_key(VK_RIGHT);
	track_key(VK_UP);
	track_key(VK_DOWN);
	track_key(0x46); //флаг
	track_key(0x44); //снять флаг
	GameLoop();
}

void ExampleGame::GameLoop()
{
	while (!EndGame())
	{
		uppdateInput();
	}
}

void ExampleGame::on_button_press(const int button) {

	switch (button)
	{
	case VK_LEFT:
	{
		system("cls");
		user_col--;
		FieldPrint();
		break;
	}

	case VK_RIGHT:
	{
		system("cls");
		user_col++;
		FieldPrint();
		break;

	}
	case VK_UP:
	{
		system("cls");
		user_row--;
		FieldPrint();
		break;

	}

	case VK_DOWN:
	{
		system("cls");
		user_row++;
		FieldPrint();
		break;

	}
	case VK_SPACE:
	{
		system("cls");
		OpenBox();
		break;
	}

	case 0x46:
	{
		system("cls");
		FlagBox();
		//FlagBox();
		FieldPrint();
		break;
	}

	case 0x44:
	{
		system("cls");
		UnFlagBox();
		//UnFlagBox();
		FieldPrint();
		break;
	}
	default:
		break;
	}
}

void ExampleGame::uppdateInput() {
	for (const int& key : m_TrackedKeys) {
		const SHORT keyState = GetKeyState(key);
		const bool isDown = keyState & 0x8000;

		const std::set<int>::const_iterator keyItr = m_PressedKeys.find(key);
		if (isDown && keyItr == m_PressedKeys.end()) {
			m_PressedKeys.insert(key);
			on_button_press(key);
		}
		else if (!isDown && keyItr != m_PressedKeys.end()) {
			m_PressedKeys.erase(keyItr);
		}
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