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
void average(Student* Stu) {
    _asm {
        xor edx, edx
        mov ecx, Stu
        lopa :
        xor ax, ax
            add ax, [ecx + edx + 12]
            shl ax, 1
            add ax, [ecx + edx + 14]
            shl ax, 1
            add ax, [ecx + edx + 16]
            mov bl, 7
            div bl
            mov ah, 0
            mov[ecx + edx + 18], ax
            add edx, 20
            cmp edx, 20 * 1000
            jnz lopa
    }
}
int find(Student* Stu, char* name) {
    _asm {
        mov ebx, name
        mov ecx, Stu
        start :
        xor esi, esi
            jmp first
            second :
        xor edx, edx
            cmp byte ptr name[esi], '\0'
            jz success
            add esi, 1
            first :
            xor edx, edx
            mov dl, [ecx + esi]
            cmp dl, [ebx + esi]
            jz second
            sub ecx, Stu
            cmp ecx, 20 * 1000
            jz failure
            add ecx, Stu
            add ecx, 20
            jmp start
            success :
        sub ecx, Stu
            mov eax, ecx
            mov bl, 20
            div bl
            add eax, 1
            jmp done
            failure :
        mov eax, 0
            done :
    }
}
char get_grade(short avg) {
    _asm {
        mov bx, avg
        cmp bx, 90
        jnb grade_a
        cmp bx, 80
        jnb grade_b
        cmp bx, 70
        jnb grade_c
        cmp bx, 60
        jnb grade_d
        mov eax, 'F'
        jmp over
        grade_a :
        mov eax, 'A'
            jmp over
            grade_b :
        mov eax, 'B'
            jmp over
            grade_c :
        mov eax, 'C'
            jmp over
            grade_d :
        mov eax, 'D'
            jmp over
            over :
    }
}
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