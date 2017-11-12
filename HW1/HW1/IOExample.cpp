#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


class BattleBoard
{
public:
	string boardName;
	string playerName;
	int R;
	int C;
	string* matrix;

	BattleBoard() : matrix(NULL) {}
	~BattleBoard()
	{
		if (matrix != NULL)
		{
			delete[] matrix;
		}
	}
};

void createSimple()
{

	cout << "Creating file: simpleBattleBoard.txt" << endl;
	ofstream fout("simpleBattleBoard.txt");
	fout << "simpleBattleBoard" << endl;
	fout << "Nathanel" << endl;
	fout << 10 << endl;
	fout << 10 << endl;
	fout << "___XXX____" << endl;
	fout << "X______XX_" << endl;
	fout << "X____X____" << endl;
	fout << "X_________" << endl;
	fout << "X___X____X" << endl;
	fout << "__________" << endl;
	fout << "____X____X" << endl;
	fout << "X___X_____" << endl;
	fout << "X_________" << endl;
	fout << "X______XX_" << endl;
	fout.close();
}

void input(BattleBoard& battleBoard)
{
	cout << "Reading battleBoard from file: simpleBattleBoard.txt into class BattleBoard" << endl;
	ifstream fin("simpleBattleBoard.txt");
	getline(fin, battleBoard.boardName);
	std::getline(fin, battleBoard.playerName);
	fin >> battleBoard.R;
	fin >> battleBoard.C;
	fin.ignore(); //skip newline and go the begining of matrix
	battleBoard.matrix = new string[battleBoard.R];
	for (int i = 0; i < battleBoard.R; ++i)
	{
		std::getline(fin, battleBoard.matrix[i]);
	}
}

void output(const BattleBoard& battleBoard)
{
	cout << "Printing battleBoard from instance into standard output" << endl;
	cout << "Board name: " << battleBoard.boardName << endl;
	cout << "Player name: " << battleBoard.playerName << endl;
	for (int i = 0; i < battleBoard.R; ++i)
	{
		for (int j = 0; j < battleBoard.C; ++j)
		{
			cout << battleBoard.matrix[i][j];
		}
		cout << endl;
	}
}

int main()
{
	BattleBoard battleBoard;
	createSimple();
	input(battleBoard);
	output(battleBoard);
	return 0;
}
