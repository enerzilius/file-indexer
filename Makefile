all: main.cpp ./src/CommandLineInterface.cpp ./utils/utils.cpp
	g++ -o main main.cpp ./src/CommandLineInterface.cpp ./utils/utils.cpp