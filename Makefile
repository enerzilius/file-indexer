all: main.cpp ./src/CommandLineInterface.cpp ./src/TextProcessor.cpp ./utils/utils.cpp 
	g++ -o main main.cpp ./src/CommandLineInterface.cpp ./src/TextProcessor.cpp ./utils/utils.cpp