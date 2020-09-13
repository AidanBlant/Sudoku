//
//  main.cpp
//  Sudoku
//
//  Created by Aidan Blant on 9/9/20.
//  Copyright © 2020 Aidan Blant. All rights reserved.
//

#include <iostream>
#include <map>
#include "Board.hpp"
#include "BoardCreator.cpp"
#include "BoardSolver.cpp"
#include <set>

template <typename T>
void findDuplicates(std::vector<T> & vecOfElements, map<T, int> & countMap);
void createXBoardsAndExport(int numBoards, string fileName);

int main(int argc, const char * argv[]) {
    // Creates BoadCreator with BoardList from file
    // BoardCreator bc = BoardCreator("sampleBoards.txt");
    string samplePuzzle = ".43.8.25.6.............1.949....4.7....6.8....1.2....382.5.............5.34.9.71.";
    string samplePuzzle2 = "53..7....6..195....98....6.8...6...34..8.3..17...2...6.6....28....419..5....8..79";
    string answer = BoardSolver::returnSolution(samplePuzzle2);
    
    cout << "answer: " << answer << endl;
    
    return 0;
}

// Create list of numBoards boards and save to fileName.txt
void createXBoardsAndExport(int numBoards, string fileName){
    BoardCreator bc = BoardCreator(numBoards);
    
    for( int i = 0; i < bc.boardList.size(); i++){
        Board::printGrid( bc.boardList[i] );
        if( Board::noRepeats( bc.boardList[i] ) == false ){
            cout << "Board: " << i << " has repeats" << endl;
        }else{
            cout << "Board: " << i << " is good!" << endl;
        }
    }
    bc.exportFilledBoardList(fileName);
}
