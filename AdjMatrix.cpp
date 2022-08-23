//
// File:   AdjMatrix.cpp
// Author: Nicholas White
// Purpose:
// Adjacency Matrix implementation of a graph class
// 
//
#include <iostream>
#include <vector>
#include <stack>
#include <list>


using namespace std;

template <class ValueType>
class Adj_Matrix {
private:

    vector<vector<bool>> Graph_Matrix;
    vector<ValueType> position;

    int findnode(ValueType Target_NodeValue) {
        int location = 0;
        for (ValueType node : position) {
            if (node == Target_NodeValue)
                return location;
            location++;
        }
        return -1;
    }

public:

    Adj_Matrix() {
        Graph_Matrix.resize(0);
        position.resize(0);
    }

    bool adjacent(ValueType node1_Value, ValueType node2_Value) {
        int node1, node2;
        node1 = findnode(node1_Value);
        node2 = findnode(node2_Value);

        if (node1 == -1 || node2 == -1)
            return false;

        return Graph_Matrix.at(node1).at(node2);
    }

    vector<ValueType> neighbors(ValueType node1_Value) {
        vector<ValueType>* Neighbor_List = new vector<ValueType>();
        Neighbor_List->resize(0);
        int node1 = findnode(node1_Value);

        if (node1 == -1)
            return *Neighbor_List;

        for (ValueType node : position) {
            if (adjacent(node1_Value, node) && node != node1_Value) {
                Neighbor_List->resize(Neighbor_List->size() + 1);
                Neighbor_List->at(Neighbor_List->size() - 1) = node;
            }
        }
        return *Neighbor_List;
    }

    void addEdge(ValueType source, ValueType dest) {
        int node1, node2;
        node1 = findnode(source);
        node2 = findnode(dest);

        if (node1 == -1 || node2 == -1)
            return;
        
        Graph_Matrix.at(node1).at(node2) = true;
    }

    void addNode(ValueType NewNode_Value) {
        int node1 = findnode(NewNode_Value);
        
        if (node1 != -1)
            return;
        
        position.resize(position.size() + 1);
        position.at(position.size() - 1) = NewNode_Value;
        Graph_Matrix.resize(Graph_Matrix.size() + 1);
        for (int location = 0; location < Graph_Matrix.size(); location++) {
            Graph_Matrix.at(location).resize(Graph_Matrix.size());
            Graph_Matrix.at(location).at(Graph_Matrix.size() - 1) = false;
        }
        Graph_Matrix.at(position.size() - 1).at(position.size() - 1) = true;
        return;
    }

    void deleteEdge(ValueType source, ValueType dest) {
        int node1, node2;
        node1 = findnode(source);
        node2 = findnode(dest);

        if (node1 == -1 || node2 == -1)
            return;

        if (node1 == node2)
            return;

        Graph_Matrix.at(node1).at(node2) = false;
        return;
    }

    void deleteNode(ValueType Delete_NodeValue) {
        int node1 = findnode(Delete_NodeValue);
        int previous = 0;
        ValueType lastnode = position.at(position.size() - 1);

        if (node1 == -1)
            return;
     
        if (lastnode != node1) {
            position.at(node1) = lastnode;
            for (int location = 0; location < Graph_Matrix.size() - 1; location++) {
                if (location >= node1) {
                    Graph_Matrix.at(node1).at(location) = Graph_Matrix.at(position.size() - 1).at(location + 1);
                    Graph_Matrix.at(location).at(node1) = Graph_Matrix.at(location + 1).at(position.size() - 1);
                }
                else {
                    Graph_Matrix.at(node1).at(location) = Graph_Matrix.at(position.size() - 1).at(location);
                    Graph_Matrix.at(location).at(node1) = Graph_Matrix.at(location).at(position.size() - 1);
                }
            }
        }

        position.resize(position.size() - 1);
        Graph_Matrix.resize(Graph_Matrix.size() - 1);
        for (int location = 0; location < Graph_Matrix.size(); location++) {
            Graph_Matrix.at(location).resize(Graph_Matrix.size());
        }

        return;
    }
};

