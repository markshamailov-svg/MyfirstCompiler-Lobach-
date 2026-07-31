#include "lexer.h"
#include "parcer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node* make_false_ast(){
    return NULL;
}
struct Node* parse_assignment(Token cur) {
    struct Node*Ast = malloc(sizeof(struct Node));
    if (Ast == NULL){
        return make_false_ast();
    }
    Ast->type = cur.type;
    if (Ast->type != TOKEN_IDENTIFIER){
        return make_false_ast();
    }
    Ast->st = malloc(cur.length+1);
    strncpy(Ast->st,(char*)cur.start,cur.length);
    Ast->st[cur.length] = '\0';

    cur = get_next_tok();
    struct Node*Mom;
    if (cur.type == TOKEN_EQUAL){
        Mom = malloc(sizeof(struct Node));
        Mom->type = cur.type;
        Mom->st = malloc(cur.length+1);
        strncpy(Mom->st,(char*)cur.start,cur.length);
        Mom->st[cur.length] = '\0';
        Mom->lchild = Ast;
    }
    else{
        return make_false_ast();
    }
    cur = get_next_tok();
    struct Node* astfinal;
    if(cur.type == TOKEN_NUMBER){
        const char* num_start = cur.start;
        int num_lengt = cur.length;
        Token sem = get_next_tok();
        if (sem.type != TOKEN_SEMICOLON){
            return make_false_ast();
        }
        astfinal = malloc(sizeof(struct Node));
        if (astfinal == NULL){
            return make_false_ast();
        }
        astfinal->type = TOKEN_NUMBER;
        astfinal->st = malloc(num_lengt+1);
        strncpy(astfinal->st,(char*)num_start,num_lengt);
        astfinal->st[num_lengt]= '\0';
        Mom->rchild = astfinal;
}
    else if(cur.type == TOKEN_STRING){
        const char* num_start = cur.start;
        int num_lengt = cur.length;
        Token sem = get_next_tok();
        if (sem.type != TOKEN_SEMICOLON){
            return make_false_ast();
        }
        astfinal = malloc(sizeof(struct Node));
        if (astfinal == NULL){
            return make_false_ast();
        }
        astfinal->type = TOKEN_STRING;
        astfinal->st = malloc(num_lengt+1);
        strncpy(astfinal->st,(char*)num_start,num_lengt);
        astfinal->st[num_lengt]= '\0';
        Mom->rchild = astfinal;
    }
    else{
        return make_false_ast();
    }
    return Mom;
}
struct Node* ParceProgram(){
    Token cur = get_next_tok();
    if (cur.type != TOKEN_IDENTIFIER){
        fprintf(stderr,"Ошибка: ожидался индефикатор\n");
        return NULL;
    }
    struct Node *AST = parse_assignment(cur);
    if (AST == NULL){
        fprintf(stderr,"Ошибка парсинга присваивания");
        return NULL;
    }
    Token next = get_next_tok();
    if (next.type != TOKEN_EOF){
        fprintf(stderr, "Ошибка компиляции лишние действия");
        return NULL;
    }
    return AST;

}