#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

class TrueField 
{
public:
	int rows = 9, cols = 9, mines=10;
	char tField[9][9];

	void GenField();
	void GenMines();
	int GenNeighbours(int rows, int cols);
	bool CheckIfInside(int row, int col);
	void PrintField();
};


