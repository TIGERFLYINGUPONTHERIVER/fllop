CUR_DAR = ./
MAIN_DAR = 

a.out : main.o piece.o  
	g++ -o a.out main.o piece.o

main.o : main.cpp 
	g++ -c main.cpp -std=c++11 

piece.o : piece.cpp
	g++ -c piece.cpp -std=c++11 -lmysqlclient
