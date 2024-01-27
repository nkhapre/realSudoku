#ifndef SUDOKU_H
#define SUDOKU_H
#include "ArrayList.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "Graph.h"
#include "Vertex.h"
#include <vector>
#include <unordered_map>

struct SudokuConnections{

    Graph<int> graph;
    int rows = 9;
    int columns = 9;
    int total_blocks = rows * columns;

    

    SudokuConnections(){
        generateGraph(graph, total_blocks);
        connectEdges();
      

    }

    //makes a graph with 81 vertices
    template <class T>
    void generateGraph(Graph<T>& graph, int amount){
        for(int i =1; i <= amount; i++){
            Vertex<T>* newVertex =  new Vertex<T>(i);
            graph.addVertex(newVertex);
        }

    }

   
    void connectEdges() {
        auto matrix = getGridMatrix();
        std::unordered_map<int, std::unordered_map<std::string, std::vector<int> > > headConnections;

        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                int head = matrix[row][col];
                auto connections = whatToConnect(matrix, row, col);
                headConnections[head] = connections;
            }
        }

        connectThose(headConnections);
    }

    void connectThose(const std::unordered_map<int, std::unordered_map<std::string, std::vector<int> > >& headConnections) {
        for (const auto& entry : headConnections) {
        int head = entry.first;
        const auto& connections = entry.second;
        for (const auto& pair : connections) {
            const auto& vertices = pair.second;
            for (int v : vertices) {
                graph.addEdge(graph.vertices[head - 1], graph.vertices[v - 1], 0);  // Adjust indices if needed
            }
        }
    }
}

    std::unordered_map<std::string, std::vector<int> > whatToConnect(const std::vector<std::vector<int> >& matrix, int rows, int cols) {
        std::unordered_map<std::string, std::vector<int> > connections;

        std::vector<int> row;
        std::vector<int> col;
        std::vector<int> block;

        // ROWS
        for (int c = cols + 1; c < 9; ++c) {
            row.push_back(matrix[rows][c]);
        }
        connections["rows"] = row;

        // COLS 
        for (int r = rows + 1; r < 9; ++r) {
            col.push_back(matrix[r][cols]);
        }
        connections["cols"] = col;

        // BLOCKS
        if (rows % 3 == 0) {
            if (cols % 3 == 0) {
                for (int offset_r = 1; offset_r < 3; ++offset_r) {
                    for (int offset_c = 1; offset_c < 3; ++offset_c) {
                        block.push_back(matrix[rows + offset_r][cols + offset_c]);
                    }
                }
            }
            // Add similar blocks for other cases...
        }
        connections["blocks"] = block;

        return connections;
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

    std::vector<int> allIds;

    ~SudokuConnections(){
         for(int i =0; i < total_blocks; i++){
            delete graph.vertices[i];
    }  
    }
};




#endif
