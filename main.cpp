#include <iostream>
#include "ArrayList.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "Graph.h"
#include "Vertex.h"
#include "Sudoku.h"
#include <vector>


using namespace std;


template <class T>
void display(Waypoint<T>* end){
    Stack<Waypoint<T>*> stack;
    Waypoint<T>* temp = end;
    while (temp != nullptr){
        stack.push(temp);
        temp = temp->parent;
    }
    while (stack.length() > 0){
        Waypoint<T>* curr = stack.pop();
        cout << curr->vertex->data << ", " << curr->weight << ", " << curr->partialCost << endl;
    }
}







void printBoard(vector<vector<int> > board){
    cout << "    1 2 3     4 5 6     7 8 9" << endl;
    for(int i = 0; i < board.size(); i++){
        if(i % 3 ==0){
            cout << "  - - - - - - - - - - - - - - " << endl;
        }
        for(int j = 0; j < board[i].size(); j++){
            if(j % 3 ==0){
                cout <<" | ";
            }
            if(j == 8){
                cout << board[i][j] << " | " <<i +1;
            }
            else{
                cout << board[i][j];
            }
        }
    }
    cout << "  - - - - - - - - - - - - - - ";
}



struct SudokuBoard{
    SudokuConnections graph;
    std::vector<std::vector<int> > matrix = getGridMatrix();
    int arr[9][9] ={
            {0,0,0,4,0,0,0,0,0},
            {4,0,9,0,0,6,8,7,0},
            {0,0,0,9,0,0,1,0,0},
            {5,0,4,0,2,0,0,0,9},
            {0,7,0,8,0,4,0,6,0},
            {6,0,0,0,3,0,5,0,2},
            {0,0,1,0,0,7,0,0,0},
            {0,4,3,2,0,0,6,0,5},
            {0,0,0,0,0,5,0,0,0}
    };


    void displayBoard(int arr[9][9]){
        std::cout << "    1 2 3     4 5 6     7 8 9" << std::endl;
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0 && i != 0) {
                std::cout << "  - - - - - - - - - - - - - - " << std::endl;
            }

            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0 && j != 0) {
                    std::cout << " |  ";
                }
                if (j == 8) {
                    std::cout << arr[i][j] << " | " << i + 1 << std::endl;
                } else {
                    std::cout << arr[i][j] << " ";
                }
            }
        }
        std::cout << "  - - - - - - - - - - - - - - " << std::endl;
    }

std::vector<std::vector<int> > getGridMatrix() {
        std::vector<std::vector<int> > matrix(9, std::vector<int>(9, 0));
        int count = 1;
        for (int rows = 0; rows < 9; ++rows) {
            for (int cols = 0; cols < 9; ++cols) {
                matrix[rows][cols] = count;
                ++count;
            }
        }
        return matrix;
    }
std::pair<int, int> isBlank() {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (arr[row][col] == 0) {
                    return std::make_pair(row, col);
                }
            }
        }
        return std::make_pair(-1, -1);
    }

    bool isValid(int num, std::pair<int, int> pos) {
        // ROW
        for (int col = 0; col < 9; col++) {
            if (arr[pos.first][col] == num && pos.first != col) {
                return false;
            }
        }

        // COL
        for (int row = 0; row < 9; row++) {
            if (arr[row][pos.second] == num && pos.second != row) {
                return false;
            }
        }

        // BLOCK
        int x = pos.second / 3;
        int y = pos.first / 3;
        for (int row = y * 3; row < y * 3 + 3; row++) {
            for (int col = x * 3; col < x * 3 + 3; col++) {
                if (arr[row][col] == num && std::make_pair(row, col) != pos) {
                    return false;
                }
            }
        }

        return true;
    }

    bool solveItNaive() {
        std::pair<int, int> findBlank = isBlank();
        if (findBlank.first == -1 && findBlank.second == -1) {
            return true;
        }
        int row = findBlank.first;
        int col = findBlank.second;
        for (int i = 1; i <= 9; i++) {
            if (isValid(i, std::make_pair(row, col))) {
                arr[row][col] = i;
                if (solveItNaive()) {
                    return true;
                }
                arr[row][col] = 0;
            }
        }
        return false;
    }
};






int main(){
    SudokuBoard sudoku;
    
    sudoku.displayBoard(sudoku.arr);
    sudoku.solveItNaive();
    sudoku.displayBoard(sudoku.arr);

    

   
    



    
    

    return 0;
}