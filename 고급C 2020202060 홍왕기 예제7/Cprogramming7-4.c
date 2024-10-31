#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num = 0;

int my_strcmp(char str1[], char str2[]) {
    int i = 0;
    //compare str1 str2
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (tolower(str1[i]) > tolower(str2[i])) {
            return 1;
        }
        else if (tolower(str1[i]) < tolower(str2[i])) {
            return -1;
        }
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0') {
        return 0;
    }
    else if (str1[i] == '\0') {
        return -1;
    }
    else {
        return 1;
    }
}
void make_dictionary(char** word) {
    char temp[100];
    // 문자열의 사전순서로
    for (int i = 0; i < num - 1; i++) {
        for (int j = i + 1; j < num; j++) {
            if (my_strcmp(word[i], word[j]) > 0) {
                strcpy(temp, word[i]);	
                strcpy(word[i], word[j]);
                strcpy(word[j], temp);
            }
        }
    }
    FILE* fr;
    //file open
    fr = fopen("dictionary.txt", "w");
    for (int i = 0; i < num; i++) {
        fputs(word[i], fr);
        fprintf(fr, "\n");
        
    }
    fprintf(fr, "\n");
    fclose(fr);
}


int main() {
    FILE* fw;
    char temp[100];

    fw = fopen("words.txt", "r");
    if (fw == NULL) {
        printf("dont file open.\n");
        return 1;
    }

    char** word = NULL;

    while (fgets(temp, sizeof(temp), fw) != NULL) {
        int start = 0;
        for (int i = 0; temp[i] != '\0'; i++) {
            //' '  \t  | , \n ; 로 파싱
            if (temp[i] == ' ' || temp[i] == '\t' || temp[i] == '|' || temp[i] == ',' || temp[i] == '\n' || temp[i] == ';') {
                if (start < i) {
                    int len = i - start;
                    //단어가 하나 있다면 사이즈 조절
                    word = (char**)realloc(word, sizeof(char*) * (num + 1));
                    //단어 크기만큼 동적할당
                    word[num] = (char*)malloc(len + 1);
                    strncpy(word[num], temp + start, len);
                    word[num][len] = '\0';
                    num++;
                }
                start = i + 1; // 다음 단어의 시작 위치
            }
        }
    }
    //사전식 정렬
    make_dictionary(word);

    fclose(fw);

    free(word);

    return 0;
}
