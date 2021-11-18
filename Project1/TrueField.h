#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

class TrueField 
{
public:
	int rows = 9, cols = 9, mines=10, neighbours=0;
	char tField[9][9] = {};


	void GenField();
	void GenMines();
	void GenNeighbours();
	void PrintField();
};
