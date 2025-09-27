#include <stdio.h>
#include <string.h>
#define N 5
typedef struct student
{
    char name[8];
    short age;
    float score;
    char remark[200];
} student;
typedef unsigned char *byte_pointer;
int pack_student_bytebybyte(student *s, int sno, char *buf);
int pack_student_whole(student *s, int sno, char *buf);
int restore_student(char *buf, int len, student *s);
int pack_student_bytebybyte(student *s, int sno, char *buf)
{
    int cnt = 0;
    for (int num = 0; num < sno; num++)
    {
        byte_pointer p = (byte_pointer)(s + num);
        while (*p != '\0')
        {
            buf[cnt++] = *(p++);
        }
        buf[cnt++] = *(p++);
        p = (byte_pointer)s + sizeof(s[num].name);
        buf[cnt++] = *(p++);
        buf[cnt++] = *(p++);
        p = (byte_pointer)s + sizeof(s[num].name) + sizeof(s[num].age) + 2;
        for (int i = 0; i < 4; i++)
        {
            buf[cnt++] = *(p++);
        }
        p = p = (byte_pointer)s + sizeof(s[num].name) + sizeof(s[num].age) + 2 + sizeof(s[num].score);
        while (*p != '\0')
        {
            buf[cnt++] = *(p++);
        }
        buf[cnt++] = *(p++);
    }
    return cnt;
}
int pack_student_whole(student *s, int sno, char *buf)
{
    int cnt = 0;
    for (int num = 0; num < sno; num++)
    {
        strcpy(buf + cnt, s[num].name);
        cnt += strlen(s[num].name) + 1;
        *(short *)(buf + cnt) = s[num].age;
        cnt += sizeof(s[num].age);
        *(float *)(buf + cnt) = s[num].score;
        cnt += sizeof(s[num].score);
        strcpy(buf + cnt, s[num].remark);
        cnt += strlen(s[num].remark) + 1;
    }
    return cnt;
}
int restore_student(char *buf, int len, student *s)
{
    int cnt = 0;
    int byte_cnt = 0;
    byte_pointer p = buf;
    while (byte_cnt < len)
    {
        strcpy(s[cnt].name, p);
        byte_cnt += strlen(s[cnt].name) + 1;
        p += strlen(s[cnt].name) + 1;
        s[cnt].age = *((short *)p);
        byte_cnt += sizeof(s[cnt].age);
        p += sizeof(s[cnt].age);
        s[cnt].score = *((float *)p);
        byte_cnt += sizeof(s[cnt].score);
        p += sizeof(s[cnt].score);
        strcpy(s[cnt].remark, p);
        byte_cnt += strlen(s[cnt].remark) + 1;
        p += strlen(s[cnt].remark) + 1;
        cnt++;
    }
    return cnt;
}

int main()
{
    student old_s[N] = {
        {"zhang", 19, 48.0, "handsome boy"},
        {"bob", 18, 90.0, "good boy"},
        {"alice", 20, 88, "pretty girl"},
        {"mike", 17, 60, "nice,nice!"},
        {"amy", 28, 100, "5th student"}};
    student new_s[N];
    char message[1024];
    // student s = {"bob", 18, 90.0, "good boy"};
    student *p = old_s;
    printf("Original data size: %lu\n", sizeof(old_s));
    printf("Original data:\n");
    for(int i=0;i<5;i++){
        printf("%s %d %.2f %s\n",old_s[i].name,old_s[i].age,old_s[i].score,old_s[i].remark);
    }
    int byte_cnt = pack_student_bytebybyte(p, 2, message);
    byte_cnt += pack_student_whole(p + 2, 3, message + byte_cnt);
    printf("The packed data size: %d\n", byte_cnt);
    printf("The packed data:\n");
    for (int i = 0; i < byte_cnt; i++)
    {
        printf("0x%02x ", (unsigned char)message[i]);
        if (!((i + 1) % 8))
        {
            printf("\n");
        }
    }
    printf("\n");
    
    int stu_cnt = restore_student(message, byte_cnt, new_s);
    printf("The restored data:\n");
    for(int i=0;i<stu_cnt;i++){
        printf("%s %d %.2f %s\n",new_s[i].name,new_s[i].age,new_s[i].score,new_s[i].remark);
    };
}