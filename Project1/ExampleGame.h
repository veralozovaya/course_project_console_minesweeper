#pragma once

#include <iostream>
#include <set>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <Windows.h>

using namespace std;

class Fields
{
public:
	int trows = 9, tcols = 9, tmines = 10;
	char tField[9][9] = {};

	void GenField();
	void GenMines();
	int GenNeighbours(int rows, int cols);
	bool CheckIfInside(int row, int col);

	int urows = 9, ucols = 9, umines = 10;
	char uField[9][9] = {};

	void uGenField();
	void uPrintField(int userpos[2]);
	void OpenBox(int row, int col);
	void FlagBox(int row, int col);
	int user_row = 0;
	int user_col = 0;
	int UserPos[2] = { user_row, user_col };
	bool EndGame();
};

	
class ExampleGame : public Fields
{
public:
	ExampleGame();


protected:
	void track_key(const int key);
	void untrack_key(const int key);
private:
	virtual void on_button_press(const int button);
	set<int> m_PressedKeys;
	set<int> m_TrackedKeys;
};
