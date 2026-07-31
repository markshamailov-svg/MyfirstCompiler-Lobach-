#ifndef PARCER_H
#define PARCER_H

#include "lexer.h"

struct Node{
    TokenType type;
    struct Node*rchild;
    struct Node *lchild;

     char *st;
    int lenght;
};

struct Node* ParceProgram();
void generatefinal(struct Node*AST);
#endif
