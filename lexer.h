#ifndef LEXER_H
#define LEXER_H
typedef enum{
    TOKEN_FN, //fn
    TOKEN_IDENTIFIER, //любая переменная/название
    TOKEN_NUMBER, // целочисленные цифры
    TOKEN_STRING, // строка
    TOKEN_LPAREN, // (
    TOKEN_RPAREN, // )
    TOKEN_LBRACE, // {
    TOKEN_RBRACE, // }
    TOKEN_SEMICOLON,// ; 
    TOKEN_PLUS,//+
    TOKEN_MINUS, //-
    TOKEN_MULTIPLICATION,//*
    TOKEN_DIVISION,// /
    TOKEN_EQUAL, // =
    TOKEN_EOF // окончание файла
} TokenType;

typedef struct{
    TokenType type;
    const char *start;
    int length;
}Token;
void init_lexer(const char *source);
Token get_next_tok();
#endif