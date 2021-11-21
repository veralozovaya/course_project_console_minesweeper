#pragma once

#include <iostream>
#include "TrueField.h"

using namespace std;

class UserField
{
public:
	int urows = 9, ucols = 9, umines = 10;
	char uField[9][9];

	void GenField();
	void PrintField();
	void OpenBox();
	void FlagBox();
};