#Naveh Marchoom 312275746 Ex3
a.out: main.o Block.o Board.o Game.o Point.o Ai.o
	g++ main.o Block.o Board.o Game.o Point.o Ai.o
	
Block.o: src/Block.cpp include/Block.h
	g++ -c src/Block.cpp

Board.o: src/Board.cpp include/Board.h include/Block.h
	g++ -c src/Board.cpp

Game.o: src/Game.cpp include/Game.h include/Board.h include/Point.h
	g++ -c src/Game.cpp

Point.o: src/Point.cpp include/Point.h
	g++ -c src/Point.cpp

Ai.o : src/Ai.cpp include/Ai.h include/Game.h
	g++ -c src/Ai.cpp

main.o: main.cpp include/Game.h
	g++ -c main.cpp
