#ifndef SUDOKU_H
#define SUDOKU_H
#include "ArrayList.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "Graph.h"
#include "Vertex.h"
#include <vector>



//makes a graph with 81 vertices
template <class T>
void generateGraph(Graph<T>& graph, int amount){
    for(int i =1; i <= amount; i++){
        Vertex<T>* newVertex =  new Vertex<T>(i);
        graph.addVertex(newVertex);
    }

}

// std::vector<std::vector<int> >  addConnections(int arr[9][9], int rows, int cols){
//     //the plan is to make an vector where the n element contains all the connections the n vertex has
//    std::vector<std::vector<int> > connections;

//    std::vector<int> row;
//    std::vector<int> columns;
//    std::vector<int> block;
//     //for every row connection
//    for(int i=cols+1; i < 9; i++){
//     row.push_back(arr[rows][i]);
//    }
//    connections.push_back(row);

//    for(int i=rows+1; i < 9; i++){
//     columns.push_back(arr[i][cols]);
//    }
//    connections.push_back(columns);

//    if(rows% 3 ==0){
//     if(cols % 3 ==0){
//         block.push_back(arr[rows+1][cols+1]);
//         block.push_back(arr[rows+1][cols+2]);
//         block.push_back(arr[rows+2][cols+1]);
//         block.push_back(arr[rows+2][cols+2]);
//     }
//     else if(cols% 3 ==1){
//         block.push_back(arr[rows+1][cols-1]);
//         block.push_back(arr[rows+1][cols+1]);
//         block.push_back(arr[rows+2][cols-1]);
//         block.push_back(arr[rows+2][cols+1]);

//     }
//     else if(cols% 3== 2){
//         block.push_back(arr[rows+1][cols-2]);
//         block.push_back(arr[rows+1][cols-1]);
//         block.push_back(arr[rows+2][cols-2]);
//         block.push_back(arr[rows+2][cols-1]);

//     }
//    }
//    else if(rows %3 ==1){
//     if(cols% 3 ==0){
//         block.push_back(arr[rows-1][cols+1]);
//         block.push_back(arr[rows-1][cols+2]);
//         block.push_back(arr[rows+1][cols+1]);
//         block.push_back(arr[rows+1][cols+2]);

//     }
//     else if(cols %3 == 1){
//         block.push_back(arr[rows-1][cols-1]);
//         block.push_back(arr[rows-1][cols+1]);
//         block.push_back(arr[rows+1][cols-1]);
//         block.push_back(arr[rows+1][cols+1]);

//     }
//     else if(cols %3 ==2){
//         block.push_back(arr[rows-1][cols-2]);
//         block.push_back(arr[rows-1][cols-1]);
//         block.push_back(arr[rows+1][cols-2]);
//         block.push_back(arr[rows+1][cols-1]);

//     }
//    }

//    else if(rows % 3 == 2){
//     if(cols%3 ==0){
//         block.push_back(arr[rows-2][cols+1]);
//         block.push_back(arr[rows-2][cols+2]);
//         block.push_back(arr[rows-1][cols+1]);
//         block.push_back(arr[rows-1][cols+2]);

//     }
//     else if(cols%3 ==1){
//         block.push_back(arr[rows-2][cols-1]);
//         block.push_back(arr[rows-2][cols+1]);
//         block.push_back(arr[rows-1][cols-1]);
//         block.push_back(arr[rows-1][cols+1]);

//     }
//     else if(cols%3 ==2){
//         block.push_back(arr[rows-2][cols-1]);
//         block.push_back(arr[rows-2][cols+1]);
//         block.push_back(arr[rows-1][cols-1]);
//         block.push_back(arr[rows-1][cols+1]);
 
//     }
//    }
//    connections.push_back(block);
//    return connections;

// }

// template <class T>
// void connectThose(std::vector<std::vector<int> > connections, Graph<T>& graph ){
//     for(int i =0; i < connections.size();i++){
//        std::vector<int> poop = connections[i];
//        for(int j =0; j < poop.size();j++){


//        }
//     }
// }

// template <class T>
// void connectEdges(Graph<T>& graph){
//     //makes 2d array to know where to position squares
//         int arr[9][9];
//         int num =1;
//         for(int i =0; i< 9;i++){
//             for(int j =0; j <9; j++){
//                 arr[i][j] = num;
//                 num += 1;
//             }
//         }

   


    

    
// }
template <class T>
void connectEdges(Graph<T>& graph) {
    const int rows = 9;
    const int columns = 9;
        // Connect vertices in the same row
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns - 1; ++j) {
                for (int k = j + 1; k < columns; ++k) {
                    graph.addEdge(graph.vertices[i * columns + j], graph.vertices[i * columns + k], 0);
                }
            }
        }

        // Connect vertices in the same column
        for (int j = 0; j < columns; ++j) {
            for (int i = 0; i < rows - 1; ++i) {
                for (int k = i + 1; k < rows; ++k) {
                    graph.addEdge(graph.vertices[i * columns + j], graph.vertices[k * columns + j], 0);
                }
            }
        }

        // Connect vertices in the same 3x3 grid
        for (int startRow = 0; startRow < rows; startRow += 3) {
            for (int startCol = 0; startCol < columns; startCol += 3) {
                for (int i = startRow; i < startRow + 3; ++i) {
                    for (int j = startCol; j < startCol + 3; ++j) {
                        for (int k = startRow; k < startRow + 3; ++k) {
                            for (int l = startCol; l < startCol + 3; ++l) {
                                if (i != k || j != l) {
                                    graph.addEdge(graph.vertices[i * columns + j], graph.vertices[k * columns + l], 0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    

struct SudokuConnections{

    Graph<int> graph;
    int rows = 9;
    int columns = 9;
    int total_blocks = rows * columns;
    

    SudokuConnections(){
        generateGraph(graph, total_blocks);
        connectEdges(graph);
      

    }

    ~SudokuConnections(){
         for(int i =0; i < total_blocks; i++){
            delete graph.vertices[i];
    }  
    }
};




#endif
