#include "lexer.h"
#include <stdio.h>

typedef struct{
    const char *start;
    const char *current;
}Lexer;

static Lexer lexer;
static int is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static int is_digit(char c) {
    return (c >= '0' && c <= '9');
}
Token make_token(TokenType i, const char *start,int lenght){
    Token t;
    t.type = i;
    t.start = start;
    t.length = lenght;
    return t;
}
void init_lexer(const char *source){
    lexer.start = source;
    lexer.current = source;
}
Token get_next_tok(){
    if (*lexer.current == '\0'){
        return make_token(TOKEN_EOF,lexer.current,0);
    }
        while (*lexer.current == ' ' || *lexer.current == '\t' || *lexer.current == '\n' || *lexer.current == '\r'){
            lexer.current++;
        }
    
    if (*lexer.current == '\0'){
        return make_token(TOKEN_EOF,lexer.current,0);
    }
    if (is_digit(*lexer.current)) {
        const char *st = lexer.current;
        int lenght = 0;
        while (is_digit(*lexer.current)) {
            lexer.current++;
            lenght++;
        }
        return make_token(TOKEN_NUMBER,st,lenght);

    }
        if (is_alpha(*lexer.current) ){
            int length = 0;
            const char *start = lexer.current;
            while(is_alpha(*lexer.current) || is_digit(*lexer.current)){
                lexer.current++;
                length++;
            }
            return  make_token(TOKEN_IDENTIFIER,start,length);
        }
    // оставлено место для кейсов ключевых слов 
    if (*lexer.current == '='){
        lexer.current++;
        return make_token(TOKEN_EQUAL,lexer.current-1,1);
    }
    if (*lexer.current == '('){
        lexer.current++;
        return make_token(TOKEN_LPAREN,lexer.current-1,1);
    }
    if (*lexer.current == ')'){
        lexer.current++;
        return make_token(TOKEN_RPAREN,lexer.current-1,1);
    }
    if (*lexer.current == '{'){
        lexer.current++;
        return make_token(TOKEN_LBRACE,lexer.current-1,1);
    }
    if (*lexer.current == '}'){
        lexer.current++;
        return make_token(TOKEN_RBRACE,lexer.current-1,1);
    }
    if (*lexer.current == ';'){
        lexer.current++;
        return make_token(TOKEN_SEMICOLON,lexer.current-1,1);
    }
    if (*lexer.current == '+'){
        lexer.current++;
        return make_token(TOKEN_PLUS,lexer.current-1,1);
    }
    if (*lexer.current == '-'){
        lexer.current++;
        return make_token(TOKEN_MINUS,lexer.current-1,1);
    }
    if (*lexer.current == '*'){
        lexer.current++;
        return make_token(TOKEN_MULTIPLICATION,lexer.current-1,1);
    }
    if (*lexer.current == '/'){
        lexer.current++;
        return make_token(TOKEN_DIVISION,lexer.current-1,1);
    }
    if (*lexer.current == '"'){
        lexer.current++;
        const char *st = lexer.current;
        int lenght = 1;
        while(*lexer.current != '"' && *lexer.current != '\0'){
            lexer.current++;
            lenght++;
        }
        if (*lexer.current == '\0'){
            fprintf(stderr, "Ошибка компиляции строка не закрыта", *lexer.current);
            return make_token(TOKEN_EOF,lexer.current,0);
        }
        if(*lexer.current == '"'){
        lexer.current++;
        return make_token(TOKEN_STRING,st,lenght);
        }
        fprintf(stderr, "Ошибка компиляции строка не закрыта", *lexer.current);
        return make_token(TOKEN_EOF,lexer.current,0);
    }
    fprintf(stderr,"Неизвестный символ %c\n",*lexer.current);
    lexer.current++;
    return make_token(TOKEN_EOF,lexer.current-1,0);
    
}