#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "alloc.h"

#define WRITE 1 
#define DELETE 2
#define EXECUTE 3

#define NOTE_NUM 10

long long *notes[NOTE_NUM];

void initialize() {
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
}

void print_flag(){
    char buffer[0x100] = {0, };
    int fd = open("./flag", O_RDONLY);
    if(fd == -1){
        printf("DKSWC{FLAG_ERROR}");
        return;
    }

    read(fd, buffer, 0x99);
    printf("%s\n", buffer);
}

void init_note(){
    for(int i=0;i<NOTE_NUM;i++){
        notes[i] = NULL;
    }
}

void print_menu(){
    printf("=====숫자 노트=====\n");
    printf("1. 노트 쓰기\n"); 
    printf("2. 노트 삭제\n");
    printf("3. 노트 실행하기\n");
    printf("4. 노트 주소 출력하기\n");
    printf("> ");
}

int write_note(){
    int num;
    char term;
    long long buf;
    printf("작성할 노트의 인덱스를 작성하세요: ");
    if(scanf("%d%c", &num, &term) != 2 || term != '\n'){
        return -1;
    }

    if(num < 0 || num >= NOTE_NUM){
        return -1;
    }

    notes[num] = swc_alloc(8);
    if(notes[num] == NULL){
        printf("failed allocate\n");
        return -1;
    }

    printf("노트를 8바이트 만큼 작성하세요: ");
    if(scanf("%llx%c", &buf, &term) != 2 || term != '\n'){
        return 1;
    }

    if(buf == 0x0){
        return 0;
    }

    *((long long*)notes[num]) = (long long*)buf;
    return 0;
}

int delete_note(){
    int num;
    char term;
    printf("삭제할 노트의 인덱스를 작성하세요: ");
    if(scanf("%d%c", &num, &term) != 2 || term != '\n'){
        return -1;
    }

    if(num < 0 || num >= NOTE_NUM){
        return -1;
    }

    swc_free(notes[num]);
    return 0;
} 

int execute_note(){
    int num;
    char term;
    printf("실행할 노트의 인덱스를 작성하세요: ");
    if(scanf("%d%c", &num, &term) != 2 || term != '\n'){
        return -1;
    }

    if(num < 0 || num >= NOTE_NUM){
        return -1;
    }

    if(notes[num] == NULL){
        return -1;
    }

    void (*func)();
    func = (void*)notes[num];
    func();

    return 0;
}

int main(void){
    int num; 
    char term;

    initialize();
    init_note();
    printf("print_flag function's address: %p\n", print_flag);
    
    while(1){
        print_menu();
        if(scanf("%d%c", &num, &term) != 2 || term != '\n'){
            printf("Invalid Number\n");
            return 1;
        }

        switch (num)
        {
            case WRITE:
                if(write_note() == -1){
                    return 1;
                }
                break;

            case DELETE:
                if(delete_note() == -1){
                    return 1;
                }
                break;

            case EXECUTE:
                if(execute_note() == -1){
                    return 1;
                }
                break;
            
            case 4:
                printf("노트의 주소를 출력할 인덱스: ");
                if(scanf("%d%c", &num, &term) != 2 || term != '\n'){
                    printf("Invalid Number\n");
                    return 1;
                }

                printf("note address %p\n", notes[num]);
                break;

            default:
                printf("Invalid Number\n");
                return 1;
        }
    }
    return 0;
}
