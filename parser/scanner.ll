%{

#include "scanner.hh"
#include <string>
#include <cstdlib>

#define YY_NO_UNISTD_H

using token = yy::Parser::token;

#undef  YY_DECL
#define YY_DECL int Scanner::yylex( yy::Parser::semantic_type * const lval, yy::Parser::location_type *loc )

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option c++
%option yyclass="Scanner"
%option noyywrap

%%

%{
    yylval = lval;
%}

--.* {
    return token::COMMENT;
}

fin return token::END;

[0-9]+      {
    yylval->build<int>(std::atoi(yytext));
    return token::NUMBER;
}

"\n"          {
    loc->lines();
    return token::NL;
}

"+" {
    return token::PLUS;
}

"-" {
    return token::MINUS;
}

"/" {
    return token::DIVIDE;
}

"*" {
    return token::MULTIPLY;
}

"(" {
    return token::EXPRESSION_START;
}

")" {
    return token::EXPRESSION_END;
}

mur {
    return token::WALL;
}

vide {
    return token::EMPTY;
}

"pas de" {
    return token::NOT;
}

devant {
    return token::FRONT;
}

derriere {
    return token::BACK;
}

droite {
    return token::RIGHT;
}

avance {
    return token::FORWARD;
}

recule {
    return token::BACKWARD;
}

saute {
    return token::JUMP;
}

"tourne à" {
    return token::ROTATE;
}

fois {
    return token::TIMES;
}

gauche {
    return token::LEFT;
}

si {
    return token::IF;
}

sinon {
    return token::ELSE;
}

"tant que" {
    return token::WHILE;
}

repete {
    return token::REPEAT;
}

fonction {
    return token::FUNCTION;
}

" :" {
    return token::BRANCH_START;
}

couleur {
    return token::COLOR_CHANGE;
}

carapace {
    return token::SHELL;
}

motif {
    return token::PATTERN;
}

tortues {
    return token::TURTLES;
}

jardin {
    return token::GARDEN;
}

@[0-9]+ {
    yylval->build<std::size_t>(std::atoi(yytext+1));
    return token::TARGET;
}

#[0-9A-Fa-f]{6} {
    yylval->build<std::string>(yytext+1);
    return token::COLOR;
}

'.*' {
    std::string str(yytext);
    yylval->build<std::string>(str.substr(1, str.size() - 2));
    return token::STRING;
}

[a-zA-Z][a-zA-Z0-9]* {
    yylval->build<std::string>(yytext);
    return token::IDENTIFIER;
}

%%
