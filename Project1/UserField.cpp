#include "UserField.h"
#include "TrueField.h"

using namespace std;

void UserField::GenField()
{
	for (int i = 0; i < urows; i++)
	{
		for (int j = 0; j < ucols; j++)
		{
			uField[i][j] = '+';
		}
	}
}

void UserField::PrintField()
{
	for (int i = 0; i < urows; i++)
	{
		for (int j = 0; j < ucols; j++)
		{
			cout<<uField[i][j]<<"  ";
			if (j == ucols)
			{
				cout << "\n";
			}
		}
	}
}

void UserField::OpenBox()
{
	
}
