#include "sort.h"
void free_of_array(char **array_of_strings, int number_of_lines) {
    for (int i = 0; i < number_of_lines; i++) {
        free(array_of_strings[i]);
    }
    free(array_of_strings);
}

int main(int argc, char **argv) {
    char **array_of_strings;
    int number_of_lines = 0;
    if (argc != 2) {
        fprintf(stdout,
                "Use %s <input file>.txt\n", argv[0]);
        return -1;
    }
    if (!(array_of_strings = reading_file(argv[1], &number_of_lines))) {
        return -1;
    }
    quick(array_of_strings, number_of_lines);
    for (int i = 0; i < number_of_lines && i < MAX_STRING_PRINT; i++) {
        fprintf(stdout, "%s", array_of_strings[i]);
    }
    free_of_array(array_of_strings, number_of_lines);
    return 0;
}
