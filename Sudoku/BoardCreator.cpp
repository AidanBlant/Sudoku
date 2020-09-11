//
//  BoardCreator.cpp
//  Sudoku
//
//  Created by Aidan Blant on 9/10/20.
//  Copyright © 2020 Aidan Blant. All rights reserved.
//

#include "BoardCreator.hpp"
#include "Board.cpp"
#include <vector>

#include <unistd.h>
#define GetCurrentDir getcwd

class BoardCreator{
public:
    vector<Board> boardList;
    
    // Swap two rows in a board string rows 0-8
    void swapRows(string& board, int a, int b){
        // so any given row will start on a/b * 9, and go for 9 characters
        string tempA = board.substr(a*9, 9);
        string tempB = board.substr(b*9, 9);
        board.replace(a*9, 9, tempB);
        board.replace(b*9, 9, tempA);
    }
    
    // Swap two columns in a board string rows 0-8
    void swapCols(string& board, int a, int b){
        for( int i = 0; i < 9; i++){
            // i is row, so i*9 + a or b
            int tempA = board[i*9+a];
            board[i*9+a] = board[i*9+b];
            board[i*9+b] = tempA;
        }
    }
    
    void moveRight(string& board){
        for( int i = 0; i < 9; i++ ){
            string firstSix = board.substr(i*9,6);
            board.replace((i*9),3,board.substr(i*9+6,3));
            board.replace(i*9+3,6,firstSix);
        }
    }
    void moveLeft(string& board){
        // Go row by row moving all tiles 3 to the left
        for( int i = 0; i < 9; i++ ){
            string firstThree = board.substr(i*9,3);
            board.replace((i*9),6,board.substr(i*9+3,6));
            board.replace((i*9+6),3,firstThree);
        }
    }
    
    // Rotate Right/Left based on the transpose + horizontal flip formula
    void rotateRight(string& board){
        // Transpose over diagonal
        for( int i = 0; i < 9; i++ ){
            for( int j = i; j < 9; j++ ){
                swap(board[ i*9 + j ],board[ j*9 + i ]);
            }
        }
        //Flip horizontally
        for( int i = 0; i < 9; i++ ){ // row
            for( int j = 0; j < 9/2; j++){ // col
                swap( board[i*9+j], board[ i*9 + (8-j) ] );
            }
        }
    }
    
    void rotateLeft(string& board){
        // Transpose over diagonal
        for( int i = 0; i < 9; i++ ){
            for( int j = i; j < 9; j++ ){
                swap(board[ i*9 + j ],board[ j*9 + i ]);
            }
        }
        //Flip vertically
        for( int i = 0; i < 9/2; i++ ){ // row
            for( int j = 0; j < 9; j++){ // col
                swap( board[i*9+j], board[ (8-i)*9 + j]);
            }
        }
    }
    
    
    BoardCreator(int numBoards){
        string seedBoard = "152489376739256841468371295387124659591763428246895713914637582625948137873512964";
        boardList.push_back( Board(seedBoard) );
        for( int i = 0; i < numBoards; i++){
            
            for( int j = 0; j < 100; j++ ){
                int op = rand() % 6;
               
                int rowOrCol2 = rand() % 3;
                int rowOrCol3 = rand() % 3;
                int rowOrCol4 = rand() % 3;
                
                // pick board row or col 0-3
                // swap two rows or columns in it
                if( op == 0 ){
                    swapRows(seedBoard, rowOrCol2*3 + rowOrCol3, rowOrCol2*3+rowOrCol4);
                }else if( op == 1 ){
                    swapCols(seedBoard, rowOrCol2*3 + rowOrCol3, rowOrCol2*3+rowOrCol4);
                }else if( op == 2 ){
                    moveLeft(seedBoard);
                }else if( op == 3 ){
                    moveRight(seedBoard);
                }else if( op == 4 ){
                    rotateLeft(seedBoard);
                }else{
                    rotateRight(seedBoard);
                }
            }
            boardList.push_back( Board(seedBoard) );
        }

    }
    
    
    // Initialize from file of completeBoards
    BoardCreator(string inputFile){
        string line;
        ifstream myfile (inputFile);
        if (myfile.is_open()){
          while ( getline (myfile,line) ){
              // Make board with the line, then add it to boardList
              boardList.push_back( Board(line) );
          }
          myfile.close();
        }
        else cout << "Unable to open file\n";
    }

    
    // A very poor brute-force sudoku creating algorithm
    string createFilledBoard(){
        bool fill[3][9][9] = {false};
        bool beenTried[81][9] = {false};
        int board[81] = {0};

        createFilled(board, fill, beenTried, 0);

        string boardString = "";
        // Parse int array in to string
        for( int i = 0; i < 81; i++ ){
            boardString += (char)(board[i]-'0');
        }
        
        return boardString;
    }
    
    bool createFilled(int board[], bool fill[3][9][9], bool beenTried[81][9], int inc){
        printIntArray(board);
//        printFill(fill);
//        int inc = incrementer;
        int row = inc/9;
        int col = inc%9;
        int box = inc/27 + (inc%9)/3;
        
        for( int i = 0; i < 9; i++ ){
            
            if( inc > 20 and beenTried[inc][i] ){
            }

            // If value can be added validly, add it and move onto next position
            if( !fill[0][row][i] and !fill[1][col][i] and !fill[2][box][i] ){
                // If is valid and incrementer is 81, we are done return
                if( inc == 81 ){
                    cout << "Board Done!" << endl;
                    return true;
                }else{

                    // Set flags and recursive call
                    fill[0][row][i] = true;
                    fill[1][col][i] = true;
                    fill[2][box][i] = true;
                    
                    // Make recursive call, if true, we're done, just return true all the way back
                    board[inc] = (i+1);
                    beenTried[inc][i] = true;
                    if( createFilled(board, fill, beenTried, inc+1) ){
                        cout << "filled board created!" << endl;
                        return true;
                    }else{
                        // If not true, undo flags, and move onto next value to try
                        // TODO: Issue is here stilllllll, not getting undone correctly
//                        cout << "i: " << i << "  incrementer: " << incrementer << endl;
                        board[inc] = 0;
                        fill[0][row][i] = false;
                        fill[1][col][i] = false;
                        fill[2][box][i] = false;
                    }
                }
            } else{
//                cout << i+1 << " invalid at " << inc << endl;
            }
            // Else, not valid and simply continue
        }
        
        // No valid values
        return false;
    }
    
    /* Display ß*/
    void printIntArray(int board[81]){
        for( int i = 0; i < 81; i++ ){
            if( board[i] == 0 ){
                cout << endl;
                return;
            }
            cout << board[i];
        }
        cout << endl;
    }
    
    void printFill(bool fill[3][9][9]){
        cout << "___________________________________" << endl;
        cout << "Rows:       Cols:       Boxes:    |" << endl;
        for(int j = 0; j < 9; j++){
            for( int i = 0; i < 3; i++ ){
                for( int k = 0; k < 9; k++){
                    if( fill[i][j][k] == true ){
                        cout << 1;
                    }else {
                        cout << 0;
                    }
                }
                cout << " | ";
            }
            cout << endl;
        }
        cout << "___________________________________" << endl;
    }
    
};


