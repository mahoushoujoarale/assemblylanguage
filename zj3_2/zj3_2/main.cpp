#include <stdio.h>
#include <string.h>
typedef struct Student {
    char name[11];
    short ch;
    short mt;
    short en;
    short avg;
};
Student Stu[1000] = {
{"ZhangSan", 94, 99, 98,},
{"LiSi", 78, 88, 64,},
{"WangWu", 32, 11, 17,},
{"ZhaoJie", 84, 95, 93,},
};
extern "C" {void average(Student *); }
extern "C" {int find(Student *, char*); }
extern "C" {char get_grade(short); }
int main() {
    char name[10];
    average(Stu);
    while (1) {
        printf("Please enter your name, enter q to quit.");
        printf("(the input string shoule be no more than 10 words)\n");
        scanf_s("%s", name, 10);
        if (name[0] == 'q' && name[1] == '\0') break;
        if (find(Stu, name)) printf("Your grade is: %c\n", get_grade(Stu[find(Stu, name) - 1].avg));
        else printf("Your name is not found, please check your input!\n");
        printf("\n");
    }
    return 0;
}