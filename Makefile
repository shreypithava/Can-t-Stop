
output: main.o game.o board.o column.o dice.o enums.o exception.o player.o tools.o score.o
	g++ main.o game.o board.o column.o dice.o enums.o exception.o player.o tools.o score.o -o output


main.o: main.cpp
	g++ -c main.cpp

game.o: game.cpp game.hpp
	g++ -c game.cpp

board.o: board.cpp board.hpp
	g++ -c board.cpp

column.o: column.cpp column.hpp
	g++ -c column.cpp

dice.o: dice.cpp dice.hpp
	g++ -c dice.cpp

enums.o: enums.cpp enums.hpp
	g++ -c enums.cpp

exception.o: exception.cpp exception.hpp
	g++ -c exception.cpp

player.o: player.cpp player.hpp
	g++ -c player.cpp

tools.o: tools.cpp tools.hpp
	g++ -c tools.cpp

score.o: score.cpp score.hpp
	g++ -c score.cpp

clean:
	rm *.o output
