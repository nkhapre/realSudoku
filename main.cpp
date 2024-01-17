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

int main(){
    

    

    SudokuConnections sudoku;
    
    cout << sudoku.graph << endl;

    
    

    return 0;
}