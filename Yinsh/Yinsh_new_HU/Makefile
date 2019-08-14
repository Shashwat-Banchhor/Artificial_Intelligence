all: exec


exec: yinsh2.o board_config_updated.o node.o 
	g++  yinsh2.o board_config_updated.o node.o -o custom_player 


yinsh2.o: yinsh2.cpp
	g++ -c yinsh2.cpp 

board_config_updated.o : board_config_updated.cpp
	g++ -c board_config_updated.cpp 

node.o : node.cpp
	g++ -c node.cpp

