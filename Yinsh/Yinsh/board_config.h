


// using namespace std; 
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "node.h"
class Board 
{ 
    
    public: 
  
    // int no_of_hexagons ;
    // std::vector<std::vector<int> >  board_status;
    int no_of_hexagons ;
    int discs_req_in_line_to_win;
    int max_rings_to_remove;
    int rings_with_each_player;
   
    std::vector<std::vector<int> >  board_status;  // stores board in hexagon form
    
    int board_array[30][30];//new int[30][30] ;    // stores board in array form

    int my_ring[10];     	   // stores position (x,y) of my rings  
    int computers_ring[10];    // stores position (x,y) of opponents rings 

    int ring_count;
    int ring_removed; 

    // Constructor
    Board(int N , int M , int K, int L);
    
  
    // Member Functions() 
    void print(); 

    void print2();

    void update(int player,string s,int temp);

    void reverse_update(int player,int x1,int y1,int x2,int y2,std::string mo);

    std::string play();

     bool check_five(int val,int a1,int a2,int a3,int a4,int a5); 

     std::vector<int>  find_five_consecutive(int ht);

     std::vector<int> find_which_ring_to_remove(int ht);

     std::vector<int> find_which_ring_to_remove_board_array(int ht);



    std::vector<int> change_coordinates(int to_convert, int x, int y); 

    void remove_five(string s);


    Node* tree();

    std::string mini_max_decision();

    Node* min_val( Node* node );

    Node* max_val( Node* node );

    std::vector<int> find_five_consecutive_board_array(int ht);

    std::string anything_to_remove_before_proceeding();

    int how_good_disc_is(int x,int y);

    int my_ring_on_blank(int x,int y);

    int how_good_ring_is(int x,int y);

    int eval_five(int b1,int a1,int a2,int a3,int a4,int a5,int b2,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,int x5,int y5);

    int each_ring(int x, int y);

    int evaluate_heuristic();


};











