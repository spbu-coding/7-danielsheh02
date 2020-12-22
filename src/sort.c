#include "sort.h"
void swap(char **first_str, char **second_str) {
    char *tmp = *second_str;
    *second_str = *first_str;
    *first_str = tmp;
}

int partition_quick(char **array_of_strings, int low, int high) {
    char *pivot = array_of_strings[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(array_of_strings[j], pivot) > 0) {
            i++;
            swap(&array_of_strings[i], &array_of_strings[j]);
        }
    }
    swap(&array_of_strings[i + 1], &array_of_strings[high]);
    return (i + 1);
}

void quickSort(char **array_of_strings, int low, int high) {
    if (low < high) {
        int pi = partition_quick(array_of_strings, low, high);
        quickSort(array_of_strings, low, pi - 1);
        quickSort(array_of_strings, pi + 1, high);
    }
}

void quick(char **array_of_strings, int number_of_lines) {
    quickSort(array_of_strings, 0, (int) number_of_lines - 1);
}
