#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct student make
struct student {
    char subject[30];
    int credit;
    char grade[3];

};

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
        gradeTonum = 1, 5;
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
    double sum = 0;
    double creditsum = 0;
    char temp[50];
    // file open
    Fw = fopen("grade.txt", "r");
    if (Fw == NULL) {
        perror("file dont open");
        return 1;
    }

    // 1 line pass
    fgets(temp, sizeof(temp), Fw);
    struct student stu[7];
    // 2 line start
    for (int i = 0; i < 7; i++) {
        if (fgets(temp, sizeof(temp), Fw) != NULL) {
            sscanf(temp, "%29s %d %2s", stu[i].subject, &stu[i].credit, stu[i].grade);
            printf("==============\n");
            printf("과목: %s, 학점: %d, 성적: %s\n", stu[i].subject, stu[i].credit, stu[i].grade);
            printf("학점 x 성적 : %f \n", totalgrade(stu[i].credit, stu[i].grade));
            printf("==============\n");
            sum += totalgrade(stu[i].credit, stu[i].grade);
            creditsum += (double)stu[i].credit;
        }

    }
    //print total
    printf("총평점 : %f\n", sum / creditsum);
    //file close
    fclose(Fw);
    return 0;
}
