// #include <stdio.h>
#include <cstdlib>
#include <iostream>
// #include <vector>
#include "board_config.h"
#include "node.h"
#include <ctime>
// using namespace std; 


int main(int argc , char** argv)
{

		
	
	Board board(5,5,5,3);
	time_t start_time = time(0);
	
	int n;
	int player_id, board_size, time_limit;
    std::string move;
    std::string trash;


    // Get input from server about game specifications
    std::cin >> player_id ;
    std::cin >> board_size;
    std::cin >> time_limit;
    getline(cin,trash);
    


    if(player_id == 2) {
        // Get other player's move
        getline(std::cin,move); 
        
        while(true) {

			board.update(1,move,0);
			move = board.play();

			std::cout << move; 
			std::cerr << "done";
        	getline(cin,move); 
            
        }
    }  

    else if(player_id == 1) {
       
        while(true) {

			move = board.play();
			std::cout << move;
			std::cerr << "done";

        	getline(std::cin,move);
			std::cerr << "done2";

        	board.update(1,move,0);
            
        }
    }

	


	return 0;

}
