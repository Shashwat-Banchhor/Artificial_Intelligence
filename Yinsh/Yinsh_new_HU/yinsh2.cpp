#include <stdio.h>
#include <cstdlib>
#include <iostream>
// #include <vector>
#include "board_config.h"
#include "node.h"
#include <ctime>
#include <ratio>
#include <chrono>

// using namespace std; 


int main(int argc , char** argv)

// test_main_function
// {
//     Board board(5,5,5,3);
//     int temp = 1;

//     board.update(-1,"P 4 0",temp);
//     // board.print2();
    
//     board.update(1,"P 0 0",temp);

//     board.update(-1,"P 4 1",temp);

//     board.update(1,"P 3 0",temp);


//     board.update(-1,"P 4 2",temp);
//     board.update(1,"P 3 1",temp);


//     board.update(-1,"P 4 3",temp);
//     board.update(1,"P 3 17",temp);


//     board.update(-1,"P 4 4",temp); 
//     board.update(1,"P 3 16",temp);
//     // std::string move = board.play();
//     board.update(1,"S 3 0 M 2 0",temp);
//     board.update(-1,"S 4 4 M 5 6",temp);

//     board.update(1,"S 3 17 M 2 11",temp);
//     board.update(-1,"S 4 0 M 5 29",temp);
    
//     board.update(1,"S 3 16 M 2 10",temp);
//     board.update(-1,"S 4 1 M 3 ",temp);
    
//     board.print2();
//     //board.reverse_update(0,1,2,3,4,"S 4 0 M 3 0");
//     //board.print2();
//     board.update(1,"S 0 0 M 1 2",1);
//     board.print2();
//     // exit(0);
//     board.update(-1,"S 3 0 M 3 1",1);
//     board.print2();
//     board.reverse_update(0,1,2,3,4,"S 3 0 M 3 1");
//     board.print2();

//     // move = board.play();
//     // Node* root = board.tree();
//     // std::string move = board.tree();
//     // std::cerr << "\nMove this: " << move<<"\n";
//      // std::cerr << "Size of children: "<<root->children.size()<<endl;
//      //    for (int i = 0; i < root->children.size(); ++i)
//      //    {
//      //        Node* child = root->children.at(i);
//      //        std::cerr <<  i << " moved ->"<< child->get_move() <<endl; 
//      //    }

// }

// main_function
{

		
	
	time_t start_time = time(0);
	
	int n;
	int player_id, board_size, time_limit, number_of_rings_to_remove,number_of_rings_to_place;
    std::string move;
    std::string trash;


    // Get input from server about game specifications
    std::cin >> player_id ;
    std::cin >> board_size;
    std::cin >> time_limit;
    getline(cin,trash);
    
    board_size = 5;
    number_of_rings_to_place = 5;//M;
    number_of_rings_to_remove = 5;//K;

    Board board(board_size,5,5,3);


    if(player_id == 2) {
        // Get other player's move
        getline(std::cin,move); 
        
        while(true) {
            std::cerr << "Hai i am pl2";

			board.update(1,move,0);
			move = board.play(board_size,number_of_rings_to_remove);

			std::cout << move.append("\n"); 
			std::cerr << "done";
  

              time_t end_time = time(0);

 //  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

 //  cerr << "printing out 1000 stars...\n";
 // for (int i = 0; i < 1000; ++i)
 // {
 //     cout<< "Hai Shashwat\n"; }

 //  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

 //  std::chrono::duration<double, std::milli> time_span = t2 - t1;

 //  cerr << "It took me " << time_span.count() << " milliseconds.";
 //  cerr << endl;

            cout<<"time:"<<end_time -start_time<<endl;
        	getline(cin,move); 
            
        }
    }  

    else if(player_id == 1) {
       
        while(true) {
            std::cerr << "Hai i am pl1";

			move = board.play(board_size,number_of_rings_to_remove);
			std::cout << move.append("\n");
			std::cerr << "done";
            time_t end_time = time(0);
            cout<<"time:"<<end_time -start_time<<endl;
        	getline(std::cin,move);
			std::cerr << "done2";

        	board.update(1,move,0);
            
        }
    }

	
    time_t end_time = time(0);


	return 0;

}
