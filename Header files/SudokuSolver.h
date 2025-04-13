#pragma once

#include <iostream>
#include <string>
#include "Stack.h"
#include "SudokuPuzzle.h"
#include "SudokuSolver.h"
#include "Coordinates.h"
using namespace std;
struct SudokuSolver {
	
	SudokuPuzzle* problem;
	int stepNo=0;

	/// <summary>
	/// Checks if row, based on Coordinates variable, has a number that is required to check
	/// </summary>
	/// <param name="temp"> temp </param>
	/// <param name="checkNo"></param>
	/// <returns></returns>
	bool checkRow(Coordinates temp,short checkNo)
	{
		for (short i = 0; i < problem->columns; i++) {
			if (temp.col == i)
			{
				continue;
			}
			if (problem->sudoku[temp.row][i] == checkNo)
			{
				return false;
			}
		}
		return true;
	}

	/// <summary>
	/// Checks if column, based on Coordinates variable, has a number that is required to check
	/// </summary>
	/// <param name="temp"></param>
	/// <param name="checkNo"></param>
	/// <returns></returns>
	bool checkCol(Coordinates temp, short checkNo)
	{
		for (short i = 0; i < problem->rows; i++) {
			if (temp.row == i)
			{
				continue;
			}
			if (problem->sudoku[i][temp.col] == checkNo)
			{
				return false;
			}
		}
		return true;
	}
	/// <summary>
	/// Checks if 3x3 block, based on Coordinates variable, has a number that is required to check
	/// </summary>
	/// <param name="temp"></param>
	/// <param name="checkNo"></param>
	/// <returns></returns>
	bool checkBlock(Coordinates temp, short checkNo)
	{
		for (short i = temp.row / 3 * 3; i < temp.row / 3 * 3 + 3; i++)
		{
			for (short j = temp.col / 3 * 3; j < temp.col / 3 * 3 + 3; j++) {
				
				if (temp.row == i && j == temp.col)
				{
					continue;
				}
				if (problem->sudoku[i][j] == checkNo)
				{
					return false;
				}
			}
		}
		return true;
	}
	/// <summary>
	/// Gives next position of unknown number in sudoku grid
	/// </summary>
	/// <param name="tmp"></param>
	/// <returns></returns>
	Coordinates getNextPos(Coordinates tmp)
	{
		for (short i = tmp.row; i < problem->rows; i++)
		{
			for (short j = 0; j < problem->columns; j++)
			{
				if (tmp.row == i && j <= tmp.col)
				{
					continue;
				}
				if (problem->locked[i][j])
				{
					continue;
				}
				Coordinates ans;
				ans.col = j;
				ans.row = i;
				return ans;
			}
		}
	}
	/// <summary>
	/// Prints answer in required format
	/// </summary>
	void printAnswer() {
		cout << "Solution found in " << stepNo << " steps!" << endl;
		cout << "+-----------------+" << endl;
		for (short i = 0; i < problem->rows; i++)
		{
			cout << "|";
			for (short j = 0; j < problem->columns; j++)
			{
				cout << problem->sudoku[i][j] << "|";
			}
			cout << endl;
		}
		cout << "+-----------------+" << endl;
	}
	/// <summary>
	/// Checks if sudoku is even possible to solve
	/// </summary>
	/// <returns></returns>
	bool isPossible()
	{

		for (short i = 0; i < problem->rows; i++)
		{
			for (short j = 0; j < problem->columns; j++)
			{
				if (!problem->locked[i][j])
				{
					continue;
				}
				Coordinates tmp;
				tmp.row = i;
				tmp.col = j;
				if (!checkRow(tmp, problem->sudoku[i][j]) || !checkCol(tmp, problem->sudoku[i][j]) || !checkBlock(tmp, problem->sudoku[i][j]))
				{
					return false;
				}
			}
		}
		return true;
	}
	void sudokuSolution() 
	{
		if (isPossible()) {
			Stack<Coordinates> stack;
			stack.push(problem->start);
			while (!stack.isEmpty())
			{
				stepNo++;
				Coordinates currentPos = stack.top();
				bool flag = true;
				for (short i = problem->sudoku[currentPos.row][currentPos.col] + 1; i <= 9; i++)
				{
					if (checkRow(currentPos, i) && checkCol(currentPos, i) && checkBlock(currentPos, i))
					{
						problem->sudoku[currentPos.row][currentPos.col] = i;
						flag = false;
						break;
					}
				}
				if (flag)
				{
					problem->sudoku[currentPos.row][currentPos.col] = 0;
					stack.pop();
					continue;
				}
				if (currentPos.row == problem->finish.row && currentPos.col == problem->finish.col)
				{
					printAnswer();
					return;
				}
				else {
					stack.push(getNextPos(currentPos));
				}
			}
		}
		else {
			cout << "Sudoku is not possible to solve!" << endl; 
		}
	}
};