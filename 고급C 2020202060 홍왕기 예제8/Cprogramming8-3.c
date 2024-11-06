#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//국어 평균 구조체
struct KorAvg {
	float koravg;
};

//영어 평균 구조체
struct EngAvg {
	float engavg;
};

//학생 구조체
struct Student {
	char name[10];
	float kor;
	float eng;
	float avg;
};

//전체 평균 구조체
struct AllStudentAvg {
	float allavg;
};

int main() {
	int count;

	// 학생 수 입력
	printf("학생들의 숫자? ");
	scanf("%d", &count);

	struct AllStudentAvg allavg;
	struct KorAvg koravg;
	struct EngAvg engavg;
	struct Student* p;

	allavg.allavg = 0;
	koravg.koravg = 0;
	engavg.engavg = 0;

	p = (struct Student*)malloc(sizeof(struct Student) * count);

	// 학생 정보 입력 (이름, 국어, 영어 점수)
	for (int i = 0; i < count; i++) {
		printf("%d 학생 이름, 국어 점수, 영어 점수 차례로 입력 (ex 정현 100 100): ", i + 1);
		scanf("%s %f %f", p[i].name, &p[i].kor, &p[i].eng);
		koravg.koravg += p[i].kor;
		engavg.engavg += p[i].eng;
		p[i].avg = (p[i].kor + p[i].eng) / 2;
		allavg.allavg += p[i].avg;
	}

	//평균 구하기
	koravg.koravg /= count;
	engavg.engavg /= count;
	allavg.allavg /= count;

	FILE* fw = fopen("average_student.txt", "w");
	if (fw == NULL) {
		perror("파일 열기 실패");
		free(p);
		return 1;
	}

	//파일에 결과 출력
	for (int i = 0; i < count; i++) {
		fprintf(fw, "%s 학생 평균 : %.2f\n", p[i].name, p[i].avg);
	}

	fprintf(fw, "전체 국어 평균 성적 : %.2f\n", koravg.koravg);
	fprintf(fw, "전체 영어 평균 성적 : %.2f\n", engavg.engavg);
	fprintf(fw, "모든 학생들의 총 평균 점수 : %.2f\n", allavg.allavg);

	free(p);
	fclose(fw);

	return 0;
}
