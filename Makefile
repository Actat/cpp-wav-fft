a.out: main.o wav.o
	g++ -o a.out main.o wav.o

main.o: main.cpp
	g++ -c main.cpp

wav.o: wav.cpp
	g++ -c wav.cpp
