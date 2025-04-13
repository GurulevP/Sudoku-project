#pragma once
#include <iostream>
#include "Coordinates.h"
using namespace std;
struct SudokuPuzzle {
	short** sudoku;
	bool** locked;
	short rows;
	short columns;
	short count = 0;
	Coordinates start;
	Coordinates finish;
    /// <summary>
    /// prints the loaded data as it required in the assignment brief
    /// </summary>
    /// <param name="Puzzle"></param>
    void printProblem(SudokuPuzzle* Puzzle)
    {
        cout << "+-----------------+" << endl;
        for (short i = 0; i < Puzzle->rows; i++)
        {
            cout << "|";
            for (short j = 0; j < Puzzle->columns; j++)
            {
                cout << Puzzle->sudoku[i][j] << "|";
            }
            cout << endl;
        }
        cout << "+-----------------+" << endl;
        cout << "Number of missing numbers: " << Puzzle->count << endl;
        cout << "First missing number: (" << Puzzle->start.row << ", " << Puzzle->start.col << ")" << endl;
        cout << "Last missing number: (" << Puzzle->finish.row << ", " << Puzzle->finish.col << ")" << endl;
        cout << "Puzzle Numbers: ";
        for (short i = 0; i < Puzzle->rows; i++)
        {
            for (short j = 0; j < Puzzle->columns; j++)
            {
                if (Puzzle->locked) {
                    cout << Puzzle->sudoku[i][j] << ":(" << i << ", " << j << "), ";
                }
            }
        }
        cout << endl;
    }
    
};