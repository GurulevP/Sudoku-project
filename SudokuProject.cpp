// SudokuProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>
#include "Stack.h"
#include "SudokuPuzzle.h"
#include "SudokuSolver.h"
#include "Coordinates.h"

using namespace std;

/// <summary>
/// Initialises and fills SudokuPuzzle variable
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
SudokuPuzzle* loadPuzzle(string filename) {
    SudokuPuzzle* puzzle = new SudokuPuzzle;
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Cannot open file!" << endl;
        return nullptr;
    }
    file >> puzzle->rows;
    file >> puzzle->columns;
    puzzle->sudoku = new short* [puzzle->rows];
    puzzle->locked = new bool* [puzzle->rows];
    puzzle->finish.col = 0;
    puzzle->finish.row = 0;
    for (short i = 0; i < puzzle->rows; i++)
    {
        puzzle->sudoku[i] = new short[puzzle->columns];
        puzzle->locked[i] = new bool[puzzle->columns];
    }
    for (short i = 0; i < puzzle->rows; i++)
    {
        for (short j = 0; j < puzzle->columns; j++)
        {
            file >> puzzle->sudoku[i][j];
            if (puzzle->sudoku[i][j] == 0)
            {
                puzzle->locked[i][j] = false;
                if (puzzle->count == 0)
                {
                    puzzle->start.col = j;
                    puzzle->start.row = i;
                }
                puzzle->count++;
                if (puzzle->finish.row < i)
                {
                    puzzle->finish.row = i;
                    puzzle->finish.col = j;
                }
                else if (puzzle->finish.row == i && puzzle->finish.col <= j)
                {
                    puzzle->finish.row = i;
                    puzzle->finish.col = j;
                }
            }
            else {
                puzzle->locked[i][j] = true;
            }
        }
    }
    puzzle->printProblem(puzzle);
    return puzzle;
}


int main()
{
    SudokuPuzzle* puzzle = new SudokuPuzzle();
    puzzle = loadPuzzle("test1.txt");
    SudokuSolver* solution = new SudokuSolver();
    solution->problem = puzzle;
    solution->sudokuSolution();
    puzzle = loadPuzzle("test2.txt");
    solution->problem = puzzle;
    solution->sudokuSolution();
    puzzle = loadPuzzle("test3.txt");
    solution->problem = puzzle;
    solution->sudokuSolution();
    puzzle = loadPuzzle("test4.txt");
    solution->problem = puzzle;
    solution->sudokuSolution();
    puzzle = loadPuzzle("test5.txt");
    solution->problem = puzzle;
    solution->sudokuSolution();
}
