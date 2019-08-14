


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
   
    
    int board_array[30][30];//new int[30][30] ;    // stores board in array form

   

    // Constructor
    Board(int N , int M , int K, int L);
    
  
    // Member Functions() 
    void print(); 

    void print2();

    void update(int player,string s,int temp);

    void reverse_update(int player,int x1,int y1,int x2,int y2,std::string mo);

    std::string play(int N,int K);

     bool check_five(int val,int a1,int a2,int a3,int a4,int a5); 

     bool check_six(int val,int a1,int a2,int a3,int a4,int a5,int a6); 

    std::vector<int>  find_K_consecutive_temp_board_array(int N,int K,int ht);

     std::vector<int> find_which_ring_to_remove(int N,int K,int ht);

     std::vector<int> find_which_ring_to_remove_board_array(int N,int K,int ht);



    std::vector<int> change_coordinates(int to_convert, int x, int y); 

    void remove_five(string s);


    Node* tree(int N,int K);

    std::string mini_max_decision();

    Node* min_val( Node* node ,int alpha, int beta);

    Node* max_val( Node* node ,int alpha, int beta);

    std::vector<int> find_K_consecutive_board_array(int N,int K,int ht);

    std::string anything_to_remove_before_proceeding(int N,int K);

    int how_good_disc_is(int N,int x,int y);

    int my_ring_on_blank(int N,int x,int y,int player_type);

    int how_good_ring_is(int N,int x,int y);

    std::vector<int>  eval_five(int N,int check,int ht,int b1,int a1,int a2,int a3,int a4,int a5,int b2,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,int x5,int y5);
    std::vector<int>  eval_six(int N,int check,int ht,int b1,int a1,int a2,int a3,int a4,int a5,int a6,int b2,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,int x5,int y5,int x6,int y6);

    int each_ring(int N,int x, int y);

    std::vector<int>  evaluate_heuristic(int N,int K,int ht);


};











