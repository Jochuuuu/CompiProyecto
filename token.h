#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
public:
   enum Type {
    PLUS, MINUS, MUL, DIV, NUM, ERR, PD, PI, END, ID, PRINT, ASSIGN, PC,
    LT, LE, EQ, IF, THEN, ELSE, ENDIF, WHILE, DO, COMA, IFEXP,
    VAR, FOR, TRUE, FALSE, RETURN, FUN, ENDFUN,
    BEGIN, END_BLOCK, COLON, PROGRAM, DOT,TO,COMMENT,ENDLINE,USES,DOWNTO
};


    Type type;
    std::string text;

    Token(Type type);
    Token(Type type, char c);
    Token(Type type, const std::string& source, int first, int last);

    friend std::ostream& operator<<(std::ostream& outs, const Token& tok);
    friend std::ostream& operator<<(std::ostream& outs, const Token* tok);
};

#endif // TOKEN_H
