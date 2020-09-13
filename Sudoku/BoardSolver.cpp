//
//  BoardSolver.cpp
//  Sudoku
//
//  Created by Aidan Blant on 9/12/20.
//  Copyright © 2020 Aidan Blant. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class BoardSolver{
public:
    int grid[9][9] = {0};
    
    BoardSolver(string puzzle) {
        // Create BoardSolver by converting string to grid
        for(int i = 0; i < 9; i++){
            for( int j = 0; j < 9; j++){
                if( puzzle[i*9 + j] != '.' ){
                    grid[i][j] = (int)(puzzle[ i*9 + j ] - '0');
                }
            }
        }
    }
    
    // Sudoku Backtracking Algorithm expanded on from
    // a Stanford lecture: https://see.stanford.edu/materials/icspacs106b/Lecture11.pdf
    bool solveSudoku(){
//        printGrid(); For debugging
        int row, col;
        if (!FindUnassignedLocation(row,col))
            return true; // all locations successfully assigned!
        for (int num = 1; num <= 9; num++) { // options are 1-9
            if (NoConflicts(row,col,num)) { // if # looks ok
                grid[row][col] = num; // try assign #
                if (solveSudoku())
                    return true; // recur if succeed stop
                grid[row][col] = 0; // undo & try again
            }
        }
        return false; // this triggers backtracking from early decisions
    }
        
    bool FindUnassignedLocation(int &row, int &col){
        for (row = 0; row < 9; row++)
            for (col = 0; col < 9; col++)
                if (grid[row][col] == 0)
                    return true;
        return false;
    }

    // TODO: Experiment I can make this faster by keeping my list of box/row/col conflicts
    // similar to 'noRepeats' box/row/col keeping
    bool NoConflicts(int row, int col, int num){
        for( int i = 0; i < 9; i++){
            if(grid[i][col] == num){
//                cout << "conflict with " << num << " at pos(" << i << "," << col << endl;
                return false;
            }
            if(grid[row][i] == num){
//                cout << "conflict with " << num << " at pos(" << row << "," << i << endl;
                return false;
            }
        }
        //Get Box
        for( int i = 0; i < 3; i++){
            for( int j = 0; j < 3; j++){
                if( grid[row/3*3+i][col/3*3+j] == num ){
//             cout << "conflict with " << num << " at box(" << row/3*3 << "," << col/3*3 << endl;
                    return false;
                }
            }
        }
        return true;
    }
    
        
    // Given incomplete sudoku board as string
    // return solution as string
    // if no solution return "NOSOLUTION"
    static string returnSolution(string puzzle){
        BoardSolver bs = BoardSolver(puzzle);
        
//        cout << "_PUZZLE ENTERED_" << endl; bs.printGrid(); cout << endl;
        bs.solveSudoku();
//        cout << "AFTER SOLVER_" << endl; bs.printGrid(); cout << endl;

        return bs.returnGrid();
    }
    
    
    // If Grid is a solution, return it as string
    // otherwise return no solution
    string returnGrid(){
        string toReturn = "";
        for( int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if( grid[i][j] != '.' ){
                    toReturn += to_string(grid[i][j]);
                }else{
                    return "NOSOLUTION";
                }
            }
        }
        return toReturn;
    }
    
    // Print grid to console
    void printGrid(){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                cout << grid[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
    
    
};
