//
//  main.cpp
//  eight-queen
//
//  Created by 胡欣妍 on 2018/6/8.
//  Copyright © 2018年 胡欣妍. All rights reserved.
//

#include <iostream>
using namespace std;

const bool available = true;

class ChessBoard {
    const int squares, norm;
    bool *column, *leftDiagnoal, *rightDiagnoal;
    int *positionInRow, howMany;
    void putQueen(int);
    void initBoard();
public:
    ChessBoard();
    ChessBoard(int);
    void findSolutions();
    ~ChessBoard();
};

ChessBoard::ChessBoard() : squares(8), norm(squares - 1) {
    initBoard();
}

ChessBoard::ChessBoard(int n) : squares(n), norm(squares - 1) {
    initBoard();
}

ChessBoard::~ChessBoard() {
    if (column) {
        delete [] column;
        column = NULL;
    }
    if (leftDiagnoal) {
        delete [] leftDiagnoal;
        leftDiagnoal = NULL;
    }
    if (rightDiagnoal) {
        delete [] rightDiagnoal;
        rightDiagnoal = NULL;
    }
}

void ChessBoard::initBoard() {
    int i;
    column = new bool(squares);
    positionInRow = new int(squares);
    leftDiagnoal = new bool(squares*2 - 1);
    rightDiagnoal = new bool(squares*2 - 1);
    
    for (i = 0; i < squares; i++) {
        positionInRow[i]  = -1;
        column[i] = available;
    }
    
    for (i = 0; i < squares*2 - 1; i++) {
        leftDiagnoal[i] = rightDiagnoal[i] = available;
    }
    howMany = 0;
}

void ChessBoard::putQueen(int row) {
    for (int col = 0; col < squares; col++){
        if (column[col] == available &&
            leftDiagnoal[col + row] == available &&
            rightDiagnoal[col - row + norm] == available) {
            positionInRow[col] = col;
            column[col]  = leftDiagnoal[col + row] = rightDiagnoal[col - row + norm] = !available;
            if (row < squares - 1) {
                putQueen(row + 1);
            }
            else {
                howMany++;
            }
            column[col]  = leftDiagnoal[col + row] = rightDiagnoal[col - row + norm] = available;
        }
    }
}

void ChessBoard::findSolutions() {
    putQueen(0);
    cout << "solutions: " << howMany << endl;
}
int main(int argc, const char * argv[]) {
    ChessBoard board(13);
    board.findSolutions();
    board.~ChessBoard();
    return 0;
}
