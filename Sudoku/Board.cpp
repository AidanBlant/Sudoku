//
//  Board.cpp
//  Sudoku
//
//  Created by Aidan Blant on 9/9/20.
//  Copyright © 2020 Aidan Blant. All rights reserved.
//

#include "Board.hpp"
#include <iostream>
#include <fstream>
using namespace std;

class Board {
public:
    	int board[9][9];
    int setTiles;
    	
    // Creates empty board with 0's 
    Board(){
        for(int i=0; i < 9; i++){
            for(int j=0; j<9; j++){
                board[i][j] = 0;
            }
        }
        setTiles = 0;
    }
    
    // Load board from 81 character string
    Board(string boardString){
        if( boardString.length() != 81 ){
            cout << "Incorrect String length to load board." << endl;
            return;
        }        
        for( int i = 0; i < 81; i++ ){
           board[i/9][i%9] = (int)(boardString[i]-'0');
        }
    }
    
    // Is entire board valid (no incorrect tiles)
    bool noRepeats(){
        bool col[9][9] = {false};
        bool box[9][9] = {false};
        
        for( int i = 0; i < 9; i++ ){
            bool row[9] = {false};
            for( int j = 0; j < 9; j++ ){
                if( board[i][j] != 0 ){
                    
                    // If repeat on row, false, otherwise add to row bool array
                    if( row[ board[i][j] -1 ] == true ){
                        cout << "Row repetition of " << board[i][j] << " at (" << i << "," << j << ")" << endl;
                        return false; // False based on row repeat
                    }else{
                        row[ board[i][j] -1] = true;
                    }
                    
                    // If repeat on column, false, otherwise add to column bool array
                    if( col[i][ board[i][j] -1] == true ){
                        cout << "Col repetition of " << board[i][j] << " at (" << i << "," << j << ")" << endl;
                        return false; // False based on column repeat
                    }else{
                        col[i][ board[i][j] -1] = true;
                    }
                    
                    // If repeat on box, false, otherwise add to box bool array
                    int boxRow = i/3;
                    int boxCol = j/3;
                    if( box[boxRow*3 + boxCol ][ board[i][j] - 1 ] == true ){
                        cout << "Box repetition of " << board[i][j] << " at (" << i << "," << j << ")" << endl;
                        return false; // False based on box repeat
                    }else{
                        box[boxRow*3 + boxCol][ board[i][j] - 1] = true;
                    }
                    
                }
            }
        }
        
        return true;
    }
    
    //
    bool validMove(int move, int row, int col){
        return false;
    }
    
    // Display Board in Console
    void print(){
        cout << endl;
        cout <<  "-------------" << endl;
        for(int i=0; i<9; i++){
            cout << "|";
            for(int j=0; j<9; j++){
                if( board[i][j] == 0 ){
                    cout << "0";
                }else{
                    cout << board[i][j];
                }
                if(j%3==2){
                    cout << "|";
                }
            }
            if(i%3==2){
                cout << endl <<  "-------------";
            }
            cout << endl;
        }
        cout << endl;
    }
    
};
