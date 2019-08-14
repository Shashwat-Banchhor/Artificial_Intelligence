// #ifndef BOARDDB_BOARD_H
// #define BOARDDB_BOARD_H



using namespace std; 
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "node.h"



	// int board_array[30][30];//new int[30][30] ;    // stores board in array formstd::vector<int> >  board_status; 
	int score;
	int alpha;
	int beeta;
	std::vector<Node*> children;
	Node* parent;
    std::string move;


    // Constructor
    Node::Node( Node * p, int s,std::string mov){
    	parent = p;
        score = s;
        move = mov;
        
    }
    
  
    // Member Functions() 
    int Node::utility(){
        return score;
    	// return heuristic(Node);
    }

    Node* Node::get_parent(){
    	return parent;
    }


    void Node::add_children(Node* c){
    	children.push_back(c);
    }

    bool Node::isTerminal(){
        if (children.size()==0){
            return true;
        }
        return false;
    }

    int Node::get_alpha(){
    	return alpha;
    }
    void Node::set_alpha(int a){
    	alpha = a;
    }

    int Node::get_beta(){
    	return beeta;
    }
    void Node::set_beta(int b){
    	beeta = b;
    }

    int Node::get_score(){
    	return score;
    }

    std::string Node::get_move(){
        return move;
    }

   













