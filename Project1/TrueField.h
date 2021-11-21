#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

class TrueField 
{
public:
	int trows = 9, tcols = 9, tmines=10;
	char tField[9][9];

	void GenField();
	void GenMines();
	int GenNeighbours(int rows, int cols);
	bool CheckIfInside(int row, int col);
	void PrintField();
};


