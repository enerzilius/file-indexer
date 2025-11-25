#include <iostream>
#include "src/CommandLineInterface.h"

int main(int argc, char** argv) {
    // Instancia a CLI e dá o start assim que ./main é executadi
    CLI cli;

    cli.start();

    return 0;
}