// #ifndef BOARDDB_BOARD_H
// #define BOARDDB_BOARD_H



using namespace std; 
#ifndef NODE_H
#define NODE_H
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class Node 
{ 
    
    public: 
  

	// int board_array[30][30];//new int[30][30] ;    // stores board in array formstd::vector<int> >  board_status; 
	int score;
	int alpha;
	int beeta;
	std::vector<Node*> children;
	Node * parent;
    std::string move;


    // Constructor
    Node(Node * p ,int s,std::string move);
    
  
    // Member Functions() 
    int utility(); 

    Node* get_parent();

    void add_children(Node* c);

    bool isTerminal();

    int get_alpha();
    void set_alpha(int a );

    int get_beta();
    void set_beta(int b);

    int get_score();

    std::string get_move();
   
};




#endif







