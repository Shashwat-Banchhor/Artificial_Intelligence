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


    std::vector<std::vector<int> > board_vec ; // as vector of vec
	// int board_vec[30][30];//new int[30][30] ;    // stores board in array formstd::vector<int> >  board_status; 
	int score;
	int alpha;
	int beeta;
	std::vector<Node*> children;
	Node* parent;
    std::string move;


    // Constructor
    Node::Node( Node * p, int s,std::string mov,std::vector<std::vector<int> > v){ //pass board_vec as arg
    	parent = p;
        score = s;
        move = mov;
        board_vec.clear();
        alpha=-10000;
        beeta=10000;
        for (int i = 0; i < v.size(); ++i)
        {
            std::vector<int> v_row;
            v_row = v.at(i);
            std::vector<int> v_to_add;
            for (int j = 0; j < v_row.size(); ++j)
            {
                int a = v_row.at(j);
                v_to_add.push_back(a);
            }
            board_vec.push_back(v_to_add);
        }
        // std::cerr <<"\nBoard vec size: "<< board_vec.size();

        
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


    std::vector<std::vector<int> > Node::get_board(){
        // std::vector<std::vector<int> > v_array ;
        // for (int i = 0; i < count; ++i)
        // {
        //     for (int i = 0; i < count; ++i)
        //     {
        //         /* code */
        //     }
        //     v_array.push_back(v_row);
        // }
        return board_vec;
        // return v_array ;// converted to vector of int 
    }


    void Node::print_board(){
        std::vector<std::vector<int> > v_array ;
        for (int i = 0; i < board_vec.size(); ++i)
        {
            std::vector<int> v;
            v = board_vec.at(i);
            for (int j = 0; j < v.size(); ++j)
            {
                if (v.at(j)==0)
                {
                    std::cerr << "..";
                }
                else{
                    if (v.at(j)>0){
                        std::cerr << "+"<< v.at(j);
                    }
                    else{
                        std::cerr << v.at(j);
                    }
                }
                std::cerr << " ";
            }
            std::cerr << "\n";
            
        }
        
        // return v_array ;// converted to vector of int 
    }
   













