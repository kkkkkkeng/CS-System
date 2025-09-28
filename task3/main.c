#include <stdio.h>
#include <string.h>
#include <sys/time.h> // gettimeofday

#define STUDENTS_NUM 10

typedef struct temp
{
	char sname[8];
	char sid[11];	 //  如U202315123
	short scores[8]; //  8门课的分数
	short average;	 //  平均分
} student;

extern void display(student *s, int num);

void initStudents(student *s, int num)
{
	strcpy(s[0].sname, "zhang");
	strcpy(s[0].sid, "U202413848");
	s[0].scores[0] = 95;
	s[0].scores[1] = 85;
	s[0].scores[2] = 90;
	for (int i = 1; i < 8; i++)
		s[0].scores[i] = 80 + i;
	s[0].average = 0;

	strcpy(s[1].sname, "wang");
	strcpy(s[1].sid, "U202315002");
	for (int i = 0; i < 8; i++)
		s[1].scores[i] = 70 + 2 * i;
	strcpy(s[2].sname, "li");
	strcpy(s[2].sid, "U202315123");
	for (int i = 0; i < 8; i++)
		s[2].scores[i] = 60 + 3 * i;
	strcpy(s[3].sname, "zhao");
	strcpy(s[3].sid, "U202315456");
	for (int i = 0; i < 8; i++)
		s[3].scores[i] = 56 + 4 * i;
	strcpy(s[4].sname, "qian");
	strcpy(s[4].sid, "U202315789");
	for (int i = 0; i < 8; i++)
		s[4].scores[i] = 90 - 3 * i;
	strcpy(s[5].sname, "sun");
	strcpy(s[5].sid, "U202316001");
	for (int i = 0; i < 8; i++)
		s[5].scores[i] = 88 - 2 * i;
	strcpy(s[6].sname, "zhou");
	strcpy(s[6].sid, "U202316123");
	for (int i = 0; i < 8; i++)
		s[6].scores[i] = 78 - 2 * i;
	strcpy(s[7].sname, "wu");
	strcpy(s[7].sid, "U202316456");
	for (int i = 0; i < 8; i++)
		s[7].scores[i] = 66 - 2 * i;
	strcpy(s[8].sname, "xu");
	strcpy(s[8].sid, "U202316789");
	for (int i = 0; i < 8; i++)
		s[8].scores[i] = 55 + 6 * i;
	strcpy(s[9].sname, "hu");
	strcpy(s[9].sid, "U202317000");
	for (int i = 0; i < 8; i++)
		s[9].scores[i] = 100 - 5 * i;
	s[9].average = 0;
}

void computeAverageScore(student *s, int num)
{
	for (int i = 0; i < num; i++)
	{
		int sum = 0;
		for (int j = 0; j < 8; j++)
		{
			sum += s[i].scores[j];
		}
		s[i].average = sum / 8;
	}
}

// 获取当前时间（毫秒）
long long current_millis()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
void sortStudentsByAverage(student *s, int num)
{
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num -i-1; j++)
		{
			if (s[j].average < s[j+1].average)
			{
				student temp;
				temp = s[j];
				s[j]=s[j+1];
				s[j+1]=temp;
			}
		}
	}
}
void displayall(student *s, int num)
{
	for (int i = 0; i < num;i++){
		printf("%s %s ", s[i].sname, s[i].sid);
		for (int j = 0; j < 8; j++)
		{
			printf("%d ", s[i].scores[j]);
		}
		printf("average=%d\n", s[i].average);
	}
}
int main()
{
	student s[STUDENTS_NUM];
	long long start, finish, duration;

	printf("%d\n", sizeof(student));
	initStudents(s, STUDENTS_NUM);
	// display(s, STUDENTS_NUM);
	start = current_millis();
	for (int i = 0; i < 200000; i++)
	{
		computeAverageScore(s, STUDENTS_NUM);
	}
	finish = current_millis();
	duration = finish - start;
	printf("计算平均成绩用时： %lld  毫秒\n", duration);
	displayall(s, STUDENTS_NUM);
	start = current_millis();
	for(int i=0;i<200000;i++){
		sortStudentsByAverage(s, STUDENTS_NUM);
	}
	finish = current_millis();
	duration = finish - start;
	printf("排序用时： %lld  毫秒\n", duration);
	displayall(s, STUDENTS_NUM);
	return 0;
}
