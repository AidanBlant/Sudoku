//
//  main.cpp
//  Sudoku
//
//  Created by Aidan Blant on 9/9/20.
//  Copyright © 2020 Aidan Blant. All rights reserved.
//

#include <iostream>
#include "BoardCreator.cpp"

int main(int argc, const char * argv[]) {
    
    // Creates BoadCreator with BoardList from file
    // BoardCreator bc = BoardCreator("sampleBoards.txt");
    
    BoardCreator bc = BoardCreator("sampleBoards.txt");
    
    for( int i = 0; i < bc.boardList.size(); i++){
        if( bc.boardList[i].noRepeats() == false ){
            cout << "Board: " << i << " has repeats" << endl;
        }else{
            cout << "Board: " << i << " is good!" << endl;
        }
    }
    
    return 0;
}
