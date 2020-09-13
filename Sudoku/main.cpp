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
#include <set>

template <typename T>
void findDuplicates(std::vector<T> & vecOfElements, map<T, int> & countMap);

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

int main(int argc, const char * argv[]) {
    // Creates BoadCreator with BoardList from file
    // BoardCreator bc = BoardCreator("sampleBoards.txt");
    
    return 0;
}

