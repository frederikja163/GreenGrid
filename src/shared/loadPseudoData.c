#include "loadPseudoData.h"

#include <stdio.h>
#include <stdlib.h>

int loadData(const char *input_file, const char *output_file) {
    FILE *ifp, *ofp;

    if ((ifp = fopen(input_file, "r")) == NULL) {
        printf("Error : Unable to open %s for reading\n", input_file);
        exit(EXIT_FAILURE);
    }
    if ((ofp = fopen(output_file, "w+")) == NULL) {
        printf("Error : Unable to open %s for reading\n", output_file);
        exit(EXIT_FAILURE);
    }

    copyData(ifp, ofp);

    fclose(ifp);
    fclose(ofp);
}

void copyData(FILE *ifp, FILE *ofp) {
    int c;
    while ((c = fgetc(ifp)) != EOF) {
        fputc(c, ofp);
    }
}