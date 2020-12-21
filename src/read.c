#include "sort.h"
char *remove_punctuation_marks(const char *buffer, int file_size, int *number_of_lines, int *count_of_recorded_chars) {
    int count_of_chars = 0, i;
    char *buffer2 = calloc(file_size + 2, sizeof(char));
    if (!buffer2) {
        fprintf(stdout, "Can not create buffer\n");
        return NULL;
    }
    for (i = 0; count_of_chars < file_size;) {
        if (buffer[count_of_chars] != '.' && buffer[count_of_chars] != ',' &&
            buffer[count_of_chars] != ';' && buffer[count_of_chars] != ':' &&
            buffer[count_of_chars] != '!' &&
            buffer[count_of_chars] != '?') {
            if (buffer[count_of_chars] == '\n') {
                *number_of_lines = *number_of_lines + 1;
            }
            buffer2[i] = buffer[count_of_chars];
            *count_of_recorded_chars = *count_of_recorded_chars + 1;
            count_of_chars++;
            i++;
        } else {
            count_of_chars++;
        }
    }
    if (buffer2[i - 1] != '\n') {
        buffer2[i] = '\r';
        buffer2[i + 1] = '\n';
        *count_of_recorded_chars = *count_of_recorded_chars + 2;
        *number_of_lines = *number_of_lines + 1;
    }
    return buffer2;
}

char **fill_array_of_strings(const char *buffer2, int number_of_lines, int count_of_recorded_chars) {
    int count_of_chars = 0, count_of_chars_in_one_string;
    char **array_of_strings = calloc(number_of_lines, sizeof(char *));
    if (!array_of_strings) {
        return NULL;
    }
    for (int i = 0; i < number_of_lines; i++) {
        array_of_strings[i] = calloc(MAX_INPUT_STRING_SIZE, sizeof(char));
        if (!array_of_strings[i]) {
            free_of_array(array_of_strings, i);
            return NULL;
        }
        count_of_chars_in_one_string = 0;
        while (count_of_chars < count_of_recorded_chars) {
            array_of_strings[i][count_of_chars_in_one_string] = buffer2[count_of_chars];
            count_of_chars_in_one_string++;
            if (buffer2[count_of_chars] == '\n') {
                count_of_chars++;
                break;
            }
            count_of_chars++;
        }
    }
    return array_of_strings;
}

int determine_file_size(FILE *file) {
    int file_size;
    fseek(file, 0, SEEK_END);
    file_size = (int) ftell(file);
    fseek(file, 0, SEEK_SET);
    return file_size;
}

char **reading_file(char *file_name, int *number_of_lines) {
    FILE *file;
    if ((file = fopen(file_name, "rb")) == NULL) {
        fprintf(stdout, "Cannot open file. No file with name %s exists.", file_name);
        return NULL;
    }
    int file_size = determine_file_size(file);
    char *buffer = calloc(file_size, sizeof(char));
    if (!buffer) {
        fprintf(stderr, "Can not create buffer\n");
        fclose(file);
        return NULL;
    }
    fread(buffer, file_size, sizeof(char), file);
    char *buffer2;
    int count_of_recorded_chars = 0;
    if (!(buffer2 = remove_punctuation_marks(buffer, file_size, number_of_lines, &count_of_recorded_chars))) {
        fclose(file);
        free(buffer);
        return NULL;
    }
    char **array_of_strings;
    if (!(array_of_strings = fill_array_of_strings(buffer2, *number_of_lines, count_of_recorded_chars))) {
        fclose(file);
        free(buffer);
        free(buffer2);
        return NULL;
    }
    free(buffer);
    free(buffer2);
    fclose(file);
    return array_of_strings;
}
