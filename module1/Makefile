calc: main.o add.o divide.o print.o
	g++ main.o add.o divide.o print.o -o calc
main.o: main.cpp
	g++ -g -Wall -c main.cpp -o main.o
add.o: add.cpp
	g++ -g -Wall -c add.cpp -o add.o
divide.o: divide.cpp
	g++ -g -Wall -c divide.cpp -o divide.o
print.o: print.cpp
	g++ -g -Wall -c print.cpp -o print.o

clean:
	rm main.o add.o divide.o print.o calc
