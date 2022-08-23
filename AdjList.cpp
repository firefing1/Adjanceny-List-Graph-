//
// File:   AdjList.cpp
// Author: Nicholas White
// Purpose:
// Adjacency list implementation of a graph class
// 
//
#include <iostream>
#include <vector>
#include <stack>
#include <list>


using namespace std;

template <class ValueType>
class Adj_List {
private:

    struct head_tail {
        ValueType value;
        list<int>* tailing_list;
    };

    vector<head_tail> adjlist;

    int findnode(ValueType node1_Value) {
        int cnt = 0;
        for (head_tail location : adjlist) {
            if (location.value == node1_Value)
                return cnt;
            cnt++;
        }
        return -1;
    }

public:
    Adj_List() {
        adjlist.resize(0);
    }
    bool adjacent(ValueType node1_Value, ValueType node2_Value) {
        int node1, node2;
        node1 = findnode(node1_Value);
        node2 = findnode(node2_Value);

        if (node1 == -1 || node2 == -1)
            return false;

        for (int node : *(adjlist.at(node1).tailing_list)) {
            if (node == node2)
                return true;
        }
        return false;
    }

    vector<ValueType> neighbors(ValueType node1_Value) {
        int node1 = findnode(node1_Value);
        vector<ValueType>* return_vector = new vector<ValueType>();

        if (node1 == -1)
            return *return_vector;

        for (int node : *(adjlist.at(node1).tailing_list)) {
            return_vector->resize(return_vector->size() + 1);
            return_vector->at(return_vector->size() - 1) = adjlist[node].value;
        }
        return *return_vector;
    }
    void addEdge(ValueType source, ValueType dest) {
        int node1, node2;
        node1 = findnode(source);
        node2 = findnode(dest);
        
        if (node1 == -1 || node2 == -1)
            return;
           
        if (!adjacent(source, dest)) {
            adjlist[node1].tailing_list->push_back(node2);
        }
        return;
    }
    void addNode(ValueType NewNode_Value) {
        int node1 = findnode(NewNode_Value);

        if (node1 != -1)
            return;

        adjlist.resize(adjlist.size() + 1);
        adjlist[adjlist.size() - 1].value = NewNode_Value;
        adjlist[adjlist.size() - 1].tailing_list = new list<int>();
        return;
    }
    void deleteEdge(ValueType source, ValueType dest) {
        int node1 = findnode(source);
        int node2 = findnode(dest);

        if (node1 == -1)
            return;

        adjlist[node1].tailing_list->remove(node2);
        return;
    }
    void deleteNode(ValueType Delete_NodeValue) {
        int node1 = findnode(Delete_NodeValue);

        if (node1 == -1)
            return;
        bool k;
        int lastnode = adjlist.size()-1;
        for (head_tail list : adjlist) {
            list.tailing_list->remove(node1);
            k = false;
            for (int node : *(list.tailing_list)) {
                if (node == lastnode)
                    k = true;
            }
            if (k) {
                list.tailing_list->remove(lastnode);
                list.tailing_list->push_back(node1);
            }
        }

        adjlist[node1].value = adjlist[lastnode].value;
        adjlist[node1].tailing_list = adjlist[lastnode].tailing_list;
        adjlist.resize(adjlist.size() - 1);
        return;
    }
};

