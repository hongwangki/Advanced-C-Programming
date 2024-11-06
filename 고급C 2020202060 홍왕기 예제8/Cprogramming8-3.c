#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//���� ��� ����ü
struct KorAvg {
	float koravg;
};

//���� ��� ����ü
struct EngAvg {
	float engavg;
};

//�л� ����ü
struct Student {
	char name[10];
	float kor;
	float eng;
	float avg;
};

//��ü ��� ����ü
struct AllStudentAvg {
	float allavg;
};

int main() {
	int count;

	// �л� �� �Է�
	printf("�л����� ����? ");
	scanf("%d", &count);

	struct AllStudentAvg allavg;
	struct KorAvg koravg;
	struct EngAvg engavg;
	struct Student* p;

	allavg.allavg = 0;
	koravg.koravg = 0;
	engavg.engavg = 0;

	p = (struct Student*)malloc(sizeof(struct Student) * count);

	// �л� ���� �Է� (�̸�, ����, ���� ����)
	for (int i = 0; i < count; i++) {
		printf("%d �л� �̸�, ���� ����, ���� ���� ���ʷ� �Է� (ex ���� 100 100): ", i + 1);
		scanf("%s %f %f", p[i].name, &p[i].kor, &p[i].eng);
		koravg.koravg += p[i].kor;
		engavg.engavg += p[i].eng;
		p[i].avg = (p[i].kor + p[i].eng) / 2;
		allavg.allavg += p[i].avg;
	}

	//��� ���ϱ�
	koravg.koravg /= count;
	engavg.engavg /= count;
	allavg.allavg /= count;

	FILE* fw = fopen("average_student.txt", "w");
	if (fw == NULL) {
		perror("���� ���� ����");
		free(p);
		return 1;
	}

	//���Ͽ� ��� ���
	for (int i = 0; i < count; i++) {
		fprintf(fw, "%s �л� ��� : %.2f\n", p[i].name, p[i].avg);
	}

	fprintf(fw, "��ü ���� ��� ���� : %.2f\n", koravg.koravg);
	fprintf(fw, "��ü ���� ��� ���� : %.2f\n", engavg.engavg);
	fprintf(fw, "��� �л����� �� ��� ���� : %.2f\n", allavg.allavg);

	free(p);
	fclose(fw);

	return 0;
}
