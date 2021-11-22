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
	char tField[9][9] = {};
	int trows = 9, tcols = 9, tmines = 10;
	char uField[9][9] = {};
	int urows = 9, ucols = 9;
	int user_row = 0;
	int user_col = 0;
	int count = 0;
	vector <pair<int, int>> FlagCoords;
	vector <pair<int, int>> BoxCoords;

	void GenField();
	void GenMines();
	int GenNeighbours(int rows, int cols);
	bool CheckIfInside(int row, int col);
	void FlagBox();
	void UnFlagBox();
	void FieldPrint();
	void OpenBox();
	bool EndGame();

};

	
class ExampleGame : public Fields
{
public:
	ExampleGame();
	void GameLoop();

protected:
	void track_key(const int key);
	void untrack_key(const int key);
private:
	virtual void on_button_press(const int button);
	void uppdateInput();
	set<int> m_PressedKeys;
	set<int> m_TrackedKeys;
};
