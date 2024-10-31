#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// grade x credit fun
double totalgrade(int credit, char grade[]) {
    double gradeTonum;
    if (strcmp(grade, "A+") == 0) {
        gradeTonum = 4.5;
    }
    else if (strcmp(grade, "A0") == 0) {
        gradeTonum = 4.0;
    }
    else if (strcmp(grade, "B+") == 0) {
        gradeTonum = 3.5;
    }
    else if (strcmp(grade, "B0") == 0) {
        gradeTonum = 3.0;
    }
    else if (strcmp(grade, "C+") == 0) {
        gradeTonum = 2.5;
    }
    else if (strcmp(grade, "C0") == 0) {
        gradeTonum = 2.0;
    }
    else if (strcmp(grade, "D+") == 0) {
        gradeTonum = 1,5;
    }
    else if (strcmp(grade, "D0") == 0) {
        gradeTonum = 1.0;
    }
    else {
        gradeTonum = 0;
    }
    return gradeTonum * (double)credit;
}
int main() {
    FILE* Fw;
    char subject[7][30];
    int credit[7];
    char grade[7][3];
    char temp[50];
    double sum = 0;
    double creditsum = 0;
    // file open
    Fw = fopen("grade.txt", "r");
    if (Fw == NULL) {
        perror("file dont open");
        return 1;
    }

    // 1 line pass
    fgets(temp, sizeof(temp), Fw);

    // 2 line start
    for (int i = 0; i < 7; i++) { 
        if (fgets(temp, sizeof(temp), Fw) != NULL) {
            sscanf(temp, "%29s %d %2s", subject[i], &credit[i], grade[i]);
            printf("==============\n");
            printf("과목: %s, 학점: %d, 성적: %s\n", subject[i], credit[i], grade[i]);
            printf("학점 x 성적 : %f \n", totalgrade(credit[i], grade[i]));
            printf("==============\n");
            sum+=totalgrade(credit[i], grade[i]);
            creditsum += (double)credit[i];
        }
        
    }
    //print total
    printf("총평점 : %f\n", sum / creditsum);
    //file close
    fclose(Fw);
    return 0;
}
