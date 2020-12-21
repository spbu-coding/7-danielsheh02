#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  MAX_INPUT_STRING_SIZE 1000
#define MAX_STRING_PRINT 100

void free_of_array(char **array_of_strings, int number_of_lines);
void quick(char **array_of_strings, int number_of_lines);
char **reading_file(char *file_name, int *number_of_lines);

#endif
