all: main.cpp ./src/CommandLineInterface.cpp 
	g++ -o main main.cpp ./src/CommandLineInterface.cpp -I ./src