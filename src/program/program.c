#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loadPseudoData.h"

int main(int argc, char **argv) {
    char *contents = read_file("src/shared/input.txt");

    write_file("src/shared/output_file.txt", contents);

    free(contents);

    return EXIT_SUCCESS;
}