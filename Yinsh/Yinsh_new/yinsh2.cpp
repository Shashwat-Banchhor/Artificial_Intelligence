#include <stdio.h>
#include <cstdlib>
#include <iostream>
// #include <vector>
#include "board_config.h"
#include "node.h"
#include <ctime>
// using namespace std; 


int main(int argc , char** argv)


// {
//     Board board(5,5,5,3);
//     std::
//     // board.update(-1,"P 4 0",0);
//     board.play();
//     board.update(1,"P 0 0",0);

//     // board.update(-1,"P 4 1",0);

//     board.update(1,"P 1 0",0);


//     board.update(-1,"P 4 2",0);
//     board.update(1,"P 2 0",0);


//     board.update(-1,"P 4 3",0);
//     board.update(1,"P 1 2",0);


//     board.update(-1,"P 4 4",0); 
//     board.update(1,"P 2 2",0);

//     board.print();

//     // move = board.play();
//     Node* root = board.tree();
//     // std::string move = board.tree();
//     // std::cerr << "\nMove this: " << move<<"\n";
//      std::cerr << "Size of children: "<<root->children.size()<<endl;
//         for (int i = 0; i < root->children.size(); ++i)
//         {
//             Node* child = root->children.at(i);
//             std::cerr <<  i << " moved ->"<< child->get_move() <<endl; 
//         }

// }
{

		
	
	time_t start_time = time(0);
	
	int n;
	int player_id, board_size, time_limit,number_of_rings_to_remove,number_of_rings_to_place;
    std::string move;
    std::string trash;


    // Get input from server about game specifications
    std::cin >> player_id ;
    std::cin >> board_size;
    std::cin >> time_limit;
    std::cin >> number_of_rings_to_remove;
    //std::cerr << board_size << time_limit;
    Board board(board_size,board_size,number_of_rings_to_remove,3);

    getline(cin,trash);
    
    //board_size = 5;
//number_of_rings_to_remove = 5;

    if(player_id == 2) {
        // Get other player's move
        getline(std::cin,move); 
        
        while(true) {
            std::cerr << "Hai i am pl2";

			board.update(1,move,0);
			move = board.play(board_size,number_of_rings_to_remove);

			std::cout << move.append("\n"); 
			std::cerr << "done Time: " << time(0)- start_time;
        	getline(cin,move); 

            
        }
    }  

    else if(player_id == 1) {
       
        while(true) {
            std::cerr << "Hai i am pl1";

			move = board.play(board_size,number_of_rings_to_remove);
			std::cout << move.append("\n");
			std::cerr << "done Time: " << time(0)- start_time;

        	getline(std::cin,move);
			std::cerr << "done2";

        	board.update(1,move,0);
            
        }
    }

	


	return 0;

}
