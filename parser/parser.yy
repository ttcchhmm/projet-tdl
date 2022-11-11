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
    #include "directions.hh"
    
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

%type <int>             move
%type <directions>      rotate

// --- PRECEDENCES --- //
%precedence             MINUS

%%

start:
    instruction NL {
        std::cout << "Parsed line." << std::endl;
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

move:
    FORWARD mathlitteral {
        $$ = $2;
    } |

    BACKWARD mathlitteral {
        $$ = -$2;
    }

rotate:
    ROTATE LEFT {
        $$ = directions::LEFT;
    } |

    ROTATE RIGHT {
        $$ = directions::RIGHT;
    }
    
instruction:
    move {
        float orientation = driver.getJardin()->orientation(0);
        int x = driver.getJardin()->position(0).x();
        int y = driver.getJardin()->position(0).y();

        std::cout << orientation << " | " << x << "/" << y << std::endl;

        if(orientation == 0) {
            driver.getJardin()->changePosition(0, x, y - $1);
        } else if(orientation == 90) {
            driver.getJardin()->changePosition(0, x + $1, y);
        } else if(orientation == 180) {
            driver.getJardin()->changePosition(0, x, y + $1);
        } else if(orientation == 270) {
            driver.getJardin()->changePosition(0, x - $1, y);
        }
    } |

    rotate {
        float newOrientation = driver.getJardin()->orientation(0);
        switch($1) {
            case directions::LEFT: {
                newOrientation -= 90;

                if(newOrientation < 0) {
                    newOrientation += 360;
                }
            }

            case directions::RIGHT: {
                newOrientation += 90;

                if(newOrientation > 360) {
                    newOrientation -= 360;
                }
            }
        }

        driver.getJardin()->changeOrientation(0, newOrientation);
    }
%%

void yy::Parser::error( const location_type &l, const std::string & err_msg) {
    std::cerr << "Erreur : " << l << ", " << err_msg << std::endl;
}
