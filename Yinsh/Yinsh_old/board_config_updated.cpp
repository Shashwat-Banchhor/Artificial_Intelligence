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

    int total_moves=0;
    
    int tmp_my_ring[10];           // stores position (x,y) of my rings 
    int tmp_tmp_ring[10];           // stores position (x,y) of my rings  
    int tmp_computers_ring[10];    // stores position (x,y) of opponents rings 
    int tmp_ring[10];
    std::vector<int> rings_removed;


    std::vector<std::vector<int> >  board_status;  // stores board in hexagon form
    
    int board_array[30][30];   //new int[30][30] ;    // stores board in array form
    int temp_board_array[30][30];

    int my_ring[10];     	   // stores position (x,y) of my rings  
    int computers_ring[10];    // stores position (x,y) of opponents rings 

    int my_ring_count=0;
    int computers_ring_count=0;

    int ring_count;
    int ring_removed;
    

    // Constructor
    Board::Board(int N , int M , int K, int L)
    {
        // std::cerr << "abc";
        no_of_hexagons         = N;
        rings_with_each_player = M;
		discs_req_in_line_to_win  = K;
		max_rings_to_remove    = L; 

        for (int i = 0; i <=no_of_hexagons; i++)
        {
            
            std::vector<int> vect; 
            if (i ==0)
            {
                vect.push_back(0);
            }
            else
            {
                for (int j = 0; j < 6*i; j++)
                {
                    vect.push_back(0);
                }   
            }   

            board_status.push_back(vect);     // stored as hexagons
        }

        
        // INITIALIZE BOARD_ARRAY
        for (int i = 0; i < 30; ++i)
        {
            for (int j = 0; j <30; ++j)
            {
                board_array[i][j] = 0;		// array
            }
            
        }
    }
  
    // Member Functions() 
    void Board::print() 
    { 
       

        
        // for (int i = 0; i < no_of_hexagons; i++)
        // {
            
        //     std::vector<int> vect = board_status.at(i);
        //     if (i ==0)
        //     {
        //         // std::cerr << "Yup";
        //         board_array[15][15] = vect.at(0);
        //         // std::cerr << vect.at(0) ;//vect.at(0);
        //     }
        //     else
        //     {
        //         int p=0;
        //         for (int j = 0; j <= i; j++)
        //         {
        //             //board_array[15+j][15-2*no_of_hexagons+j] = 3;
        //             board_array[15-2*i+j][15+j] = vect.at(p);
        //             p++;
        //         }   
        //         for (int j = 0; j < i; j++)
        //         {
        //             // board_array[15+i][15-i+2+2*j] = 1;
        //              board_array[15-i+2+2*j][15+i] = vect.at(p);
        //             p++;
        //         }
        //         for (int j = 0; j < i; j++)
        //         {
        //             // board_array[15+i-j-1][15+(i)-j-1] = 2;
        //             board_array[15+(i)+j+1][15+i-j-1] = vect.at(p);
        //             p++;
        //         }
        //         p=6*i-1;
        //         for (int j = 1; j <= i; j++)
        //         {
        //             //board_array[15+j][15-2*no_of_hexagons+j] = 3;
        //             board_array[15-2*i+j][15-j] = vect.at(p);
        //             p--;
        //         }   
        //         for (int j = 0; j < i; j++)
        //         {
        //             // board_array[15+i][15-i+2+2*j] = 1;
        //              board_array[15-i+2+2*j][15-i] = vect.at(p);
        //             p--;
        //         }
        //         for (int j = 0; j < i-1; j++)
        //         {
        //             // board_array[15+i-j-1][15+(i)-j-1] = 2;
        //             board_array[15+(i)+j+1][15-i+j+1] = vect.at(p);
        //             p--;
        //         }
        //     }   


        // }

        // std::cerr << "def\n";
        for (int i = 0; i < 30; ++i)
        {
            for (int j = 0; j <30; ++j)
            {
                if (board_array[i][j] == 0)
                {
                    std::cerr << ".";

                }
                else
                {
                    std::cerr << board_array[i][j];
                }
                std::cerr << "  ";
            }
            std::cerr << "\n";
        }
	} 

    void Board::print2() 
    { 
       

        
        
        for (int i = 0; i < 30; ++i)
        {
            for (int j = 0; j <30; ++j)
            {
                if (temp_board_array[i][j] == 0)
                {
                    std::cerr << ".";

                }
                else
                {
                    std::cerr << temp_board_array[i][j];
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
            // std::cerr << "\nComputers Ring Start Up\n"; 
            // for (int i = 0; i < 5; ++i)
            // {
            //     {
            //         std::cerr<< computers_ring[2*i] <<","<<computers_ring[2*i+1]<< "\n" ; 
            //     }
            // }
 
        

        	std::string text = s;
        	// std::istream_iterator<std::string>(iss);
    		std::istringstream iss(text);
    		std::vector<std::string> results((std::istream_iterator<std::string>(iss)),  // Move store in results
    		std::istream_iterator<std::string>());

    		// for (int i = 0; i < results.size(); ++i)
    		// {
    		// 	std::cerr << results.at(i);
    		// }


    		// exit(0);




            // // Print  board status
            // for (int i = 0; i < board_status.size(); ++i)   // update in hexagon
            // {
            //     std::vector<int> v;
            //     v= board_status.at(i);
            //     for (int j = 0; j <v.size(); ++j)
            //     {
            //         std::cerr << v.at(j);
            //     }
            //     std::cerr << "\n";
            // }


            int n = results.size(); 
         
            // // declaring character array
            // char char_array[n+1]; 
         
            // // copying the contents of the 
            // // string to char array
            // strcpy(char_array, s.c_str()); 

            
            // Variables for updating coordinates in the array 
            int sel_x,sel_y,  mov_x,mov_y,  place_x,place_y, start_x,start_y, end_x,end_y, ring_x,ring_y ; 
            std::vector<int> v;

            if (results.at(0).compare("S")==0)       // Select ring
            {
            
                int sel[2];
                int mov[2];
               	// if (n<7)   // select and move ring  // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS 
                // {
                    
                    sel[0] =  std::stoi(results.at(1));//int(char_array[1])-48;
                    sel[1] =  std::stoi(results.at(2));//int(char_array[2])-48;
                    mov[0] =  std::stoi(results.at(4));//int(char_array[4])-48;
                    mov[1] =  std::stoi(results.at(5));//int(char_array[5])-48;

               		// // -------- U P D A T E   I N   T H E  H E X A G O N ---------- 
                    
                 //    std::vector<int> vect1 =  board_status.at(sel[0]);
                 //    vect1[sel[1]] = vect1[sel[1]]/2;
                 //    board_status[sel[0]] = vect1;

                 //    std::vector<int> vect2 =  board_status.at(mov[0]);
                 //    vect2[mov[1]] = player*2;
                 //    board_status[mov[0]] = vect2;

                    // -------- U P D A T E   I N   T H E  A R R A Y  ---------- 

                    v = change_coordinates(0,sel[0],sel[1]);
                    sel_x = v.at(0)+15;
                    sel_y = v.at(1)+15;

                    int selected_point_should_be = board_array[sel_x][sel_y] / 2; 
                    cerr<<selected_point_should_be <<"selected_point_should_be"<<endl;
                    board_array[sel_x][sel_y] = board_array[sel_x][sel_y] / 2; 

                    v = change_coordinates(0,mov[0],mov[1]);
                    mov_x = v.at(0)+15;
                    mov_y = v.at(1)+15;

                    int moved_point_should_be = player*2;
                    board_array[mov_x][mov_y] = player * 2; 

                    ////////////////////////////////////////////////////////////////////////////////////////////////////


                    // v = change_coordinates(0,start[0],start[1]);  // remove discs start
                    start_x = sel_x-15;//sel[0];//v.at(0)+15;
                    start_y = sel_y-15;//sel[1];//v.at(1)+15;

                    // v = change_coordinates(0,end[0],end[1]);  // remove discs end
                    end_x = mov_x-15;//mov[0];//v.at(0)+15;
                    end_y = mov_y-15;//mov[1];//v.at(1)+15;
                    // std::cerr << "s_xy e_xy" << s<<":::"<<start_x << start_y << end_x << end_y ;

                    if (start_y == end_y)           // vertical line slope 0
                    {   
                        
                        

                        
                        for (int i = min(start_x,end_x); i < max(start_x,end_x)+1; i++)
                        {
                            board_array[15+i][15+start_y] = - board_array[15+i][15+start_y];
                        }
                    }
                    else if((start_x>end_x && start_y>end_y) || (start_x<end_x && start_y<end_y))  // slope 1
                    {
                        int disc_x = min(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            board_array[15+disc_x+ (i- disc_y)][15+i] = - board_array[15+disc_x+ (i- disc_y)][15+i];
                        }
                    }
                    else if((start_x>end_x && start_y<end_y) || (start_x<end_x && start_y>end_y))  // slope -1
                    {

                        int disc_x = max(start_x,end_x);
                        int disc_y = min(start_y,end_y);
                        // std::cerr << ("Enter1\n");

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            board_array[15+disc_x + disc_y - i][15+i] = - board_array[15+disc_x + disc_y - i][15+i] ;
                             std::cerr << disc_x + disc_y - i << i << board_array[15+disc_x + disc_y - i][15+i] <<"\n";
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
                    if (player==1) // me
                    {
                        for (int i = 0; i < 5; ++i)
                        {
                            if (sel_x-15== my_ring[2*i] && sel_y-15==my_ring[2*i+1])
                            {
                                my_ring[2*i] = mov_x-15;
                                my_ring[2*i+1] = mov_y-15;
                            }
                        }
                    }
                    else{  // computer
                        for (int i = 0; i < 5; ++i)
                        {
                            if (sel_x-15== computers_ring[2*i] && sel_y-15==computers_ring[2*i+1])
                            {
                                computers_ring[2*i] = mov_x-15;
                                computers_ring[2*i+1] = mov_y-15;
                            }
                        }

                    }



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
                    // sel_x = v.at(0)+15;
                    // sel_y = v.at(1)+15;

                    // board_array[sel_x][sel_y] = board_array[sel_x][sel_y] / 2; 

                    // v = change_coordinates(0,mov[0],mov[1]);    // move ring
                    // mov_x = v.at(0)+15;
                    // mov_y = v.at(1)+15;

                    // board_array[mov_x][mov_y] = player * 2; 


                    v = change_coordinates(0,start[0],start[1]);  // remove discs start
                    start_x = v.at(0);//+15;
                    start_y = v.at(1);//+15;

                    v = change_coordinates(0,end[0],end[1]);  // remove discs end
                    end_x = v.at(0);//+15;
                    end_y = v.at(1);//+15;

                    if (start_y == end_y) 			// vertical line slope 0
                    {	
                    	

                    	for (int i = min(start_x,end_x); i < max(start_x,end_x)+1; i++)
                    	{
                    		board_array[15+i][15+start_y] = 0;
                    	}
                    }
                    else if((start_x>end_x && start_y>end_y) || (start_x<end_x && start_y<end_y))  // slope 1
                    {
                    	int disc_x = min(start_x,end_x);
                    	int disc_y = min(start_y,end_y);

                    	for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                    	{
                    		board_array[15+disc_x+ (i- disc_y)][15+i] = 0;
                    	}
                    }
                    else if((start_x>end_x && start_y<end_y) || (start_x<end_x && start_y>end_y))  // slope -1
                    {

                    	int disc_x = max(start_x,end_x);
                    	int disc_y = min(start_y,end_y);

                    	for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                    	{
                    		board_array[15+disc_x + disc_y - i][15+i] = 0;
                    	}

                    }
                    else{ std::cerr << " Error in update function" ; }  

                    if (player==1) // me
                    {
                        for (int i = 0; i < 5; ++i)
                        {
                            if (sel_x-15== my_ring[2*i] && sel_y-15==my_ring[2*i+1])
                            {
                                my_ring[2*i] = mov_x-15;
                                my_ring[2*i+1] = mov_y-15;
                            }
                        }
                    }
                    else{  // computer
                        for (int i = 0; i < 5; ++i)
                        {
                            if (sel_x-15== my_ring[2*i] && sel_y-15==my_ring[2*i+1])
                            {
                                computers_ring[2*i] = mov_x-15;
                                computers_ring[2*i+1] = mov_y-15;
                            }
                        }

                    }
                    




                    v = change_coordinates(0,ring[0],ring[1]);  // remove ring
                    ring_x = v.at(0)+15;
                    ring_y = v.at(1)+15;

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

                // -------- U P D A T E   I N   T H E  H E X A G O N ---------- 
                vect = board_status.at(place[0]);
                // std::cerr << "Entered2";
                vect[place[1]] = 2*player;
                board_status[place[0]] = vect;
                // std::cerr << "Updated"<<vect[place[1]];  


                // -------- U P D A T E   I N   T H E  A R R A Y  ---------- 

                std::vector<int> v = change_coordinates(0,place[0],place[1]);
                place_x = v.at(0)+15;
                place_y = v.at(1)+15;

                
                board_array[place_x][place_y] = player*2; 
                if (player==1) // me
                {
                    my_ring_count++;
                    my_ring[2*(my_ring_count-1)] = place_x-15;
                    my_ring[2*(my_ring_count-1)+1] = place_y-15;
                }
                else{   // computer
                    computers_ring_count++;
                    computers_ring[2*(computers_ring_count-1)] = place_x-15;
                    computers_ring[2*(computers_ring_count-1)+1] = place_y-15;

                }

            }
            std::cerr << "\nComputers Ring End Up\n"; 
            for (int i = 0; i < 5; ++i)
            {
                {
                    std::cerr<< computers_ring[2*i] <<","<<computers_ring[2*i+1]<< "\n" ; 
                }
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

            // for (int i = 0; i < results.size(); ++i)
            // {
            //  std::cerr << results.at(i);
            // }


            // exit(0);




            // // Print  board status
            // for (int i = 0; i < board_status.size(); ++i)   // update in hexagon
            // {
            //     std::vector<int> v;
            //     v= board_status.at(i);
            //     for (int j = 0; j <v.size(); ++j)
            //     {
            //         std::cerr << v.at(j);
            //     }
            //     std::cerr << "\n";
            // }


            int n = results.size(); 
         
            // // declaring character array
            // char char_array[n+1]; 
         
            // // copying the contents of the 
            // // string to char array
            // strcpy(char_array, s.c_str()); 

            
            // Variables for updating coordinates in the array 
            std::vector<int> v_dash = change_coordinates(0,std::stoi(results.at(1)),std::stoi(results.at(2)));
            player = temp_board_array[v_dash.at(0)+15][v_dash.at(1)+15]/2;
            std::cerr << "player:::"<<player;
            int sel_x,sel_y,  mov_x,mov_y,  place_x,place_y, start_x,start_y, end_x,end_y, ring_x,ring_y ; 
            std::vector<int> v;

            if (results.at(0).compare("S")==0)       // Select ring
            {
            
                int sel[2];
                int mov[2];
                // if (n<7)   // select and move ring  // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS 
                // {
                    
                    sel[0] =  std::stoi(results.at(1));//int(char_array[1])-48;
                    sel[1] =  std::stoi(results.at(2));//int(char_array[2])-48;
                    mov[0] =  std::stoi(results.at(4));//int(char_array[4])-48;
                    mov[1] =  std::stoi(results.at(5));//int(char_array[5])-48;

                    // -------- U P D A T E   I N   T H E  H E X A G O N ---------- 
                    
                    // std::vector<int> vect1 =  board_status.at(sel[0]);
                    // vect1[sel[1]] = vect1[sel[1]]/2;
                    // board_status[sel[0]] = vect1;

                    // std::vector<int> vect2 =  board_status.at(mov[0]);
                    // vect2[mov[1]] = player*2;
                    // board_status[mov[0]] = vect2;

                    // -------- U P D A T E   I N   T H E  A R R A Y  ---------- 

                    v = change_coordinates(0,sel[0],sel[1]);
                    sel_x = v.at(0)+15;
                    sel_y = v.at(1)+15;

                    int selected_point_should_be = temp_board_array[sel_x][sel_y] / 2; ; 
                    temp_board_array[sel_x][sel_y] = temp_board_array[sel_x][sel_y] / 2; 

                    v = change_coordinates(0,mov[0],mov[1]);
                    mov_x = v.at(0)+15;
                    mov_y = v.at(1)+15;

                    int moved_point_should_be = selected_point_should_be*2;
                    temp_board_array[mov_x][mov_y] = selected_point_should_be * 2; 
                    std::cerr << ("Ha ya ho rha\n");
                    std::cerr << "Hai" <<  temp_board_array[15][15]<< "Uii";

                    ////////////////////////////////////////////////////////////////////////////////////////////////////


                    // v = change_coordinates(0,start[0],start[1]);  // remove discs start
                    start_x = sel_x-15;//sel[0];//v.at(0)+15;
                    start_y = sel_y-15;//sel[1];//v.at(1)+15;

                    // v = change_coordinates(0,end[0],end[1]);  // remove discs end
                    end_x = mov_x-15;//mov[0];//v.at(0)+15;
                    end_y = mov_y-15;//mov[1];//v.at(1)+15;
                    // std::cerr << "s_xy e_xy" << s<<":::"<<start_x << start_y << end_x << end_y ;

                    if (start_y == end_y)           // vertical line slope 0
                    {   
                        
                        

                        
                        for (int i = min(start_x,end_x); i < max(start_x,end_x)+1; i++)
                        {
                            temp_board_array[15+i][15+start_y] = - temp_board_array[15+i][15+start_y];
                        }
                    }
                    else if((start_x>end_x && start_y>end_y) || (start_x<end_x && start_y<end_y))  // slope 1
                    {
                        int disc_x = min(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            temp_board_array[15+disc_x+ (i- disc_y)][15+i] = - temp_board_array[15+disc_x+ (i- disc_y)][15+i];
                        }
                    }
                    else if((start_x>end_x && start_y<end_y) || (start_x<end_x && start_y>end_y))  // slope -1
                    {

                        int disc_x = max(start_x,end_x);
                        int disc_y = min(start_y,end_y);
                        // std::cerr << ("Enter1\n");

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            temp_board_array[15+disc_x + disc_y - i][15+i] = - temp_board_array[15+disc_x + disc_y - i][15+i] ;
                             std::cerr << disc_x + disc_y - i << i << temp_board_array[15+disc_x + disc_y - i][15+i] <<"\n";
                        }

                    }
                    else{ std::cerr << " Error in update function" ; }  
                    
                    // change the selected and move coordinates;
                    temp_board_array[sel_x][sel_y] = selected_point_should_be;
                    temp_board_array[mov_x][mov_y]  = moved_point_should_be;
                    
                    std::cerr << "Hai" <<  temp_board_array[mov_x][mov_y]<< "Uii";
                    // print2();
                    std::cerr << ("check2\n");
                    // std::cerr << sel_x<<sel_y<<mov_x<<mov_y << "board" << temp_board_array[14][16] ;

                    // std::cerr << ("checking board\n");
                    // print();
                    // std::cerr << ("checked\n");
                    // if (player==1) // me
                    // {
                        for (int i = 0; i < 5; ++i)
                        {
                            if (sel_x-15== tmp_ring[2*i] && sel_y-15==tmp_ring[2*i+1])
                            {
                                tmp_ring[2*i] = mov_x-15;
                                tmp_ring[2*i+1] = mov_y-15;
                            }
                        }
                    // }
                    // else{  // computer
                    //     for (int i = 0; i < 5; ++i)
                    //     {
                    //         if (sel_x-15== tmp_computer_ring[2*i] && sel_y-15==tmp_computer_ring[2*i+1])
                    //         {
                    //             tmp_computers_ring[2*i] = mov_x-15;
                    //             tmp_computers_ring[2*i+1] = mov_y-15;
                    //         }
                    //     }

                    // }



                // }
                std::cerr << results.size()<<"result siz"<<endl;
                if(n>7)//else   // select and move ring & remove discs and ring
                {
                    int start[2];
                    int end[2];
                    int ring[2];
                    std::cerr << "chk1\n";
                    start[0] =  std::stoi(results.at(7));//int(char_array[6])-48;   
                    start[1] =  std::stoi(results.at(8));//int(char_array[7])-48;
                    end[0] =  std::stoi(results.at(10));//int(char_array[8])-48;
                    end[1] = std::stoi(results.at(11));//int(char_array[9])-48;
                    ring[0] =  std::stoi(results.at(13));//int(char_array[10])-48;
                    ring[1] =  std::stoi(results.at(14));//int(char_array[11])-48;

                

                  

                    std::cerr << "chk2\n";
                    std::cerr << start[0] <<",,"<<start[1]<<endl;
                    v = change_coordinates(0,start[0],start[1]);  // remove discs start
                    start_x = v.at(0);//+15;
                    start_y = v.at(1);//+15;

                    std::cerr << "chk21\n";

                    v = change_coordinates(0,end[0],end[1]);  // remove discs end
                    end_x = v.at(0);//+15;
                    end_y = v.at(1);//+15;
                    std::cerr << "chk22\n";
                    if (start_y == end_y)           // vertical line slope 0
                    {   
                        

                        for (int i = min(start_x,end_x); i < max(start_x,end_x)+1; i++)
                        {
                            temp_board_array[15+i][15+start_y] = 0;
                        }
                    }
                    else if((start_x>end_x && start_y>end_y) || (start_x<end_x && start_y<end_y))  // slope 1
                    {
                        int disc_x = min(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            temp_board_array[15+disc_x+ (i- disc_y)][15+i] = 0;
                        }
                    }
                    else if((start_x>end_x && start_y<end_y) || (start_x<end_x && start_y>end_y))  // slope -1
                    {

                        int disc_x = max(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            temp_board_array[15+disc_x + disc_y - i][15+i] = 0;
                        }

                    }
                    else{ std::cerr << " Error in update function" ; }  

                    // if (player==1) // me
                    // {
                        for (int i = 0; i < 5; ++i)
                        {
                            if (sel_x-15== tmp_ring[2*i] && sel_y-15==tmp_ring[2*i+1])
                            {
                                tmp_ring[2*i] = mov_x-15;
                                tmp_ring[2*i+1] = mov_y-15;
                            }
                        }
                    // }
                    // else{  // computer
                    //     for (int i = 0; i < 5; ++i)
                    //     {
                    //         if (sel_x-15== tmp_my_ring[2*i] && sel_y-15==tmp_my_ring[2*i+1])
                    //         {
                    //             tmp_computers_ring[2*i] = mov_x-15;
                    //             tmp_computers_ring[2*i+1] = mov_y-15;
                    //         }
                    //     }

                    // }

                    

                        std::cerr << "chk3\n";


                    v = change_coordinates(0,ring[0],ring[1]);  // remove ring
                    ring_x = v.at(0)+15;
                    ring_y = v.at(1)+15;

                    temp_board_array[ring_x][ring_y] = 0; 


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

                // // -------- U P D A T E   I N   T H E  H E X A G O N ---------- 
                // vect = board_status.at(place[0]);
                // // std::cerr << "Entered2";
                // vect[place[1]] = 2*player;
                // board_status[place[0]] = vect;
                // // std::cerr << "Updated"<<vect[place[1]];  


                // -------- U P D A T E   I N   T H E  A R R A Y  ---------- 

                std::vector<int> v = change_coordinates(0,place[0],place[1]);
                place_x = v.at(0)+15;
                place_y = v.at(1)+15;

                
                temp_board_array[place_x][place_y] = player*2; 
                if (player==1) // me
                {
                    my_ring_count++;
                    tmp_my_ring[2*(my_ring_count-1)] = place_x-15;
                    tmp_my_ring[2*(my_ring_count-1)+1] = place_y-15;
                }
                else{   // computer
                    computers_ring_count++;
                    tmp_computers_ring[2*(computers_ring_count-1)] = place_x-15;
                    tmp_computers_ring[2*(computers_ring_count-1)+1] = place_y-15;

                }

            }
        
        }

    
        
    }

    void Board::reverse_update(int player,int x1,int y1,int x2,int y2,std::string mo)   /// make a reverse update function  to do dfs easily  /// rings are changing globLALY AT EACH STEP
    {
        // -1 Computer
        // 1 Me
 

        std::string text = mo;
        // std::istream_iterator<std::string>(iss);
        std::istringstream iss(text);
        std::vector<std::string> results((std::istream_iterator<std::string>(iss)),  // Move store in results
        std::istream_iterator<std::string>());

        for (int i = 0; i < results.size(); ++i)
        {
         std::cerr << results.at(i);
        }






        // // Print  board status
        // for (int i = 0; i < board_status.size(); ++i)   // update in hexagon
        // {
        //     std::vector<int> v;
        //     v= board_status.at(i);
        //     for (int j = 0; j <v.size(); ++j)
        //     {
        //         std::cerr << v.at(j);
        //     }
        //     std::cerr << "\n";
        // }


        int n = results.size(); 
     
        // // declaring character array
        // char char_array[n+1]; 
     
        // // copying the contents of the 
        // // string to char array
        // strcpy(char_array, s.c_str()); 

        
        // Variables for updating coordinates in the array 
        std::cerr << ("Inside_rev_up\n");
        // print2();
        int sel_x,sel_y,  mov_x,mov_y,  place_x,place_y, start_x,start_y, end_x,end_y, ring_x,ring_y ; 
        std::vector<int> v;

       
        // if (results.at(0).compare("S")==0)       // Select ring
        // {
                    int selected_point_should_be ;
                int sel[2];
                int mov[2];
            // if (n<7)   // select and move ring  // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS // CHANGE DISCS 
            //  {
                
                std::vector<int> v2;std::vector<int> v1;
                v2 = change_coordinates(0,std::stoi(results.at(4)),std::stoi(results.at(5)));
                v1 = change_coordinates(0,std::stoi(results.at(1)),std::stoi(results.at(2)));

                sel[0] = v2.at(0);//x2; //std::stoi(results.at(1));//int(char_array[1])-48;
                sel[1] = v2.at(1);//y2;//std::stoi(results.at(2));//int(char_array[2])-48;
                mov[0] = v1.at(0);//x1; //std::stoi(results.at(4));//int(char_array[4])-48;
                mov[1] = v1.at(1);//y1;//std::stoi(results.at(5));//int(char_array[5])-48;
                std::cerr << "X1 : " << x1 << "\n" ; 
                std::cerr << "Y1 : " << y1 << "\n" ; 
                std::cerr << "X2 : " << x2 << "\n" ; 
                std::cerr << "Y2 : " << y2 << "\n" ;   
            
                sel_x = sel[0]+15;
                sel_y = sel[1]+15;
                selected_point_should_be = temp_board_array[sel_x][sel_y];// / 2; ;
                player = selected_point_should_be/2;


                if(n>=7)   // select and move ring & remove discs and ring
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

                  

                    // // -------- U P D A T E   I N   T H E  A R R A Y  ---------- 


                    // v = change_coordinates(0,sel[0],sel[1]);    // select ring
                    // sel_x = v.at(0)+15;
                    // sel_y = v.at(1)+15;

                    // temp_board_array[sel_x][sel_y] = temp_board_array[sel_x][sel_y] / 2; 

                    // v = change_coordinates(0,mov[0],mov[1]);    // move ring
                    // mov_x = v.at(0)+15;
                    // mov_y = v.at(1)+15;

                    // temp_board_array[mov_x][mov_y] = player * 2; 


                    v = change_coordinates(0,start[0],start[1]);  // remove discs start
                    start_x = v.at(0);//+15;
                    start_y = v.at(1);//+15;

                    v = change_coordinates(0,end[0],end[1]);  // remove discs end
                    end_x = v.at(0);//+15;
                    end_y = v.at(1);//+15;

                    if (start_y == end_y)           // vertical line slope 0
                    {   
                        

                        for (int i = min(start_x,end_x); i < max(start_x,end_x)+1; i++)
                        {
                            temp_board_array[15+i][15+start_y] = selected_point_should_be/2;
                        }
                    }
                    else if((start_x>end_x && start_y>end_y) || (start_x<end_x && start_y<end_y))  // slope 1
                    {
                        int disc_x = min(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            temp_board_array[15+disc_x+ (i- disc_y)][15+i] = selected_point_should_be/2;
                        }
                    }
                    else if((start_x>end_x && start_y<end_y) || (start_x<end_x && start_y>end_y))  // slope -1
                    {

                        int disc_x = max(start_x,end_x);
                        int disc_y = min(start_y,end_y);

                        for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                        {
                            temp_board_array[15+disc_x + disc_y - i][15+i] = selected_point_should_be/2;
                        }

                    }
                    else{ std::cerr << " Error in update function" ; }  

                    // if (player==1) // me
                    // {
                        // for (int i = 0; i < 5; ++i)
                        // {
                        //     if (sel_x-15== tmp_ring[2*i] && sel_y-15==tmp_ring[2*i+1])
                        //     {
                        //         tmp_ring[2*i] = mov_x-15;
                        //         tmp_ring[2*i+1] = mov_y-15;
                        //     }
                        // }
                    // }
                    // else{  // computer
                    //     for (int i = 0; i < 5; ++i)
                    //     {
                    //         if (sel_x-15== tmp_my_ring[2*i] && sel_y-15==tmp_my_ring[2*i+1])
                    //         {
                    //             tmp_computers_ring[2*i] = mov_x-15;
                    //             tmp_computers_ring[2*i+1] = mov_y-15;
                    //         }
                    //     }

                    // }

                    




                    v = change_coordinates(0,ring[0],ring[1]);  // remove ring
                    ring_x = v.at(0)+15;
                    ring_y = v.at(1)+15;

                    temp_board_array[ring_x][ring_y] = selected_point_should_be; 


                }

           


                // // -------- U P D A T E   I N   T H E  H E X A G O N ---------- 
                
                // std::vector<int> vect1 =  board_status.at(sel[0]);
                // vect1[sel[1]] = vect1[sel[1]]/2;
                // board_status[sel[0]] = vect1;

                // std::vector<int> vect2 =  board_status.at(mov[0]);
                // vect2[mov[1]] = player*2;
                // board_status[mov[0]] = vect2;

                // -------- U P D A T E   I N   T H E  A R R A Y  ---------- 

                // v = change_coordinates(0,sel[0],sel[1]);
                

                temp_board_array[sel_x][sel_y] = temp_board_array[sel_x][sel_y] / 2; 
                std::cerr << ("abcede\n");

                // std::cerr << mov[0]<<mov[1];               
                // v = change_coordinates(0,mov[0],mov[1]);
                mov_x = mov[0]+15;
                mov_y = mov[1]+15;
                std::cerr << ("abcede\n");


                int moved_point_should_be = selected_point_should_be;//player*2;
                temp_board_array[mov_x][mov_y] = selected_point_should_be;//player * 2; 

                ////////////////////////////////////////////////////////////////////////////////////////////////////


                 // v = change_coordinates(0,start[0],start[1]);  // remove discs start
                    start_x = sel_x-15;//sel[0];//v.at(0)+15;
                    start_y = sel_y-15;//sel[1];//v.at(1)+15;

                    // v = change_coordinates(0,end[0],end[1]);  // remove discs end
                    end_x = mov_x-15;//mov[0];//v.at(0)+15;
                    end_y = mov_y-15;//mov[1];//v.at(1)+15;
                    // std::cerr << "s_xy e_xy" << s<<":::"<<start_x << start_y << end_x << end_y ;

                if (start_y == end_y)           // vertical line slope 0
                {   
                    
                    

                    
                    for (int i = min(start_x,end_x); i < max(start_x,end_x)+1; i++)
                    {
                        temp_board_array[15+i][15+start_y] = - temp_board_array[15+i][15+start_y];
                    }
                }
                else if((start_x>end_x && start_y>end_y) || (start_x<end_x && start_y<end_y))  // slope 1
                {
                    int disc_x = min(start_x,end_x);
                    int disc_y = min(start_y,end_y);

                    for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                    {
                        temp_board_array[15+disc_x+ (i- disc_y)][15+i] = - temp_board_array[15+disc_x+ (i- disc_y)][15+i];
                    }
                }
                else if((start_x>end_x && start_y<end_y) || (start_x<end_x && start_y>end_y))  // slope -1
                {

                    int disc_x = max(start_x,end_x);
                    int disc_y = min(start_y,end_y);

                    for (int i = min(start_y,end_y); i < max(start_y,end_y)+1; i++)
                    {
                        temp_board_array[15+disc_x + disc_y - i][15+i] = -temp_board_array[15+disc_x + disc_y - i][15+i] ;
                    }

                }
                else{ std::cerr << " Error in update function" ; }  
                
                // change the selected and move coordinates;
                temp_board_array[sel_x][sel_y] = 0;//selected_point_should_be;
                temp_board_array[mov_x][mov_y]  = selected_point_should_be;//moved_point_should_be;

                std::cerr << ("check_rev_cop\n");
                // print2();
                std::cerr << ("rev_up_comp\n");
                

                   
                   




                // if (player==1) // me
                //     {
                //  std::cerr << "\n reverse tmp_Ring Start Up\n"; 
                // for (int i = 0; i < 5; ++i)
                // {
                //     {
                //         std::cerr<< "i :: "<<tmp_tmp_ring[2*i] <<","<<tmp_tmp_ring[2*i+1]<< "\n" ; 
                //     }
                // }
                        for (int i = 0; i < 5; ++i)
                        {
                            if (sel_x-15== tmp_tmp_ring[2*i] && sel_y-15==tmp_tmp_ring[2*i+1])
                            {
                                tmp_tmp_ring[2*i] = mov_x-15;
                                tmp_tmp_ring[2*i+1] = mov_y-15;


                            }
                        }
                // std::cerr << "\n reverse tmp_Ring Start Up\n"; 
                // for (int i = 0; i < 5; ++i)
                // {
                //     {
                //         std::cerr<< "i :: "<<tmp_tmp_ring[2*i] <<","<<tmp_tmp_ring[2*i+1]<< "\n" ; 
                //     }
                // }
                //     }
                // else{  // computer
                //     for (int i = 0; i < 5; ++i)
                //     {
                //         if (sel_x-15== tmp_computers_ring[2*i] && sel_y-15==tmp_computers_ring[2*i+1])
                //         {
                //             tmp_computers_ring[2*i] = mov_x-15;
                //             tmp_computers_ring[2*i+1] = mov_y-15;
                //         }
                //     }

                // }



            // }
            

            

        //}
        
    }

 

    //add (-15,-15), give input, get output, add 15,15 
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

    std::string Board::play() // returns the move to be played
    {
        
        // std::cerr << "\nComputers Ring\n"; 
        // for (int i = 0; i < 5; ++i)
        // {
        //     {
        //         std::cerr<< computers_ring[2*i] <<","<<computers_ring[2*i+1]<< "\n" ; 
        //     }
        // }
        // std::cerr << "\nMy Ring\n";     
        // for (int i = 0; i < 5; ++i)
        // {
        //    std::cerr<< my_ring[2*i] <<","<<my_ring[2*i+1] << "\n"; 
        // }
        std::string move;
        
        total_moves ++;
        if(total_moves==1)
        {
            
            
            move = "P 4 0";
            update(-1,move,0);
        }
        else if(total_moves==2)
        {
           
            move = "P 4 3";
            update(-1,move,0);
        }
         else if(total_moves==3)
        {
            
         
            move = "P 4 2";
            update(-1,move,0);
        }
           else if(total_moves==4)
        {
               

            move = "P 4 1";
            update(-1,move,0);
          }
          else if(total_moves==5)
        {
                

            move = "P 4 4";
            update(-1,move,0);
            

        }
        else
        {    
            
            Node* root = tree();
            std::cerr << ("Output_frm_tree\n");
            int ht = 0;

            for (int i = 0; i < root->children.size(); ++i)
            {
                Node* ch;
                ch = root->children.at(i);
                std::cerr <<  "Child: "<< i<< ":: "<< ch->move << " score "<<ch->score<<endl;   
                for (int j = 0; j < ch->children.size(); ++j)
                {
                    Node* chhh;
                    chhh = ch->children.at(j);
                    std::cerr <<  "           Child: "<< j<< ":: "<< chhh->move<< " score "<<chhh->score << endl;   
                }
            }
            
            // while(root->children.size()!=0)
            // {
            //     root = root->children.at(0);
            //     ht++;
            // }

            Node* state  = max_val(root);
            std::cerr << "Height of the tree: "<< ht << endl;
            move = state->get_move();
            std::cerr << move;
            // print();
            update(-1,move,0);
            
            cerr<<"marker"<<endl;
            // print();

            // std::cerr << "\nComputers Ring end\n"; 
            // for (int i = 0; i < 5; ++i)
            // {
            //     {
            //         std::cerr<< computers_ring[2*i] <<","<<computers_ring[2*i+1]<< "\n" ; 
            //     }
            // }
            // std::cerr << "\nMy Ring end\n";     
            // for (int i = 0; i < 5; ++i)
            // {
            //    std::cerr<< my_ring[2*i] <<","<<my_ring[2*i+1] << "\n"; 
            // }
            // std::cerr<<"\n"<<find_five_consecutive_board_array(0).size();
        }
        print();
        return move ;
    }


    Node* Board::tree()
    {
        
        

        // temp = board_config;
        int score = 0;//evaluate_heuristic(temp);
        int cut_off_height = 1;
        Node* root = new Node(NULL,score,"S 1 2 M 3 4");
        Node* temp_node ;
        temp_node = root;
        for (int i = 0; i < 30; ++i)
        {
            for (int j = 0; j < 30; ++j)
            {
                temp_board_array[i][j] = board_array[i][j];
            }
        }
        ////////////////////////////////
        bool flag =true;

        int max_X[] = {3,6,7,8,9,8,9,8,7,6,3};
        
        std::vector<int>  current_ring ; 
        std::vector<int>  x1; 
        std::vector<int>  y1; 

        std::vector<int>  x2; 
        std::vector<int>  y2; 
        std::vector<int>  next_x; //
        std::vector<int>  next_y; //


        // tmp_my_ring = my_ring;
        for (int i = 0; i < 10; ++i)
        {
            tmp_my_ring[i] = my_ring[i];
            tmp_tmp_ring[i] = computers_ring[i];
        }
        // tmp_computers_ring = computers_ring;
        for (int i = 0; i < 10; ++i)
        {
            tmp_computers_ring[i] = computers_ring[i];
            tmp_tmp_ring[i] = my_ring[i];
        }

        std::vector<int>  direction_of_play;

        current_ring.push_back(0);
        direction_of_play.push_back(0);
        // consider ring0 is at  0,0 ;
        next_x.push_back(computers_ring[0]-2);
        next_y.push_back(computers_ring[1]);

        x2.push_back(0);
        y2.push_back(0);
        

        // ERRORS TO BE REMOVED// ERRORS TO BE REMOVED// ERRORS TO BE REMOVED// ERRORS TO BE REMOVED// ERRORS TO BE REMOVED
        // check it doesnt go into for loop if only discs ; exceed boundary; //done
        // next move should change player alternatively; // done 
        // add the cut off height                  // done 
        // pop from emty;                           // done 
        // updating the board array currently      // done prob/
        // use only those ring which are present on the board; 
        // move,  from which child came;
        // check whether all cases covered in each direction w.r.t possible moves; //done


        /// change input move given to child of tree;
        //  
        //

        int ht = 0;
        bool global_flag = true;





        while (global_flag==true)
        {
            
            int httep=ht;
            
            std::cerr << "\nMy Ring\n";     
            // for (int i = 0; i < 5; ++i)
            // {
            //    std::cerr<< my_ring[2*i] <<","<<my_ring[2*i+1] << "\n"; 
            // }

            std::cerr << ht<<" <- Height \n"<<endl;
            // print2();
            // if(x1.size()!=0){
            //     std::cerr << temp_node->children.size()<<" <- Height \n"<<x1.at(x1.size()-1)<<"Y1:"<<y1.at(y1.size()-1)<<endl;

            //    std::cerr << temp_node->children.size()<<" <- Height \n"<<x2.at(x2.size()-1)<<"Y1:"<<y2.at(y2.size()-1)<<endl;
            // }
            // print2();

            // for (int i = 0; i < next_x.size(); ++i)
            // {
            //     std::cerr << "\nnext_x"<<i<<": "<<next_x.at(i)<<"\n";
            //     std::cerr << "\nnext_y"<<i<<": "<<next_y.at(i)<<"\n";
            // }

            // for (int i = 0; i < current_ring.size(); ++i)
            // {
            //     std::cerr << "\ncurrent_ring"<<i<<": "<<current_ring.at(i)<<"\n";
            //     std::cerr << "\ndirection of play"<<i<<": "<<direction_of_play.at(i)<<"\n";
            // }
            // cerr<<"                               "<<current_ring.size()<<","<<next_x.size()<<","<<x1.size()<<endl;

            if(httep%2==0)
            {
                for (int i = 0; i < 10; ++i)
                {
                    tmp_ring[i] = tmp_computers_ring[i];
                    tmp_tmp_ring[i] = tmp_my_ring[i];
                }
            }

            else
            {
                for (int i = 0; i < 10; ++i)
                {
                    tmp_ring[i] = tmp_my_ring[i];
                    tmp_tmp_ring[i] = tmp_computers_ring[i];
                }
            }

            for (int i = 0; i < rings_removed.size(); i=i+2)
            {
                if (tmp_ring[2*current_ring.at(current_ring.size()-1)]==rings_removed.at(i) &&  tmp_ring[2*current_ring.at(current_ring.size()-1) + 1]==rings_removed.at(i+1))
                {
                    
                    int r = current_ring.at(current_ring.size()-1);
                    tmp_ring[2*r] =  -15;
                    tmp_ring[2*r+1] = -15;


                    current_ring.pop_back();

                    current_ring.push_back(r+1);
                    int ring_x_pre  = tmp_ring[2*current_ring.at(current_ring.size()-1)];    // x and y co-ordinates of ring  w.r.t board
                    int ring_y_pre  = tmp_ring[2*current_ring.at(current_ring.size()-1)+1];
                    direction_of_play.pop_back();
                    direction_of_play.push_back(0);
                    next_x.pop_back();
                    next_x.push_back(ring_x_pre-2);
                    next_y.pop_back();
                    next_y.push_back(ring_y_pre);
                }
            }
 

            

            //  std::cerr << "\n tmp_Ring Start Up\n"; 
            // for (int i = 0; i < 5; ++i)
            // {
            //     {
            //         std::cerr<< "i :: "<<tmp_ring[2*i] <<","<<tmp_ring[2*i+1]<< "\n" ; 
            //     }
            // }

            // std::cerr << "\n tmp_tmp_Ring Start Up\n"; 
            // for (int i = 0; i < 5; ++i)
            // {
            //     {
            //         std::cerr<< "i :: "<<tmp_tmp_ring[2*i] <<","<<tmp_tmp_ring[2*i+1]<< "\n" ; 
            //     }
            // }


            flag = false;
            int r_prime = current_ring.at(current_ring.size()-1);
            // std::cerr << ("Will_enter cut_off :>)}---^\n"); 

            if (ht== cut_off_height)
            {
                // std::cerr << "\n tmp_Ring Start Up in Cutoof\n"; 
                // for (int i = 0; i < 5; ++i)
                // {
                //     {
                //         std::cerr<< "i :: "<<tmp_ring[2*i] <<","<<tmp_ring[2*i+1]<< "\n" ; 
                //     }
                // }

                // std::cerr << "\n tmp_tmp_Ring Start Up in Cutoof\n"; 
                // for (int i = 0; i < 5; ++i)
                // {
                //     {
                //         std::cerr<< "i :: "<<tmp_tmp_ring[2*i] <<","<<tmp_tmp_ring[2*i+1]<< "\n" ; 
                //     }
                // }
                std::string mo = root->move;
                root = root->get_parent();
                std::cerr << ("cut_off_0\n"); 

                std::cerr<< x1.size()<<endl;
                std::cerr<< x2.size()<<endl;

                reverse_update(0,x1.at(x1.size()-1),y1.at(y1.size()-1),x2.at(x2.size()-1),y2.at(y2.size()-1),mo); 
                std::cerr << ("cut_off_1\n"); 
                // std::cerr << "\n tmp_Ring Start Up in Cutoof\n"; 
                
                current_ring.pop_back();
                // tmp_tmp_ring[2*current_ring.at(current_ring.size()-1)]    =  x1.at(x1.size()-1);    // x and y co-ordinates of ring  w.r.t board
                // tmp_tmp_ring[2*current_ring.at(current_ring.size()-1)+1]  =  y1.at(y1.size()-1);

                // for (int i = 0; i < 5; ++i)
                // {
                //     {
                //         std::cerr<< "i :: "<<tmp_ring[2*i] <<","<<tmp_ring[2*i+1]<< "\n" ; 
                //     }
                // }

                // std::cerr << "\n tmp_tmp_Ring Start Up in Cutoof\n"; 
                // for (int i = 0; i < 5; ++i)
                // {
                //     {
                //         std::cerr<< "i :: "<<tmp_tmp_ring[2*i] <<","<<tmp_tmp_ring[2*i+1]<< "\n" ; 
                //     }
                // }



                // tmp_tmp_ring[2*current_ring.at(current_ring.size()-1)]    =  x1.at(x1.size()-1);    // x and y co-ordinates of ring  w.r.t board
                // tmp_tmp_ring[2*current_ring.at(current_ring.size()-1)+1]  =  y1.at(y1.size()-1);


                x1.pop_back();
                y1.pop_back();
                x2.pop_back();
                y2.pop_back();
                std::cerr << ("cut_off_2 \n"); 
                cerr<<tmp_tmp_ring[2*current_ring.at(current_ring.size()-1)] <<" x1 and x2 "<<tmp_tmp_ring[2*current_ring.at(current_ring.size()-1)+1]; 

                next_x.pop_back();
                next_y.pop_back();
                ht--;
                direction_of_play.pop_back();

                               
                std::cerr << ("cut_off_3\n"); 

                std::cerr<< x1.size();
                

                std::cerr << ("cutt_off_4\n");
            }
            else if (r_prime==5)
            {   

                cerr<<"moving to next ring"<<endl;
                if (ht==0)   
                {
                    std::cerr << ("oh_yes\n");
                    global_flag = false;
                }
                else
                {
                    direction_of_play.pop_back();
                    next_x.pop_back();
                    next_y.pop_back();
                    current_ring.pop_back();
                    ht --;

                    std::string mo = root->move;

                    root = root->get_parent();
                   
                    // check the player;
                    reverse_update(0,x1.at(x1.size()-1),y1.at(y1.size()-1),x2.at(x2.size()-1),y2.at(y2.size()-1),mo); 
                    
                    tmp_tmp_ring[2*current_ring.at(current_ring.size()-1)]    =  x1.at(x1.size()-1);    // x and y co-ordinates of ring  w.r.t board
                    tmp_tmp_ring[2*current_ring.at(current_ring.size()-1)+1]  =  y1.at(y1.size()-1);

                    x1.pop_back();
                    x2.pop_back();
                    y1.pop_back();
                    y2.pop_back();
                    
                }

            }

            
            else if(direction_of_play.at(direction_of_play.size()-1)==0)  // last element of direction_of_play
            {
            
                // flag = false;
                int ring_x  = tmp_ring[2*current_ring.at(current_ring.size()-1)];    // x and y co-ordinates of ring  w.r.t board
                int ring_y  = tmp_ring[2*current_ring.at(current_ring.size()-1)+1];

                //call move +ve y  ..... start again leaving x2,y2
                // assume child obtained has store : x2,y2 | direectio_of_play | score_of_board | 
                
                std::cerr << ("0oh_yes1\n");
                bool flag1 = false;
                if(abs(ring_y)<6 && abs(next_y.at(next_y.size()-1))<6)
                {    
                    for (int i = next_x.at(next_x.size()-1); (i >= - max_X[ring_y+5]) && (i <=  max_X[ring_y+5]) &&abs(ring_y)<=5; i=i-2)
                    {

                        
                        
                        if (abs(temp_board_array[15+i][15+ring_y]) == 2)
                        {
                            // reverse_update(board_config,move)
                            // x2.pop_back();
                            // y2.pop_back();

                            

                            direction_of_play.pop_back();
                            direction_of_play.push_back(1);
                            next_x.pop_back();
                            next_x.push_back(ring_x+2);
                            next_y.pop_back();
                            next_y.push_back(ring_y);
                            // current_ring.pop_back();
                            flag1 = true;
                            break;

                        }
                        else if (abs(temp_board_array[15+i][15+ring_y]) == 1 )
                        {
                            std::cerr << ("0oh_yes2\n");

                            flag=true;
                        } 
                        else if (temp_board_array[15+i][15+ring_y] == 0  &&  flag==false){
                            std::cerr << ("0oh_yes3\n");

                            // direction_of_play.pop_back();
                            // direction_of_play.push_back(1);
                            cerr<<"i is:"<<i<<endl;
                            next_x.pop_back();
                            next_x.push_back(i-2);//(ring_x+2);
                            next_y.pop_back();
                            next_y.push_back(ring_y);

                            // flag = false;
                            x1.push_back(ring_x);
                            y1.push_back(ring_y);

                            std::cerr <<"The current ring is : ... " << current_ring.at(current_ring.size()-1) << " i is "<< i << " ring_y is " << ring_y<<endl;
                            tmp_ring[2*current_ring.at(current_ring.size()-1)]    =  i ;    // x and y co-ordinates of ring  w.r.t board
                            tmp_ring[2*current_ring.at(current_ring.size()-1)+1]  =  ring_y;

                            direction_of_play.push_back(0);
                            current_ring.push_back(0);
                            
                            // for (int j = 0; j< rings_removed.size(); ++j)
                            // {
                            //     if((tmp_tmp_ring[0])==rings_removed.at(2*j) && tmp_tmp_ring[1]==rings_removed.at(2*j+1))
                            //     {

                            //     }
                            // }
                                
                            next_x.push_back(tmp_tmp_ring[0]-2);
                            next_y.push_back(tmp_tmp_ring[1]);
                            
                            x2.push_back(i);
                            y2.push_back(ring_y);


                            //Updateing Public Board Array , Discs not accounted
                            std::vector<int> v1 = change_coordinates(1,x1.at(x1.size()-1),y1.at(y1.size()-1)); 
                            std::vector<int> v2 = change_coordinates(1,x2.at(x2.size()-1),y2.at(y2.size()-1));
                            std::string s_d  = "S ";
                            s_d.append(std::to_string(v1.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v1.at(1)));
                            s_d.append(" ");
                            s_d.append("M ");
                            s_d.append(std::to_string(v2.at(0)));
                            s_d.append(" ");

                            s_d.append(std::to_string(v2.at(1)));

                                            update(0,s_d,1);

                            
                            std::vector<int> v = find_five_consecutive(httep);

                            ht = ht+1;
                            std::cerr << ("Height is inc in 0\n");               
                            int child_score;
                            if (ht%2==1)
                            {
                                 child_score =  1*evaluate_heuristic() ;
                            }
                            else if (ht%2==0)
                            {
                                 child_score =  -1*evaluate_heuristic() ;
                            }
                            
                            reverse_update(0,1,2,3,4,s_d);
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

                                std::vector<int> v_prime = find_which_ring_to_remove(httep);
                                    
                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(1)));

                                rings_removed.push_back(v_prime.at(0));
                                rings_removed.push_back(v_prime.at(1));

                            }

                            update(0,s_d,1);
                            
                            Node* child = new Node(root,child_score,s_d);
                            root->add_children(child);
                            root = child;        
                            std::cerr << s_d ;

                            flag1 = true;
                            break;

                        }
                        else if (temp_board_array[15+i][15+ring_y] == 0  &&  flag==true){
                            // value of this change and place in its child
                           std::cerr << ("0oh_yes4\n");


                            // change_direction to 3 ; 
                            direction_of_play.pop_back();
                            direction_of_play.push_back(1);
                            next_x.pop_back();
                            next_x.push_back(ring_x+2);
                            next_y.pop_back();
                            next_y.push_back(ring_y);

                            flag = false;
                            x1.push_back(ring_x);
                            y1.push_back(ring_y);

                            tmp_ring[2*current_ring.at(current_ring.size()-1)]    =  i ;    // x and y co-ordinates of ring  w.r.t board
                            tmp_ring[2*current_ring.at(current_ring.size()-1)+1]  =  ring_y;

                            direction_of_play.push_back(0);
                            current_ring.push_back(0);
                            
                            next_x.push_back(tmp_tmp_ring[0]-2);
                            next_y.push_back(tmp_tmp_ring[1]);
                            
                            x2.push_back(i);
                            y2.push_back(ring_y);

                            

                           
                           
                            //Updateing Public Board Array , Discs not accounted
                            std::vector<int> v1 = change_coordinates(1,x1.at(x1.size()-1),y1.at(y1.size()-1)); 
                            std::vector<int> v2 = change_coordinates(1,x2.at(x2.size()-1),y2.at(y2.size()-1));
                            std::string s_d  = "S ";
                            s_d.append(std::to_string(v1.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v1.at(1)));
                            s_d.append(" ");
                            s_d.append("M ");
                            s_d.append(std::to_string(v2.at(0)));
                            s_d.append(" ");

                            s_d.append(std::to_string(v2.at(1)));

                            update(0,s_d,1);


                            std::vector<int> v = find_five_consecutive(httep);

                            ht = ht+1;
                            std::cerr << ("Height is inc in 0\n");               
                            int child_score;
                            if (ht%2==1)
                            {
                                 child_score =  1*evaluate_heuristic() ;
                            }
                            else if (ht%2==0)
                            {
                                 child_score =  -1*evaluate_heuristic() ;
                            }
                            reverse_update(0,1,2,3,4,s_d);
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

                                std::vector<int> v_prime = find_which_ring_to_remove(httep);
                                    
                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(1)));
                                rings_removed.push_back(v_prime.at(0));
                                rings_removed.push_back(v_prime.at(1));

                            }


                            update(0,s_d,1);
                    
                            
                            
                            Node* child = new Node(root,child_score,s_d);
                            root->add_children(child);
                            root = child;        

                            flag1 = true;
                            break;
                        }

                    }
                }
                if (flag1==false)
                {
                        direction_of_play.pop_back();
                        direction_of_play.push_back(1);
                        next_x.pop_back();
                        next_x.push_back(ring_x+2);
                        next_y.pop_back();
                        next_y.push_back(ring_y);
                        // current_ring.pop_back();
                        flag1 = true;
                }
                std::cerr << ("0oh_yes5\n");
                // exit(0);
            }

            else if(direction_of_play.at(direction_of_play.size()-1)==1)  // last element of direction_of_play
            {
                std::cerr << ("1oh_yes2\n");               
                int ring_x  = tmp_ring[2*current_ring.at(current_ring.size()-1)];    // x and y co-ordinates of ring  w.r.t board
                int ring_y  = tmp_ring[2*current_ring.at(current_ring.size()-1)+1];

                //call move +ve y  ..... start again leaving x2,y2
                // assume child obtained has store : x2,y2 | direectio_of_play | score_of_board | 
                
                bool flag1 = false;
                if(abs(ring_y)<6 && abs(next_y.at(next_y.size()-1))<6)
                {    
                    for (int i = next_x.at(next_x.size()-1); (i <=  max_X[ring_y+5])&&(i >= - max_X[ring_y+5])&&abs(ring_y)<=5; i=i+2)
                    {
                        
                        if (abs(temp_board_array[15+i][15+ring_y]) == 2)
                        {
                            // reverse_update(board_config,move)
                            // x2.pop_back();
                            // y2.pop_back();

                            direction_of_play.pop_back();
                            direction_of_play.push_back(2);
                            next_x.pop_back();
                            next_x.push_back(ring_x+1);
                            next_y.pop_back();
                            next_y.push_back(ring_y+1);
                            // current_ring.pop_back();
                            flag1 = true;
                            break;
                        }
                        else if (abs(temp_board_array[15+i][15+ring_y]) == 1 )
                        {
                            flag=true;
                        } 
                        else if (temp_board_array[15+i][15+ring_y] == 0  &&  flag==false){

                            next_x.pop_back();
                            next_x.push_back(i+2);//(ring_x+2);
                            next_y.pop_back();
                            next_y.push_back(ring_y);

                            // flag = false;
                            x1.push_back(ring_x);
                            y1.push_back(ring_y);

                            tmp_ring[2*current_ring.at(current_ring.size()-1)]    =  i ;    // x and y co-ordinates of ring  w.r.t board
                            tmp_ring[2*current_ring.at(current_ring.size()-1)+1]  =  ring_y;

                            direction_of_play.push_back(0);
                            current_ring.push_back(0);
                            
                            next_x.push_back(tmp_tmp_ring[0]-2);
                            next_y.push_back(tmp_tmp_ring[1]);
                            
                            x2.push_back(i);
                            y2.push_back(ring_y);


                            //Updateing Public Board Array , Discs not accounted
                            std::vector<int> v1 = change_coordinates(1,x1.at(x1.size()-1),y1.at(y1.size()-1)); 
                            std::vector<int> v2 = change_coordinates(1,x2.at(x2.size()-1),y2.at(y2.size()-1));
                            std::string s_d  = "S ";
                            s_d.append(std::to_string(v1.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v1.at(1)));
                            s_d.append(" ");
                            s_d.append("M ");
                            s_d.append(std::to_string(v2.at(0)));
                            s_d.append(" ");

                            s_d.append(std::to_string(v2.at(1)));

                                            update(0,s_d,1);

                            std::vector<int> v = find_five_consecutive(httep);

                            ht = ht+1;
                            std::cerr << ("Height is inc in 0\n");               
                            int child_score;
                            if (ht%2==1)
                            {
                                 child_score =  1*evaluate_heuristic() ;
                            }
                            else if (ht%2==0)
                            {
                                 child_score =  -1*evaluate_heuristic() ;
                            }
                            reverse_update(0,1,2,3,4,s_d);
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

                                std::vector<int> v_prime = find_which_ring_to_remove(httep);
                                    
                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(1)));
                                rings_removed.push_back(v_prime.at(0));
                                rings_removed.push_back(v_prime.at(1));
                            }
                            else{

                            }
                            
                                            update(0,s_d,1);

                            // update(0,s_d,1);
                            
                            
                            Node* child = new Node(root,child_score,s_d);
                            root->add_children(child);
                            root = child; 
                                                    std::cerr << s_d ;

                            flag1=true;   
                            break;    

                        }
                        else if (temp_board_array[15+i][15+ring_y] == 0  &&  flag==true){
                            // value of this change and place in its child
                           

                            // change_direction to 3 ; 
                            std::cerr << ("1oh_yes3\n");               
                            
                            direction_of_play.pop_back();
                            direction_of_play.push_back(2);
                            next_x.pop_back();
                            next_x.push_back(ring_x+1);
                            next_y.pop_back();
                            next_y.push_back(ring_y+1);

                            flag = false;
                            x1.push_back(ring_x);
                            y1.push_back(ring_y);

                            tmp_ring[2*current_ring.at(current_ring.size()-1)]    =  i ;    // x and y co-ordinates of ring  w.r.t board
                            tmp_ring[2*current_ring.at(current_ring.size()-1)+1]  =  ring_y;

                            direction_of_play.push_back(0);
                            current_ring.push_back(0);

                            
                            next_x.push_back(tmp_tmp_ring[0]-2);
                            next_y.push_back(tmp_tmp_ring[1]);
                            
                            x2.push_back(i);
                            y2.push_back(ring_y);


                           
                           
                            //Updateing Public Board Array , Discs not accounted
                            std::vector<int> v1 = change_coordinates(1,x1.at(x1.size()-1),y1.at(y1.size()-1)); 
                            std::vector<int> v2 = change_coordinates(1,x2.at(x2.size()-1),y2.at(y2.size()-1));
                            std::string s_d  = "S ";
                            s_d.append(std::to_string(v1.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v1.at(1)));
                            s_d.append(" ");
                            s_d.append("M ");
                            s_d.append(std::to_string(v2.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v2.at(1)));

                                                    update(0,s_d,1);

                            std::vector<int> v = find_five_consecutive(httep);

                            ht = ht+1;
                            int child_score;
                            if (ht%2==1)
                            {
                                 child_score =  1*evaluate_heuristic() ;
                            }
                            else if (ht%2==0)
                            {
                                 child_score =  -1*evaluate_heuristic() ;
                            }        
                            reverse_update(0,1,2,3,4,s_d);
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

                                std::vector<int> v_prime = find_which_ring_to_remove(httep);
                                    
                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(1)));
                                rings_removed.push_back(v_prime.at(0));
                                rings_removed.push_back(v_prime.at(1));

                            }
                                                    update(0,s_d,1);


                            std::cerr << ("Height is inc in 1\n");               

                                           
                            Node* child = new Node(root,child_score,s_d);
                            root->add_children(child);
                            root = child;  

                            std::cerr << ("1oh_yes4\n");               
                            std::cerr << s_d ;
                             std::cerr << ("1oh_yes5\n");  
                            flag1 = true;
                            break;
                        }


                    }
                }
                if (flag1==false)
                {
                         std::cerr << ("1oh_yes6\n");  
                        direction_of_play.pop_back();
                        direction_of_play.push_back(2);
                        next_x.pop_back();
                        next_x.push_back(ring_x+1);
                        next_y.pop_back();
                        next_y.push_back(ring_y+1);
                        // current_ring.pop_back();
                        flag1 = true;
                }
                std::cerr << ("1oh_yes7\n");               

            }
            // exit(0);
            else if(direction_of_play.at(direction_of_play.size()-1)==2)  // y=X -ve
            {
                std::cerr << ("2oh_yes2\n");               
                int ring_x  = tmp_ring[2*current_ring.at(current_ring.size()-1)];    // x and y co-ordinates of ring  w.r.t board
                int ring_y  = tmp_ring[2*current_ring.at(current_ring.size()-1)+1];
                std::cerr << ("2oh_yes21\n");
                //call move +ve y  ..... start again leaving x2,y2
                // assume child obtained has store : x2,y2 | direectio_of_play | score_of_board | 
                
                bool flag1 = false;
                if (abs(ring_y)<6 && abs(next_y.at(next_y.size()-1))<6)
                {
                    
                    for (int i = next_x.at(next_x.size()-1); (i <= max_X[next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1)+5])&&(i >= -max_X[next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1)+5])&&abs(next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1))<=5; i=i+1)
                    {
                        
                        std::cerr << ("2oh_yes22\n");
                        std::cerr << next_x.size();
                        std::cerr << next_y.size();
                        std::cerr << 15+i;
                        std::cerr << 15+next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1);

                        if (abs(temp_board_array[15+i][15+next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1) ]) == 2)
                        {
                            // reverse_update(board_config,move)
                            // x2.pop_back();
                            // y2.pop_back();

                            std::cerr << ("2oh_yes23\n");
                            direction_of_play.pop_back();
                            direction_of_play.push_back(3);
                            next_x.pop_back();
                            next_x.push_back(ring_x-1);
                            next_y.pop_back();
                            next_y.push_back(ring_y-1);
                            // current_ring.pop_back();
                            flag1 = true;
                            break;
                        }
                        else if (abs(temp_board_array[15+i][15+next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1) ]) == 1)
                        {
                            std::cerr << ("2oh_yes23lLP\n");
                            std::cerr << "\n"<<i ;
                            flag=true;
                        } 
                        else if (temp_board_array[15+i][15+next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1) ] == 0  &&  flag==false){
                            // direction_of_play.pop_back();
                            // direction_of_play.push_back(3);
                            x1.push_back(ring_x);
                            y1.push_back(ring_y);
                            x2.push_back(i);
                            y2.push_back(next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1));
                            int to_push = (next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1));

                            next_x.pop_back();
                            next_x.push_back(i+1);
                            next_y.pop_back();
                            next_y.push_back(to_push+1);

                            // ASSUME CORRECT
                            tmp_ring[2*current_ring.at(current_ring.size()-1)]    =  i ;    // x and y co-ordinates of ring  w.r.t board
                            tmp_ring[2*current_ring.at(current_ring.size()-1)+1]  =  to_push;//(next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1));

                            direction_of_play.push_back(0);
                            current_ring.push_back(0);

                            
                            // check condition if point is valid
                            next_x.push_back(tmp_tmp_ring[0]-2);
                            next_y.push_back(tmp_tmp_ring[1]);
                            
                            

                            // std::cerr << ("2oh_yes25\n");
                           
                           
                            //Updateing Public Board Array , Discs not accounted

                            std::vector<int> v1 = change_coordinates(1,x1.at(x1.size()-1),y1.at(y1.size()-1)); 
                            std::vector<int> v2 = change_coordinates(1,x2.at(x2.size()-1),y2.at(y2.size()-1));
                            std::cerr << "\n"<<x1.at(x1.size()-1)<<"\n";
                            std::cerr << "\n"<<y1.at(y1.size()-1)<<"\n";
                            std::cerr << "\n"<<x2.at(x2.size()-1)<<"\n";
                            std::cerr << "\n"<<y2.at(y2.size()-1)<<"\n";
                            for (int i = 0; i < 2; ++i)
                            {
                                std::cerr << "v1 "<< i << "::"<<v1.at(i);
                                std::cerr << "v2 "<< i << "::"<<v2.at(i);
                            }
                            std::string s_d  = "S ";
                            s_d.append(std::to_string(v1.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v1.at(1)));
                            s_d.append(" ");
                            s_d.append("M ");
                            s_d.append(std::to_string(v2.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v2.at(1)));

                                                    update(0,s_d,1);

                            std::vector<int> v = find_five_consecutive(httep);

                            ht = ht+1;
                            int child_score;
                            if (ht%2==1)
                            {
                                 child_score =  1*evaluate_heuristic() ;
                            }
                            else if (ht%2==0)
                            {
                                 child_score =  -1*evaluate_heuristic() ;
                            }
                            reverse_update(0,1,2,3,4,s_d);
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

                                std::vector<int> v_prime = find_which_ring_to_remove(httep);
                                    
                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(1)));
                                rings_removed.push_back(v_prime.at(0));
                                rings_removed.push_back(v_prime.at(1));

                            }
                            update(0,s_d,1);
                            
                            Node* child = new Node(root,child_score,s_d);
                            root->add_children(child);
                            root = child;  

                            std::cerr << ("2oh_yes26\n");

                            std::cerr << "s_d: "<< s_d ;
                            
                            std::cerr << ("2oh_yes26_1\n");

                            flag1 = true;
                            break; 

                        }
                        else if (temp_board_array[15+i][15+next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1) ] == 0  &&  flag==true){
                            // value of this change and place in its child
                           

                            // change_direction to 3 ; 
                            std::cerr << ("2oh_yes24\n");
                            direction_of_play.pop_back();
                            direction_of_play.push_back(3);
                            x1.push_back(ring_x);
                            y1.push_back(ring_y);
                            x2.push_back(i);
                            y2.push_back(next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1));


                            tmp_ring[2*current_ring.at(current_ring.size()-1)]    =  i ;    // x and y co-ordinates of ring  w.r.t board
                            tmp_ring[2*current_ring.at(current_ring.size()-1)+1]  =  (next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1));

                            next_x.pop_back();
                            next_x.push_back(ring_x-1);
                            next_y.pop_back();
                            next_y.push_back(ring_y-1);

                            flag = false;


                            // ASSUME CORRECT
                            

                            direction_of_play.push_back(0);
                            current_ring.push_back(0);

                            
                            // check condition if point is valid
                            next_x.push_back(tmp_tmp_ring[0]-2);
                            next_y.push_back(tmp_tmp_ring[1]);
                            
                            

                            std::cerr << ("2oh_yes25\n");
                           
                           
                            //Updateing Public Board Array , Discs not accounted

                            std::vector<int> v1 = change_coordinates(1,x1.at(x1.size()-1),y1.at(y1.size()-1)); 
                            std::vector<int> v2 = change_coordinates(1,x2.at(x2.size()-1),y2.at(y2.size()-1));
                            std::cerr << "\n"<<x1.at(x1.size()-1)<<"\n";
                            std::cerr << "\n"<<y1.at(y1.size()-1)<<"\n";
                            std::cerr << "\n"<<x2.at(x2.size()-1)<<"\n";
                            std::cerr << "\n"<<y2.at(y2.size()-1)<<"\n";
                            for (int i = 0; i < 2; ++i)
                            {
                                std::cerr << "v1 "<< i << "::"<<v1.at(i);
                                std::cerr << "v2 "<< i << "::"<<v2.at(i);
                            }
                            std::string s_d  = "S ";
                            s_d.append(std::to_string(v1.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v1.at(1)));
                            s_d.append(" ");
                            s_d.append("M ");
                            s_d.append(std::to_string(v2.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v2.at(1)));


                                                    update(0,s_d,1);

                            std::vector<int> v = find_five_consecutive(httep);

                            ht = ht+1;
                            int child_score;

                            if (ht%2==1)
                            {
                                 child_score =  1*evaluate_heuristic() ;
                            }
                            else if (ht%2==0)
                            {
                                 child_score =  -1*evaluate_heuristic() ;
                            }
                            reverse_update(0,1,2,3,4,s_d);
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

                                std::vector<int> v_prime = find_which_ring_to_remove(httep);
                                    
                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(1)));
                                rings_removed.push_back(v_prime.at(0));
                                rings_removed.push_back(v_prime.at(1));

                            }
                            update(0,s_d,1);
                            
                            Node* child = new Node(root,child_score,s_d);
                            root->add_children(child);
                            root = child;  

                            std::cerr << ("2oh_yes26\n");

                            std::cerr << "s_d: "<< s_d ;
                            
                            std::cerr << ("2oh_yes26_1\n");

                            flag1 = true;
                            break;
                        }


                    }
                }
                if (flag1==false)
                {
                        std::cerr << ("2oh_yes27\n");
                        
                        direction_of_play.pop_back();
                        direction_of_play.push_back(3);
                        next_x.pop_back();
                        next_x.push_back(ring_x-1);
                        next_y.pop_back();
                        next_y.push_back(ring_y-1);
                        // current_ring.pop_back();
                        std::cerr << ("2oh_yes28\n");

                        flag1 = true;
                }
                std::cerr << ("2oh_yes3\n");               


            }

            else if(direction_of_play.at(direction_of_play.size()-1)==3)  // y = X +ve
            {
                std::cerr << ("3oh_yes1\n");
                int ring_x  = tmp_ring[2*current_ring.at(current_ring.size()-1)];    // x and y co-ordinates of ring  w.r.t board
                int ring_y  = tmp_ring[2*current_ring.at(current_ring.size()-1)+1];

                //call move +ve y  ..... start again leaving x2,y2
                // assume child obtained has store : x2,y2 | direectio_of_play | score_of_board | 
                
                bool flag1 = false;
                if(abs(ring_y)<6 && abs(next_y.at(next_y.size()-1))<6)
                {    
                    for (int i = next_x.at(next_x.size()-1); (i >= - max_X[next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1)+5])&& (i <=  max_X[next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1)+5])&&abs(next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1))<=5; i=i-1)
                    {
                        
                        if (abs(temp_board_array[15+i][15+next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1) ]) == 2)
                        {
                            // reverse_update(board_config,move)
                            // x2.pop_back();
                            // y2.pop_back();

                            direction_of_play.pop_back();
                            direction_of_play.push_back(4);
                            next_x.pop_back();
                            next_x.push_back(ring_x+1);
                            next_y.pop_back();
                            next_y.push_back(ring_y-1);
                            // current_ring.pop_back();
                            flag1 = true;
                            break;
                        }
                        else if (abs(temp_board_array[15+i][15+next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1) ]) == 1)
                        {
                            flag=true;
                        } 
                        else if (temp_board_array[15+i][15+next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1) ] == 0  &&  flag==false){
                             // change_direction to 3 ; 
                            

                            x1.push_back(ring_x);
                            y1.push_back(ring_y);
                            x2.push_back(i);
                            y2.push_back(next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1) );
                            int to_push = (next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1) );

                            tmp_ring[2*current_ring.at(current_ring.size()-1)]    =  i ;    // x and y co-ordinates of ring  w.r.t board
                            tmp_ring[2*current_ring.at(current_ring.size()-1)+1]  =  (next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1) );

                            next_x.pop_back();
                            next_x.push_back(i-1);
                            next_y.pop_back();
                            next_y.push_back(to_push-1);

                            flag = false;



                            // ASSUME CORRECT
                            

                            direction_of_play.push_back(0);
                            current_ring.push_back(0);

                            
                            // check condition if point is valid
                            next_x.push_back(tmp_tmp_ring[0]-2);
                            next_y.push_back(tmp_tmp_ring[1]);
                            
                            

                           
                           
                            //Updateing Public Board Array , Discs not accounted
                             std::vector<int> v1 = change_coordinates(1,x1.at(x1.size()-1),y1.at(y1.size()-1)); 
                            std::vector<int> v2 = change_coordinates(1,x2.at(x2.size()-1),y2.at(y2.size()-1));
                            std::string s_d  = "S ";
                            s_d.append(std::to_string(v1.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v1.at(1)));
                            s_d.append(" ");
                            s_d.append("M ");
                            s_d.append(std::to_string(v2.at(0)));
                            s_d.append(" ");

                            s_d.append(std::to_string(v2.at(1)));

                                                    update(0,s_d,1);

                            std::vector<int> v = find_five_consecutive(httep);

                            ht = ht+1;
                            int child_score;

                            if (ht%2==1)
                            {
                                 child_score =  1*evaluate_heuristic() ;
                            }
                            else if (ht%2==0)
                            {
                                 child_score =  -1*evaluate_heuristic() ;
                            }
                            reverse_update(0,1,2,3,4,s_d);
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

                                std::vector<int> v_prime = find_which_ring_to_remove(httep);
                                    
                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(1)));
                                rings_removed.push_back(v_prime.at(0));
                                rings_removed.push_back(v_prime.at(1));

                            }
                            update(0,s_d,1);
                            
                            Node* child = new Node(root,child_score,s_d);
                            root->add_children(child);
                            root = child;  
                    
                            flag1 = true;
                            break;
                        }
                        else if (temp_board_array[15+i][15+next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1) ] == 0  &&  flag==true){
                            // value of this change and place in its child
                           

                            // change_direction to 3 ; 
                            direction_of_play.pop_back();
                            direction_of_play.push_back(4);

                            x1.push_back(ring_x);
                            y1.push_back(ring_y);
                            x2.push_back(i);
                            y2.push_back(next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1) );

                            tmp_ring[2*current_ring.at(current_ring.size()-1)]    =  i ;    // x and y co-ordinates of ring  w.r.t board
                            tmp_ring[2*current_ring.at(current_ring.size()-1)+1]  =  (next_y.at(next_y.size()-1)+i -next_x.at(next_x.size()-1) );

                            next_x.pop_back();
                            next_x.push_back(ring_x+1);
                            next_y.pop_back();
                            next_y.push_back(ring_y-1);

                            flag = false;



                            // ASSUME CORRECT
                            

                            direction_of_play.push_back(0);
                            current_ring.push_back(0);

                            
                            // check condition if point is valid
                            next_x.push_back(tmp_tmp_ring[0]-2);
                            next_y.push_back(tmp_tmp_ring[1]);
                            
                            

                           
                           
                            //Updateing Public Board Array , Discs not accounted
                             std::vector<int> v1 = change_coordinates(1,x1.at(x1.size()-1),y1.at(y1.size()-1)); 
                            std::vector<int> v2 = change_coordinates(1,x2.at(x2.size()-1),y2.at(y2.size()-1));
                            std::string s_d  = "S ";
                            s_d.append(std::to_string(v1.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v1.at(1)));
                            s_d.append(" ");
                            s_d.append("M ");
                            s_d.append(std::to_string(v2.at(0)));
                            s_d.append(" ");

                            s_d.append(std::to_string(v2.at(1)));

                                                    update(0,s_d,1);

                            std::vector<int> v = find_five_consecutive(httep);

                            ht = ht+1;
                            int child_score;
                            if (ht%2==1)
                            {
                                 child_score =  1*evaluate_heuristic() ;
                            }
                            else if (ht%2==0)
                            {
                                 child_score =  -1*evaluate_heuristic() ;
                            }
                            reverse_update(0,1,2,3,4,s_d);
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

                                std::vector<int> v_prime = find_which_ring_to_remove(httep);
                                    
                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(1)));
                                rings_removed.push_back(v_prime.at(0));
                                rings_removed.push_back(v_prime.at(1));

                            }
                            
                            update(0,s_d,1);
                            
                            Node* child = new Node(root,child_score,s_d);
                            root->add_children(child);
                            root = child;  
                    
                            flag1 = true;
                            break;
                        }

                    }
                }
                if (flag1==false)
                {
                        direction_of_play.pop_back();
                        direction_of_play.push_back(4);
                        next_x.pop_back();
                        next_x.push_back(ring_x+1);
                        next_y.pop_back();
                        next_y.push_back(ring_y-1);
                        // current_ring.pop_back();
                        flag1 = true;
                }
                std::cerr << ("3oh_yes1\n");


            }

            else if(direction_of_play.at(direction_of_play.size()-1)==4)  // y = -X +ve
            {
                std::cerr << ("4oh_yes1\n");
                // print2();
                int ring_x  = tmp_ring[2*current_ring.at(current_ring.size()-1)];    // x and y co-ordinates of ring  w.r.t board
                int ring_y  = tmp_ring[2*current_ring.at(current_ring.size()-1)+1];

                //call move +ve y  ..... start again leaving x2,y2
                // assume child obtained has store : x2,y2 | direectio_of_play | score_of_board | 
                
                bool flag1 = false;
                if(abs(ring_y)<6 && abs(next_y.at(next_y.size()-1))<6)
                { 
                    for (int i = next_x.at(next_x.size()-1); (i >= - max_X[next_y.at(next_y.size()-1)-i + next_x.at(next_x.size()-1)+5])&& (i <=  max_X[next_y.at(next_y.size()-1)-i + next_x.at(next_x.size()-1)+5])&&abs(next_y.at(next_y.size()-1)-i + next_x.at(next_x.size()-1))<=5; i=i+1)
                    {
                        
                        std::cerr << ("4oh_yes2\n");
                        
                        if (abs(temp_board_array[15+i][15+next_y.at(next_y.size()-1)-i + next_x.at(next_x.size()-1) ]) == 2)
                        {
                            // reverse_update(board_config,move)
                            // x2.pop_back();
                            // y2.pop_back();

                             std::cerr << ("4oh_yes3\n");
                            
                            direction_of_play.pop_back();
                            direction_of_play.push_back(5);
                            next_x.pop_back();
                            next_x.push_back(ring_x-1);
                            next_y.pop_back();
                            next_y.push_back(ring_y+1);
                            // current_ring.pop_back();
                            flag1 = true;
                            break;
                        }
                        else if (abs(temp_board_array[15+i][15+next_y.at(next_y.size()-1)-i +next_x.at(next_x.size()-1) ]) == 1)
                        {
                             std::cerr << ("4oh_yes4\n");
                            
                            flag=true;
                        } 
                        else if (temp_board_array[15+i][15+next_y.at(next_y.size()-1)-i +next_x.at(next_x.size()-1) ] == 0  &&  flag==false){

                            std::cerr << ("4oh_yes5\n");
                            x1.push_back(ring_x);
                            y1.push_back(ring_y);

                            x2.push_back(i);
                            y2.push_back(next_y.at(next_y.size()-1)-i + next_x.at(next_x.size()-1) );
                            int to_push = (next_y.at(next_y.size()-1)-i + next_x.at(next_x.size()-1) );
                            

                            tmp_ring[2*current_ring.at(current_ring.size()-1)]    =  i ;    // x and y co-ordinates of ring  w.r.t board
                            tmp_ring[2*current_ring.at(current_ring.size()-1)+1]  =  (next_y.at(next_y.size()-1)-i + next_x.at(next_x.size()-1) );

                            next_x.pop_back();
                            next_x.push_back(i+1);
                            next_y.pop_back();
                            next_y.push_back(to_push-1);

                            flag = false;
                           

                            // ASSUME CORRECT
                            

                            direction_of_play.push_back(0);
                            current_ring.push_back(0);

                            
                            // check condition if point is valid
                            next_x.push_back(tmp_tmp_ring[0]-2);
                            next_y.push_back(tmp_tmp_ring[1]);
                            
                            
                           

                           
                           
                            //Updateing Public Board Array , Discs not accounted
                            std::vector<int> v1 = change_coordinates(1,x1.at(x1.size()-1),y1.at(y1.size()-1)); 
                            std::vector<int> v2 = change_coordinates(1,x2.at(x2.size()-1),y2.at(y2.size()-1));
                            std::string s_d  = "S ";
                            s_d.append(std::to_string(v1.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v1.at(1)));
                            s_d.append(" ");
                            s_d.append("M ");
                            s_d.append(std::to_string(v2.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v2.at(1)));

                                                    update(0,s_d,1);

                            std::vector<int> v = find_five_consecutive(httep);

                            ht = ht+1;
                            int child_score;

                            if (ht%2==1)
                            {
                                 child_score =  1*evaluate_heuristic() ;
                            }
                            else if (ht%2==0)
                            {
                                 child_score =  -1*evaluate_heuristic() ;
                            }
                            reverse_update(0,1,2,3,4,s_d);
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

                                std::vector<int> v_prime = find_which_ring_to_remove(httep);
                                    
                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(1)));
                                rings_removed.push_back(v_prime.at(0));
                                rings_removed.push_back(v_prime.at(1));

                            }
                            update(0,s_d,1);
                            
                            Node* child = new Node(root,child_score,s_d);
                            root->add_children(child);
                            root = child;  
                             std::cerr << ("4oh_yes6_1\n");
                            std::cerr << s_d;
                             std::cerr << ("4oh_yes6_2\n");

                            flag1 = true;
                            break;
                        }
                        else if (temp_board_array[15+i][15+next_y.at(next_y.size()-1)-i +next_x.at(next_x.size()-1) ] == 0  &&  flag==true){
                            // value of this change and place in its child
                           

                            // change_direction to 3 ; 
                             std::cerr << ("4oh_yes6\n");
                            
                            direction_of_play.pop_back();
                            direction_of_play.push_back(5);

                             x1.push_back(ring_x);
                            y1.push_back(ring_y);

                            x2.push_back(i);
                            y2.push_back(next_y.at(next_y.size()-1)-i + next_x.at(next_x.size()-1) );

                            tmp_ring[2*current_ring.at(current_ring.size()-1)]    =  i ;    // x and y co-ordinates of ring  w.r.t board
                            tmp_ring[2*current_ring.at(current_ring.size()-1)+1]  =  (next_y.at(next_y.size()-1)-i + next_x.at(next_x.size()-1) );

                            next_x.pop_back();
                            next_x.push_back(ring_x-1);
                            next_y.pop_back();
                            next_y.push_back(ring_y+1);

                            flag = false;
                           

                            // ASSUME CORRECT
                            

                            direction_of_play.push_back(0);
                            current_ring.push_back(0);

                            
                            // check condition if point is valid
                            next_x.push_back(tmp_tmp_ring[0]-2);
                            next_y.push_back(tmp_tmp_ring[1]);
                            
                            
                           

                           
                           
                            //Updateing Public Board Array , Discs not accounted
                            std::vector<int> v1 = change_coordinates(1,x1.at(x1.size()-1),y1.at(y1.size()-1)); 
                            std::vector<int> v2 = change_coordinates(1,x2.at(x2.size()-1),y2.at(y2.size()-1));
                            std::string s_d  = "S ";
                            s_d.append(std::to_string(v1.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v1.at(1)));
                            s_d.append(" ");
                            s_d.append("M ");
                            s_d.append(std::to_string(v2.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v2.at(1)));

                                                    update(0,s_d,1);

                            std::vector<int> v = find_five_consecutive(httep);

                            ht = ht+1;
                            int child_score;
                            if (ht%2==1)
                            {
                                 child_score =  1*evaluate_heuristic() ;
                            }
                            else if (ht%2==0)
                            {
                                 child_score =  -1*evaluate_heuristic() ;
                            }
                            reverse_update(0,1,2,3,4,s_d);
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

                                std::vector<int> v_prime = find_which_ring_to_remove(httep);
                                    
                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(1)));
                                rings_removed.push_back(v_prime.at(0));
                                rings_removed.push_back(v_prime.at(1));

                            }
                            
                            update(0,s_d,1);
                            

                            Node* child = new Node(root,child_score,s_d);
                            root->add_children(child);
                            root = child;  
                             std::cerr << ("4oh_yes6_1\n");
                            std::cerr << s_d;
                             std::cerr << ("4oh_yes6_2\n");

                            flag1 = true;
                            break;
                        }

                    }
                }
                if (flag1==false)
                {
                    
                        std::cerr << ("4oh_yes7\n");
                        
                        direction_of_play.pop_back();
                        direction_of_play.push_back(5);
                       
                         next_x.pop_back();
                        next_x.push_back(ring_x-1);
                        next_y.pop_back();
                        next_y.push_back(ring_y+1);
                        // current_ring.pop_back();
                        flag1 = true;
                }
                std::cerr << ("4oh_yes8\n");
                // print2();


            }

            else if(direction_of_play.at(direction_of_play.size()-1)==5)  // y = -X -ve
            {
                cerr<<"5oh_yes1 "<<next_x.at(next_x.size()-1)<<" "<<- max_X[next_y.at(next_y.size()-1)+5]<<"\n";
                
                int ring_x  = tmp_ring[2*current_ring.at(current_ring.size()-1)];    // x and y co-ordinates of ring  w.r.t board
                int ring_y  = tmp_ring[2*current_ring.at(current_ring.size()-1)+1];

                //call move +ve y  ..... start again leaving x2,y2
                // assume child obtained has store : x2,y2 | direectio_of_play | score_of_board | 
                
                bool flag1 = false;
                if(abs(ring_y)<6 && abs(next_y.at(next_y.size()-1))<6)
                {
                    for (int i = next_x.at(next_x.size()-1); (i >= - max_X[next_y.at(next_y.size()-1)-i + next_x.at(next_x.size()-1)+5])&& (i <=  max_X[next_y.at(next_y.size()-1)-i + next_x.at(next_x.size()-1)+5]) && abs(next_y.at(next_y.size()-1)-i + next_x.at(next_x.size()-1))<=5; i=i-1)
                    {
                        std::cerr << ("In for loop\n");
                        
                        if (abs(temp_board_array[15+i][15+next_y.at(next_y.size()-1)-i + next_x.at(next_x.size()-1) ]) == 2)
                        {
                            std::cerr << ("5oh_yes11\n");

                            // reverse_update(board_config,move)
                            // x2.pop_back();
                            // y2.pop_back();

                           
                            int r = current_ring.at(current_ring.size()-1);
                            current_ring.pop_back();


                            // if (r==4)
                            // {   
                            //     direction_of_play.pop_back();
                            //     next_x.pop_back();
                            //     next_y.pop_back();
                            //     ht --;

                            //     root = root->getparent();
                               
                                

                            //     reverse_update(0,x1.at(x1.size()-1),y1.at(y1.size()-1),x2.at(x2.size()-1),y2.at(y2.size()-1));
                            //     x1.pop_back();
                            //     x2.pop_back();
                            //     y1.pop_back();
                            //     y2.pop_back();
                            // }
                            // else
                            // {
                                current_ring.push_back(r+1);
                                int ring_x_pre  = tmp_ring[2*current_ring.at(current_ring.size()-1)];    // x and y co-ordinates of ring  w.r.t board
                                int ring_y_pre  = tmp_ring[2*current_ring.at(current_ring.size()-1)+1];
                                direction_of_play.pop_back();
                                direction_of_play.push_back(0);
                                next_x.pop_back();
                                next_x.push_back(ring_x_pre-2);
                                next_y.pop_back();
                                next_y.push_back(ring_y_pre);


                           // }
                            flag1 = true;
                            break;
                        }
                        else if (abs(temp_board_array[15+i][15+next_y.at(next_y.size()-1)-i +next_x.at(next_x.size()-1) ]) == 1)
                        {
                            std::cerr << ("5oh_yes12\n");
                            flag=true;
                        } 
                        else if (temp_board_array[15+i][15+next_y.at(next_y.size()-1)-i +next_x.at(next_x.size()-1) ] == 0  &&  flag==false)
                        {
                            std::cerr << ("5oh_yes13\n");
                            int r = current_ring.at(current_ring.size()-1);
                            // current_ring.pop_back();
                            // if (r==4)
                            // {   
                            //     direction_of_play.pop_back();
                            //     next_x.pop_back();
                            //     next_y.pop_back();
                            //     reverse_update(0,x1.at(x1.size()-1),y1.at(y1.size()-1),x2.at(x2.size()-1),y2.at(y2.size()-1));
                            //     x1.pop_back();
                            //     x2.pop_back();
                            //     y1.pop_back();
                            //     y2.pop_back();
                                
                            //     ht--;
                            // }
                            


                                // direction_of_play.pop_back();
                                // direction_of_play.push_back(0);
                                // current_ring.push_back(r+1);
                                int ring_x_pre  = tmp_ring[2*current_ring.at(current_ring.size()-1)];    // x and y co-ordinates of ring  w.r.t board
                                int ring_y_pre  = tmp_ring[2*current_ring.at(current_ring.size()-1)+1];

                                x1.push_back(ring_x);
                                y1.push_back(ring_y);
                                x2.push_back(i);
                                y2.push_back(next_y.at(next_y.size()-1)-i +next_x.at(next_x.size()-1));

                                int to_push = (next_y.at(next_y.size()-1)-i +next_x.at(next_x.size()-1));
                            // ASSUME CORRECT
                                tmp_ring[2*r]    =  i ;    // x and y co-ordinates of ring  w.r.t board
                                tmp_ring[2*r+1]  =  (next_y.at(next_y.size()-1)-i +next_x.at(next_x.size()-1));

                                next_x.pop_back();
                                next_x.push_back(i-1);
                                next_y.pop_back();
                                next_y.push_back(to_push+1);

                               
                                

                                
                            // }







                            direction_of_play.push_back(0);
                            current_ring.push_back(0);

                            
                            // check condition if point is valid
                            next_x.push_back(tmp_tmp_ring[0]-2);
                            next_y.push_back(tmp_tmp_ring[1]);
                            
                            


                           
                           
                            //Updateing Public Board Array , Discs not accounted
                            std::vector<int> v1 = change_coordinates(1,x1.at(x1.size()-1),y1.at(y1.size()-1)); 
                            std::vector<int> v2 = change_coordinates(1,x2.at(x2.size()-1),y2.at(y2.size()-1));
                            std::string s_d  = "S ";
                            s_d.append(std::to_string(v1.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v1.at(1)));
                            s_d.append(" ");
                            s_d.append("M ");
                            s_d.append(std::to_string(v2.at(0)));
                            s_d.append(" ");

                            s_d.append(std::to_string(v2.at(1)));

                                                    update(0,s_d,1);

                            std::vector<int> v = find_five_consecutive(httep);

                            int child_score;

                            ht = ht+1;

                            if (ht%2==1)
                            {
                                 child_score =  1*evaluate_heuristic() ;
                            }
                            else if (ht%2==0)
                            {
                                 child_score =  -1*evaluate_heuristic() ;
                            }

                            reverse_update(0,1,2,3,4,s_d);
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

                                std::vector<int> v_prime = find_which_ring_to_remove(httep);
                                    
                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(1)));
                                rings_removed.push_back(v_prime.at(0));
                                rings_removed.push_back(v_prime.at(1));

                            }
                            update(0,s_d,1);
                            
                            
                            Node* child = new Node(root,child_score,s_d);
                            root->add_children(child);
                            root = child; 


                            flag1 = true; 
                            break;

                        }
                        else if (temp_board_array[15+i][15+next_y.at(next_y.size()-1)-i +next_x.at(next_x.size()-1) ] == 0  &&  flag==true)
                        {
                            // value of this change and place in its child
                           
                            std::cerr << ("5oh_yes14\n");

                            int r = current_ring.at(current_ring.size()-1);
                            current_ring.pop_back();
                            // if (r==4)
                            // {   
                            //     direction_of_play.pop_back();
                            //     next_x.pop_back();
                            //     next_y.pop_back();
                            //     reverse_update(0,x1.at(x1.size()-1),y1.at(y1.size()-1),x2.at(x2.size()-1),y2.at(y2.size()-1));
                            //     x1.pop_back();
                            //     x2.pop_back();
                            //     y1.pop_back();
                            //     y2.pop_back();
                                
                            //     ht--;
                            // }
                            // else
                            // {


                                x1.push_back(ring_x);
                                y1.push_back(ring_y);
                                x2.push_back(i);
                                y2.push_back(next_y.at(next_y.size()-1)-i +next_x.at(next_x.size()-1));

                                direction_of_play.pop_back();
                                direction_of_play.push_back(0);
                                current_ring.push_back(r+1);
                                int ring_x_pre  = tmp_ring[2*current_ring.at(current_ring.size()-1)];    // x and y co-ordinates of ring  w.r.t board
                                int ring_y_pre  = tmp_ring[2*current_ring.at(current_ring.size()-1)+1];

                                tmp_ring[2*r]    =  i ;    // x and y co-ordinates of ring  w.r.t board
                                tmp_ring[2*r+1]  =  (next_y.at(next_y.size()-1)-i +next_x.at(next_x.size()-1));

                                next_x.pop_back();
                                next_x.push_back(ring_x_pre-2);
                                next_y.pop_back();
                                next_y.push_back(ring_y_pre);

                                // x1.push_back(ring_x);
                                // y1.push_back(ring_y);
                                // x2.push_back(i);
                                // y2.push_back(next_y.at(next_y.size()-1)-i +next_x.at(next_x.size()-1));
                                

                                
                            // }



                            flag = false;



                            // ASSUME CORRECT


                            direction_of_play.push_back(0);
                            current_ring.push_back(0);

                            
                            // check condition if point is valid
                            next_x.push_back(tmp_tmp_ring[0]-2);
                            next_y.push_back(tmp_tmp_ring[1]);
                            
                            


                           
                           
                            //Updateing Public Board Array , Discs not accounted
                            std::vector<int> v1 = change_coordinates(1,x1.at(x1.size()-1),y1.at(y1.size()-1)); 
                            std::vector<int> v2 = change_coordinates(1,x2.at(x2.size()-1),y2.at(y2.size()-1));
                            std::string s_d  = "S ";
                            s_d.append(std::to_string(v1.at(0)));
                            s_d.append(" ");
                            s_d.append(std::to_string(v1.at(1)));
                            s_d.append(" ");
                            s_d.append("M ");
                            s_d.append(std::to_string(v2.at(0)));
                            s_d.append(" ");

                            s_d.append(std::to_string(v2.at(1)));

                                                    update(0,s_d,1);

                            std::vector<int> v = find_five_consecutive(httep);

                            ht = ht+1;
                            int child_score;

                            if (ht%2==1)
                            {
                                 child_score =  1*evaluate_heuristic() ;
                            }
                            else if (ht%2==0)
                            {
                                 child_score =  -1*evaluate_heuristic() ;
                            }
                            reverse_update(0,1,2,3,4,s_d);
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

                                std::vector<int> v_prime = find_which_ring_to_remove(httep);
                                    
                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(0)));

                                s_d.append(" ");
                                s_d.append(std::to_string(v_prime.at(1)));
                                rings_removed.push_back(v_prime.at(0));
                                rings_removed.push_back(v_prime.at(1));

                            }
                            update(0,s_d,1);
                            
                            Node* child = new Node(root,child_score,s_d);
                            root->add_children(child);
                            root = child; 


                            flag1 = true;
                            break;
                        }

                    }
                }
                if (flag1==false)
                {
                        direction_of_play.pop_back();
                        direction_of_play.push_back(0);
                        int curr_ring = current_ring.at(current_ring.size()-1);                        
                        current_ring.pop_back();
                        current_ring.push_back(curr_ring+1);       
                        int ring_x_pre  = tmp_ring[2*current_ring.at(current_ring.size()-1)];    // x and y co-ordinates of ring  w.r.t board
                        int ring_y_pre  = tmp_ring[2*current_ring.at(current_ring.size()-1)+1];                 
                        next_x.pop_back();
                        next_x.push_back(ring_x_pre-2);
                        next_y.pop_back();
                        next_y.push_back(ring_y_pre);
                        flag1 = true;
                }
                // print2();
                std::cerr << ("5oh_yes1\n");


            }

            else
            {
                std::cerr << "Error in tree";
            }
            if(httep%2==0)
            {
                for (int i = 0; i < 10; ++i)
                {
                    tmp_computers_ring[i] = tmp_ring[i];
                    tmp_my_ring[i] = tmp_tmp_ring[i];
                }
            }
            else
            {
                for (int i = 0; i < 10; ++i)
                {
                    tmp_my_ring[i] = tmp_ring[i];
                    tmp_computers_ring[i] = tmp_tmp_ring[i];

                }
            }
            // exit(0);
        }

        for (int i = 0; i < 5; ++i)
        {
            std::cerr<<"Temp_Comps_RIng:: "<<tmp_computers_ring[2*i]<<", "<<tmp_computers_ring[2*i+1]<<"\n"; 
        }
        std::cerr << "Children Size"<<temp_node->children.size();

        return temp_node;
    }


    std::vector<int> Board::find_which_ring_to_remove(int ht){
        std::vector<int> v;

        int min_heuristic = 100000;
        int to_remove = -1;
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < rings_removed.size(); j=j+2)
            {
                if (tmp_ring[2*i]==rings_removed.at(j) && tmp_ring[2*i+1]==rings_removed.at(j+1) ){
                    continue;
                }
            }
            int to_re_update = -3;
            int ring_x = tmp_ring[2*i];
            int ring_y = tmp_ring[2*i+1];
            to_re_update =  temp_board_array[ring_x][ring_y] ;
            temp_board_array[ring_x][ring_y] = 0 ;
            int score = evaluate_heuristic();
            if (to_re_update == 2){
                score = -score;
            }
            if (score<min_heuristic){
                min_heuristic = score;
                to_remove = i;
            }
            temp_board_array[ring_x][ring_y] = to_re_update;

        }


        v.push_back(tmp_ring[2*to_remove]);
        v.push_back(tmp_ring[2*to_remove+1]);

        std::vector<int> v1 = change_coordinates(1,v.at(0),v.at(1));
        v1.push_back(to_remove);
        return v1;
    }
   

    int Board::eval_five(int b1,int a1,int a2,int a3,int a4,int a5,int b2)
    {
  		int points[] = {b1,a1,a2,a3,a4,a5,b2};

        int result = 0;
        int weights[] = {0,1,2,5,13,30}; // 0 ,1,2,3,4,5 discs or rings or blanks
        
        int flag = -1;

        for (int i = 0; i < 7; ++i)
        {
            if ((points[i]== 2 || abs(points[i])==3)&& flag==-1 )
            {
                flag = i;
            }
            else if((points[i] ==2 || abs(points[i])==3)&& (not (i==6 && flag==0)))  // found 2nd ring // 
            {


                for (int j = flag; j < i; j++)  // not to be evaluated 
                {
                    points[j] = 2;
                }
            }

        }
        int disc=0;
        int ring=0;
        int blank=0;
        for (int i = 1; i < 6; ++i)
        {
            if (points[i]==-1) // comp disc
            {
                disc = disc+1;
            }
            else if (points[i]==-2) // comp ring
            {
                ring  = ring +1;
            }
            else{ blank = blank +1;} // blank
        }

        result = 7*weights[disc] +  3* weights[ring] + 1*weights[blank] ;





        return result;
    }

    int Board::evaluate_heuristic()
     {
     int result = 0;
        int b1 = -3 ; 
        int b2 = -3 ; 
        int max_X[] = {6,7,8,9,8,9,8,7,6};
        // Y = 0;
        for (int i = -4; i < 5; i++) // y axis
        {
            
            int y_m = max_X[i+4];
            for (int j = -y_m; j < y_m-8+1; j=j+2) // x-axis
            {   
                if (j== -y_m)
                {
                    b1 = -3;
                    b2 = temp_board_array[15+j+10][15+i];
                }
                else if (j== y_m - 8)
                {
                    b2 = -3;
                    b1 = temp_board_array[15+j-2][15+i];
                }
                else
                {
                    b1 = temp_board_array[15+j-2][15+i];
                    b2 = temp_board_array[15+j+10][15+i];   
                }
                result = result + eval_five(b1,temp_board_array[15+j][15+i],temp_board_array[15+j+2][15+i],temp_board_array[15+j+4][15+i],temp_board_array[15+j+6][15+i],temp_board_array[15+j+8][15+i],b2);
                result = result - eval_five(-b1,-temp_board_array[15+j][15+i],-temp_board_array[15+j+2][15+i],-temp_board_array[15+j+4][15+i],-temp_board_array[15+j+6][15+i],-temp_board_array[15+j+8][15+i],-b2);

            }
        }

        int y_cor[] = {-1,-2,-3,-4,-4,-5,-5,-5,-5} ; 
        int x_cor[] = {-9,-8,-7,-6,-4,-3,-1,1,3};
        int in_line[] = {2,3,4,5,4,5,4,3,2};
        int x = 0;
        int y = 0;
        int points_count = 0;
        
        // Y = X
        for (int i = 0; i < 9; ++i) 
        {
            x = x_cor[i];
            y = y_cor[i];
            while(true)
            {
                
                if (points_count==0)
                {
                    b1 = -3;
                    b2 = temp_board_array[15+x+5][15+y+5];
                }
                else if (points_count == in_line[i])
                {
                    b2 = -3;
                    b1 = temp_board_array[15+x-1][15+y-1];
                }
                else
                {
                    b1 = temp_board_array[15+x-1][15+y-1];
                    b2 = temp_board_array[15+x+5][15+y+5];
                }
                result = result + eval_five(b1,temp_board_array[15+x][15+y],temp_board_array[15+x+1][15+y+1],temp_board_array[15+x+2][15+y+2],temp_board_array[15+x+3][15+y+3],temp_board_array[15+x+4][15+y+4],b2);
                result = result - eval_five(-b1,-temp_board_array[15+x][15+y],-temp_board_array[15+x+1][15+y+1],-temp_board_array[15+x+2][15+y+2],-temp_board_array[15+x+3][15+y+3],-temp_board_array[15+x+4][15+y+4],-b2);
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
        int y_cord[] = {-5,-5,-5,-5,-4,-4,-3,-2,-1};
        int x_cord[] = {-3,-1,1,3,4,6,7,8,9};
        points_count=0;
        
        for (int i = 0; i < 9; ++i)
        {
            x = x_cord[i];
            y = y_cord[i];
            while(true)
            {
                
                if (points_count==0)
                {
                    b1 = -3;
                    b2 = temp_board_array[15+x-5][15+y+5];
                }
                else if (points_count == in_line[i])
                {
                    b2 = -3;
                    b1 = temp_board_array[15+x+1][15+y-1];
                }
                else
                {
                    b1 = temp_board_array[15+x+1][15+y-1];
                    b2 = temp_board_array[15+x-5][15+y+5];
                }
                result = result + eval_five(b1,temp_board_array[15+x][15+y],temp_board_array[15+x-1][15+y+1],temp_board_array[15+x-2][15+y+2],temp_board_array[15+x-3][15+y+3],temp_board_array[15+x-4][15+y+4],b2);
                result = result -eval_five(-b1,-temp_board_array[15+x][15+y],-temp_board_array[15+x-1][15+y+1],-temp_board_array[15+x-2][15+y+2],-temp_board_array[15+x-3][15+y+3],-temp_board_array[15+x-4][15+y+4],-b2);
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
        
        cerr<<"result:"<<result<<endl;
        // print2();
       return result;


    }

    bool Board::check_five(int val,int a1,int a2,int a3,int a4,int a5){
        
        int m;
        if (a1==val && a2==val && a3==val && a4==val && a5==val){
            // std::cin >> m;
            return true;
        }
        return false;
    }

    std::vector<int>  Board::find_five_consecutive(int ht)
     {
        
        // print2();
        int max_X[] = {6,7,8,9,8,9,8,7,6};
        

        std::vector<int> v;
            bool result=false;
        
        // Y = 0;
        for (int i = -4; i < 5; i++) // y axis
        {
            int y_m = max_X[i+4];
            for (int j = -y_m; j < y_m-8+1; j=j+2) // x-axis
            {   
                if (ht%2==0)
                {

                   result = check_five(-1,temp_board_array[15+j][15+i],temp_board_array[15+j+2][15+i],temp_board_array[15+j+4][15+i],temp_board_array[15+j+6][15+i],temp_board_array[15+j+8][15+i]);
                }
                else{
                    result = check_five(1,temp_board_array[15+j][15+i],temp_board_array[15+j+2][15+i],temp_board_array[15+j+4][15+i],temp_board_array[15+j+6][15+i],temp_board_array[15+j+8][15+i]);
                }
                if (result==true){

                    std::vector<int> v1 = change_coordinates(1,j,i);
                    std::vector<int> v2 = change_coordinates(1,j+8,i);
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);
                    return v;
                    break;
                }
            }
        }

        int y_cor[] = {-1,-2,-3,-4,-4,-5,-5,-5,-5} ; 
        int x_cor[] = {-9,-8,-7,-6,-4,-3,-1,1,3};
        int in_line[] = {2,3,4,5,4,5,4,3,2};
        int x = 0;
        int y = 0;
        int points_count = 0;
        
        // Y = Xs
        for (int i = 0; i < 9; ++i) 
        {
            x = x_cor[i];
            y = y_cor[i];
            while(true)
            {
                if(ht%2==0)
                {

                    result =  check_five(-1,temp_board_array[15+x][15+y],temp_board_array[15+x+1][15+y+1],temp_board_array[15+x+2][15+y+2],temp_board_array[15+x+3][15+y+3],temp_board_array[15+x+4][15+y+4]);
                }
                else
                {
                    result =  check_five(1,temp_board_array[15+x][15+y],temp_board_array[15+x+1][15+y+1],temp_board_array[15+x+2][15+y+2],temp_board_array[15+x+3][15+y+3],temp_board_array[15+x+4][15+y+4]);
                }
                if( result==true){

                     std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x+4,y+4);
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
        int y_cord[] = {-5,-5,-5,-5,-4,-4,-3,-2,-1};
        int x_cord[] = {-3,-1,1,3,4,6,7,8,9};
        points_count=0;
        
        for (int i = 0; i < 9; ++i)
        {
            x = x_cord[i];
            y = y_cord[i];
            while(true)
            {
                
                if(x==1 && y==-1) {std::cerr << "its checked"; };
                if (ht%2==0 )
                {
                   
                    result = check_five(-1,temp_board_array[15+x][15+y],temp_board_array[15+x-1][15+y+1],temp_board_array[15+x-2][15+y+2],temp_board_array[15+x-3][15+y+3],temp_board_array[15+x-4][15+y+4]);
                }
                else
                {
                    result = check_five(1,temp_board_array[15+x][15+y],temp_board_array[15+x-1][15+y+1],temp_board_array[15+x-2][15+y+2],temp_board_array[15+x-3][15+y+3],temp_board_array[15+x-4][15+y+4]);
                }
                if( result==true){

                     std::vector<int> v1 = change_coordinates(1,x,y);
                    std::vector<int> v2 = change_coordinates(1,x-4,y+4);
                    v.push_back(v1.at(0));//(j);
                    v.push_back(v1.at(1));//(i);
                    v.push_back(v2.at(0));//(j+8);
                    v.push_back(v2.at(1));//(i);

                    // v.push_back(x);
                    // v.push_back(y);
                    // v.push_back(x-4);
                    // v.push_back(y+4);
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
       // return result;


    }

    
    Node* Board::max_val(Node* node)
    {
        // cerr<<"no of child:"<<node->children.size()<<endl;
    	if (node->isTerminal())
    	{
    		return node;//->utility();
    	}
    	std::vector<Node*>  childs;
    	childs = node->children;
    	Node* child = new Node(NULL,0,"S 1 2 M 3 4");
        Node* max_child = new Node(NULL,0,"S 1 2 M 3 4");
    	max_child->score = -10000000; /// infinity
    	for (int i = 0; i < childs.size(); ++i)
    	{

            Node* child_at_i = childs.at(i);
    		child = min_val(childs.at(i));//,node->alpha,node->beeta);
    		child_at_i->score = child->score;
            // node->alpha = max(node->alpha,child->utility()); 
    		if (child_at_i->utility()>max_child->utility())
    		{
    			max_child->score = child_at_i->utility();
                max_child->move = child_at_i->move; 
    		}
	    	
	    	// if (node->alpha >= node->beeta)
	    	// {
	    	// 	return child;
	    	// }
	    }

        std::cerr << "Move & score  of mac_C " << max_child->move << " "<< max_child->score << endl ; 
    	return max_child;
    }

     std::vector<int>  Board::find_five_consecutive_board_array(int ht)
     {
        
         
        int max_X[] = {6,7,8,9,8,9,8,7,6};
        

        std::vector<int> v;
            bool result=false;
        
        // Y = 0;
        for (int i = -4; i < 5; i++) // y axis
        {
            int y_m = max_X[i+4];
            for (int j = -y_m; j < y_m-8+1; j=j+2) // x-axis
            {   
                if (ht%2==0)
                {

                   result = check_five(-1,board_array[15+j][15+i],board_array[15+j+2][15+i],board_array[15+j+4][15+i],board_array[15+j+6][15+i],board_array[15+j+8][15+i]);
                }
                else{
                    result = check_five(1,board_array[15+j][15+i],board_array[15+j+2][15+i],board_array[15+j+4][15+i],board_array[15+j+6][15+i],board_array[15+j+8][15+i]);
                }
                if (result==true){

                    v.push_back(j);
                    v.push_back(i);
                    v.push_back(j+8);
                    v.push_back(i);
                    return v;
                    break;
                }
            }
        }

        int y_cor[] = {-1,-2,-3,-4,-4,-5,-5,-5,-5} ; 
        int x_cor[] = {-9,-8,-7,-6,-4,-3,-1,1,3};
        int in_line[] = {2,3,4,5,4,5,4,3,2};
        int x = 0;
        int y = 0;
        int points_count = 0;
        
        // Y = Xs
        for (int i = 0; i < 9; ++i) 
        {
            x = x_cor[i];
            y = y_cor[i];
            while(true)
            {
                if(ht%2==0)
                {

                    result =  check_five(-1,board_array[15+x][15+y],board_array[15+x+1][15+y+1],board_array[15+x+2][15+y+2],board_array[15+x+3][15+y+3],board_array[15+x+4][15+y+4]);
                }
                else
                {
                    result =  check_five(1,board_array[15+x][15+y],board_array[15+x+1][15+y+1],board_array[15+x+2][15+y+2],board_array[15+x+3][15+y+3],board_array[15+x+4][15+y+4]);
                }
                if( result==true){
                    v.push_back(x);
                    v.push_back(y);
                    v.push_back(x+4);
                    v.push_back(y+4);
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
        int y_cord[] = {-5,-5,-5,-5,-4,-4,-3,-2,-1};
        int x_cord[] = {-3,-1,1,3,4,6,7,8,9};
        points_count=0;
        
        for (int i = 0; i < 9; ++i)
        {
            x = x_cord[i];
            y = y_cord[i];
            while(true)
            {
                
                if(x==1 && y==-1) {std::cerr << "its checked" ;
                    std::cerr << board_array[15+x][15+y]<<","<<board_array[15+x-1][15+y+1]<<","<<board_array[15+x-2][15+y+2]<<","<<board_array[15+x-3][15+y+3]<<","<<board_array[15+x-4][15+y+4] << endl;};
                if (ht%2==0 )
                {
                   
                    result = check_five(-1,board_array[15+x][15+y],board_array[15+x-1][15+y+1],board_array[15+x-2][15+y+2],board_array[15+x-3][15+y+3],board_array[15+x-4][15+y+4]);
                }
                else
                {
                    result = check_five(1,board_array[15+x][15+y],board_array[15+x-1][15+y+1],board_array[15+x-2][15+y+2],board_array[15+x-3][15+y+3],board_array[15+x-4][15+y+4]);
                }
                if( result==true){
                    v.push_back(x);
                    v.push_back(y);
                    v.push_back(x-4);
                    v.push_back(y+4);
                    std::cerr <<  v.at(0)<<v.at(1)<<v.at(2)<<v.at(3);
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
       // return result;


    }


    Node* Board::min_val( Node* node )
    {
    	// cerr<<"no of child:"<<node->children.size()<<endl;

        if (node->isTerminal())
    	{
    		return node;//node->utility();
    	}
    	std::vector<Node*>  childs;
    	childs = node->children;
        // tmp = childs.at(0);
    	Node* child = new Node(NULL,0,"S 1 2 M 3 4");
    	Node* min_child = new Node(NULL,0,"S 1 2 M 3 4");
        min_child->score = 10000000; /// infinity
    	for (int i = 0; i < childs.size(); ++i)
    	{

            Node* child_at_i = childs.at(i);
            child = max_val(childs.at(i));//,node->alpha,node->beeta);

            child_at_i->score = child->score;

    		// node->beeta = min(node->beeta,child->utility()); 
    	
	    	if (child_at_i->utility()<min_child->utility())
    		{
    			min_child->score = child_at_i->utility();
                                min_child->move = child_at_i->move; 

    		}
	    	// if (node->alpha >= node->beeta)
	    	// {
	    	// 	return child;
	    	// }
	    }
        std::cerr << "Move & score  of mic_C " << min_child->move << " "<< min_child->score << endl ; 

	    return min_child;

    }
