all: main.cpp ./src/CommandLineInterface.cpp ./src/TextProcessor.cpp
	g++ -o main main.cpp ./src/CommandLineInterface.cpp ./src/TextProcessor.cpp 