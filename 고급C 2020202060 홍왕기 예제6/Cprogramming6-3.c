#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 20
#define MAX_LENGTH 100

// read file a arr save fun
void read_file_to_array(const char* filename, char* array_A[MAX_WORDS], int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("file dont open");
        exit(1);
    }

    char buffer[MAX_LENGTH];
    *count = 0;
    while (fscanf(file, "%99[^|]|", buffer) != EOF && *count < MAX_WORDS) {
        size_t len = strlen(buffer);

        // \n remove
        if (buffer[0] == '\n') {
            memmove(buffer, buffer + 1, len);
            len--;
        }

        // end point if \n ->remove
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == ' ')) {
            buffer[--len] = '\0';
        }

        // malloc
        array_A[*count] = (char*)malloc(len + 1);
        if (array_A[*count] == NULL) {
            perror("malloc fail");
            exit(1);
        }
        strcpy(array_A[*count], buffer);
        (*count)++;
    }

    fclose(file);
}

// ascending fun
void sort_ascending(char* array_B[MAX_WORDS], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(array_B[j], array_B[j + 1]) > 0) {
                char* temp = array_B[j];
                array_B[j] = array_B[j + 1];
                array_B[j + 1] = temp;
            }
        }
    }
}

//descending fun
void sort_descending(char* array_B[MAX_WORDS], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(array_B[j], array_B[j + 1]) < 0) {
                char* temp = array_B[j];
                array_B[j] = array_B[j + 1];
                array_B[j + 1] = temp;
            }
        }
    }
}

// reusult save file fun
void write_result_to_file(const char* filename, char* array_B[MAX_WORDS], int count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("file dont open");
        exit(1);
    }
    fprintf(file, "======Sorting Result======\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "[%25s]\n", array_B[i]);
    }

    fclose(file);
}

int main() {
    char* array_A[MAX_WORDS];
    char* array_B[MAX_WORDS];
    int word_count = 0;

    //read data txt
    read_file_to_array("data.txt", array_A, &word_count);

    //copy arr
    for (int i = 0; i < word_count; i++) {
        array_B[i] = (char*)malloc(strlen(array_A[i]) + 1); 
        if (array_B[i] == NULL) {
            perror("malloc fail");
            exit(1);
        }
        strcpy(array_B[i], array_A[i]); // บนป็
    }

    //ascending sort and save file
    sort_ascending(array_B, word_count);
    write_result_to_file("Result_Ascending.txt", array_B, word_count);

    //descending sort and save file
    sort_descending(array_B, word_count);
    write_result_to_file("Result_Descending.txt", array_B, word_count);

    // free
    for (int i = 0; i < word_count; i++) {
        free(array_A[i]);
        free(array_B[i]);
    }

    return 0;
}
