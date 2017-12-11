#Naveh Marchoom 312275746 Ex4
a.out: main.o Server.o 
	g++ main.o Server.o
	
Server.o : src/Server.cpp include/Server.h include/Point.h
	g++ -c src/Server.cpp

main.o: main.cpp include/Server.h
	g++ -c main.cpp
