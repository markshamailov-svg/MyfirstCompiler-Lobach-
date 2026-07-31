#include <stdio.h>
#include <stdlib.h>
#include "parcer.h"
#include "lexer.h"
void generatecode(struct Node*node,FILE*file){
    if (node==NULL) return;
        if (node->type == TOKEN_EQUAL) {
        struct Node* left = node->lchild;
        struct Node* right = node->rchild;
        
        if (right->type == TOKEN_NUMBER) {
            fprintf(file, "    int %s = %s;\n", left->st, right->st);
        } else if (right->type == TOKEN_STRING) {
            fprintf(file, "    char* %s = \"%s\";\n", left->st, right->st);
        }
    }
}
void generatefinal(struct Node* AST) {
    FILE* out = fopen("out.c", "w");
    if (out == NULL) {
        fprintf(stderr, "Ошибка не удалось создать out.c");
        return;
    }
    fprintf(out, "#include <stdio.h>\n");
    fprintf(out, "int main(){\n");
    generatecode(AST, out);
    fprintf(out, "return 0;\n}\n");
    fclose(out);

    if (system("gcc out.c -o out") != 0) {
        fprintf(stderr, "Ошибка: gcc не скомпилировал out.c\n");
        return;
    }
    system("./out");
}