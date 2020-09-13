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
    vector<string> boardList;

    BoardCreator(int numBoards){
        while( boardList.size() <numBoards ){
            addBoard(makeBoard());
        }
    }

    // Initialize from file of completeBoards
    BoardCreator(string inputFile){
        string line;
        ifstream myfile (inputFile);
        if (myfile.is_open()){
          while ( getline (myfile,line) ){
              // Make board with the line, then add it to boardList
              boardList.push_back( line );
          }
          myfile.close();
        }
        else cout << "Unable to open file\n";
    }
    
private:
    // MARK: - Board Transformation Operations
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
    
    void rotate180(string& board){
        // Transpose over diagonal
        for( int i = 0; i < 9; i++ ){
            for( int j = i; j < 9; j++ ){
                swap(board[ i*9 + j ],board[ j*9 + i ]);
            }
        }
        
        // Transpose over opposite diagonal
        for( int i = 0; i < 9; i++){
            for( int j = 0; j < (9-i); j++){
                swap(board[ i*9 + j ],board[ (8-i) + ((8-j)*9) ]);
            }
        }
        
    }
    
    // Return a board created from transformations on seedboard
    string makeBoard(){
        string seedBoard = "123456789456789123789123456234567891567891234891234567345678912678912345912345678";
        for( int j = 0; j < 1000; j++ ){
            int op = rand() % 26;
           
            // TODO: These are preset based on following scheme
            // 0 = rows01, 1=row12, 2=swap02 | 3=rows34, 4=rows45, 5=rows35
            // 9 = col01, 10=col12, etc...
            // To maintain repeatability from seedString
            int rowOrCol2 = rand() % 3;
            int rowOrCol3 = rand() % 3;
            int rowOrCol4 = rand() % 3;
            
            // pick board row or col 0-3
            // swap two rows or columns in it
            if( op < 9){
                swapRows(seedBoard, rowOrCol2*3 + rowOrCol3, rowOrCol2*3+rowOrCol4);
            }else if( op < 18 ){
                swapCols(seedBoard, rowOrCol2*3 + rowOrCol3, rowOrCol2*3+rowOrCol4);
            }else if( op < 19 ){
                moveLeft(seedBoard);
            }else if( op < 20 ){
                moveRight(seedBoard);
            }else if( op < 21 ){
                rotateLeft(seedBoard);
            }else if(op < 22 ){
                rotateRight(seedBoard);
            }else{
                rotate180(seedBoard);
            }
        }
        return seedBoard;
    }
    
    // Add board if not a duplicate
    void addBoard(string newBoard){
        if( !existsInBoardList(newBoard) ){
            boardList.push_back(newBoard);
            return;
        }
        return;
    }
    
    bool existsInBoardList(string toCheck){
        if (std::find(boardList.begin(), boardList.end(), toCheck) != boardList.end())
        {
            cout << "Already exists in board" << std::endl;
            return true;
        }
        return false;
    }

public:
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
    
    // I/O
    int exportFilledBoardList(string fileName){
        if( boardList.size() == 0 ){
            cout << "No Boards in BoardList to export" << endl;
            return 1; // Error, No Boards in BoardList to Export
        }
        
        ofstream myfile;
        myfile.open (fileName+".txt");
        for( int i = 0; i < boardList.size(); i++ ){
            myfile << boardList[i] << "\n";
        }
        myfile.close();
        return 0;
    }
    
};
