// #ifndef NODE_H
// #define NODE_H
#include "board_config.h"
#include "node.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>


    // account for RS RE X .. S M ..  moves dfrom other player
    // using namespace std; 

    // 2 My Ring
    // 1 My Disc
    // 0 Empty
    // -1 Opponents's Disc
    // -2 Opponents's Ring

    int no_of_hexagons ;
    int discs_req_in_line_to_win;
    int max_rings_to_remove;
    int rings_with_each_player;
    int computer_ring[5][2];
    int my_ring[5][2];


    int total_moves=0;
    int count=0;
    


    std::vector<std::vector<int> >  board_status;  // stores board in hexagon form
    
    int board_array[22][14];   //new int[22][22] ;    // stores board in array form
    int temp_board_array[22][14];

  
    

    // Constructor
    Board::Board(int N , int M , int K, int L)
    {
        // std::cerr << "abc";
        no_of_hexagons         = N;
        rings_with_each_player = M;
        discs_req_in_line_to_win  = K;
        max_rings_to_remove    = L; 

       

        
        // INITIALIZE BOARD_ARRAY
        for (int i = 0; i < 22; ++i)
        {
            for (int j = 0; j <14; ++j)
            {
                board_array[i][j] = 0;      // array
            }
            
        }
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j <2; ++j)
            {
                computer_ring[i][j] = 0;      // array
                my_ring[i][j] = 0;      // array
            }
            
        }
    }
  
    // Member Functions() 
    void Board::print() 
    { 
       

        
        for (int i = 0; i < 22; ++i)
        {
            for (int j = 0; j <14; ++j)
            {
                if (board_array[i][j] == 0)
                {
                    std::cerr << "..";

                }
                else
                {
                    if (board_array[i][j]>0){
                        std::cerr <<"+"<< board_array[i][j];
                    }
                    else
                    {
                        std::cerr << board_array[i][j];
                    }

                }
                std::cerr << "  ";
            }
            std::cerr << "\n";
        }
    } 

    void Board::print2() 
    { 
       

        
        
        for (int i = 0; i < 22; ++i)
        {
            for (int j = 0; j <14; ++j)
            {
                if (temp_board_array[i][j] == 0)
                {
                    std::cerr << "..";

                }
                else
                {
                    if (temp_board_array[i][j]>0){
                        std::cerr << "+"<<temp_board_array[i][j];
                    }
                    else{
                        std::cerr <<temp_board_array[i][j];
                    }
                }
                std::cerr << "  ";
            }
            std::cerr << "\n";
        }
    } 
   
    
    void Board::update(int player,string s,int temp)   /// make a reverse update function  to do dfs easily
    {
        if (temp==0)
        {
        // -1 Computer
        // 1 Me
            
            std::string text = s;
            // std::istream_iterator<std::string>(iss);
            std::istringstream iss(text);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),  // Move store in results
            std::istream_iterator<std::string>());


            int n = results.size(); 
         
            
            // Variables for updating coordinates in the array 
            int sel_x,sel_y,  mov_x,mov_y,  place_x,place_y, start_x,start_y, end_x,end_y, ring_x,ring_y ; 
            std::vector<int> v;

            if (results.at(0).compare("S")==0)       // Select ring
            {
            
                int sel[2];
                int mov[2];
                
                    sel[0] =  std::stoi(results.at(1));
                    sel[1] =  std::stoi(results.at(2));
                    mov[0] =  std::stoi(results.at(4));
                    mov[1] =  std::stoi(results.at(5));
                    // std::cerr << "Entered Upd";

                    // print();
                    // std::cerr << "\nboard_array 3 11"<< board_array[12][12] ; 
                    // std::cerr << "\nSelct x,y "<< sel[0] <<" " << sel[1] ;
                    // std::cerr << "\nMove x,y "<< mov[0] <<" " << mov[1] ;

                    // -------- U P D A T E   I N   T H E  A R R A Y  ---------- 

                    v = change_coordinates(0,sel[0],sel[1]);
                    sel_x = v.at(0)+11;
                    sel_y = v.at(1)+7;
                    // std::cerr << "\nCSelct x,y "<< sel_x <<" " << sel_y ;
                    // std::cerr << "\nCMove x,y "<< mov_ <<" " << mov[1] ;

                    int selected_point_should_be = board_array[sel_x][sel_y] / 2; 
                    // cerr<<selected_point_should_be <<"selected_point_should_be"<<endl;
                    board_array[sel_x][sel_y] = board_array[sel_x][sel_y] / 2; 
                    // std::cerr << "here0232";
                    v = change_coordinates(0,mov[0],mov[1]);
                    mov_x = v.at(0)+11;
                    mov_y = v.at(1)+7;

                    int moved_point_should_be = player*2;
                    board_array[mov_x][mov_y] = player * 2; 

                    ////////////////////////////////////////////////////////////////////////////////////////////////////


                    // v = change_coordinates(0,start[0],start[1]);  // remove discs start
                    start_x = sel_x-11;//sel[0];//v.at(0)+11;
                    start_y = sel_y-7;//sel[1];//v.at(1)+11;

                    // v = change_coordinates(0,end[0],end[1]);  // remove discs end
                    end_x = mov_x-11;//mov[0];//v.at(0)+11;
                    end_y = mov_y-7;//mov[1];//v.at(1)+11;
                    // std::cerr << "s_xy e_xy" << s<<":::"<<start_x << start_y << end_x << end_y ;

                    if (start_y == end_y)           // vertical line slope 0
                    {   
                        
                        

                        
                        for (int i = min(start_x,end_x); i < max(start_x,end_x)+1; i++)
                        {
                            board_array[11+i][7+start_y] = - board_array[11+i][7+start_y];
                        }
                    }
                    else if((start_x>end_x && start_y>end_y) || (start_x<end_x && start_y<end_y))  // slope 1
                    {
                        int disc_x = min(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            board_array[11+disc_x+ (i- disc_y)][7+i] = - board_array[11+disc_x+ (i- disc_y)][7+i];
                        }
                    }
                    else if((start_x>end_x && start_y<end_y) || (start_x<end_x && start_y>end_y))  // slope -1
                    {

                        int disc_x = max(start_x,end_x);
                        int disc_y = min(start_y,end_y);
                        // std::cerr << ("Enter1\n");

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            board_array[11+disc_x + disc_y - i][7+i] = - board_array[11+disc_x + disc_y - i][7+i] ;
                             // std::cerr << disc_x + disc_y - i << i << board_array[11+disc_x + disc_y - i][11+i] <<"\n";
                        }

                    }
                    else{ std::cerr << " Error in update function" ; }  

                    
                    // change the selected and move coordinates;
                    board_array[sel_x][sel_y] = selected_point_should_be;
                    board_array[mov_x][mov_y]  = moved_point_should_be;
                    // std::cerr << sel_x<<sel_y<<mov_x<<mov_y << "board" << board_array[14][16] ;

                    // std::cerr << ("checking board\n");
                    // print();
                    // std::cerr << ("checked\n");
                    

                    // std::cerr << "here345";

                // }
                if (n>=7)   // select and move ring & remove discs and ring
                {
                    int start[2];
                    int end[2];
                    int ring[2];
                    // sel[0] =  std::stoi(results.at(1));//int(char_array[1])-48;
                    // sel[1] =  std::stoi(results.at(2));//int(char_array[2])-48;
                    // mov[0] =  std::stoi(results.at(4));//int(char_array[4])-48;
                    // mov[1] = std::stoi(results.at(5));//int(char_array[5])-48;
                    start[0] =  std::stoi(results.at(7));//int(char_array[6])-48;   
                    start[1] =  std::stoi(results.at(8));//int(char_array[7])-48;
                    end[0] =  std::stoi(results.at(10));//int(char_array[8])-48;
                    end[1] = std::stoi(results.at(11));//int(char_array[9])-48;
                    ring[0] =  std::stoi(results.at(13));//int(char_array[10])-48;
                    ring[1] =  std::stoi(results.at(14));//int(char_array[11])-48;

                    

                    // -------- U P D A T E   I N   T H E  A R R A Y  ---------- 


                    // v = change_coordinates(0,sel[0],sel[1]);    // select ring
                    // sel_x = v.at(0)+11;
                    // sel_y = v.at(1)+11;

                    // board_array[sel_x][sel_y] = board_array[sel_x][sel_y] / 2; 

                    // v = change_coordinates(0,mov[0],mov[1]);    // move ring
                    // mov_x = v.at(0)+11;
                    // mov_y = v.at(1)+11;

                    // board_array[mov_x][mov_y] = player * 2; 


                    v = change_coordinates(0,start[0],start[1]);  // remove discs start
                    start_x = v.at(0);//+11;
                    start_y = v.at(1);//+11;

                    v = change_coordinates(0,end[0],end[1]);  // remove discs end
                    end_x = v.at(0);//+11;
                    end_y = v.at(1);//+11;

                    if (start_y == end_y)           // vertical line slope 0
                    {   
                        

                        for (int i = min(start_x,end_x); i < max(start_x,end_x)+1; i++)
                        {
                            board_array[11+i][7+start_y] = 0;
                        }
                    }
                    else if((start_x>end_x && start_y>end_y) || (start_x<end_x && start_y<end_y))  // slope 1
                    {
                        int disc_x = min(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            board_array[11+disc_x+ (i- disc_y)][7+i] = 0;
                        }
                    }
                    else if((start_x>end_x && start_y<end_y) || (start_x<end_x && start_y>end_y))  // slope -1
                    {

                        int disc_x = max(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            board_array[11+disc_x + disc_y - i][7+i] = 0;
                        }

                    }
                    else{ std::cerr << " Error in update function" ; }  

                  
                    v = change_coordinates(0,ring[0],ring[1]);  // remove ring
                    ring_x = v.at(0)+11;
                    ring_y = v.at(1)+7;

                    // board_array[mov_x][mov_y] = 0; 
                    board_array[ring_x][ring_y] = 0;


                }

            }
            else if (results.at(0).compare("P")==0)  // Place Ring  
            {
                // std::cerr << "Entered";
                int place[2];
                place[0] =  std::stoi(results.at(1));//int(char_array[1]) -48;
                // std::cerr << place[0]<<"\n";
                place[1] = std::stoi(results.at(2));//int(char_array[2]) -48;
                // std::cerr << place[1];
                std::vector<int> vect ;

                


                // -------- U P D A T E   I N   T H E  A R R A Y  ---------- 

                std::vector<int> v = change_coordinates(0,place[0],place[1]);
                place_x = v.at(0)+11;
                place_y = v.at(1)+7;

                
                board_array[place_x][place_y] = player*2; 
               

            }
            
        }

        else if(temp==1)
        {

        // -1 Computer
        // 1 Me
 
        

            
            std::string text = s;
            // std::istream_iterator<std::string>(iss);
            std::istringstream iss(text);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),  // Move store in results
            std::istream_iterator<std::string>());

         

            int n = results.size(); 
         
         
            
            std::vector<int> v_dash = change_coordinates(0,std::stoi(results.at(1)),std::stoi(results.at(2)));
            
            if (temp_board_array[v_dash.at(0)+11][v_dash.at(1)+7] != 0){    
                player = temp_board_array[v_dash.at(0)+11][v_dash.at(1)+7]/2;
            }

            
            int sel_x,sel_y,  mov_x,mov_y,  place_x,place_y, start_x,start_y, end_x,end_y, ring_x,ring_y ; 
            std::vector<int> v;

            if (results.at(0).compare("S")==0)       // Select ring
            {
            
                int sel[2];
                int mov[2];
                // if (n<7)   // select and move ring  // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS 
                // {
                    
                    sel[0] =  std::stoi(results.at(1));
                    sel[1] =  std::stoi(results.at(2));
                    mov[0] =  std::stoi(results.at(4));
                    mov[1] =  std::stoi(results.at(5));

                    

                    // -------- U P D A T E   I N   T H E  A R R A Y  ---------- 

                    v = change_coordinates(0,sel[0],sel[1]);
                    sel_x = v.at(0)+11;
                    sel_y = v.at(1)+7;

                    int selected_point_should_be = temp_board_array[sel_x][sel_y] / 2; ; 
                    temp_board_array[sel_x][sel_y] = temp_board_array[sel_x][sel_y] / 2; 

                    v = change_coordinates(0,mov[0],mov[1]);
                    mov_x = v.at(0)+11;
                    mov_y = v.at(1)+7;

                    int moved_point_should_be = selected_point_should_be*2;
                    temp_board_array[mov_x][mov_y] = selected_point_should_be * 2; 

                    ////////////////////////////////////////////////////////////////////////////////////////////////////


                    // v = change_coordinates(0,start[0],start[1]);  // remove discs start
                    start_x = sel_x-11;
                    start_y = sel_y-7;

                    // v = change_coordinates(0,end[0],end[1]);  // remove discs end
                    end_x = mov_x-11;
                    end_y = mov_y-7;

                    if (start_y == end_y)           // vertical line slope 0
                    {   
                        
                        

                        
                        for (int i = min(start_x,end_x); i < max(start_x,end_x)+1; i++)
                        {
                            temp_board_array[11+i][7+start_y] = - temp_board_array[11+i][7+start_y];
                        }
                    }
                    else if((start_x>end_x && start_y>end_y) || (start_x<end_x && start_y<end_y))  // slope 1
                    {
                        int disc_x = min(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            temp_board_array[11+disc_x+ (i- disc_y)][7+i] = - temp_board_array[11+disc_x+ (i- disc_y)][7+i];
                        }
                    }
                    else if((start_x>end_x && start_y<end_y) || (start_x<end_x && start_y>end_y))  // slope -1
                    {

                        int disc_x = max(start_x,end_x);
                        int disc_y = min(start_y,end_y);
                        // std::cerr << ("Enter1\n");

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            temp_board_array[11+disc_x + disc_y - i][7+i] = - temp_board_array[11+disc_x + disc_y - i][7+i] ;
                             // std::cerr << disc_x + disc_y - i << i << temp_board_array[11+disc_x + disc_y - i][11+i] <<"\n";
                        }

                    }
                    else{ std::cerr << " Error in update function" ; }  
                    
                    // change the selected and move coordinates;
                    temp_board_array[sel_x][sel_y] = selected_point_should_be;
                    temp_board_array[mov_x][mov_y]  = moved_point_should_be;
                    
                   
                if(n>7)//else   // select and move ring & remove discs and ring
                {
                    int start[2];
                    int end[2];
                    int ring[2];
                    // std::cerr << "chk1\n";
                    start[0] =  std::stoi(results.at(7));
                    start[1] =  std::stoi(results.at(8));
                    end[0] =  std::stoi(results.at(10));
                    end[1] = std::stoi(results.at(11));
                    ring[0] =  std::stoi(results.at(13));
                    ring[1] =  std::stoi(results.at(14));

                

                  

                    
                    v = change_coordinates(0,start[0],start[1]);  
                    start_x = v.at(0);
                    start_y = v.at(1);


                    v = change_coordinates(0,end[0],end[1]);  // remove discs end
                    end_x = v.at(0);
                    end_y = v.at(1);
                    
                    if (start_y == end_y)           // vertical line slope 0
                    {   
                        

                        for (int i = min(start_x,end_x); i < max(start_x,end_x)+1; i++)
                        {
                            temp_board_array[11+i][7+start_y] = 0;
                        }
                    }
                    else if((start_x>end_x && start_y>end_y) || (start_x<end_x && start_y<end_y))  // slope 1
                    {
                        int disc_x = min(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            temp_board_array[11+disc_x+ (i- disc_y)][7+i] = 0;
                        }
                    }
                    else if((start_x>end_x && start_y<end_y) || (start_x<end_x && start_y>end_y))  // slope -1
                    {

                        int disc_x = max(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            temp_board_array[11+disc_x + disc_y - i][7+i] = 0;
                        }

                    }
                    else{ std::cerr << " Error in update function" ; }  

                  


                    v = change_coordinates(0,ring[0],ring[1]);  // remove ring
                    ring_x = v.at(0)+11;
                    ring_y = v.at(1)+7;

                    temp_board_array[ring_x][ring_y] = 0; 


                }

            }
            else if (results.at(0).compare("P")==0)  // Place Ring  
            {
                
                int place[2];
                place[0] =  std::stoi(results.at(1));
                
                place[1] = std::stoi(results.at(2));
                
                std::vector<int> vect ;


                std::vector<int> v = change_coordinates(0,place[0],place[1]);
                place_x = v.at(0)+11;
                place_y = v.at(1)+7;

                
                temp_board_array[place_x][place_y] = player*2; 
               
                

            }
        
        }

    
        
    }

    std::string Board::anything_to_remove_before_proceeding(int N,int K){
    



                std::string s_d = "";
                std::vector<int> v = find_K_consecutive_board_array(N,K,0);
                
                print();
                std::vector<int> v_prime;



                if (v.size()!=0)
                {
                                s_d.append(" ");
                                s_d.append("RS");

                                s_d.append(" ");
                                s_d.append(std::to_string(v.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v.at(1)));

                                s_d.append(" ");
                                s_d.append("RE");

                                s_d.append(" ");
                                s_d.append(std::to_string(v.at(2)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v.at(3)));

                                s_d.append(" ");
                                s_d.append("X");

                                    v_prime = find_which_ring_to_remove_board_array(N,K,0);
                                    print();
                                    // std::cerr << "this is after ring rem check"; 

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(1)));
                                s_d.append(" ");

                                

                            



                    int start[2];
                    int end[2];
                    int ring[2];

                    int start_x,start_y, end_x,end_y, ring_x,ring_y ; 
                  
                    // mov[1] = std::stoi(results.at(5));//int(char_array[5])-48;
                    start[0] =  v.at(0);//std::stoi(results.at(1));//int(char_array[6])-48;   
                    start[1] =  v.at(1);//std::stoi(results.at(2));//int(char_array[7])-48;
                    end[0] =  v.at(2);//std::stoi(results.at(4));//int(char_array[8])-48;
                    end[1] = v.at(3);//std::stoi(results.at(5));//int(char_array[9])-48;
                    ring[0] =  v_prime.at(0);//std::stoi(results.at(7));//int(char_array[10])-48;
                    ring[1] =  v_prime.at(1);//std::stoi(results.at(8));//int(char_array[11])-48;

                

                    v = change_coordinates(0,start[0],start[1]);  // remove discs start
                    start_x = v.at(0);//+11;
                    start_y = v.at(1);//+11;

                    v = change_coordinates(0,end[0],end[1]);  // remove discs end
                    end_x = v.at(0);//+11;
                    end_y = v.at(1);//+11;

                    if (start_y == end_y)           // vertical line slope 0
                    {   
                        

                        for (int i = min(start_x,end_x); i < max(start_x,end_x)+1; i++)
                        {
                            board_array[11+i][7+start_y] = 0;
                        }
                    }
                    else if((start_x>end_x && start_y>end_y) || (start_x<end_x && start_y<end_y))  // slope 1
                    {
                        int disc_x = min(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            board_array[11+disc_x+ (i- disc_y)][7+i] = 0;
                        }
                    }
                    else if((start_x>end_x && start_y<end_y) || (start_x<end_x && start_y>end_y))  // slope -1
                    {

                        int disc_x = max(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            board_array[11+disc_x + disc_y - i][7+i] = 0;
                        }

                    }
                    
                    
                    




                    v = change_coordinates(0,ring[0],ring[1]);  
                    ring_x = v.at(0)+11;
                    ring_y = v.at(1)+7;

                    board_array[ring_x][ring_y] = 0;
                   
                }


                return s_d;



    }



    void Board::reverse_update(int player,int x1,int y1,int x2,int y2,std::string mo)   /// make a reverse update function  to do dfs easily  /// rings are changing globLALY AT EACH STEP
    {
        // -1 Computer
        // 1 Me
 

        std::string text = mo;
        std::istringstream iss(text);
        std::vector<std::string> results((std::istream_iterator<std::string>(iss)),  // Move store in results
        std::istream_iterator<std::string>());



        int n = results.size(); 
     
        int sel_x,sel_y,  mov_x,mov_y,  place_x,place_y, start_x,start_y, end_x,end_y, ring_x,ring_y ; 
        std::vector<int> v;

        int selected_point_should_be ;
        int sel[2];
        int mov[2];
            // if (n<7)   // select and move ring  // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS 
            //  {
                
                std::vector<int> v2;std::vector<int> v1;
                v2 = change_coordinates(0,std::stoi(results.at(4)),std::stoi(results.at(5)));  // moved here
                v1 = change_coordinates(0,std::stoi(results.at(1)),std::stoi(results.at(2)));  // selected this

                sel[0] = v2.at(0);
                sel[1] = v2.at(1);
                mov[0] = v1.at(0);
                mov[1] = v1.at(1);
               
            
                sel_x = sel[0]+11;
                sel_y = sel[1]+7;

                selected_point_should_be = temp_board_array[sel_x][sel_y];// / 2; ;
                int pl=player;
                player = selected_point_should_be/2;


                if(n>=7)   // select and move ring & remove discs and ring
                {
                    
                    int start[2];
                    int end[2];
                    int ring[2];
                    
                    start[0] =  std::stoi(results.at(7));
                    start[1] =  std::stoi(results.at(8));
                    end[0] =  std::stoi(results.at(10));
                    end[1] = std::stoi(results.at(11));
                    ring[0] =  std::stoi(results.at(13));
                    ring[1] =  std::stoi(results.at(14));

                    v = change_coordinates(0,ring[0],ring[1]);  // remove ring
                    ring_x = v.at(0)+11;
                    ring_y = v.at(1)+7;

                    temp_board_array[ring_x][ring_y] = 2*pl;

                    selected_point_should_be = 2*player;//temp_board_array[sel_x][sel_y];// / 2; ;
                    player = selected_point_should_be/2;

                    

                    v = change_coordinates(0,start[0],start[1]);  // remove discs start
                    start_x = v.at(0);
                    start_y = v.at(1);

                    v = change_coordinates(0,end[0],end[1]);  // remove discs end
                    end_x = v.at(0);
                    end_y = v.at(1);

                    if (start_y == end_y)           // vertical line slope 0
                    {   
                        

                        for (int i = min(start_x,end_x); i < max(start_x,end_x)+1; i++)
                        {
                            temp_board_array[11+i][7+start_y] = selected_point_should_be/2;
                        }
                    }
                    else if((start_x>end_x && start_y>end_y) || (start_x<end_x && start_y<end_y))  // slope 1
                    {
                        int disc_x = min(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            temp_board_array[11+disc_x+ (i- disc_y)][7+i] = selected_point_should_be/2;
                        }
                    }
                    else if((start_x>end_x && start_y<end_y) || (start_x<end_x && start_y>end_y))  // slope -1
                    {

                        int disc_x = max(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            temp_board_array[11+disc_x + disc_y - i][7+i] = selected_point_should_be/2;
                        }

                    }
                    else{ std::cerr << " Error in update function" ; }  

                   
                    


                }

           

                // -------- U P D A T E   I N   T H E  A R R A Y  ---------- 

                

                temp_board_array[sel_x][sel_y] = temp_board_array[sel_x][sel_y] / 2; 
                
                mov_x = mov[0]+11;
                mov_y = mov[1]+7;
                


                int moved_point_should_be = selected_point_should_be;//player*2;
                temp_board_array[mov_x][mov_y] = selected_point_should_be;//player * 2; 

                ////////////////////////////////////////////////////////////////////////////////////////////////////


                 // v = change_coordinates(0,start[0],start[1]);  // remove discs start
                    start_x = sel_x-11;
                    start_y = sel_y-7;

                    // v = change_coordinates(0,end[0],end[1]);  // remove discs end
                    end_x = mov_x-11;
                    end_y = mov_y-7;

                
                if (start_y == end_y)           // vertical line slope 0
                {   
                   for (int i = min(start_x,end_x); i < max(start_x,end_x)+1; i++)
                    {
                        temp_board_array[11+i][7+start_y] = - temp_board_array[11+i][7+start_y];
                    }
                }
                else if((start_x>end_x && start_y>end_y) || (start_x<end_x && start_y<end_y))  // slope 1
                {
                    int disc_x = min(start_x,end_x);
                    int disc_y = min(start_y,end_y);

                    for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                    {
                        temp_board_array[11+disc_x+ (i- disc_y)][7+i] = - temp_board_array[11+disc_x+ (i- disc_y)][7+i];
                    }
                }
                else if((start_x>end_x && start_y<end_y) || (start_x<end_x && start_y>end_y))  // slope -1
                {

                    int disc_x = max(start_x,end_x);
                    int disc_y = min(start_y,end_y);

                    for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                    {
                        temp_board_array[11+disc_x + disc_y - i][7+i] = -temp_board_array[11+disc_x + disc_y - i][7+i] ;
                    }

                }
                else{ std::cerr << " Error in update function" ; }  
                
                
                temp_board_array[sel_x][sel_y] = 0;//selected_point_should_be;
                temp_board_array[mov_x][mov_y]  = selected_point_should_be;//moved_point_should_be;

               
        
    }

 

    //add (-11,-11), give input, get output, add 11,11 
    std::vector<int> Board::change_coordinates(int to_convert, int x, int y)    // outputs the coordintes with shifted origin
    {
        std::vector<int> v ;
        int x_cord,y_cord;
        if (to_convert ==0) // convert from hexagons to array
        {
            // x : Hexagon number
            // y : Point in Hexagon

            if (x==0)
            {
                v.push_back(0);
                v.push_back(0);
                return v;
            }

            if (y/x==0)
            {
                x_cord= -2*x + y;
                y_cord = y;
                v.push_back(x_cord);                
                v.push_back(y_cord);  
            }
            else if (y/x==1)
            {
                x_cord =  2*(y - x) - x ;
                y_cord = x;
                v.push_back(x_cord);                
                v.push_back(y_cord);  
            }
            else if (y/x==2)
            {
                x_cord =  x+y-2*x; 
                y_cord =  3*x-y ;
                v.push_back(x_cord);                
                v.push_back(y_cord);  
            }
            else if (y/x==3)
            {
                x_cord = 2*x-(y-3*x) ;
                y_cord =  -(y-3*x)  ;
                v.push_back(x_cord);                
                v.push_back(y_cord);  
            }
            else if (y/x==4)
            {
                x_cord =   x- (y - 4*x)*2; 
                y_cord =  -(x);
                v.push_back(x_cord);                
                v.push_back(y_cord);  
            }
            else if (y/x==5)
            {
                x_cord =  -(x + y-5*x) ;
                y_cord =   -(6*x-y);
                v.push_back(x_cord);                
                v.push_back(y_cord);  
            }

        }
        else                // convert from array to hexagon
        {
            int z,k ; 
            if (x<=0 && y>=0 && -x>=y)      // 2nd Octant
            {
                z = y;   // z=y
                k = ((-x)+ (-y))/2  ;
                v.push_back(z+k);   // Hexagon Number
                v.push_back(z);     // Point in Hexagon
            }
            else if (x<=y && y>=(-x)) // 1st and 8th Octant
            {
                v.push_back(y);                // Hexagon Number
                v.push_back((y+x)/2 + y);     // Point in Hexagon
            }
            else if (x>=y && x>=-y) // 6th and 7th Octant
            {
                z = abs(y);
                k = (x-z)/2;
                v.push_back(z+k);           // Hexagon Number
                v.push_back(3*(z+k)-(y));     // Point in Hexagon

            }
            else if (-y>=x && -y>=-x) // 4th and 5th Octant
            {
                v.push_back(-y);   // Hexagon Number
                v.push_back(4*(-y) + (-y-x)/2 );     // Point in Hexagon
            }
            else if (-x>=-y && x<=0 && y<=0 )      // 3rd Octant
            {
                z = -y;   
                k = ((-x)+ (-z))/2  ;
                v.push_back(z+k);   // Hexagon Number
                v.push_back(6*(z+k) - z);     // Point in Hexagon
            }
        } 
        return v;
    }

    std::string Board::play(int N,int K) // returns the move to be played
    {
        
        
        std::string move;
        std::vector<int> v;
        total_moves ++;
        std::cerr << total_moves;
        
        if(total_moves==1)
        {
            
            
            int i = N-1;
            int j = N;
            v = change_coordinates(0,N-1,0);
            if (board_array[v.at(0)+11][v.at(1)+7] == 0)
            {
                if(N==5){    
                    move = "P 4 0";
                }
                else{    
                    move = "P 5 0";
                }
            }
            else
            {
                v = change_coordinates(0,i,j);
                while(board_array[v.at(0)+11][v.at(1)+7] != 0)
                {
                    // i++;
                    j++;
                }
                move = "P";
                move.append(" ");
                move.append(std::to_string(i));
                move.append(" ");
                move.append(std::to_string(j));
            }
            

            update(-1,move,0);
        }
        if(total_moves==2)
        {
            
            
            int i = N-1;
            int j = N+1;
            v = change_coordinates(0,N-1,3);
            if (board_array[v.at(0)+11][v.at(1)+7] == 0)
            {
                if(N==5){    
                    move = "P 4 3";
                }
                else{    
                    move = "P 5 3";
                }
            }
            else
            {
                v = change_coordinates(0,i,j);
                while(board_array[v.at(0)+11][v.at(1)+7] != 0)
                {
                    // i++;
                    j++;
                }
                move = "P";
                move.append(" ");
                move.append(std::to_string(i));
                move.append(" ");
                move.append(std::to_string(j));
            }
            

            update(-1,move,0);
        }
        if(total_moves==3)
        {
            
            
            int i = N-1;
            int j = N+2;
            v = change_coordinates(0,N-1,1);
            if (board_array[v.at(0)+11][v.at(1)+7] == 0)
            {
               if(N==5){    
                    move = "P 4 1";
                }
                else{    
                    move = "P 5 1";
                }
            }
            else
            {
                v = change_coordinates(0,i,j);
                while(board_array[v.at(0)+11][v.at(1)+7] != 0)
                {
                    // i++;
                    j++;
                }
                move = "P";
                move.append(" ");
                move.append(std::to_string(i));
                move.append(" ");
                move.append(std::to_string(j));
            }
            

            update(-1,move,0);
        }
        if(total_moves==4)
        {
            
            
            int i = N-1;
            int j = N+3;
            v = change_coordinates(0,N-1,4);
            if (board_array[v.at(0)+11][v.at(1)+7] == 0)
            {
                if(N==5){    
                    move = "P 4 4";
                }
                else{    
                    move = "P 5 4";
                }
            }
            else
            {
                v = change_coordinates(0,i,j);
                while(board_array[v.at(0)+11][v.at(1)+7] != 0)
                {
                    // i++;
                    j++;
                }
                move = "P";
                move.append(" ");
                move.append(std::to_string(i));
                move.append(" ");
                move.append(std::to_string(j));
            }
            

            update(-1,move,0);
        }
        if(total_moves==5)
        {
            
            
            int i =N-1;
            int j = N+4;
            v = change_coordinates(0,N-1,2);
            if (board_array[v.at(0)+11][v.at(1)+7] == 0)
            {
                 if(N==5){    
                    move = "P 4 2";
                }
                else{    
                    move = "P 5 2";
                }
            }
            else
            {
                v = change_coordinates(0,i,j);
                while(board_array[v.at(0)+11][v.at(1)+7] != 0)
                {
                    // i++;
                    j++;
                }
                move = "P";
                move.append(" ");
                move.append(std::to_string(i));
                move.append(" ");
                move.append(std::to_string(j));
            }
            

            update(-1,move,0);
        }
        if (total_moves==6 && N==6){
            int i = N-1;
            int j = N+5;
            v = change_coordinates(0,N-1,5);
            if (board_array[v.at(0)+11][v.at(1)+7] == 0)
            {
                move = "P 5 5";
            }
            else
            {
                v = change_coordinates(0,i,j);
                while(board_array[v.at(0)+11][v.at(1)+7] != 0)
                {
                    // i++;
                    j++;
                }
                move = "P";
                move.append(" ");
                move.append(std::to_string(i));
                move.append(" ");
                move.append(std::to_string(j));
            }
            

            update(-1,move,0);
        }
        if (total_moves>N)
        {    
            // std::cerr << "here786";
            std::string to_add_to_move_before = anything_to_remove_before_proceeding(N,K);
            // std::cerr << "here788";
            // std::cerr << "this is after 1 st proceed check"; 
            print();
            
            Node* root = tree(N,K,cut_off);
            // std::cerr << ("Child_size\n")<< root->children.size();
            // int ht = 0;
            int maxplay=-10000;
            string moveplayglobal="";
            
            for (int i = 0; i < root->children.size(); ++i)
            {
                Node* ch;
                ch = root->children.at(i);

            //     // temp_board_v =  ch->get_board();
            //     // ch->print_board();
                string moveplaylocal="";
                int minplay=10000;
                // std::cerr <<  "Child: "<< i << ":: "<< ch->move << " score "<<ch->score<<endl;   
                // if(ch->move.compare("S 4 1 M 2 1")==0){ch->print_board();}
                for (int j = 0; j < ch->children.size(); ++j)
                {
                    Node* chhh;
                    chhh = ch->children.at(j);
                    std::vector<std::vector<int> > temp_board_v;
                    int score_play=chhh->score;
                    if(score_play<minplay){
                        minplay=score_play;
                        moveplaylocal=chhh->move;
                    }

            //         // std::cerr <<"\nSize of child board: "<< temp_board_v.size();

            //     // for (int ii = 0; ii < temp_board_v.size(); ++ii)
            //     // {
            //     //     std::vector<int> v_temp = temp_board_v.at(ii);
            //     //     std::cerr <<"\nSize of child board_v element: "<< temp_board_v.size();
            //     //     for (int ji = 0; ji < v_temp.size(); ++ji)
            //     //     {
            //     //         temp_board_array[ii][ji] = v_temp.at(ji);
            //     //         //std::cerr << v_temp.at(ji);
            //     //     }
            //     // }
            //     // print2();
            //         std::cerr <<  "           Child: "<< j<< ":: "<< chhh->move<< " score "<<chhh->score << endl;   
               }
            //    // std::cerr<<"minimum child"<<moveplaylocal;
               if(maxplay<minplay){
                    maxplay=minplay;
                    moveplayglobal=ch->move;
               }
            }
            // std::cerr<<"maximum child"<<moveplayglobal;
            
            // while(root->children.size()!=0)
            // {
            //     root = root->children.at(0);
            //     ht++;
            // }

            Node* state  = max_val(root, -10000, 10000);
            move = state->get_move();
            // if(move.compare(moveplayglobal)==0){
            //     std::cerr<<"yes"<<move <<" SCORE: "<<state->score<< " "<<moveplayglobal<< "SCORE: "<<maxplay <<endl;
            // }
            // else{
            //    std::cerr<<"no"<<move <<" SCORE: "<<state->score<< " "<<moveplayglobal<< "SCORE: "<<maxplay <<endl;
            // }
            
            update(-1,move,0);
            // print();    

            std::string to_add_to_move_after = anything_to_remove_before_proceeding(N,K);

            print();

            return (to_add_to_move_before.append(move)).append(to_add_to_move_after) ;

        }
        
        return move;
    }


    Node* Board::tree(int N,int K)
    
    {
        
        
        
        int score = 0;
        int cut_off;
	if(N==6){
        if (total_moves>=10 && total_moves<=21){
		  cut_off = 3;
        }
        else{
            cut_off =2;
        }
	}
	else{
		cut_off = 3;
	}

        




        std::vector<Node*> children;
        std::vector<Node*> parent;

        int max_X[2*N+1];
       int max_5[]= {3,6,7,8,9,8,9,8,7,6,3};
        // int max_6 = {3,5,6,7,8,9,8,9,8,7,6,3};
        int max_6[] = {4,7,8,9,10,11,10,11,10,9,8,7,4};
        if (N==5){
           for (int i = 0; i < 2*N+1; ++i)
           {
               max_X[i] = max_5[i];
           }
        }
        else{
           for (int i = 0; i < 2*N+1; ++i)
           {
               max_X[i] = max_6[i];
           }
        }

        for (int i = 0; i < 22; ++i)
        {
            for (int j = 0; j < 14; ++j)
            {
                temp_board_array[i][j] =  board_array[i][j];
            }
        }
        std::vector<std::vector<int> > v_g;
        for (int i = 0; i < 22; ++i)
        {
            std::vector<int> v_temp_g;
            for (int j = 0; j <14 ; ++j)
            {
                v_temp_g.push_back(temp_board_array[i][j]);
            }
            v_g.push_back(v_temp_g);
        }

        Node* root = new Node(NULL,score,"S 1 2 M 3 4",v_g);
        Node* permanent_root;
        permanent_root = root;
        bool globalflag=true;
        int ht = 0;
        while (globalflag==true)
        {
                            if(ht==cut_off){
                                globalflag=false;
                                root=permanent_root;
                                return permanent_root;   
                            }
            if (ht==0){
                parent.push_back(root);

            }
            children.clear();
            
            

 
            // /flag = false;

                        for(int z=0;z<parent.size();z++)
                        {
                            if(ht==cut_off){
                                root=permanent_root;
                                return permanent_root;   
                            }
                            else{
                                root=parent.at(z);
                                 // std::cerr<< "\nPrint :"<<z<<" "<<ht<<"\n";

                                std::vector<std::vector<int> > temp_board_v;
                                temp_board_v =  parent.at(z)->get_board();
                                for (int i = 0; i < temp_board_v.size(); ++i)
                                {
                                    std::vector<int> v_temp = temp_board_v.at(i);
                                    for (int j = 0;j < v_temp.size(); ++j)
                                    {
                                        temp_board_array[i][j] = v_temp.at(j);
                                    }
                                }
                                // std::cerr<<"parent change"<<"\n";
                                // parent.at(z)->print_board();
                                // print2();
                                // std::cerr<< "\nExit:";
                                // exit(0);
                                for(int i=0;i<22;i++){
                                    for(int j=0;j<14;j++){
                                        bool flag=false;
                                        // std::cerr<<"E";
                                        if((temp_board_array[i][j]== -2&&ht%2==0)||(temp_board_array[i][j]== 2&&ht%2==1))
                                        {
                                            // std::cerr << "Entered At ring position:"<<i-11<<" "<<j-11;
                                            int p=0;
                                            int cons;   //
                                            int cons2;  // check
                                            i = i-11;
                                            j = j-7;
                                            while(p<6)
                                            {
                                                
                                                int start;
                                                if(p==0){
                                                    start=i-2;
                                                    cons=0;
                                                    cons2=-2;
                                                }
                                                else if(p==1){
                                                    start=i+2;
                                                    cons=0;
                                                    cons2=2;
                                                }
                                                else if(p==2){
                                                    start=i+1;
                                                    cons=1;
                                                    cons2=1;
                                                }
                                                else if(p==3){
                                                    start=i-1;
                                                    cons=1;
                                                    cons2=-1;
                                                }
                                                else if(p==4){
                                                    start=i+1;
                                                    cons=-1;
                                                    cons2=+1;
                                                }
                                                else if(p==5){
                                                    start=i-1;
                                                    cons=-1;
                                                    cons2=-1;
                                                }   


                                                p++;   // change the direcction

                                                // -8 , 0 should be -2
                                                bool flag = false;
                                                for (int k = start; (k >= - max_X[cons*(k-start)+j+cons*cons2+N]) && (k <=  max_X[cons*cons2+cons*(k-start)+j+N]) && abs(cons*cons2+cons*(k-start)+j)<=N; k=k+cons2)
                                                {
                                                    
                                                    // std::cerr << "\nEntering for loop" <<" " <<p-1 <<" "<< k<<" "<<cons*cons2+cons*(k-start)+j<<" "<<temp_board_array[11+k][cons*cons2+11+cons*(k-start)+j]<<"\n";
                                                    // std::cerr << "\nhere0";
                                                    if (abs(temp_board_array[11+k][cons*cons2+7+cons*(k-start)+j]) == 2){
                                                    // std::cerr << "\nExiting for loop" << p-1 << "\n";
                                                        
                                                        break;
                                                    }
                                                    // std::cerr << "\nhere1";
                                                    else if (abs(temp_board_array[11+k][cons*cons2+7+cons*(k-start)+j]) == 1 ){
                                                        flag=true;
                                                    }
                                                    //std::cerr << "\nhere2";
                                                    else if (abs(temp_board_array[11+k][cons*cons2+7+cons*(k-start)+j]) == 0  &&  flag==false)
                                                    {
                                                        
                                                        std::vector<int> v1 = change_coordinates(1,i,j); 
                                                        std::vector<int> v2 = change_coordinates(1,k,cons*cons2+cons*(k-start)+j);

                                                        std::string s_d  = "S ";
                                                        
                                                        s_d.append(std::to_string(v1.at(0)));

                                                        s_d.append(" ");
                                                        s_d.append(std::to_string(v1.at(1)));
                                                        s_d.append(" ");
                                                        s_d.append("M ");
                                                        s_d.append(std::to_string(v2.at(0)));
                                                        s_d.append(" ");

                                                        s_d.append(std::to_string(v2.at(1)));

                                                        update(0,s_d,1);  // 1arg redundant , move , temp_board_arrray

                                                        // std::cerr << "Move: "<<s_d <<" ht";



                                                          // cerr << "get in find_K and evla stars...\n";
                                                        std::vector<int> v = find_K_consecutive_temp_board_array(N,K,ht);
                                                          // std::chrono::high_resolution_clock::time_point t1= std::chrono::high_resolution_clock::now();

                                                        // ht = ht+1;
                                                        // std::cerr << ("Height is inc in 0\n");               
                                                        int child_score;
                                                        child_score =  1*evaluate_heuristic(N,K) ;

                                                         // std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

                                                          // std::chrono::duration<double, std::milli> time_span = t2 - t1;

                                                          // cerr << "It took me " << time_span.count() << " milliseconds total";
                                                          // cerr << endl;
                                                          // exit(0);
                                                        
                                                     
                                                        
                                                        string s_d_old = s_d;
                                                        if (v.size()!=0)
                                                        {
                                                            s_d.append(" ");
                                                            s_d.append("RS");

                                                            s_d.append(" ");
                                                            s_d.append(std::to_string(v.at(0)));

                                                            s_d.append(" ");
                                                            s_d.append(std::to_string(v.at(1)));

                                                            s_d.append(" ");
                                                            s_d.append("RE");

                                                            s_d.append(" ");
                                                            s_d.append(std::to_string(v.at(2)));

                                                            s_d.append(" ");
                                                            s_d.append(std::to_string(v.at(3)));

                                                            s_d.append(" ");
                                                            s_d.append("X");

                                                            std::vector<int> v_prime = find_which_ring_to_remove(N,K,ht);
                                                                
                                                            s_d.append(" ");
                                                            s_d.append(std::to_string(v_prime.at(0)));

                                                            s_d.append(" ");
                                                            s_d.append(std::to_string(v_prime.at(1)));

                                                            v_prime = change_coordinates(0,v_prime.at(0),v_prime.at(1));
                                                            // rings_removed.push_back(v_prime.at(0));
                                                            // rings_removed.push_back(v_prime.at(1));

                                                        }
                                                        

                                                        if(v.size()!=0){
                                                            reverse_update(2*ht%2-1,1,2,3,4,s_d_old);
                                                            update(0,s_d,1);
                                                        }
                                                     // std::cerr << "Move: "<<s_d <<" ht "<< ht<<"\n";
                                                        // print2();
                                                        // std::cerr <<  "\nEnd\n";
                                                        std::vector<std::vector<int> > v_i;
                                                        if(ht!=cut_off-1){
                                                            for (int ii = 0; ii < 22; ++ii)
                                                            {
                                                                std::vector<int> v_temp;
                                                                for (int jj = 0; jj <14 ; ++jj)
                                                                {
                                                                    v_temp.push_back(temp_board_array[ii][jj]);
                                                                }
                                                                v_i.push_back(v_temp);
                                                                v_temp.clear();
                                                            }
                                                        }
                                                        // std::cerr << "\nSize of v_i : "<< v_i.size() << "Element "<< v_i.at(0).size();
                                                        Node* child = new Node(root,child_score,s_d,v_i);

                                                        // std::cerr << k<< " "<< cons*cons2+cons*(k-start)+j<<"  YUP";
                                                                                // std::cerr<< "\nPrint1 :\n";

                                                        // for (int ag= 0; ag < children.size(); ++ag)
                                                        // {
                                                        //     std::cerr<< "\nchildern at each for loop :"<<ag<<"ht: "<<ht<<"\n";

                                                        //     children.at(ag)->print_board();
                                                        //         /* code */
                                                        // }
                                                        // child->print_board() ;// print2();
                                                        // std::cerr<< "\nExit:\n";
                                                        children.push_back(child);
                                                        root->add_children(child);
                                                        reverse_update(2*ht%2-1,1,2,3,4,s_d);
                                                        // flag1 = true;
                                                        if(v.size()!=0&&ht==0){return permanent_root;}

                                                    }
                                                    //std::cerr << "\nhere3";
                                                    else if (abs(temp_board_array[11+k][cons*cons2+7+cons*(k-start)+j]) == 0  &&  flag==true){

                                                        // std::cerr << "\nhere1";
                                                        
                                                        std::vector<int> v1 = change_coordinates(1,i,j); 
                                                        std::vector<int> v2 = change_coordinates(1,k,cons*cons2+cons*(k-start)+j);

                                                        std::string s_d  = "S ";
                                                        s_d.append(std::to_string(v1.at(0)));
                                                        s_d.append(" ");
                                                        s_d.append(std::to_string(v1.at(1)));
                                                        s_d.append(" ");
                                                        s_d.append("M ");
                                                        s_d.append(std::to_string(v2.at(0)));
                                                        s_d.append(" ");
                                                        s_d.append(std::to_string(v2.at(1)));
                                                        // std::cerr << "\nhere2 UPD";

                                                        update(0,s_d,1);

                                                        // std::cerr << "\nhere2 FFC";

                                                         // std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

                                                          // cerr << "get in eval2 1000 stars...\n";
                                                        
                                                              std::vector<int> v = find_K_consecutive_temp_board_array(N,K,ht);
                                                        // ht = ht+1;
                                                        // std::cerr << ("Height is inc in 0\n");        

                                                        // std::cerr << "\nhere2 EH";

                                                        int child_score;
                                                        child_score =  1*evaluate_heuristic(N,K) ;

                                                          // std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

                                                          // std::chrono::duration<double, std::milli> time_span = t2 - t1;

                                                          // cerr << "It took me " << time_span.count() << " milliseconds.";
                                                          // cerr << endl;
                                                                                                                

                                                       
                                                        // std::cerr << "\nhere2 REVUPD";

                                                       
                                                         string s_d_old = s_d;
                                                        // std::cerr << "\nhere2 REVUPD";

                                                        if (v.size()!=0){
                                                            s_d.append(" ");
                                                            s_d.append("RS");

                                                            s_d.append(" ");
                                                            s_d.append(std::to_string(v.at(0)));

                                                            s_d.append(" ");
                                                            s_d.append(std::to_string(v.at(1)));

                                                            s_d.append(" ");
                                                            s_d.append("RE");

                                                            s_d.append(" ");
                                                            s_d.append(std::to_string(v.at(2)));

                                                            s_d.append(" ");
                                                            s_d.append(std::to_string(v.at(3)));

                                                            s_d.append(" ");
                                                            s_d.append("X");
                                                            // std::cerr << "\nhere2 FWRTR";

                                                            std::vector<int> v_prime = find_which_ring_to_remove(N,K,ht);
                                                            // std::cerr << "\nhere2 FWRTR2";
                                                                
                                                            s_d.append(" ");
                                                            s_d.append(std::to_string(v_prime.at(0)));

                                                            s_d.append(" ");
                                                            s_d.append(std::to_string(v_prime.at(1)));
                                                            // std::cerr << "\nhere2 CC1";
                                                            v_prime = change_coordinates(0,v_prime.at(0),v_prime.at(1));
                                                            // std::cerr << "\nhere2 CC2";

                                                            // rings_removed.push_back(v_prime.at(0));
                                                            // rings_removed.push_back(v_prime.at(1));

                                                        }

                                                        // std::cerr << "\nEntering update line 1929\n";
                                                        if(v.size()!=0){                                                        
                                                            reverse_update(2*ht%2-1,1,2,3,4,s_d_old);
                                                            update(0,s_d,1);
                                                        }
                                                        // std::cerr << "\nEntering vect convert line 1931\n";
                                                        // std::cerr<< "\nPrint1 :\n";

                                                        // print2();
                                                        
                                                        
                                                        std::vector<std::vector<int> > v_i;
                                                        if(ht!=cut_off-1){
                                                            for (int ii = 0; ii < 22; ++ii)
                                                            {
                                                                std::vector<int> v_temp;
                                                                for (int jj = 0; jj <14 ; ++jj)
                                                                {
                                                                    v_temp.push_back(temp_board_array[ii][jj]);
                                                                }
                                                                v_i.push_back(v_temp);
                                                            }
                                                        }
                                                        // std::cerr << "\nEntering child convert line 1931\n";
                                                        
                                                        Node* child = new Node(root,child_score,s_d,v_i);
                                                        // child->print_board();

                                                        // std::cerr << k<< " "<< cons*(k-start)+j<<"  YUP2";
                                                        children.push_back(child);
                                                        root->add_children(child);
                                                        // std::cerr << "\nEntering rev_up rev_up line 1931\n";

                                                        reverse_update(2*ht%2-1,1,2,3,4,s_d);
                                                        // std::cerr << "\nExit rev_up rev_up line 1931\n";

                                                       if(v.size()!=0&&ht==0){return permanent_root;}
                                                        break;
                                                    }
                                                   // std::cerr << "\nhere";

                                                }

                                                
                                            }
                                            i = i+11;
                                            j = j+7;
                                            // std::cerr<< " Board_for: \n" ;print2();
                                        }
                                    }
                                }

                            }
                        }
                        parent.clear();
                        for(int z=0;z<children.size();z++){
                            parent.push_back(children.at(z));
                            // std::cerr << "\nHt is inc: with move"<< children.at(z)->move <<" z: "<< z << "\n";
                            // children.at(z)->print_board();
                        }
               
                        ht++; 

                            
                       
        }



        return root;
    }


    std::vector<int> Board::find_which_ring_to_remove(int N,int K,int ht){
        std::vector<int> v;

        int min_heuristic = 100000;
        int to_removex = -1;
        int to_removey = -1;
        bool flag = false;
        for(int i =0;i<22;i++){
            for(int j = 0 ; j<14;j++){
                if((temp_board_array[i][j]==2 && ht%2==1) ||(temp_board_array[i][j]==-2 && ht%2==0)) {
                    
                    
                int to_re_update=temp_board_array[i][j];
                temp_board_array[i][j]=0;
                int score = evaluate_heuristic(N,K);
                if(to_re_update == 2){
                    score=-score;
                }

                if(score<min_heuristic){
                    min_heuristic = score;
                    to_removex = i;
                    to_removey = j;
                }
                temp_board_array[i][j]=to_re_update;
                }

            }
        }
        // for (int i = 0; i < 5; ++i)
        // {
        //     for (int j = 0; j < rings_removed.size(); j=j+2)
        //     {
        //         if (tmp_ring[2*i]==rings_removed.at(j) && tmp_ring[2*i+1]==rings_removed.at(j+1) ){
        //             flag = true;
        //         }
        //     }
                
        //     if(flag==true){
        //         flag=false;
        //     }
        //     else
        //     {
        //         int to_re_update = -3;
        //         int ring_x = tmp_ring[2*i];
        //         int ring_y = tmp_ring[2*i+1];
        //         to_re_update =  temp_board_array[ring_x][ring_y] ;
        //         temp_board_array[ring_x][ring_y] = 0 ;
        //         int score = evaluate_heuristic();
        //         if (to_re_update == 2){
        //             score = -score;
        //         }

        //         if (score<min_heuristic){
        //             min_heuristic = score;
        //             to_remove = i;
        //         }
        //         temp_board_array[ring_x][ring_y] = to_re_update;
        //     }

        // }

        v.push_back(to_removex);
        v.push_back(to_removey);
        // std::cerr << "Rings_removed: "<< to_removex <<","<<to_removey<<","<<"////";
        std::vector<int> v1 = change_coordinates(1,v.at(0)-11,v.at(1)-7);
        // v1.push_back(to_remove);

    //     v.push_back(tmp_ring[2*to_remove]);
    //     v.push_back(tmp_ring[2*to_remove+1]);
       // std::cerr << "Rings_removed: "<< tmp_ring[2*to_remove] <<","<<tmp_ring[2*to_remove+1]<<","<<to_remove<<"////";
    //     std::vector<int> v1 = change_coordinates(1,v.at(0),v.at(1));
    //     v1.push_back(to_remove);
        return v1;
    }
   
    std::vector<int> Board::find_which_ring_to_remove_board_array(int N,int K,int ht){
        std::vector<int> v;

        int min_heuristic = 100000;
        int to_removex = -1;
        int to_removey = -1;
        bool flag = false;
        for(int i =0;i<22;i++){
            for(int j = 0 ; j<14;j++){
                if((board_array[i][j]==2 && ht%2==1) ||(board_array[i][j]==-2 && ht%2==0)){

                    int to_re_update=board_array[i][j];
                    board_array[i][j]=0;
                    int score = evaluate_heuristic( N,K);
                    if(to_re_update == 2){
                        score=-score;
                    }

                    if(score<min_heuristic){
                        min_heuristic = score;
                        to_removex = i;
                        to_removey = j;
                    }
                    board_array[i][j]=to_re_update;
                }

            }
        }


        v.push_back(to_removex);
        v.push_back(to_removey);
        // std::cerr << "Rings_removed: "<< to_removex <<","<<to_removey<<","<<"////";
        std::vector<int> v1 = change_coordinates(1,v.at(0)-11,v.at(1)-7);
        // v1.push_back(to_remove);

        return v1;
    }
    


    bool Board::check_five(int val,int a1,int a2,int a3,int a4,int a5){
        
        int m;
        if (a1==val && a2==val && a3==val && a4==val && a5==val){
            // std::cin >> m;
            return true;
        }
        return false;
    }


    bool Board::check_six(int val,int a1,int a2,int a3,int a4,int a5,int a6){
        
        int m;
        if (a1==val && a2==val && a3==val && a4==val && a5==val && a6==val){
            
            return true;
        }
        return false;
    }

    std::vector<int>  Board::find_K_consecutive_temp_board_array(int N,int K,int ht)
    {
        
        // print2();
        // int max_X[] = {6,7,8,9,8,9,8,7,6};


        int max_X[2*N+1];
       int max_5[]= {3,6,7,8,9,8,9,8,7,6,3};
        // int max_6 = {3,5,6,7,8,9,8,9,8,7,6,3};
        int max_6[] = {4,7,8,9,10,11,10,11,10,9,8,7,4};
        if (N==5){
           for (int i = 0; i < 2*N+1; ++i)
           {
               max_X[i] = max_5[i];
           }
        }
        else{
           for (int i = 0; i < 2*N+1; ++i)
           {
               max_X[i] = max_6[i];
           }
        }
        

        std::vector<int> v;
         bool result=false;
        
        // Y = 0;
        for (int i = -(N); i < N+1; i++) // y axis
        {
            int y_m = max_X[i+N];
            for (int j = -y_m; j < y_m-2*(K-1)+1; j=j+2) // x-axis
            {   
                if (ht%2==0)
                {
                    if (K==5){
                        result = check_five(-1,temp_board_array[11+j][7+i],temp_board_array[11+j+2][7+i],temp_board_array[11+j+4][7+i],temp_board_array[11+j+6][7+i],temp_board_array[11+j+8][7+i]);
                    }
                    else{
                     result = check_six(-1,temp_board_array[11+j][7+i],temp_board_array[11+j+2][7+i],temp_board_array[11+j+4][7+i],temp_board_array[11+j+6][7+i],temp_board_array[11+j+8][7+i],temp_board_array[11+j+10][7+i]);   
                    }
                }
                else{
                    if (K==5){
                        result = check_five(1,temp_board_array[11+j][7+i],temp_board_array[11+j+2][7+i],temp_board_array[11+j+4][7+i],temp_board_array[11+j+6][7+i],temp_board_array[11+j+8][7+i]);
                    }
                    else
                    {
                        result = check_six(1,temp_board_array[11+j][7+i],temp_board_array[11+j+2][7+i],temp_board_array[11+j+4][7+i],temp_board_array[11+j+6][7+i],temp_board_array[11+j+8][7+i],temp_board_array[11+j+10][7+i]);
                    }
                }
                if (result==true){

                    std::vector<int> v1 = change_coordinates(1,j,i);
                    std::vector<int> v2 = change_coordinates(1,j+2*(K-1),i);
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);
                    return v;
                    break;
                }
            }
        }

        int y_cor[2*N-1];
        int y_cor_5[] = {-1,-2,-3,-4,-4,-5,-5,-5,-5} ; 
        int y_cor_6[] = {-1,-2,-3,-4,-5,-5,-6,-6,-6,-6,-6} ; // size 13

        int x_cor[2*N-1];
        int x_cor_5[] = {-9,-8,-7,-6,-4,-3,-1,1,3};
        int x_cor_6[] = {-11,-10,-9,-8,-7,-5,-4,-2,0,2,4};
        
        int in_line[2*N-1];
        int in_line_5[] = {2,3,4,5,4,5,4,3,2};
        int in_line_6_6[] = {2,3,4,5,6,5,6,5,4,3,2};
        int in_line_6_5[] = {3,4,5,6,7,6,7,6,5,4,3};

        //Initialization
        for (int i = 0; i < 2*N-1; ++i)
        {
            if (N==6)  
            {
                if (K==6)  {
                    in_line[i] = in_line_6_6[i];
                }
                else
                {
                    in_line[i] = in_line_6_5[i];   
                }


                x_cor[i] = x_cor_6[i];
                y_cor[i] = y_cor_6[i];
            }
            else
            {
                x_cor[i] = x_cor_5[i];
                y_cor[i] = y_cor_5[i];
                in_line[i] = in_line_5[i];   
            }
        }

        if (N==6 && K==5){
            int x = -11;
            int y = 1;
            if(ht%2==0)
            {
                result =  check_six(-1,temp_board_array[11+x][7+y],temp_board_array[11+x+1][7+y+1],temp_board_array[11+x+2][7+y+2],temp_board_array[11+x+3][7+y+3],temp_board_array[11+x+4][7+y+4],temp_board_array[11+x+5][7+y+5]);
              
            }
            else
            {
               result =  check_six(1,temp_board_array[11+x][7+y],temp_board_array[11+x+1][7+y+1],temp_board_array[11+x+2][7+y+2],temp_board_array[11+x+3][7+y+3],temp_board_array[11+x+4][7+y+4],temp_board_array[11+x+5][7+y+5]);
            }

            if( result==true){

                    std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x+(K-1),y+(K-1));
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);

                    // v.push_back(x);
                    // v.push_back(y);
                    // v.push_back(x+4);
                    // v.push_back(y+4);
                    return v;
                    
            }

            x = 7;
            y = -5;

            if(ht%2==0)
            {
                result =  check_six(-1,temp_board_array[11+x][7+y],temp_board_array[11+x+1][7+y+1],temp_board_array[11+x+2][7+y+2],temp_board_array[11+x+3][7+y+3],temp_board_array[11+x+4][7+y+4],temp_board_array[11+x+5][7+y+5]);
              
            }
            else
            {
               result =  check_six(1,temp_board_array[11+x][7+y],temp_board_array[11+x+1][7+y+1],temp_board_array[11+x+2][7+y+2],temp_board_array[11+x+3][7+y+3],temp_board_array[11+x+4][7+y+4],temp_board_array[11+x+5][7+y+5]);
            }

            if( result==true){

                    std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x+(K-1),y+(K-1));
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);

                    // v.push_back(x);
                    // v.push_back(y);
                    // v.push_back(x+4);
                    // v.push_back(y+4);
                    return v;
                    
            }
        }



        int x = 0;
        int y = 0;
        int points_count = 0;
        
        // Y = X
        for (int i = 0; i < 2*N-1; ++i) 
        {
            x = x_cor[i];
            y = y_cor[i];
            while(true)
            {
                if(ht%2==0)
                {
                    if (K==5){
                        result =  check_five(-1,temp_board_array[11+x][7+y],temp_board_array[11+x+1][7+y+1],temp_board_array[11+x+2][7+y+2],temp_board_array[11+x+3][7+y+3],temp_board_array[11+x+4][7+y+4]);
                    }
                    else
                    {
                        result =  check_six(-1,temp_board_array[11+x][7+y],temp_board_array[11+x+1][7+y+1],temp_board_array[11+x+2][7+y+2],temp_board_array[11+x+3][7+y+3],temp_board_array[11+x+4][7+y+4],temp_board_array[11+x+5][7+y+5]);
                    }
                }
                else
                {
                    if (K==5){   
                        result =  check_five(1,temp_board_array[11+x][7+y],temp_board_array[11+x+1][7+y+1],temp_board_array[11+x+2][7+y+2],temp_board_array[11+x+3][7+y+3],temp_board_array[11+x+4][7+y+4]);
                    }
                    else{
                        result =  check_six(1,temp_board_array[11+x][7+y],temp_board_array[11+x+1][7+y+1],temp_board_array[11+x+2][7+y+2],temp_board_array[11+x+3][7+y+3],temp_board_array[11+x+4][7+y+4],temp_board_array[11+x+5][7+y+5]);
                    }
                }

                
            
                if( result==true){

                     std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x+(K-1),y+(K-1));
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);

                    // v.push_back(x);
                    // v.push_back(y);
                    // v.push_back(x+4);
                    // v.push_back(y+4);
                    return v;
                    break;
                }
                x = x+1;
                y = y+1;
                if (points_count==in_line[i])
                {
                    points_count=0;

                    break;
                }
                points_count = points_count +1; 
            }

        }

        //// Y = - X
        int y_cord[2*N-1];
        int y_cord_5[] = {-5,-5,-5,-5,-4,-4,-3,-2,-1};
        int y_cord_6[] = {-6,-6,-6,-6,-6,-5,-5,-4,-3,-2,-1};
        int x_cord[2*N-1];
        int x_cord_5[] = {-3,-1,1,3,4,6,7,8,9};
        int x_cord_6[] = {-4,-2,0,2,4,5,7,8,9,10,11};

        for (int i = 0; i < 2*N-1; ++i)
        {
            if (N==6)  
            {
                x_cord[i] = x_cord_6[i];
                y_cord[i] = y_cord_6[i];
            }
            else
            {
                x_cord[i] = x_cord_5[i];
                y_cord[i] = y_cord_5[i];
            }
        }

        //boundary_conds
        if (N==6 && K ==5){
                int x = -7;
                int y = -5;
                if (ht%2==0 )
                {
                   
                    result = check_six(-1,temp_board_array[11+x][7+y],temp_board_array[11+x-1][7+y+1],temp_board_array[11+x-2][7+y+2],temp_board_array[11+x-3][7+y+3],temp_board_array[11+x-4][7+y+4],temp_board_array[11+x-5][7+y+5]);
                 
                }
                else
                {
                   
                   result = check_six(1,temp_board_array[11+x][7+y],temp_board_array[11+x-1][7+y+1],temp_board_array[11+x-2][7+y+2],temp_board_array[11+x-3][7+y+3],temp_board_array[11+x-4][7+y+4],temp_board_array[11+x-5][7+y+5]);
                 
                }
                if( result==true){

                    std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x-(K-1),y+(K-1));
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);

                  
                    return v;
                    
                }

                x = 11;
                y = 1;
                if (ht%2==0 )
                {
                   
                    result = check_six(-1,temp_board_array[11+x][7+y],temp_board_array[11+x-1][7+y+1],temp_board_array[11+x-2][7+y+2],temp_board_array[11+x-3][7+y+3],temp_board_array[11+x-4][7+y+4],temp_board_array[11+x-5][7+y+5]);
                 
                }
                else
                {
                   
                   result = check_six(1,temp_board_array[11+x][7+y],temp_board_array[11+x-1][7+y+1],temp_board_array[11+x-2][7+y+2],temp_board_array[11+x-3][7+y+3],temp_board_array[11+x-4][7+y+4],temp_board_array[11+x-5][7+y+5]);
                 
                }
                if( result==true){

                    std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x-(K-1),y+(K-1));
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);

                  
                    return v;
                    
                }
        }

        points_count=0;
        
        for (int i = 0; i < 2*N-1; ++i)
        {
            x = x_cord[i];
            y = y_cord[i];
            while(true)
            {
                
                if (ht%2==0 )
                {
                   
                    if (K==5){
                        result = check_five(-1,temp_board_array[11+x][7+y],temp_board_array[11+x-1][7+y+1],temp_board_array[11+x-2][7+y+2],temp_board_array[11+x-3][7+y+3],temp_board_array[11+x-4][7+y+4]);
                    }
                    else{
                        result = check_six(-1,temp_board_array[11+x][7+y],temp_board_array[11+x-1][7+y+1],temp_board_array[11+x-2][7+y+2],temp_board_array[11+x-3][7+y+3],temp_board_array[11+x-4][11+y+4],temp_board_array[11+x-5][7+y+5]);
                    }
                }
                else
                {
                   
                    if (K==5){
                        result = check_five(1,temp_board_array[11+x][7+y],temp_board_array[11+x-1][7+y+1],temp_board_array[11+x-2][7+y+2],temp_board_array[11+x-3][7+y+3],temp_board_array[11+x-4][7+y+4]);
                    }
                    else{
                        result = check_six(1,temp_board_array[11+x][7+y],temp_board_array[11+x-1][7+y+1],temp_board_array[11+x-2][7+y+2],temp_board_array[11+x-3][7+y+3],temp_board_array[11+x-4][7+y+4],temp_board_array[11+x-5][7+y+5]);
                    }
                }
                if( result==true){

                     std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x-(K-1),y+(K-1));
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);

                  
                    return v;
                    break;
                }
                x = x-1;
                y = y+1;
                if (points_count==in_line[i])
                {
                    points_count=0;

                    break;
                }
                points_count = points_count +1;     
            }

        }
        

        return v;


    }

    std::vector<int>  Board::find_K_consecutive_board_array(int N,int K,int ht)
     {
        
        // print2();
        // int max_X[] = {6,7,8,9,8,9,8,7,6};


        int max_X[2*N+1];
       int max_5[]= {3,6,7,8,9,8,9,8,7,6,3};
        // int max_6 = {3,5,6,7,8,9,8,9,8,7,6,3};
        int max_6[] = {4,7,8,9,10,11,10,11,10,9,8,7,4};
        if (N==5){
           for (int i = 0; i < 2*N+1; ++i)
           {
               max_X[i] = max_5[i];
           }
        }
        else{
           for (int i = 0; i < 2*N+1; ++i)
           {
               max_X[i] = max_6[i];
           }
        }
        

        std::vector<int> v;
         bool result=false;
        
        // Y = 0;
        for (int i = -(N); i < N+1; i++) // y axis
        {
            int y_m = max_X[i+N];
            for (int j = -y_m; j < y_m-2*(K-1)+1; j=j+2) // x-axis
            {   
                if (ht%2==0)
                {
                    if (K==5){
                        result = check_five(-1,board_array[11+j][7+i],board_array[11+j+2][7+i],board_array[11+j+4][7+i],board_array[11+j+6][7+i],board_array[11+j+8][7+i]);
                    }
                    else{
                     result = check_six(-1,board_array[11+j][7+i],board_array[11+j+2][7+i],board_array[11+j+4][7+i],board_array[11+j+6][7+i],board_array[11+j+8][7+i],board_array[11+j+10][7+i]);   
                    }
                }
                else{
                    if (K==5){
                        result = check_five(1,board_array[11+j][7+i],board_array[11+j+2][7+i],board_array[11+j+4][7+i],board_array[11+j+6][7+i],board_array[11+j+8][7+i]);
                    }
                    else
                    {
                        result = check_six(1,board_array[11+j][7+i],board_array[11+j+2][7+i],board_array[11+j+4][7+i],board_array[11+j+6][7+i],board_array[11+j+8][7+i],board_array[11+j+10][7+i]);
                    }
                }
                if (result==true){

                    std::vector<int> v1 = change_coordinates(1,j,i);
                    std::vector<int> v2 = change_coordinates(1,j+2*(K-1),i);
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);
                    return v;
                    break;
                }
            }
        }

        int y_cor[2*N-1];
        int y_cor_5[] = {-1,-2,-3,-4,-4,-5,-5,-5,-5} ; 
        int y_cor_6[] = {-1,-2,-3,-4,-5,-5,-6,-6,-6,-6,-6}; // size 13

        int x_cor[2*N-1];
        int x_cor_5[] = {-9,-8,-7,-6,-4,-3,-1,1,3};
        int x_cor_6[] = {-11,-10,-9,-8,-7,-5,-4,-2,0,2,4};
        
        int in_line[2*N-1];
        int in_line_5[] = {2,3,4,5,4,5,4,3,2};
        int in_line_6_6[] = {2,3,4,5,6,5,6,5,4,3,2};
        int in_line_6_5[] = {3,4,5,6,7,6,7,6,5,4,3};

        //Initialization
        for (int i = 0; i < 2*N-1; ++i)
        {
            if (N==6)  
            {
                if (K==6)  {
                    in_line[i] = in_line_6_6[i];
                }
                else
                {
                    in_line[i] = in_line_6_5[i];   
                }


                x_cor[i] = x_cor_6[i];
                y_cor[i] = y_cor_6[i];
            }
            else
            {
                x_cor[i] = x_cor_5[i];
                y_cor[i] = y_cor_5[i];
                in_line[i] = in_line_5[i];   
            }
        }

        if (N==6 && K==5){
            int x = -11;
            int y = 1;
            if(ht%2==0)
            {
                result =  check_six(-1,board_array[11+x][7+y],board_array[11+x+1][7+y+1],board_array[11+x+2][7+y+2],board_array[11+x+3][7+y+3],board_array[11+x+4][7+y+4],board_array[11+x+5][7+y+5]);
              
            }
            else
            {
               result =  check_six(1,board_array[11+x][7+y],board_array[11+x+1][7+y+1],board_array[11+x+2][7+y+2],board_array[11+x+3][7+y+3],board_array[11+x+4][7+y+4],board_array[11+x+5][7+y+5]);
            }

            if( result==true){

                    std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x+(K-1),y+(K-1));
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);

                    // v.push_back(x);
                    // v.push_back(y);
                    // v.push_back(x+4);
                    // v.push_back(y+4);
                    return v;
                    
            }

            x = 7;
            y = -5;

            if(ht%2==0)
            {
                result =  check_six(-1,board_array[11+x][7+y],board_array[11+x+1][7+y+1],board_array[11+x+2][7+y+2],board_array[11+x+3][7+y+3],board_array[11+x+4][7+y+4],board_array[11+x+5][7+y+5]);
              
            }
            else
            {
               result =  check_six(1,board_array[11+x][7+y],board_array[11+x+1][7+y+1],board_array[11+x+2][7+y+2],board_array[11+x+3][7+y+3],board_array[11+x+4][7+y+4],board_array[11+x+5][7+y+5]);
            }

            if( result==true){

                    std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x+(K-1),y+(K-1));
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);

                    // v.push_back(x);
                    // v.push_back(y);
                    // v.push_back(x+4);
                    // v.push_back(y+4);
                    return v;
                    
            }
        }



        int x = 0;
        int y = 0;
        int points_count = 0;
        
        // Y = X
        for (int i = 0; i < 2*N-1; ++i) 
        {
            x = x_cor[i];
            y = y_cor[i];
            while(true)
            {
                if(ht%2==0)
                {
                    if (K==5){
                        result =  check_five(-1,board_array[11+x][7+y],board_array[11+x+1][7+y+1],board_array[11+x+2][7+y+2],board_array[11+x+3][7+y+3],board_array[11+x+4][7+y+4]);
                    }
                    else
                    {
                        result =  check_six(-1,board_array[11+x][7+y],board_array[11+x+1][7+y+1],board_array[11+x+2][7+y+2],board_array[11+x+3][7+y+3],board_array[11+x+4][7+y+4],board_array[11+x+5][7+y+5]);
                    }
                }
                else
                {
                    if (K==5){   
                        result =  check_five(1,board_array[11+x][7+y],board_array[11+x+1][7+y+1],board_array[11+x+2][7+y+2],board_array[11+x+3][7+y+3],board_array[11+x+4][7+y+4]);
                    }
                    else{
                        result =  check_six(1,board_array[11+x][7+y],board_array[11+x+1][7+y+1],board_array[11+x+2][7+y+2],board_array[11+x+3][7+y+3],board_array[11+x+4][7+y+4],board_array[11+x+5][7+y+5]);
                    }
                }
                if( result==true){

                     std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x+(K-1),y+(K-1));
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);

                    // v.push_back(x);
                    // v.push_back(y);
                    // v.push_back(x+4);
                    // v.push_back(y+4);
                    return v;
                    break;
                }
                x = x+1;
                y = y+1;
                if (points_count==in_line[i])
                {
                    points_count=0;

                    break;
                }
                points_count = points_count +1; 
            }

        }

        //// Y = - X
        int y_cord[2*N-1];
        int y_cord_5[] = {-5,-5,-5,-5,-4,-4,-3,-2,-1};
        int y_cord_6[] = {-6,-6,-6,-6,-6,-5,-5,-4,-3,-2,-1};
        int x_cord[2*N-1];
        int x_cord_5[] = {-3,-1,1,3,4,6,7,8,9};
        int x_cord_6[] = {-4,-2,0,2,4,5,7,8,9,10,11};

        for (int i = 0; i < 2*N-1; ++i)
        {
            if (N==6)  
            {
                x_cord[i] = x_cord_6[i];
                y_cord[i] = y_cord_6[i];
            }
            else
            {
                x_cord[i] = x_cord_5[i];
                y_cord[i] = y_cord_5[i];
            }
        }

        //boundary_conds
        if (N==6 && K ==5){
                int x = -7;
                int y = -5;
                if (ht%2==0 )
                {
                   
                    result = check_six(-1,board_array[11+x][7+y],board_array[11+x-1][7+y+1],board_array[11+x-2][7+y+2],board_array[11+x-3][7+y+3],board_array[11+x-4][7+y+4],board_array[11+x-5][7+y+5]);
                 
                }
                else
                {
                   
                   result = check_six(1,board_array[11+x][7+y],board_array[11+x-1][7+y+1],board_array[11+x-2][7+y+2],board_array[11+x-3][7+y+3],board_array[11+x-4][7+y+4],board_array[11+x-5][7+y+5]);
                 
                }
                if( result==true){

                    std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x-(K-1),y+(K-1));
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);

                  
                    return v;
                    
                }

                x = 11;
                y = 1;
                if (ht%2==0 )
                {
                   
                    result = check_six(-1,board_array[11+x][7+y],board_array[11+x-1][7+y+1],board_array[11+x-2][7+y+2],board_array[11+x-3][7+y+3],board_array[11+x-4][7+y+4],board_array[11+x-5][7+y+5]);
                 
                }
                else
                {
                   
                   result = check_six(1,board_array[11+x][7+y],board_array[11+x-1][7+y+1],board_array[11+x-2][7+y+2],board_array[11+x-3][7+y+3],board_array[11+x-4][7+y+4],board_array[11+x-5][7+y+5]);
                 
                }
                if( result==true){

                    std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x-(K-1),y+(K-1));
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);

                  
                    return v;
                    
                }
        }

        points_count=0;
        
        for (int i = 0; i < 2*N-1; ++i)
        {
            x = x_cord[i];
            y = y_cord[i];
            while(true)
            {
                
                if (ht%2==0 )
                {
                   
                    if (K==5){
                        result = check_five(-1,board_array[11+x][7+y],board_array[11+x-1][7+y+1],board_array[11+x-2][7+y+2],board_array[11+x-3][7+y+3],board_array[11+x-4][7+y+4]);
                    }
                    else{
                        result = check_six(-1,board_array[11+x][7+y],board_array[11+x-1][7+y+1],board_array[11+x-2][7+y+2],board_array[11+x-3][7+y+3],board_array[11+x-4][7+y+4],board_array[11+x-5][7+y+5]);
                    }
                }
                else
                {
                   
                    if (K==5){
                        result = check_five(1,board_array[11+x][7+y],board_array[11+x-1][7+y+1],board_array[11+x-2][7+y+2],board_array[11+x-3][7+y+3],board_array[11+x-4][7+y+4]);
                    }
                    else{
                        result = check_six(1,board_array[11+x][7+y],board_array[11+x-1][7+y+1],board_array[11+x-2][7+y+2],board_array[11+x-3][7+y+3],board_array[11+x-4][7+y+4],board_array[11+x-5][7+y+5]);
                    }
                }
                if( result==true){

                     std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x-(K-1),y+(K-1));
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);

                  
                    return v;
                    break;
                }
                x = x-1;
                y = y+1;
                if (points_count==in_line[i])
                {
                    points_count=0;

                    break;
                }
                points_count = points_count +1;     
            }

        }
        

        return v;


    }
    
    Node* Board::max_val(Node* node,int alpha, int beta)
    {
        // cerr<<"no of child:"<<node->children.size()<<endl;
        if (node->isTerminal())
        {
            return node;//->utility();
        }
        std::vector<Node*>  childs;
        childs = node->children;
        std::vector<std::vector<int> > v;
        Node* child = new Node(NULL,0,"S 1 2 M 3 4",v);
        Node* max_child = new Node(NULL,0,"S 1 2 M 3 4",v);
        max_child->score = -10000000; /// infinity
        for (int i = 0; i < childs.size(); ++i)
        {

            Node* child_at_i = childs.at(i);
            child = min_val(childs.at(i),node->alpha,node->beeta);
            // std::vector<Node*> child_vec = child_at_i->children;
      //       for(int j=0;j<child_vec.size();j++){
      //           std::cerr<<"move of child"<<child_vec.at(j)->move<<" score "<<child_vec.at(j)->score<<endl;
      //       }
            child_at_i->score = child->score;
            // std::cerr<<"minchild for "<<i<<" "<<child_at_i->move<<" "<<child->score<<"    "<<max_child->score<<endl;
            node->alpha = max(node->alpha,child->utility()); 
            if (child->score>max_child->score)
            {
                
                max_child->score = child_at_i->score;
                max_child->move = child_at_i->move; 
                // std::cerr<<"maxchild for "<<i<<" "<<max_child->move<<" "<<max_child->score<<endl;
            }
            
            if (node->alpha >= node->beeta)
            {
                child->move = child_at_i->move;
                return child;
            }
        }

        //std::cerr << "Move & score  of mac_C " << max_child->move << " "<< max_child->score << endl ; 
        // std::cerr<<"final maxchild for "<<" "<<max_child->move<<" "<<max_child->score<<endl;
        return max_child;
    }


    
   


    Node* Board::min_val( Node* node ,int alpha, int beta)
    {
        // cerr<<"no of child:"<<node->children.size()<<endl;

        if (node->isTerminal())
        {
            return node;//node->utility();
        }
        std::vector<Node*>  childs;
        childs = node->children;
        std::vector<std::vector<int> > v;
        Node* child = new Node(NULL,0,"S 1 2 M 3 4",v);
        Node* min_child = new Node(NULL,0,"S 1 2 M 3 4",v);
        min_child->score = 10000000; /// infinity
        for (int i = 0; i < childs.size(); ++i)
        {

            Node* child_at_i = childs.at(i);
            child = max_val(childs.at(i),node->alpha,node->beeta);

            child_at_i->score = child->score;

            node->beeta = min(node->beeta,child->utility()); 
        
            if (child_at_i->utility()<min_child->utility())
            {
                min_child->score = child_at_i->score;
                min_child->move = child_at_i->move; 

            }
            if (node->alpha >= node->beeta)
            {
                child->move = child_at_i->move;
                return child;
            }
        }
        //std::cerr << "Move & score  of mic_C " << min_child->move << " "<< min_child->score << endl ; 

        return min_child;

    }

    int Board::how_good_disc_is(int N,int x,int y){

                                            int max_X[2*N+1];
                                            int max_5[]= {3,6,7,8,9,8,9,8,7,6,3};
                                             // int max_6 = {3,5,6,7,8,9,8,9,8,7,6,3};
                                             int max_6[] = {4,7,8,9,10,11,10,11,10,9,8,7,4};
                                             if (N==5){
                                                for (int i = 0; i < 2*N+1; ++i)
                                                {
                                                    max_X[i] = max_5[i];
                                                }
                                             }
                                             else{
                                                for (int i = 0; i < 2*N+1; ++i)
                                                {
                                                    max_X[i] = max_6[i];
                                                }
                                             }


                                            int player_type = temp_board_array[x][y];

                                            int p=0;
                                            int cons;   //
                                            int cons2;  // check
                                            int start2,cons3,cons4;
                                            int i = x-11;
                                            int j = y-7;
                                            int attack;

                                            while(p<6)
                                            {
                                                
                                                
                                                int start;
                                                bool disc = false;
                                                bool empty =false;
                                                if(p==0){
                                                    start=i-2;
                                                    cons=0;
                                                    cons2=-2;

                                                    start2=i+2;
                                                    cons3=0;
                                                    cons4=2;
                                                }
                                                else if(p==1){
                                                    start=i+2;
                                                    cons=0;
                                                    cons2=2;

                                                    start2=i-2;
                                                    cons3=0;
                                                    cons4=-2;
                                                }
                                                else if(p==2){
                                                    start=i+1;
                                                    cons=1;
                                                    cons2=1;
                                                
                                                    start2=i-1;
                                                    cons3=1;
                                                    cons4=-1;
                                                }
                                                else if(p==3){
                                                    start=i-1;
                                                    cons=1;
                                                    cons2=-1;

                                                    start2=i+1;
                                                    cons3=1;
                                                    cons4=1;
                                                }
                                                else if(p==4){
                                                    start=i+1;
                                                    cons=-1;
                                                    cons2=+1;

                                                    start2=i-1;
                                                    cons3=-1;
                                                    cons4=-1;
                                                }
                                                else if(p==5){
                                                    start=i-1;
                                                    cons=-1;
                                                    cons2=-1;

                                                    start2=i+1;
                                                    cons3=-1;
                                                    cons4=+1;
                                                }   


                                                p++;   // change the direcction

                                                // -8 , 0 should be -2
                                                bool flag = false;
                                                for (int k = start; (k >= - max_X[cons*(k-start)+j+cons*cons2+N]) && (k <=  max_X[cons*cons2+cons*(k-start)+j+N]) && abs(cons*cons2+cons*(k-start)+j)<=N; k=k+cons2)
                                                {

                                                    if (temp_board_array[k][cons*cons2+cons*(k-start)+j] == -2*player_type){
                                                         for (int k2 = start2; (k2>= - max_X[cons3*(k2-start2)+j+cons3*cons4+N]) && (k2 <=  max_X[cons3*cons4+cons3*(k2-start2)+j+N]) && abs(cons3*cons4+cons3*(k2-start2)+j)<=N; k2=k2+cons2)
                                                        {
                                                            if (temp_board_array[k2][cons3*(k2-start2)+j+cons3*cons4] == 0){
                                                                attack++;
                                                                break;
                                                            }   
                                                            else if (abs(temp_board_array[k2][cons3*(k2-start2)+j+cons3*cons4]) == 2){
                                                                break;
                                                            }
                                                        }
                                                        break;
                                                    }
                                                    else if (temp_board_array[k][cons*cons2+cons*(k-start)+j] == -2*player_type){
                                                        break;
                                                    }
                                                    else if (abs(temp_board_array[k][cons*cons2+cons*(k-start)+j]) == 1 && empty == true) {
                                                        disc = true;
                                                        break;   
                                                    }

                                                    else if (abs(temp_board_array[k][cons*cons2+cons*(k-start)+j]) == 0 && disc == true) {
                                                        empty = true;
                                                        break;  
                                                    }

                                                    else if (abs(temp_board_array[k][cons*cons2+cons*(k-start)+j]) == 1) {
                                                        disc = true;
                                                        
                                                    }

                                                    else if (abs(temp_board_array[k][cons*cons2+cons*(k-start)+j]) == 0) {
                                                        empty = true;
                                                     
                                                    }
                                                }  

                                            }

        return attack;
    }   
    int Board::how_good_ring_is(int N,int x,int y){
        

                                            int max_X[2*N+1];
                                            int max_5[]= {3,6,7,8,9,8,9,8,7,6,3};
                                             // int max_6 = {3,5,6,7,8,9,8,9,8,7,6,3};
                                             int max_6[] = {4,7,8,9,10,11,10,11,10,9,8,7,4};
                                             if (N==5){
                                                for (int i = 0; i < 2*N+1; ++i)
                                                {
                                                    max_X[i] = max_5[i];
                                                }
                                             }
                                             else{
                                                for (int i = 0; i < 2*N+1; ++i)
                                                {
                                                    max_X[i] = max_6[i];
                                                }
                                             }


                                            int player_type = temp_board_array[x][y]/2;

                                            int p=0;
                                            int cons,cons2;   //
                                           
                                            int i = x-11;
                                            int j = y-7;
                                            int attack;
                                            int max = 0;
                                            while(p<6)
                                            {
                                                
                                                
                                                int start;
                                                
                                               int other_disc = 0;

                                                if(p==0){
                                                    start=i-2;
                                                    cons=0;
                                                    cons2=-2;

                                                    
                                                }
                                                else if(p==1){
                                                    start=i+2;
                                                    cons=0;
                                                    cons2=2;

                                                    
                                                }
                                                else if(p==2){
                                                    start=i+1;
                                                    cons=1;
                                                    cons2=1;
                                                
                                                    
                                                }
                                                else if(p==3){
                                                    start=i-1;
                                                    cons=1;
                                                    cons2=-1;

                                                   
                                                }
                                                else if(p==4){
                                                    start=i+1;
                                                    cons=-1;
                                                    cons2=+1;

                                                    
                                                }
                                                else if(p==5){
                                                    start=i-1;
                                                    cons=-1;
                                                    cons2=-1;

                                                   
                                                }   


                                                p++;   
                                                other_disc =0;
                                                int flag= 0 ;
                                                for (int k = start; (k >= - max_X[cons*(k-start)+j+cons*cons2+N]) && (k <=  max_X[cons*cons2+cons*(k-start)+j+N]) && abs(cons*cons2+cons*(k-start)+j)<=N; k=k+cons2)
                                                {

                                                    if (temp_board_array[k][cons*(k-start)+j+cons*cons2] == 0 ){
                                                        if (other_disc>max){
                                                            max = other_disc;
                                                        }
                                                        if (flag==1){
                                                            break;
                                                        }


                                                    }
                                                    else if (abs( temp_board_array[k][cons*(k-start)+j+cons*cons2]) ==2){
                                                        break;
                                                    }
                                                    else if ( temp_board_array[k][cons*(k-start)+j+cons*cons2] ==player_type){
                                                        other_disc--;
                                                        flag=1;
                                                    }
                                                    else if (temp_board_array[k][cons*(k-start)+j+cons*cons2] ==-player_type){
                                                        other_disc++;
                                                        flag=1;
                                                    }
                                                
                                                }
                                                  

                                            }




                                            return max;

    }


int Board::my_ring_on_blank(int N,int x,int y,int player_type){
        


                                            int max_X[2*N+1];
                                            int max_5[]= {3,6,7,8,9,8,9,8,7,6,3};
                                             // int max_6 = {3,5,6,7,8,9,8,9,8,7,6,3};
                                             int max_6[] = {4,7,8,9,10,11,10,11,10,9,8,7,4};
                                             if (N==5){
                                                for (int i = 0; i < 2*N+1; ++i)
                                                {
                                                    max_X[i] = max_5[i];
                                                }
                                             }
                                             else{
                                                for (int i = 0; i < 2*N+1; ++i)
                                                {
                                                    max_X[i] = max_6[i];
                                                }
                                             }


                                            // int player_type = temp_board_arrray[x][y]/2;

                                            int p=0;
                                            int cons,cons2;   //
                                           
                                            int i = x-11;
                                            int j = y-7;
                                            int attack;
                                            int max = 0;
                                            while(p<6)
                                            {
                                                
                                                
                                                int start;
                                                
                                               bool empty = false;
                                               bool disc = false;

                                                if(p==0){
                                                    start=i-2;
                                                    cons=0;
                                                    cons2=-2;

                                                    
                                                }
                                                else if(p==1){
                                                    start=i+2;
                                                    cons=0;
                                                    cons2=2;

                                                    
                                                }
                                                else if(p==2){
                                                    start=i+1;
                                                    cons=1;
                                                    cons2=1;
                                                
                                                    
                                                }
                                                else if(p==3){
                                                    start=i-1;
                                                    cons=1;
                                                    cons2=-1;

                                                   
                                                }
                                                else if(p==4){
                                                    start=i+1;
                                                    cons=-1;
                                                    cons2=+1;

                                                    
                                                }
                                                else if(p==5){
                                                    start=i-1;
                                                    cons=-1;
                                                    cons2=-1;

                                                   
                                                }   


                                                p++;   


                                                for (int k = start; (k >= - max_X[cons*(k-start)+j+cons*cons2+N]) && (k <=  max_X[cons*cons2+cons*(k-start)+j+N]) && abs(cons*cons2+cons*(k-start)+j)<=N; k=k+cons2)
                                                {
                                                    if (temp_board_array[k][cons*(k-start)+j+cons*cons2] == -2*player_type){
                                                        attack++;
                                                        break;
                                                    }
                                                    else if (abs( temp_board_array[k][cons*(k-start)+j+cons*cons2]) ==1 && empty == true){
                                                        disc = true;
                                                        break;
                                                    }
                                                    else if (abs( temp_board_array[k][cons*(k-start)+j+cons*cons2]) ==0 && disc == true){
                                                        empty = true;
                                                        break;
                                                    }
                                                    else if (abs( temp_board_array[k][cons*(k-start)+j+cons*cons2]) ==1){
                                                        disc = true;
                                                    }
                                                    else if (abs( temp_board_array[k][cons*(k-start)+j+cons*cons2]) ==0){
                                                        empty = true;
                                                    }
                                                }
    }


        return attack;
    }   


    // int Board::eval_five(int N,int b1,int a1,int a2,int a3,int a4,int a5,int b2,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,int x5,int y5)
    // {
        
    //     // std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    //     // cerr << "Entered Eval ...\n";
         

          


    //     int points[] = {b1,a1,a2,a3,a4,a5,b2};

    //     int result = 0;
    //     int weights[] = {0,1,2,5,13,30}; // 0 ,1,2,3,4,5 discs or rings or blanks
        
    //     int flag = -1;

    //     // for (int i = 0; i < 7; ++i)
    //     // {
    //     //     if ((points[i]== 2 || abs(points[i])==3)&& flag==-1 )
    //     //     {
    //     //         flag = i;
    //     //     }
    //     //     else if((points[i] ==2 || abs(points[i])==3)&& (not (i==6 && flag==0)))  // found 2nd ring // 
    //     //     {


    //     //         for (int j = flag; j < i; j++)  // not to be evaluated 
    //     //         {
    //     //             points[j] = 2;
    //     //         }
    //     //     }

    //     // }
    //     int disc=0;
    //     int other_disc=0;
    //     int ring=0;
    //     int blank=0;
    //     int other_ring=0;
    //     for (int i = 1; i < 6; ++i)
    //     {
    //         if (points[i]==-1) // comp disc
    //         {
    //             disc = disc+1;
    //         }
    //         else if (points[i]==1) // comp disc
    //         {
    //             other_disc = other_disc+1;
    //         }
    //         else if (points[i]==-2) // comp ring
    //         {
    //             ring  = ring +1;
    //         }
    //         else if (points[i]==2) // comp ring
    //         {
    //             other_ring  = other_ring +1;
    //         }
    //         else if(points[i]==0){ blank = blank +1;} // blank
    //     }
    //     int my_disc_can_convert_by_other=0;
    //     if(disc==5){
    //         result +=1000;
    //     }
    //     if(disc==4&&(other_disc==1||blank==1||ring==1)){
    //         result+=600;
    //         if(temp_board_array[x1][y1]==-1){
    //             my_disc_can_convert_by_other+=how_good_disc_is(N,x1,y1);
    //         }
    //         if(temp_board_array[x2][y2]==-1){
    //             my_disc_can_convert_by_other+=how_good_disc_is(N,x2,y2);
    //         }
    //         if(temp_board_array[x3][y3]==-1){
    //             my_disc_can_convert_by_other+=how_good_disc_is(N,x3,y3);
    //         }
    //         if(temp_board_array[x3][y3]==-1){
    //             my_disc_can_convert_by_other+=how_good_disc_is(N,x4,y4);
    //         }
    //         if(temp_board_array[x4][y4]==-1){
    //             my_disc_can_convert_by_other+=how_good_disc_is(N,x5,y5);
    //         }
    //         result-=my_disc_can_convert_by_other*50;
    //     }


    //     if(disc==4&&other_ring==1){     ////////////////-2 -1 -1 -1 -1 2
    //         result-=250;
    //     }

    //     if(disc==3&&other_ring==0){
    //         result+=100;
    //         // my_disc_can_convert_by_other=0;

    //         // if(blank==2||(other_disc==1&&blank==1)){
    //         //     if(temp_board_array[x1][y1]==0){
    //         //     my_disc_can_convert_by_other+=my_ring_on_blank(N,x1,y1);
    //         //     }
    //         //     if(temp_board_array[x2][y2]==0){
    //         //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x2,y2);
    //         //     }
    //         //     if(temp_board_array[x3][y3]==0){
    //         //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x3,y3);
    //         //     }
    //         //     if(temp_board_array[x3][y3]==0){
    //         //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x4,y4);
    //         //     }
    //         //     if(temp_board_array[x4][y4]==0){
    //         //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x5,y5);
    //         //     }        
    //         //     result+=my_disc_can_convert_by_other*10;
    //         // }
    //         // else if (other_disc ==2){

    //         // }
    //         // else if (my_ring==2){

    //         // }
    //         // else if(my_ring==1 && blank==1 || my_ring==1 && other_disc==1){

    //         // }
    //         // else if ( other_disc==1&&blank ==1){
    //         // }

    //     }
    //     else if (disc==3 && other_ring != 0){
    //         result -= 100;
    //     }





    //     // else if(disc + ring == 5){
    //     //     result+=1000;
    //     //     if(temp_board_array[x1][y1]==-1){
    //     //         my_disc_can_convert_by_other+=how_good_disc_is(N,x1,y1);
    //     //     }
    //     //     if(temp_board_array[x2][y2]==-1){
    //     //         my_disc_can_convert_by_other+=how_good_disc_is(N,x2,y2);
    //     //     }
    //     //     if(temp_board_array[x3][y3]==-1){
    //     //         my_disc_can_convert_by_other+=how_good_disc_is(N,x3,y3);
    //     //     }
    //     //     if(temp_board_array[x3][y3]==-1){
    //     //         my_disc_can_convert_by_other+=how_good_disc_is(N,x4,y4);
    //     //     }
    //     //     if(temp_board_array[x4][y4]==-1){
    //     //         my_disc_can_convert_by_other+=how_good_disc_is(N,x5,y5);
    //     //     }
    //     //     result-=my_disc_can_convert_by_other*200;
    //     // }
    //     // if(disc==4 && other_ring==1){
    //     //     result-=1000;
    //     //     if(temp_board_array[x1][y1]==2){
    //     //         my_disc_can_convert_by_other+=how_good_ring_is(N,x1,y1);
    //     //     }
    //     //     if(temp_board_array[x2][y2]==2){
    //     //         my_disc_can_convert_by_other+=how_good_ring_is(N,x2,y2);
    //     //     }
    //     //     if(temp_board_array[x3][y3]==2){
    //     //         my_disc_can_convert_by_other+=how_good_ring_is(N,x3,y3);
    //     //     }
    //     //     if(temp_board_array[x3][y3]==2){
    //     //         my_disc_can_convert_by_other+=how_good_ring_is(N,x4,y4);
    //     //     }
    //     //     if(temp_board_array[x4][y4]==2){
    //     //         my_disc_can_convert_by_other+=how_good_ring_is(N,x5,y5);
    //     //     }
    //     //     result-=my_disc_can_convert_by_other*200;
    //     // }
    //     // if(disc==4&&other_disc==1){
    //     //     if(temp_board_array[x1][y1]==1){
    //     //         my_disc_can_convert_by_other+=how_good_disc_is(N,x1,y1);
    //     //     }
    //     //     if(temp_board_array[x2][y2]==1){
    //     //         my_disc_can_convert_by_other+=how_good_disc_is(N,x2,y2);
    //     //     }
    //     //     if(temp_board_array[x3][y3]==1){
    //     //         my_disc_can_convert_by_other+=how_good_disc_is(N,x3,y3);
    //     //     }
    //     //     if(temp_board_array[x3][y3]==1){
    //     //         my_disc_can_convert_by_other+=how_good_disc_is(N,x4,y4);
    //     //     }
    //     //     if(temp_board_array[x4][y4]==1){
    //     //         my_disc_can_convert_by_other+=how_good_disc_is(N,x5,y5);
    //     //     }
    //     //     result+=my_disc_can_convert_by_other*200;
    //     // }
    //     // if(disc==4&&blank==1){
    //     //     if(temp_board_array[x1][y1]==0){
    //     //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x1,y1);
    //     //     }
    //     //     if(temp_board_array[x2][y2]==0){
    //     //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x2,y2);
    //     //     }
    //     //     if(temp_board_array[x3][y3]==0){
    //     //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x3,y3);
    //     //     }
    //     //     if(temp_board_array[x3][y3]==0){
    //     //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x4,y4);
    //     //     }
    //     //     if(temp_board_array[x4][y4]==0){
    //     //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x5,y5);
    //     //     }
    //     //     result+=my_disc_can_convert_by_other*80;
    //     // }

        
    //     result = 10*weights[disc] +  3* weights[ring] + 1*weights[blank] ;

    //     // std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    //     //   std::chrono::duration<double, std::milli> time_span = t2 - t1;

    //     //   cerr << "It took in eval " << time_span.count() << " milliseconds inside eval five";
    //     //   cerr << endl;
    //       // exit(0);



    //     return result;
    // }


    int Board::eval_five(int N,int b1,int start_x,int start_y,int end_x,int end_y,int b2,int direction,int sign)
    {
        // cerr << direction << " S: "<< start_x<<" "<<start_y<<" E: "<<end_x<<" "<<end_y<<" \n";
        int result = 0;
        int disc=0;
        int other_disc=0;
        int ring=0;
        int blank=0;
        int other_ring=0;
        int other_ring_potential=0;
        int my_ring_potential=0;
        int flag = 0;
        int last_ring_x=0;
        int last_ring_y=0;
        int discs_after_last_ring= 0;
        int consec_5_disc = 0; 
        int consec_4_disc = 0;
        int other_consec_5_disc = 0; 
        int other_consec_4_disc = 0;

        int cons2=0;
        int cons=0;
        if (direction==1){
            cons2=2;
            cons=0;
        }
        else if (direction==2){
            cons2=1;
            cons=1;
        }
        else if (direction==3){
            cons2=-1;
            cons=1;
        }
        // int p=0;
        // for (int k = start; (k >= - max_X[cons*(k-start)+j+cons*cons2+N]) && (k <=  max_X[cons*cons2+cons*(k-start)+j+N]) && abs(cons*cons2+cons*(k-start)+j)<=N; k=k+cons2)
            for (int i = start_x; (i <= end_x&&(direction==1||direction==2))||(i>=end_x&&direction==3); i=i+cons2)
            {
                // p++;
                //cerr<< direction << " S: "<< start_x<<" "<<start_y<<" E: "<<end_x<<" "<<end_y<<" "<<"I: "<<i<<endl;
                if (temp_board_array[i][start_y]==-1*sign) // comp disc
                {
                    if (flag==1)   {
                        discs_after_last_ring--;
                    }
                    disc = disc+1;
                    
                    if (other_consec_5_disc<5){
                        other_consec_5_disc = 0;
                    }
                    if (other_consec_4_disc<4){
                        other_consec_4_disc = 0;
                    }

                    consec_5_disc++;
                    consec_4_disc++;
                }
                else if (temp_board_array[i][start_y]==1*sign) // comp disc
                {
                    if (flag==1)   {
                        discs_after_last_ring++;
                    }
                    other_disc = other_disc+1;

                    if (consec_5_disc<5){
                        consec_5_disc = 0;
                    }
                    if (consec_4_disc<4){
                        consec_4_disc = 0;
                    }
                    other_consec_5_disc++;
                    other_consec_4_disc++;
                }
                else if (temp_board_array[i][start_y]==-2*sign) // comp ring
                {
                    if (flag==0){
                        my_ring_potential =  other_disc - disc +1;
                        flag =1;
                    }
                    ring  = ring +1;
                    discs_after_last_ring=0;
                    if (consec_5_disc<5){
                        consec_5_disc = 0;
                    }
                    if (other_consec_5_disc<5){
                        other_consec_5_disc = 0;
                    }
                     if (other_consec_4_disc<4){
                        other_consec_4_disc = 0;
                    }

                }
                else if (temp_board_array[i][start_y]==2*sign) // comp ring
                {
                    if (flag==0){
                        other_ring_potential = disc - other_disc +1;
                        flag =1;
                    }
                    discs_after_last_ring=0;
                    other_ring  = other_ring +1;
                    if (consec_5_disc<5){
                        consec_5_disc = 0;
                    }
                    if (other_consec_5_disc<5){
                        other_consec_5_disc = 0;
                    }
                    if (consec_4_disc<4){
                        consec_4_disc = 0;
                    }
                }
                else if(temp_board_array[i][start_y]==0*sign){ blank = blank +1; cerr<< "error in evaluate_heuristic; "<< direction << " S: "<< start_x<<" "<<start_y<<" E: "<<end_x<<" "<<end_y<<" "<<"I: "<<i<<endl;} // blank
                start_y = cons+start_y;
            }
            if(abs(b1)==3){
                my_ring_potential=0;
                other_ring_potential=0;
            }
            if(discs_after_last_ring+1>my_ring_potential&&abs(b2)!=3){
                my_ring_potential=discs_after_last_ring+1;
            }
            if(-discs_after_last_ring+1>other_ring_potential&&abs(b2)!=3){
                other_ring_potential=-discs_after_last_ring+1;
            }
            if (my_ring_potential<0){
                my_ring_potential = 0;
            }
            if (other_ring_potential<0){
                other_ring_potential =0;
            }
            //cerr <<my_ring_potential<<" "<<other_ring_potential<<" "<<discs_after_last_ring<<" "<<consec_5_disc<<" "<<consec_4_disc<<" "<<other_disc<<endl;

        


        // std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        // cerr << "Entered Eval ...\n";
         

          


        // int points[] = {b1,a1,a2,a3,a4,a5,b2};

        // int result = 0;
        // int weights[] = {0,1,2,5,13,30}; // 0 ,1,2,3,4,5 discs or rings or blanks
        
        // int flag = -1;

        // // for (int i = 0; i < 7; ++i)
        // // {
        // //     if ((points[i]== 2 || abs(points[i])==3)&& flag==-1 )
        // //     {
        // //         flag = i;
        // //     }
        // //     else if((points[i] ==2 || abs(points[i])==3)&& (not (i==6 && flag==0)))  // found 2nd ring // 
        // //     {


        // //         for (int j = flag; j < i; j++)  // not to be evaluated 
        // //         {
        // //             points[j] = 2;
        // //         }
        // //     }

        // // }
        
      
        // int my_disc_can_convert_by_other=0;
        if(consec_5_disc>=5){
            result +=3000;
        }
        if (other_consec_5_disc >= 5){
            result -= 3000;
        }
        if(disc>=4){
            result += (disc - other_disc) * 150;
            if(ring>0 && consec_4_disc>=4){
                
                    result +=400;
            }
            if (other_ring==1&&consec_4_disc>=4&&ring==0){
                result -= (other_ring_potential-1)*40+1000;
                

            }
            else if (other_ring>0){
                result -= (other_ring_potential-1)*40;
                

            }
            
                
           
            // if (ring>0){    
            //     result += (my_ring_potential-1)*100;
            // }
            // result += (disc - other_disc) * 15;
            // result += ring*5;
        }

        if(other_disc>=4){
            result -= (other_disc - disc) * 150;
            if(other_ring>0 && other_consec_4_disc>=4){
                
                    result -=400;
            }
            if (ring==1&&other_consec_4_disc>=4&&other_ring==0){
                result += (my_ring_potential-1)*40+1000;
                

            }
            else if (ring>0){    
                result += (my_ring_potential-1)*40;
            }
            
            
            
            // result += (disc - other_disc) * 15;
            // result += ring*5;
        }
        result += (disc - other_disc) * 100;
        if (other_ring>0){
            result -= (other_ring_potential-1)*40;
            // result += (disc - other_disc) * 15;
            // if (ring>0){    
            //     result += (my_ring_potential-1)*100;
            // }
            // result += ring*5;
        }
        if (ring>0){
            result += (my_ring_potential-1)*40;   
            // result += (disc - other_disc) * 15;
            // result += ring*5;
        }
        
        result += ring*1;
        // else {
        //     result += (disc - other_disc) * 15;
        //     result += ring*5;
        // 
        //cerr << result << " <= Result ";
        // cerr << " S: "<< start_x<<" "<<start_y<<" E: "<<end_x<<" "<<end_y<<" "<<other_ring_potential <<" " <<my_ring_potential<<" "<<disc-other_disc<<" "<<result<<endl; 

        // if(disc==4&&(other_disc==1||ring==1)){
        //     result+=600;
        //     if(temp_board_array[x1][y1]==-1){
        //         my_disc_can_convert_by_other+=how_good_disc_is(N,x1,y1);
        //     }
        //     if(temp_board_array[x2][y2]==-1){
        //         my_disc_can_convert_by_other+=how_good_disc_is(N,x2,y2);
        //     }
        //     if(temp_board_array[x3][y3]==-1){
        //         my_disc_can_convert_by_other+=how_good_disc_is(N,x3,y3);
        //     }
        //     if(temp_board_array[x3][y3]==-1){
        //         my_disc_can_convert_by_other+=how_good_disc_is(N,x4,y4);
        //     }
        //     if(temp_board_array[x4][y4]==-1){
        //         my_disc_can_convert_by_other+=how_good_disc_is(N,x5,y5);
        //     }
        //     result-=my_disc_can_convert_by_other*50;
        // }


        // if(disc==4&&other_ring==1){     ////////////////-2 -1 -1 -1 -1 2
        //     result-=250;
        // }

        // if(disc==3&&other_ring==0){
        //     result+=100;
        //     // my_disc_can_convert_by_other=0;

        //     // if(blank==2||(other_disc==1&&blank==1)){
        //     //     if(temp_board_array[x1][y1]==0){
        //     //     my_disc_can_convert_by_other+=my_ring_on_blank(N,x1,y1);
        //     //     }
        //     //     if(temp_board_array[x2][y2]==0){
        //     //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x2,y2);
        //     //     }
        //     //     if(temp_board_array[x3][y3]==0){
        //     //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x3,y3);
        //     //     }
        //     //     if(temp_board_array[x3][y3]==0){
        //     //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x4,y4);
        //     //     }
        //     //     if(temp_board_array[x4][y4]==0){
        //     //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x5,y5);
        //     //     }        
        //     //     result+=my_disc_can_convert_by_other*10;
        //     // }
        //     // else if (other_disc ==2){

        //     // }
        //     // else if (my_ring==2){

        //     // }
        //     // else if(my_ring==1 && blank==1 || my_ring==1 && other_disc==1){

        //     // }
        //     // else if ( other_disc==1&&blank ==1){
        //     // }

        // }
        // else if (disc==3 && other_ring != 0){
        //     result -= 100;
        // }





        // // else if(disc + ring == 5){
        // //     result+=1000;
        // //     if(temp_board_array[x1][y1]==-1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x1,y1);
        // //     }
        // //     if(temp_board_array[x2][y2]==-1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x2,y2);
        // //     }
        // //     if(temp_board_array[x3][y3]==-1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x3,y3);
        // //     }
        // //     if(temp_board_array[x3][y3]==-1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x4,y4);
        // //     }
        // //     if(temp_board_array[x4][y4]==-1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x5,y5);
        // //     }
        // //     result-=my_disc_can_convert_by_other*200;
        // // }
        // // if(disc==4 && other_ring==1){
        // //     result-=1000;
        // //     if(temp_board_array[x1][y1]==2){
        // //         my_disc_can_convert_by_other+=how_good_ring_is(N,x1,y1);
        // //     }
        // //     if(temp_board_array[x2][y2]==2){
        // //         my_disc_can_convert_by_other+=how_good_ring_is(N,x2,y2);
        // //     }
        // //     if(temp_board_array[x3][y3]==2){
        // //         my_disc_can_convert_by_other+=how_good_ring_is(N,x3,y3);
        // //     }
        // //     if(temp_board_array[x3][y3]==2){
        // //         my_disc_can_convert_by_other+=how_good_ring_is(N,x4,y4);
        // //     }
        // //     if(temp_board_array[x4][y4]==2){
        // //         my_disc_can_convert_by_other+=how_good_ring_is(N,x5,y5);
        // //     }
        // //     result-=my_disc_can_convert_by_other*200;
        // // }
        // // if(disc==4&&other_disc==1){
        // //     if(temp_board_array[x1][y1]==1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x1,y1);
        // //     }
        // //     if(temp_board_array[x2][y2]==1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x2,y2);
        // //     }
        // //     if(temp_board_array[x3][y3]==1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x3,y3);
        // //     }
        // //     if(temp_board_array[x3][y3]==1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x4,y4);
        // //     }
        // //     if(temp_board_array[x4][y4]==1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x5,y5);
        // //     }
        // //     result+=my_disc_can_convert_by_other*200;
        // // }
        // // if(disc==4&&blank==1){
        // //     if(temp_board_array[x1][y1]==0){
        // //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x1,y1);
        // //     }
        // //     if(temp_board_array[x2][y2]==0){
        // //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x2,y2);
        // //     }
        // //     if(temp_board_array[x3][y3]==0){
        // //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x3,y3);
        // //     }
        // //     if(temp_board_array[x3][y3]==0){
        // //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x4,y4);
        // //     }
        // //     if(temp_board_array[x4][y4]==0){
        // //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x5,y5);
        // //     }
        // //     result+=my_disc_can_convert_by_other*80;
        // // }

        
        // result = 10*weights[disc] +  3* weights[ring] + 1*weights[blank] ;

        // std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        //   std::chrono::duration<double, std::milli> time_span = t2 - t1;

        //   cerr << "It took in eval " << time_span.count() << " milliseconds inside eval five";
        //   cerr << endl;
          // exit(0);



        return result;
    }


     int Board::eval_six(int N,int b1,int start_x,int start_y,int end_x,int end_y,int b2,int direction,int sign)
    {
        // cerr << direction << " S: "<< start_x<<" "<<start_y<<" E: "<<end_x<<" "<<end_y<<" \n";
        int result = 0;
        int disc=0;
        int other_disc=0;
        int ring=0;
        int blank=0;
        int other_ring=0;
        int other_ring_potential=0;
        int my_ring_potential=0;
        int flag = 0;
        int last_ring_x=0;
        int last_ring_y=0;
        int discs_after_last_ring= 0;
        int consec_6_disc = 0; 
        int consec_5_disc = 0;
        int other_consec_6_disc = 0; 
        int other_consec_5_disc = 0;

        int cons2=0;
        int cons=0;
        if (direction==1){
            cons2=2;
            cons=0;
        }
        else if (direction==2){
            cons2=1;
            cons=1;
        }
        else if (direction==3){
            cons2=-1;
            cons=1;
        }
        // int p=0;
        // for (int k = start; (k >= - max_X[cons*(k-start)+j+cons*cons2+N]) && (k <=  max_X[cons*cons2+cons*(k-start)+j+N]) && abs(cons*cons2+cons*(k-start)+j)<=N; k=k+cons2)
            for (int i = start_x; (i <= end_x&&(direction==1||direction==2))||(i>=end_x&&direction==3); i=i+cons2)
            {
                // p++;
                //cerr<< direction << " S: "<< start_x<<" "<<start_y<<" E: "<<end_x<<" "<<end_y<<" "<<"I: "<<i<<endl;
                if (temp_board_array[i][start_y]==-1*sign) // comp disc
                {
                    if (flag==1)   {
                        discs_after_last_ring--;
                    }
                    disc = disc+1;
                    
                    if (other_consec_6_disc<6){
                        other_consec_6_disc = 0;
                    }
                    if (other_consec_5_disc<5){
                        other_consec_5_disc = 0;
                    }

                    consec_6_disc++;
                    consec_5_disc++;
                }
                else if (temp_board_array[i][start_y]==1*sign) // comp disc
                {
                    if (flag==1)   {
                        discs_after_last_ring++;
                    }
                    other_disc = other_disc+1;

                    if (consec_6_disc<6){
                        consec_6_disc = 0;
                    }
                    if (consec_5_disc<5){
                        consec_5_disc = 0;
                    }
                    other_consec_6_disc++;
                    other_consec_5_disc++;
                }
                else if (temp_board_array[i][start_y]==-2*sign) // comp ring
                {
                    if (flag==0){
                        my_ring_potential =  other_disc - disc +1;
                        flag =1;
                    }
                    ring  = ring +1;
                    discs_after_last_ring=0;
                    if (consec_6_disc<6){
                        consec_6_disc = 0;
                    }
                    if (other_consec_6_disc<6){
                        other_consec_6_disc = 0;
                    }
                     if (other_consec_5_disc<5){
                        other_consec_5_disc = 0;
                    }

                }
                else if (temp_board_array[i][start_y]==2*sign) // comp ring
                {
                    if (flag==0){
                        other_ring_potential = disc - other_disc +1;
                        flag =1;
                    }
                    discs_after_last_ring=0;
                    other_ring  = other_ring +1;
                    if (consec_6_disc<6){
                        consec_6_disc = 0;
                    }
                    if (other_consec_6_disc<6){
                        other_consec_6_disc = 0;
                    }
                    if (consec_5_disc<5){
                        consec_5_disc = 0;
                    }
                }
                else if(temp_board_array[i][start_y]==0*sign){ blank = blank +1; cerr<< "error in evaluate_heuristic; "<< direction << " S: "<< start_x<<" "<<start_y<<" E: "<<end_x<<" "<<end_y<<" "<<"I: "<<i<<endl;} // blank
                start_y = cons+start_y;
            }
            if(abs(b1)==3){
                my_ring_potential=0;
                other_ring_potential=0;
            }
            if(discs_after_last_ring+1>my_ring_potential&&abs(b2)!=3){
                my_ring_potential=discs_after_last_ring+1;
            }
            if(-discs_after_last_ring+1>other_ring_potential&&abs(b2)!=3){
                other_ring_potential=-discs_after_last_ring+1;
            }
            if (my_ring_potential<0){
                my_ring_potential = 0;
            }
            if (other_ring_potential<0){
                other_ring_potential =0;
            }
            //cerr <<my_ring_potential<<" "<<other_ring_potential<<" "<<discs_after_last_ring<<" "<<consec_6_disc<<" "<<consec_5_disc<<" "<<other_disc<<endl;

        


        // std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        // cerr << "Entered Eval ...\n";
         

          


        // int points[] = {b1,a1,a2,a3,a4,a5,b2};

        // int result = 0;
        // int weights[] = {0,1,2,5,13,30}; // 0 ,1,2,3,4,5 discs or rings or blanks
        
        // int flag = -1;

        // // for (int i = 0; i < 7; ++i)
        // // {
        // //     if ((points[i]== 2 || abs(points[i])==3)&& flag==-1 )
        // //     {
        // //         flag = i;
        // //     }
        // //     else if((points[i] ==2 || abs(points[i])==3)&& (not (i==6 && flag==0)))  // found 2nd ring // 
        // //     {


        // //         for (int j = flag; j < i; j++)  // not to be evaluated 
        // //         {
        // //             points[j] = 2;
        // //         }
        // //     }

        // // }
        
      
        // int my_disc_can_convert_by_other=0;
        if(consec_6_disc>=6){
            result +=4000;
        }
        if (other_consec_6_disc >= 6){
            result -= 4000;
        }
        if(disc>=5){
            result += (disc - other_disc) * 150;
            if(ring>0 && consec_5_disc>=5){
                
                    result +=600;
            }
            if (other_ring==1&&consec_5_disc>=4&&ring==0){
                result -= (other_ring_potential-1)*40+1250;
                

            }
            else if (other_ring>0){
                result -= (other_ring_potential-1)*40;
                

            }
            
                
           
            // if (ring>0){    
            //     result += (my_ring_potential-1)*100;
            // }
            // result += (disc - other_disc) * 15;
            // result += ring*5;
        }

        if(other_disc>=5){
            result -= (other_disc - disc) * 150;
            if(other_ring>0 && other_consec_5_disc>=4){
                
                    result -=600;
            }
            if (ring==1&&other_consec_5_disc>=4&&other_ring==0){
                result += (my_ring_potential-1)*40+1250;
                

            }
            else if (ring>0){    
                result += (my_ring_potential-1)*40;
            }
            
            
            
            // result += (disc - other_disc) * 15;
            // result += ring*5;
        }
        result += (disc - other_disc) * 100;
        if (other_ring>0){
            result -= (other_ring_potential-1)*40;
            // result += (disc - other_disc) * 15;
            // if (ring>0){    
            //     result += (my_ring_potential-1)*100;
            // }
            // result += ring*5;
        }
        if (ring>0){
            result += (my_ring_potential-1)*40;   
            // result += (disc - other_disc) * 15;
            // result += ring*5;
        }
        
        result += ring*1;
        // else {
        //     result += (disc - other_disc) * 15;
        //     result += ring*5;
        // 
        //cerr << result << " <= Result ";
        // cerr << " S: "<< start_x<<" "<<start_y<<" E: "<<end_x<<" "<<end_y<<" "<<other_ring_potential <<" " <<my_ring_potential<<" "<<disc-other_disc<<" "<<result<<endl; 

        // if(disc==4&&(other_disc==1||ring==1)){
        //     result+=600;
        //     if(temp_board_array[x1][y1]==-1){
        //         my_disc_can_convert_by_other+=how_good_disc_is(N,x1,y1);
        //     }
        //     if(temp_board_array[x2][y2]==-1){
        //         my_disc_can_convert_by_other+=how_good_disc_is(N,x2,y2);
        //     }
        //     if(temp_board_array[x3][y3]==-1){
        //         my_disc_can_convert_by_other+=how_good_disc_is(N,x3,y3);
        //     }
        //     if(temp_board_array[x3][y3]==-1){
        //         my_disc_can_convert_by_other+=how_good_disc_is(N,x4,y4);
        //     }
        //     if(temp_board_array[x4][y4]==-1){
        //         my_disc_can_convert_by_other+=how_good_disc_is(N,x5,y5);
        //     }
        //     result-=my_disc_can_convert_by_other*50;
        // }


        // if(disc==4&&other_ring==1){     ////////////////-2 -1 -1 -1 -1 2
        //     result-=250;
        // }

        // if(disc==3&&other_ring==0){
        //     result+=100;
        //     // my_disc_can_convert_by_other=0;

        //     // if(blank==2||(other_disc==1&&blank==1)){
        //     //     if(temp_board_array[x1][y1]==0){
        //     //     my_disc_can_convert_by_other+=my_ring_on_blank(N,x1,y1);
        //     //     }
        //     //     if(temp_board_array[x2][y2]==0){
        //     //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x2,y2);
        //     //     }
        //     //     if(temp_board_array[x3][y3]==0){
        //     //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x3,y3);
        //     //     }
        //     //     if(temp_board_array[x3][y3]==0){
        //     //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x4,y4);
        //     //     }
        //     //     if(temp_board_array[x4][y4]==0){
        //     //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x5,y5);
        //     //     }        
        //     //     result+=my_disc_can_convert_by_other*10;
        //     // }
        //     // else if (other_disc ==2){

        //     // }
        //     // else if (my_ring==2){

        //     // }
        //     // else if(my_ring==1 && blank==1 || my_ring==1 && other_disc==1){

        //     // }
        //     // else if ( other_disc==1&&blank ==1){
        //     // }

        // }
        // else if (disc==3 && other_ring != 0){
        //     result -= 100;
        // }





        // // else if(disc + ring == 5){
        // //     result+=1000;
        // //     if(temp_board_array[x1][y1]==-1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x1,y1);
        // //     }
        // //     if(temp_board_array[x2][y2]==-1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x2,y2);
        // //     }
        // //     if(temp_board_array[x3][y3]==-1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x3,y3);
        // //     }
        // //     if(temp_board_array[x3][y3]==-1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x4,y4);
        // //     }
        // //     if(temp_board_array[x4][y4]==-1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x5,y5);
        // //     }
        // //     result-=my_disc_can_convert_by_other*200;
        // // }
        // // if(disc==4 && other_ring==1){
        // //     result-=1000;
        // //     if(temp_board_array[x1][y1]==2){
        // //         my_disc_can_convert_by_other+=how_good_ring_is(N,x1,y1);
        // //     }
        // //     if(temp_board_array[x2][y2]==2){
        // //         my_disc_can_convert_by_other+=how_good_ring_is(N,x2,y2);
        // //     }
        // //     if(temp_board_array[x3][y3]==2){
        // //         my_disc_can_convert_by_other+=how_good_ring_is(N,x3,y3);
        // //     }
        // //     if(temp_board_array[x3][y3]==2){
        // //         my_disc_can_convert_by_other+=how_good_ring_is(N,x4,y4);
        // //     }
        // //     if(temp_board_array[x4][y4]==2){
        // //         my_disc_can_convert_by_other+=how_good_ring_is(N,x5,y5);
        // //     }
        // //     result-=my_disc_can_convert_by_other*200;
        // // }
        // // if(disc==4&&other_disc==1){
        // //     if(temp_board_array[x1][y1]==1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x1,y1);
        // //     }
        // //     if(temp_board_array[x2][y2]==1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x2,y2);
        // //     }
        // //     if(temp_board_array[x3][y3]==1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x3,y3);
        // //     }
        // //     if(temp_board_array[x3][y3]==1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x4,y4);
        // //     }
        // //     if(temp_board_array[x4][y4]==1){
        // //         my_disc_can_convert_by_other+=how_good_disc_is(N,x5,y5);
        // //     }
        // //     result+=my_disc_can_convert_by_other*200;
        // // }
        // // if(disc==4&&blank==1){
        // //     if(temp_board_array[x1][y1]==0){
        // //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x1,y1);
        // //     }
        // //     if(temp_board_array[x2][y2]==0){
        // //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x2,y2);
        // //     }
        // //     if(temp_board_array[x3][y3]==0){
        // //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x3,y3);
        // //     }
        // //     if(temp_board_array[x3][y3]==0){
        // //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x4,y4);
        // //     }
        // //     if(temp_board_array[x4][y4]==0){
        // //         my_disc_can_convert_by_other+=my_ring_on_blank(N,x5,y5);
        // //     }
        // //     result+=my_disc_can_convert_by_other*80;
        // // }

        
        // result = 10*weights[disc] +  3* weights[ring] + 1*weights[blank] ;

        // std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        //   std::chrono::duration<double, std::milli> time_span = t2 - t1;

        //   cerr << "It took in eval " << time_span.count() << " milliseconds inside eval five";
        //   cerr << endl;
          // exit(0);



        return result;
    }

   
    int Board::each_ring(int N,int x, int y){
        
        int result = 0;
        int weights[] = {0,1,2,5,13,30}; // 0 ,1,2,3,4,5 discs or rings or blanks
        int my_disc_can_convert_by_other=0;
        int other_disc_can_convert_to_my=0;
        int other_ring_good=0;
        int my_ring_good=0;
        int blank=0;
        int flag = -1;
        if(temp_board_array[x][y]==-1){
            my_disc_can_convert_by_other+=how_good_disc_is(N,x,y);
        }
        if(temp_board_array[x][y]==1){
            other_disc_can_convert_to_my+=how_good_disc_is(N,x,y);
        }
        if(temp_board_array[x][y]==-2){
            my_ring_good+=how_good_ring_is(N,x,y);
        }
        if(temp_board_array[x][y]==2){
            other_ring_good+=how_good_ring_is(N,x,y);
        }
        else{
            blank++;
        }
        result+=-4*my_disc_can_convert_by_other+4*other_disc_can_convert_to_my+20*my_ring_good-20*other_ring_good;
        return result;
    }

    // int Board::evaluate_heuristic(int N,int K){
    //     int result = 0;
    //     int b1 = -3 ; 
    //     int b2 = -3 ; 

    //     int max_X[2*N+1];
    //    int max_5[]= {3,6,7,8,9,8,9,8,7,6,3};
    //     // int max_6 = {3,5,6,7,8,9,8,9,8,7,6,3};
    //     int max_6[] = {4,7,8,9,10,11,10,11,10,9,8,7,4};
    //     if (N==5){
    //        for (int i = 0; i < 2*N+1; ++i)
    //        {
    //            max_X[i] = max_5[i];
    //        }
    //     }
    //     else{
    //        for (int i = 0; i < 2*N+1; ++i)
    //        {
    //            max_X[i] = max_6[i];
    //        }
    //     }

    //     for (int i = -(N-1); i < (N); i++) // y axis
    //     {
            
    //         int y_m = max_X[i+4];
    //         for (int j = -y_m; j < y_m-2*(K-1)+1; j=j+2) // x-axis
    //         {   
    //             if (j== -y_m)
    //             {
    //                 b1 = -3;
    //                 b2 = temp_board_array[11+j+2*K][7+i];
    //             }
    //             else if (j== y_m - 2*(K-1))
    //             {
    //                 b2 = -3;
    //                 b1 = temp_board_array[11+j-2][7+i];
    //             }
    //             else
    //             {
    //                 b1 = temp_board_array[11+j-2][7+i];
    //                 b2 = temp_board_array[11+j+2*K][7+i];   
    //             }
    //             if(K==5){
    //                 result = result + eval_five(N,b1,temp_board_array[11+j][7+i],temp_board_array[11+j+2][7+i],temp_board_array[11+j+4][7+i],temp_board_array[11+j+6][7+i],temp_board_array[11+j+8][7+i],b2,11+j,11+i,11+j+2,11+i,11+j+4,11+i,11+j+6,11+i,11+j+8,11+i);
    //                 result = result - eval_five(N,-b1,-temp_board_array[11+j][7+i],-temp_board_array[11+j+2][7+i],-temp_board_array[11+j+4][7+i],-temp_board_array[11+j+6][7+i],-temp_board_array[11+j+8][7+i],-b2,11+j,11+i,11+j+2,11+i,11+j+4,11+i,11+j+6,11+i,11+j+8,11+i);
    //             }
    //             else{
    //                 result = result + eval_six(N,b1,temp_board_array[11+j][7+i],temp_board_array[11+j+2][7+i],temp_board_array[11+j+4][7+i],temp_board_array[11+j+6][7+i],temp_board_array[11+j+8][7+i],temp_board_array[11+j+10][7+i],b2,11+j,11+i,11+j+2,11+i,11+j+4,11+i,11+j+6,11+i,11+j+8,11+i,11+j+10,11+i);
    //                 result = result - eval_six(N,-b1,-temp_board_array[11+j][7+i],-temp_board_array[11+j+2][7+i],-temp_board_array[11+j+4][7+i],-temp_board_array[11+j+6][7+i],-temp_board_array[11+j+8][7+i],-temp_board_array[11+j+10][7+i],-b2,11+j,11+i,11+j+2,11+i,11+j+4,11+i,11+j+6,11+i,11+j+8,11+i,11+j+10,11+i);   
    //             }
    //         }
    //     }


    //     // int y_cor[] = {-1,-2,-3,-4,-4,-5,-5,-5,-5} ; 
    //     // int x_cor[] = {-9,-8,-7,-6,-4,-3,-1,1,3};
    //     // int in_line[] = {2,3,4,5,4,5,4,3,2};


    //     int y_cor[2*N-1];
    //     int y_cor_5[] = {-1,-2,-3,-4,-4,-5,-5,-5,-5} ; 
    //     int y_cor_6[] = {-1,-2,-3,-4,-5,-5,-6,-6,-6,-6,-6}; // size 13

    //     int x_cor[2*N-1];
    //     int x_cor_5[] = {-9,-8,-7,-6,-4,-3,-1,1,3};
    //     int x_cor_6[] = {-11,-10,-9,-8,-7,-5,-4,-2,0,2,4};
        
    //     int in_line[2*N-1];
    //     int in_line_5[] = {2,3,4,5,4,5,4,3,2};
    //     int in_line_6_6[] = {2,3,4,5,6,5,6,5,4,3,2};
    //     int in_line_6_5[] = {3,4,5,6,7,6,7,6,5,4,3};

    //     //Initialization
    //     for (int i = 0; i < 2*N-1; ++i)
    //     {
    //         if (N==6)  
    //         {
    //             if (K==6)  {
    //                 in_line[i] = in_line_6_6[i];
    //             }
    //             else
    //             {
    //                 in_line[i] = in_line_6_5[i];   
    //             }


    //             x_cor[i] = x_cor_6[i];
    //             y_cor[i] = y_cor_6[i];
    //         }
    //         else
    //         {
    //             x_cor[i] = x_cor_5[i];
    //             y_cor[i] = y_cor_5[i];
    //             in_line[i] = in_line_5[6];   
    //         }
    //     }



    //     int x = 0;
    //     int y = 0;
    //     int points_count = 0;
        
    //     // Y = X
    //     for (int i = 0; i < 2*N-1; ++i) 
    //     {
    //         x = x_cor[i];
    //         y = y_cor[i];
    //         while(true)
    //         {
                
    //             if (points_count==0)
    //             {
    //                 b1 = -3;
    //                 b2 = temp_board_array[11+x+K][7+y+K];
    //             }
    //             else if (points_count == in_line[i])
    //             {
    //                 b2 = -3;
    //                 b1 = temp_board_array[11+x-1][7+y-1];
    //             }
    //             else
    //             {
    //                 b1 = temp_board_array[11+x-1][7+y-1];
    //                 b2 = temp_board_array[11+x+K][7+y+K];
    //             }
    //             if (K==5){   
                   
    //                                                       // std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    //                 // cerr << "       Eval 5 Entering stars123...\n";

    //                 result = result + eval_five(N,b1,temp_board_array[11+x][7+y],temp_board_array[11+x+1][7+y+1],temp_board_array[11+x+2][7+y+2],temp_board_array[11+x+3][7+y+3],temp_board_array[11+x+4][7+y+4],b2,11+x,11+y,11+x+1,11+y+1,11+x+2,11+y+2,11+x+3,11+y+3,11+x+4,11+y+4);
                    
    //                 result = result - eval_five(N,-b1,-temp_board_array[11+x][7+y],-temp_board_array[11+x+1][7+y+1],-temp_board_array[11+x+2][7+y+2],-temp_board_array[11+x+3][7+y+3],-temp_board_array[11+x+4][7+y+4],-b2,11+x,7+y,11+x+1,7+y+1,11+x+2,7+y+2,11+x+3,7+y+3,11+x+4,7+y+4);


    //                                                       // std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    //                                                       // std::chrono::duration<double, std::milli> time_span = t2 - t1;

    //                                                       // cerr << "             It took me " << time_span.count() << " milliseconds in eval heuristic";
    //                                                       // cerr << endl;
    //                                                       // exit(0);
    //             }
    //             else{
    //                 result = result + eval_six(N,b1,temp_board_array[11+x][7+y],temp_board_array[11+x+1][7+y+1],temp_board_array[11+x+2][7+y+2],temp_board_array[11+x+3][7+y+3],temp_board_array[11+x+4][7+y+4],temp_board_array[11+x+5][7+y+5],b2,11+x,11+y,11+x+1,11+y+1,11+x+2,11+y+2,11+x+3,11+y+3,11+x+4,11+y+4,11+x+5,11+y+5);
    //                 result = result - eval_six(N,-b1,-temp_board_array[11+x][7+y],-temp_board_array[11+x+1][7+y+1],-temp_board_array[11+x+2][7+y+2],-temp_board_array[11+x+3][7+y+3],-temp_board_array[11+x+4][7+y+4],-temp_board_array[11+x+5][7+y+5],-b2,11+x,11+y,11+x+1,11+y+1,11+x+2,11+y+2,11+x+3,11+y+3,11+x+4,11+y+4,11+x+5,11+y+5);
    //             }
    //             x = x+1;
    //             y = y+1;
    //             if (points_count==in_line[i])
    //             {
    //                 points_count=0;

    //                 break;
    //             }
    //             points_count = points_count +1; 
    //         }

    //     }

    //     //// Y = - X
    //     // int y_cord[] = {-5,-5,-5,-5,-4,-4,-3,-2,-1};
    //     // int x_cord[] = {-3,-1,1,3,4,6,7,8,9};


    //     int y_cord[2*N-1];
    //     int y_cord_5[] = {-5,-5,-5,-5,-4,-4,-3,-2,-1};
    //     int y_cord_6[] = {-6,-6,-6,-6,-6,-5,-5,-4,-3,-2,-1};
    //     int x_cord[2*N-1];
    //     int x_cord_5[] = {-3,-1,1,3,4,6,7,8,9};
    //     int x_cord_6[] = {-4,-2,0,2,4,5,7,8,9,10,11};

    //     for (int i = 0; i < 2*N-1; ++i)
    //     {
    //         if (N==6)  
    //         {
    //             x_cord[i] = x_cord_6[i];
    //             y_cord[i] = y_cord_6[i];
    //         }
    //         else
    //         {
    //             x_cord[i] = x_cord_5[i];
    //             y_cord[i] = y_cord_5[i];
    //         }
    //     }


    //     points_count=0;

        
    //     for (int i = 0; i < 2*N-1; ++i)
    //     {
    //         x = x_cord[i];
    //         y = y_cord[i];
    //         while(true)
    //         {
                
    //             if (points_count==0)
    //             {
    //                 b1 = -3;
    //                 b2 = temp_board_array[11+x-K][7+y+K];
    //             }
    //             else if (points_count == in_line[i])
    //             {
    //                 b2 = -3;
    //                 b1 = temp_board_array[11+x+1][7+y-1];
    //             }
    //             else
    //             {
    //                 b1 = temp_board_array[11+x+1][7+y-1];
    //                 b2 = temp_board_array[11+x-K][7+y+K];
    //             }
    //             if (K==5){    
    //                 result = result + eval_five(N,b1,temp_board_array[11+x][7+y],temp_board_array[11+x-1][7+y+1],temp_board_array[11+x-2][7+y+2],temp_board_array[11+x-3][7+y+3],temp_board_array[11+x-4][7+y+4],b2,11+x,11+y,11+x-1,11+y+1,11+x-2,11+y+2,11+x-3,11+y+3,11+x-4,11+y+4);
    //                 result = result -eval_five(N,-b1,-temp_board_array[11+x][7+y],-temp_board_array[11+x-1][7+y+1],-temp_board_array[11+x-2][7+y+2],-temp_board_array[11+x-3][7+y+3],-temp_board_array[11+x-4][7+y+4],-b2,11+x,11+y,11+x-1,11+y+1,11+x-2,11+y+2,11+x-3,11+y+3,11+x-4,11+y+4);
    //             }
    //             else{
    //                 result = result + eval_six(N,b1,temp_board_array[11+x][7+y],temp_board_array[11+x-1][7+y+1],temp_board_array[11+x-2][7+y+2],temp_board_array[11+x-3][7+y+3],temp_board_array[11+x-4][7+y+4],temp_board_array[11+x-5][7+y+5],b2,11+x,11+y,11+x-1,11+y+1,11+x-2,11+y+2,11+x-3,11+y+3,11+x-4,11+y+4,11+x-5,11+y+5);
    //                 result = result -eval_six(N,-b1,-temp_board_array[11+x][7+y],-temp_board_array[11+x-1][7+y+1],-temp_board_array[11+x-2][7+y+2],-temp_board_array[11+x-3][7+y+3],-temp_board_array[11+x-4][7+y+4],-temp_board_array[11+x-5][7+y+5],-b2,11+x,11+y,11+x-1,11+y+1,11+x-2,11+y+2,11+x-3,11+y+3,11+x-4,11+y+4,11+x-5,11+y+5);
    //             }

    //             x = x-1;
    //             y = y+1;
    //             if (points_count==in_line[i])
    //             {
    //                 points_count=0;

    //                 break;
    //             }
    //             points_count = points_count +1;     
    //         }

    //     }
        
        
    //    return result;


    // }
    int Board::evaluate_heuristic(int N,int K){
        int result = 0;
        int b1 = -3 ; 
        int b2 = -3 ; 

        int max_X[2*N+1];
       int max_5[]= {6,7,8,9,8,9,8,7,6};
        // int max_6 = {3,5,6,7,8,9,8,9,8,7,6,3};
        int max_6[] = {7,8,9,10,11,10,11,10,9,8,7};


        int  blank_start_found = 0;
        int  blank_x =0;
        int  blank_y=0;
        int  element_count = 0;

        if (N==5){
           for (int i = 0; i < 2*N+1; ++i)
           {
               max_X[i] = max_5[i];
           }
        }
        else{
           for (int i = 0; i < 2*N+1; ++i)
           {
               max_X[i] = max_6[i];
           }
        }

        for (int i = -(N-1); i < (N); i++) // y axis
        {
            
            int y_m = max_X[i+(N-1)];
            blank_start_found = 0;
            blank_x = 11-y_m;
            blank_y=7+i; 
            element_count=0;
            b1 = -3 ; 
            b2 = -3 ;
            for (int j = -y_m; j < y_m+1; j=j+2) // x-axis
            {   
            //cerr << "i: "<< i <<" "<< j<<" "<<i<<" "<<temp_board_array[11+j][7+i]<<" "<<blank_start_found<<" "<<element_count<<" "<<b1<<endl ; 

                if (temp_board_array[11+j][7+i]==0 && blank_start_found==0){
                    blank_x = 11+j+2;
                    blank_y = 7+i;
                    blank_start_found=1;
                    if (abs(b1)==3 && j!= -y_m && element_count >= 2){
                        if(K==5){
                            result = result + eval_five(N,b1,11-y_m,7+i,11+j-2,7+i,b2,1,1);
                            // result = result - eval_five(N,b1,11-y_m,7+i,11+j-2,7+i,b2,1,-1);
                        }
                        else{
                            result = result + eval_six(N,b1,11-y_m,7+i,11+j-2,7+i,b2,1,1);
                            // result = result - eval_five(N,b1,11-y_m,7+i,11+j-2,7+i,b2,1,-1);   
                        }
                    }
                    b1=0;
                    element_count = 0;

                }
                else if(temp_board_array[11+j][7+i]==0 && blank_start_found==1 && element_count >= 2){
                    if(K==5){
                        result = result + eval_five(N,b1,blank_x,blank_y,11+j-2,7+i,b2,1,1);
                        // result = result - eval_five(N,b1,blank_x,blank_y,11+j-2,7+i,b2,1,-1);
                    }
                    else{
                        result = result + eval_six(N,b1,blank_x,blank_y,11+j-2,7+i,b2,1,1);
                        // result = result - eval_five(N,b1,blank_x,blank_y,11+j-2,7+i,b2,1,-1);   
                    }
                    blank_x = 11+j+2;
                    blank_y = 7+i;
                    blank_start_found=1;
                    element_count = 0;
                }
                else if(temp_board_array[11+j][7+i]==0 && blank_start_found==1 && element_count < 2){
                    blank_x = 11+j+2;
                    blank_y = 7+i;
                    blank_start_found=1;
                    element_count = 0;
                }
                
                else if (temp_board_array[11+j][7+i]!=0){
                    element_count++;
                }


            }
            if(element_count>=2){
                if (temp_board_array[11+y_m][7+i]!= 0){

                    if(K==5){
                        result = result + eval_five(N,b1,blank_x,blank_y,11+y_m,7+i,3,1,1);
                        // result = result - eval_five(N,b1,blank_x,blank_y,11+y_m,7+i,3,1,-1);
                    }
                    else{
                        result = result + eval_six(N,b1,blank_x,blank_y,11+y_m,7+i,3,1,1);
                        // result = result - eval_five(N,b1,blank_x,blank_y,11+y_m,7+i,3,1,-1);   
                    }
                }
            }
        }


        // int y_cor[] = {-1,-2,-3,-4,-4,-5,-5,-5,-5} ; 
        // int x_cor[] = {-9,-8,-7,-6,-4,-3,-1,1,3};
        // int in_line[] = {2,3,4,5,4,5,4,3,2};


        int y_cor[2*N-1];
        int y_cor_5[] = {-1,-2,-3,-4,-4,-5,-5,-5,-5} ; 
        int y_cor_6[] = {-1,-2,-3,-4,-5,-5,-6,-6,-6,-6,-6}; // size 13

        int x_cor[2*N-1];
        int x_cor_5[] = {-9,-8,-7,-6,-4,-3,-1,1,3};
        int x_cor_6[] = {-11,-10,-9,-8,-7,-5,-4,-2,0,2,4};
        
        int in_line[2*N-1];
        int in_line_5[] = {6,7,8,9,8,9,8,7,6};//{2,3,4,5,4,5,4,3,2};
        int in_line_6_6[] = {7,8,9,10,11,10,11,10,9,8,7};//{2,3,4,5,6,5,6,5,4,3,2};
        int in_line_6_5[] = {7,8,9,10,11,10,11,10,9,8,7};//{3,4,5,6,7,6,7,6,5,4,3};

        //Initialization
        for (int i = 0; i < 2*N-1; ++i)
        {
            if (N==6)  
            {
                if (K==6)  {
                    in_line[i] = in_line_6_6[i];
                }
                else
                {
                    in_line[i] = in_line_6_5[i];   
                }


                x_cor[i] = x_cor_6[i];
                y_cor[i] = y_cor_6[i];
            }
            else
            {
                x_cor[i] = x_cor_5[i];
                y_cor[i] = y_cor_5[i];
                in_line[i] = in_line_5[i];   
            }
        }



        int x = 0;
        int y = 0;
        int points_count = 0;

        b1 = -3;
        b2 = -3;

        
        // Y = X
        for (int i = 0; i < 2*N-1; ++i) 
        {
            x = x_cor[i];
            y = y_cor[i];
            blank_start_found = 0;
            blank_x = 11+x_cor[i];
            blank_y=7+y_cor[i]; 
            element_count=0;
             b1 = -3;
            b2 = -3;
            while(true)
            {
                
                 //cerr << "i: "<< i <<" "<< x<<" "<<y<<" "<<temp_board_array[11+x][7+y]<<" "<<blank_start_found<<" "<<element_count<<" "<<b1<<endl ; 

                 if (temp_board_array[11+x][7+y]==0 && blank_start_found==0){
                    blank_x = 11+x+1;
                    blank_y = 7+y+1;
                    blank_start_found=1;
                    // cerr <<"Entered1"<< "i: "<< i <<" "<< x<<" "<<y<<" "<<temp_board_array[11+x][7+y]<<" "<<blank_start_found<<" "<<element_count<<" "<<b1<<endl ; 
                    if (abs(b1)==3 && (x != x_cor[i])&& element_count>=2){
                        if(K==5){
                             // cerr <<"Entered2"<< "i: "<< i <<" "<< x<<" "<<y<<" "<<temp_board_array[11+x][7+y]<<" "<<blank_start_found<<" "<<element_count<<" "<<b1<<endl ; 
                            result = result + eval_five(N,b1,11+x_cor[i],7+y_cor[i],11+x-1,7+y-1,b2,2,1);
                            // result = result - eval_five(N,b1,11+x_cor[i],7+y_cor[i],11+x-1,7+y-1,b2,2,-1);
                        }
                        else{
                            result = result + eval_six(N,b1,11+x_cor[i],7+y_cor[i],11+x-1,7+y-1,b2,2,1);
                            // result = result - eval_five(N,b1,11+x_cor[i],7+y_cor[i],11+x-1,7+y-1,b2,2,-1);   
                        }
                    }
                    b1=0;
                    element_count = 0;

                }
                else if(temp_board_array[11+x][7+y]==0 && blank_start_found==1 && element_count >= 2){
                    if(K==5){
                        result = result + eval_five(N,b1,blank_x,blank_y,11+x-1,7+y-1,b2,2,1);
                        // result = result - eval_five(N,b1,blank_x,blank_y,11+x-1,7+y-1,b2,2,-1);
                    }
                    else{
                        result = result + eval_six(N,b1,blank_x,blank_y,11+x-1,7+y-1,b2,2,1);
                        // result = result - eval_five(N,b1,blank_x,blank_y,11+x-1,7+y-1,b2,2,-1);   
                    }
                    blank_x = 11+x+1;
                    blank_y = 7+y+1;
                    blank_start_found=1;
                    element_count = 0;
                }
                else if(temp_board_array[11+x][7+y]==0 && blank_start_found==1 && element_count < 2){
                    blank_x = 11+x+1;
                    blank_y = 7+y+1;
                    blank_start_found=1;
                    element_count = 0;
                }
                
                else if (temp_board_array[11+x][7+y]!=0){
                    element_count++;
                }

                x = x+1;
                y = y+1;
                if (points_count==in_line[i])
                {
                    points_count=0;

                    break;
                }
                points_count = points_count +1; 
            }

            if(element_count>=2){
                if (temp_board_array[11+x_cor[i]+in_line[i]][7+y_cor[i]+in_line[i]]!= 0){

                    if(K==5){
                        result = result + eval_five(N,b1,blank_x,blank_y,11+x_cor[i]+in_line[i],7+y_cor[i]+in_line[i],3,2,1);
                        // result = result - eval_five(N,b1,blank_x,blank_y,11+x_cor[i]+in_line[i],7+y_cor[i]+in_line[i],3,2,-1);
                    }
                    else{
                        result = result + eval_six(N,b1,blank_x,blank_y,11+x_cor[i]+in_line[i],7+y_cor[i]+in_line[i],3,2,1);
                        // result = result - eval_five(N,b1,blank_x,blank_y,11+x_cor[i]+in_line[i],7+y_cor[i]+in_line[i],3,2,-1);   
                    }
                }
            }

        }

        //// Y = - X
        // int y_cord[] = {-5,-5,-5,-5,-4,-4,-3,-2,-1};
        // int x_cord[] = {-3,-1,1,3,4,6,7,8,9};


        int y_cord[2*N-1];
        int y_cord_5[] = {-5,-5,-5,-5,-4,-4,-3,-2,-1};
        int y_cord_6[] = {-6,-6,-6,-6,-6,-5,-5,-4,-3,-2,-1};
        int x_cord[2*N-1];
        int x_cord_5[] = {-3,-1,1,3,4,6,7,8,9};
        int x_cord_6[] = {-4,-2,0,2,4,5,7,8,9,10,11};

       
        for (int i = 0; i < 2*N-1; ++i)
        {
            if (N==6)  
            {
                x_cord[i] = x_cord_6[i];
                y_cord[i] = y_cord_6[i];
            }
            else
            {
                x_cord[i] = x_cord_5[i];
                y_cord[i] = y_cord_5[i];
            }
        }


        points_count=0;
        
        
        for (int i = 0; i < 2*N-1; ++i)
        {
            x = x_cord[i];
            y = y_cord[i];
             blank_start_found = 0;
            blank_x = 11+x_cord[i];
            blank_y=7+y_cord[i]; 
            b1 = -3;
        b2 = -3;
            while(true)
            {
                
               


                if (temp_board_array[11+x][7+y]==0 && blank_start_found==0){
                    blank_x = 11+x-1;
                    blank_y = 7+y+1;
                    blank_start_found=1;
                    if (abs(b1)==3 && x!= x_cord[i]&& element_count>=2){
                        if(K==5){
                            result = result + eval_five(N,b1,11+x_cord[i],7+y_cord[i],11+x+1,7+y-1,b2,3,1);
                            // result = result - eval_five(N,b1,11+x_cord[i],7+y_cord[i],11+x+1,7+y-1,b2,3,-1);
                        }
                        else{
                            result = result + eval_six(N,b1,11+x_cord[i],7+y_cord[i],11+x+1,7+y-1,b2,3,1);
                            // result = result - eval_five(N,b1,11+x_cord[i],7+y_cord[i],11+x+1,7+y-1,b2,3,-1);   
                        }
                    }
                    b1=0;
                    element_count=0;
                }
                else if(temp_board_array[11+x][7+y]==0 && blank_start_found==1 && element_count >= 2){
                    if(K==5){
                        result = result + eval_five(N,b1,blank_x,blank_y,11+x+1,7+y-1,b2,3,1);
                        // result = result - eval_five(N,b1,blank_x,blank_y,11+x+1,7+y-1,b2,3,-1);
                    }
                    else{
                        result = result + eval_six(N,b1,blank_x,blank_y,11+x+1,7+y-1,b2,3,1);
                        // result = result - eval_five(N,b1,blank_x,blank_y,11+x+1,7+y-1,b2,3,-1);   
                    }
                    blank_x = 11+x-1;
                    blank_y = 7+y+1;
                    blank_start_found=1;
                    element_count = 0;
                }
                else if(temp_board_array[11+x][7+y]==0 && blank_start_found==1 && element_count < 2){
                    blank_x = 11+x-1;
                    blank_y = 7+y+1;
                    blank_start_found=1;
                    element_count = 0;
                }
                
                else if (temp_board_array[11+x][7+y]!=0){
                    element_count++;
                }

                x = x-1;
                y = y+1;
                if (points_count==in_line[i])
                {
                    points_count=0;

                    break;
                }
                points_count = points_count +1;     
            }

            if(element_count>=2){
                if (temp_board_array[11+x_cord[i]-in_line[i]][7+y_cord[i]+in_line[i]]!= 0){

                    if(K==5){
                        result = result + eval_five(N,b1,blank_x,blank_y,11+x_cord[i]-in_line[i],7+y_cord[i]+in_line[i],3,3,1);
                        // result = result - eval_five(N,b1,blank_x,blank_y,11+x_cord[i]-in_line[i],7+y_cord[i]+in_line[i],3,3,-1);
                    }
                    else{
                        result = result + eval_six(N,b1,blank_x,blank_y,11+x_cord[i]-in_line[i],7+y_cord[i]+in_line[i],3,3,1);
                        // result = result - eval_five(N,b1,blank_x,blank_y,11+x_cord[i]-in_line[i],7+y_cord[i]+in_line[i],3,3,-1);   
                    }
                }
            }

        }
        
        
       return result;


    }
