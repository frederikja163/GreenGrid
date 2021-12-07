#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filePath);
void write_file(const char *filePath, const char *fileContents);

#endif