#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loadPseudoData.h"

int main(int argc, char **argv) {
    char *input = "src/shared/input.txt";
    char *output = "src/shared/output.txt";

    loadData(input, output);

    return EXIT_SUCCESS;
}