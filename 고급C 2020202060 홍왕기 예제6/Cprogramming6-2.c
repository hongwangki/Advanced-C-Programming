#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
    FILE* fr;
    FILE* fw;
    char arr[4][100];//get str max 100
    fr = fopen("in.txt", "r");
    fw = fopen("output2.txt", "w");

    // input str save arr
    for (int i = 0; i < 4; i++) {
        fgets(arr[i], 100, fr); //get str  <-in.txt

    }
    size_t len = strlen(arr[0]);

    // Remove arr[0] \n
    if (len > 0 && arr[0][len - 1] == '\n') {
        arr[0][len - 1] = '\0';
    }

    // arr print
        for (int i=0; i<4; i++) {
            int j = strlen(arr[i]);
            for (; j >= 0 && arr[i][j] == '\0'; j--);
            for (; j >= 0; j--) {
                fprintf(fw, "%c", arr[i][j]);
            }
        }

    fclose(fr);
    fclose(fw);
    return 0;
}