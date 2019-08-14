#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "board_config.h"
#include "node.h"
#include <ctime>
using namespace std; 




/// CHANGE IN 
 
 // 1496 - 1497  tmp_tmp and curr.pop inverted


int main(int argc , char** argv)
{

		
	
	Board board(5,5,5,3);
	time_t now = time(0);

	int tim_limit = now + 120;
	
	int n;
	int player_id, board_size, time_limit;
    // string move;
    // Get input from server about game specifications
    cin >> player_id >> board_size >> time_limit;

    time_t timer = time(0);
    timer = timer + time_limit ; 


   //  if(player_id == 2) {
   //      // Get other player's move
   //      cin>>move; 
        
   //      while(true) {
   //          cout<<"P 1 0"<<endl;
			// board.update(1,move,0);
   //          cin>>move;
   //      }
   //  }   
   //  else if(player_id == 1) {
   //      while(true) {
   //          cout<<"P 0 0"<<endl;
   //          cin>>move; 
   //      }
   //  }

 //    move = "S 2 0 M 3 0";	
	// board.update(1,move,0);
	// board.print();
	// std::cin >> n;
	// move = board.play();
	// std::cout<< move;
	// board.print();
	// std::cin >> n;


	// Node* rootptr =  new Node(NULL,3,"");
	// Node* temp = rootptr;
	// Node* child = new Node(rootptr,9,"");
	// Node* child2 = new Node(child,9,"");  

	// rootptr->add_children(child);
	// rootptr = child;
	// rootptr->score = 7;
	// rootptr = rootptr->get_parent();
	// std::cout << temp->children.at(0)->score << "\n" << endl ; 
	// // std::cout << rootptr->score << "\n" << endl ;

	
	// exit(0);
	

	//------- NEW INPUT ---------
// while(true)
// {
// 	string move;
// 	getline(cin,move);
// 	board.update(1,move,0);
// 	move = board.play();
// 	std::cout << move ; 
// }

	int total_moves = 0;

	std::string move;
	move = "P 2 6";
	board.update(1,move,0);
	
	board.print();

	move = "P 3 5";
	board.update(-1,move,0);
	board.print();

	move = "P 3 4";
	board.update(1,move,0);
	
	board.print();

	move = "P 4 4";
	board.update(-1,move,0);
	board.print();
	move = "P 4 0";
	board.update(1,move,0);
	
	board.print();

	move = "P 4 8";
	board.update(-1,move,0);
	board.print();
	move = "P 4 9";
	board.update(1,move,0);
	
	board.print();

	move = "P 3 7";
	board.update(-1,move,0);
	board.print();
	move = "P 2 8";
	board.update(1,move,0);
	
	board.print();

	move = "P 1 4";
	board.update(-1,move,0);
	board.print();
	
	std::cout<< move;
	// int m;

	// move = "S 1 2 M 3 1";
	// std::cout<< "\nmy_move\n";
	// std::cout<< move;

	// board.update(1,move,0);
	// board.print();
	// cin >> m;

	// move = "S 1 2 M 3 1";
	// std::cout<< "\nmy_move\n";
	// std::cout<< move;

	// board.update(1,move,0);
	// board.print();
	// cin >> m; 




	// int m;
	// while(true)
	// {
	// 	getline(cin,move);
	// 	// std::cin >> move;
	// 	board.update(1,move,0);
	// 	board.print();
	
	// 	printf("\n");
	// 	printf("Enter an int to continue :) \n");
	// 	std::cin >> m;
	// 	move = board.play();
	// 	std::cout<< move << "\n";
	// 	board.print();
	// 	printf("Enter your Move :::: \n");
	// 	getline(cin,move);
	// 	// std::cin >> move;
	// 	board.update(1,move,0);
	// 	board.print();
	
	// 	printf("\n");
	// 	printf("Enter an int to continue :) \n");
	// 	std::cin >> m;
	// 	move = board.play();
	// 	std::cout<< move << "\n";
	// 	board.print();
	// 	printf("2nter your Move :::: \n");


	// }
	int m;

	move = "S 2 8 M 2 7";
	board.update(1,move,0);

	move = "S 1 4 M 0 0";
	board.update(-1,move,0);

	move = "S 2 6 M 2 5";
	board.update(1,move,0);

	move = "S 0 0 M 1 1";
	board.update(-1,move,0);

	move = "S 2 5 M 2 4";
	board.update(1,move,0);

	move = "S 1 1 M 2 2";
	board.update(-1,move,0);

	move = "S 4 9 M 4 10";
	board.update(1,move,0);
	
	move = "S 2 2 M 3 3";
	board.update(-1,move,0);
	
	move = "S 4 0 M 4 2";
	board.update(1,move,0);

	board.print();
	std::cin>>  m;
board.play();
board.print();


	exit(0);



	std::cout<< "\nmy_move\n";
	std::cout<< move;
	
	board.update(1,move,0);
	board.print();
	printf("\n");
	std::cin >> m;     // 1st break
	
	move = board.play();
	// board.update(-1,move,0);
	std::cout<< move << "\n";

	board.print();
	std::cin >> m;
	
	move = "S 1 5 M 2 10";
	board.update(1,move,0);
	board.print();
	// int n;
	std::cin >> n;

	move = board.play();
	// board.update(-1,move,0);
	std::cout<< move;
	board.print();
	std::cin >> n;

	move = "S 1 3 M 3 11";
	board.update(1,move,0);
	board.print();
	// int n;
	std::cin >> n;

	move = board.play();
	board.update(-1,move,0);
	std::cout<< move;
	board.print();
	std::cin >> n;


	printf("Game End\n");


	exit(0);


	move = "S 1 0 M 2 0";	
	board.update(1,move,0);
	board.print();
	std::cin >> n;
	move = board.play();
	std::cout<< move;
	board.print();
	std::cin >> n;
	move = "S 2 0 M 3 0";	
	board.update(1,move,0);
	board.print();
	std::cin >> n;
	move = board.play();
	std::cout<< move;
	board.print();
	std::cin >> n;
	
			move = "S 1 2 M 3 4";	
	board.update(1,move,0);
	board.print();
	std::cin >> n;
	move = board.play();

	std::cout<< move;
	board.print();
	std::cin >> n;

			
		

	exit(0);
//  	while(true)
//  	{ 
// 	 	total_moves++;
// std::cout << total_moves;
// 		if (total_moves%2==1)
// 		{ 	
// 		 	cout << "Enter your move : ";
// 		    getline (cin, move);
// 			board.update(1,move,0);
// 			board.print();
// 			std::cout << "yup";
// 		}
// 		if (total_moves==2)
// 		{	
// 			move = "P 2 2";
// 			board.update(-1,move,0);
// 			board.print();
// 		}
// 		else if (total_moves==4)
// 		{	
// 			move = "P 2 3";
// 			board.update(-1,move,0);
// 			board.print();

// 		}
// 		else if (total_moves==6)
// 		{	
// 			move = "P 2 4";
// 			board.update(-1,move,0);
// 			board.print();
// 		}
// 		else if (total_moves==8)
// 		{	
// 			move = "P 2 5";
// 			board.update(-1,move,0);
// 			board.print();
// 		}
// 		else if (total_moves==10)
// 		{	
// 			move = "P 2 6";
// 			board.update(-1,move,0);
// 			board.print();
// 		}
// 		else if (total_moves%2==0)
// 		{
// 			move = board.play();
// 			board.update(-1,move,0);
// 			board.print();
// 		}
// 	}
// 	exit(0);
	string s ;
	
	
//  -----------  PREVIOUS INPUT ------------------------
	// std::cin >> s;

	// while(s.compare("-1")!= 0)
	// {
	// 	// board.update(move);
	// 	// board.play();
	// 	// board.print();
	// 	move = "";
	// 	move.append(s);
	// 	if(s.compare("S")==0){
	// 		cerr << "case 1" ; 
	// 		string t11,t12,t21,t22,t;
	// 		std::cin>>t11;
	// 		std::cin>>t12;
	// 		std::cin>>t;
	// 		std::cin>>t21;
	// 		std::cin>>t22;
	// 		std::cin>>s;
	// 		move.append(t11);
	// 		move.append(t12);
	// 		move.append(t);
	// 		move.append(t21);
	// 		move.append(t22);
	// 		if(s.compare("RS")==0){
	// 		cerr << "case 2" ; 
	// 		string t31,t32,t41,t42,t51,t52;
	// 		std::cin>>t31;
	// 		std::cin>>t32;
	// 		std::cin>>t;
	// 		std::cin>>t41;
	// 		std::cin>>t42;
	// 		std::cin>>t;
	// 		std::cin>>t51;
	// 		std::cin>>t52;
	// 		std::cin>>s;
	// 		move.append(t31);
	// 		move.append(t32);
	// 		move.append(t41);
	// 		move.append(t42);
	// 		move.append(t51);
	// 		move.append(t52);
				
	// 		}
	// 		else{
	// 			cerr << "case 3" ; ;
	// 		}
				
	// 	}
		
	// 	else if(s.compare("P")==0){
	// 		// cerr << "case 4" ; 
	// 		string t61,t62;
	// 		std::cin>>t61;
	// 		std::cin>>t62;
	// 		std::cin>>s;
	// 		move.append(t61);
	// 		move.append(t62);

	// 	}
	// 	std::cout << move;
	// 	board.update(1,move);
	// 	board.print();

	// }

	return 0;

}
