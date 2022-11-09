%skeleton "lalr1.cc"
%require "3.0"

%defines
%define parser_class_name { Parser }
%define api.value.type variant
%define parse.assert

%locations

%code requires{
    #include "contexte.hh"
    #include "expressionBinaire.hh"
    #include "expressionUnaire.hh"
    #include "constante.hh"
    #include "variable.hh"
    
    class Scanner;
    class Driver;
}

%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%code{
    #include <iostream>
    #include <string>

    #include <QCoreApplication>
    
    #include "scanner.hh"
    #include "driver.hh"

    #undef  yylex
    #define yylex scanner.yylex
}

// --- PRIMITIVES --- //
%token                  NL
%token                  END
%token <int>            NUMBER
%token <std::string>    IDENTIFIER
%token <int>            TARGET
%token <std::string>    COLOR
%token <std::string>    STRING

// --- COMMENTS --- //
%token                  COMMENT

// --- WALL CHECKS --- //
%token                  WALL
%token                  EMPTY

// --- ARITHMETICS --- //
%token                  PLUS
%token                  MINUS
%token                  MULTIPLY
%token                  DIVIDE
%token                  NOT
%token                  EXPRESSION_START
%token                  EXPRESSION_END

// --- MOVE INSTRUCTIONS --- //
%token                  FORWARD
%token                  BACKWARD
%token                  JUMP
%token                  ROTATE
%token                  TIMES

// --- COLOR INSTRUCTIONS --- //
%token                  COLOR_CHANGE
%token                  SHELL

// --- TURTLES CREATION --- //
%token                  TURTLES

// --- GARDEN LOADING --- //
%token                  GARDEN

// --- DIRECTIONS --- //
%token                  LEFT
%token                  RIGHT
%token                  FRONT
%token                  BACK

// --- BRANCHING --- //
%token                  BRANCH_START
%token                  IF
%token                  ELSE
%token                  BRANCH_END

// --- LOOPS --- //
%token                  WHILE
%token                  REPEAT

// --- FUNCTIONS --- //
%token                  FUNCTION_START

// --- TYPES --- //
%type <int>             mathlitteral
%type <int>             mathoperation

// --- PRECEDENCES --- //
%precedence             MINUS

%%

start:
    instruction NL {

    } start
    | END NL {
        QCoreApplication::instance()->quit();
        YYACCEPT;
    }

mathoperation:
    mathlitteral PLUS mathlitteral {
        $$ = $1 + $3;
    } |

    mathlitteral MULTIPLY mathlitteral {
        $$ = $1 * $3;
    } |

    mathlitteral MINUS mathlitteral {
        $$ = $1 - $3;
    } |

    mathlitteral DIVIDE mathlitteral {
        if($3 == 0) {
            std::cerr << "Division by zero." << std::endl;
            YYERROR;
        }

        $$ = $1 / $3;
    }

mathlitteral:
    MINUS NUMBER %prec MINUS {
        $$ = -$2;
    } |

    NUMBER | mathoperation {
        $$ = $1;
    } |

    EXPRESSION_START mathoperation EXPRESSION_END {
        $$ = $2;
    }
    
instruction:

%%

void yy::Parser::error( const location_type &l, const std::string & err_msg) {
    std::cerr << "Erreur : " << l << ", " << err_msg << std::endl;
}
