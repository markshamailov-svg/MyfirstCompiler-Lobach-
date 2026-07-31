#include <stdio.h>
#include "lexer.h"
#include "parcer.h"
#include <stdlib.h>

int main(int argс,char *argv[]){
    //проверка запуска   
    if (argс < 2){
        fprintf(stderr,"Ошибка компиляции, недостает аргументов для %s\n", argv[0]);
        return 1;
    }
    const char *source_filename = argv[1];
    //пусть пока означает начало просто
    printf("Начало компиляции файла %s\n",source_filename);
    //чтение файлика
    FILE *file = fopen(argv[1],"r");
    //защита
    if (file == NULL){
        fprintf(stderr,"Файл не найден");
        return 1;
    }
    fseek(file,0,SEEK_END);

    long file_size = ftell(file);

    rewind(file);
    char *source  = malloc(file_size+1);
    if (source == NULL){
        fprintf(stderr,"Ошибка компиляции, файла нет/пуст");
        return 1;
    }
    size_t read = fread(source,1,file_size,file);
    if (read != file_size){
        fprintf(stderr,"Ошибка компиляции");
        return 1;
    }
    source[read] = '\0';

    fclose(file);
    init_lexer(source);
    struct Node *AST = ParceProgram();
    if (AST == NULL) {
    fprintf(stderr, "Ошибка парсинга, AST не создан\n");
    free(source);
    return 1;
}
    generatefinal(AST);
    free(source);
    printf("Компиляция завершена успешно!");
    return 0;
}
