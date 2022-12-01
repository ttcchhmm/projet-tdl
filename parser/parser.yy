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

    #include "Forward.hh"

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

    Contexte context;
}

// --- PRIMITIVES --- //
%token                  NL
%token                  END
%token <int>            NUMBER
%token <std::string>    IDENTIFIER
%token <std::size_t>    TARGET
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

// --- LOOPS --- //
%token                  WHILE
%token                  REPEAT

// --- FUNCTIONS --- //
%token                  FUNCTION_START

// --- TYPES --- //
%type <ExpressionPtr>   math

%type <int>             move
%type <directions>      rotate
%type <int>             target
%type <std::size_t>     turtles

// --- PRECEDENCES --- //
%left                   PLUS        MINUS
%left                   MULTIPLY    DIVIDE
%precedence             NEGATIVE

%%

start:
    instruction NL {
        std::cout << "Parsed line." << std::endl;
    } start
    | END NL {
        YYACCEPT;
    }

math:
    NUMBER {
        $$ = std::make_shared<Constante>($1);
    } |

    math PLUS math {
        $$ = std::make_shared<ExpressionBinaire>($1, $3, OperateurBinaire::plus);
    } |

    math MULTIPLY math {
        $$ = std::make_shared<ExpressionBinaire>($1, $3, OperateurBinaire::multiplie);
    } |

    math MINUS math {
        $$ = std::make_shared<ExpressionBinaire>($1, $3, OperateurBinaire::moins);
    } |

    math DIVIDE math {
        if($3 == 0) {
            std::cerr << "Division by zero." << std::endl;
            YYERROR;
        }

        $$ = std::make_shared<ExpressionBinaire>($1, $3, OperateurBinaire::divise);
    } |

    EXPRESSION_START math EXPRESSION_END {
        $$ = $2;
    } |

    MINUS math %prec NEGATIVE {
        $$ = std::make_shared<ExpressionUnaire>($2, OperateurUnaire::neg);
    }

target:
    TARGET {
        if(driver.getJardin()->getTortues().size() >= $1) {
            $$ = $1 - 1;
        } else {
            std::cerr << "Invalid turtle ID. Got " << $1 << " but there are " << driver.getJardin()->getTortues().size() << " turtle(s) on the field." << std::endl;
            YYERROR;
        }
    } |

    %empty {
        $$ = 0;
    }

move:
    FORWARD math {
        $$ = $2->calculer(context);
    } |

    BACKWARD math {
        $$ = -$2->calculer(context);
    }

turtles:
    TURTLES math {
        $$ = $2->calculer(context);
    }

rotate:
    ROTATE LEFT {
        $$ = directions::LEFT;
    } |

    ROTATE RIGHT {
        $$ = directions::RIGHT;
    }
    
instruction:
    move target {
        Forward f;
        f.execute(driver.getJardin(), $2, {$1});

        // float orientation = driver.getJardin()->orientation($2);
        // int x = driver.getJardin()->position($2).x();
        // int y = driver.getJardin()->position($2).y();

        // std::cout << orientation << " | " << x << "/" << y << std::endl;

        // if(orientation == 0) {
        //     driver.getJardin()->changePosition($2, x, y - $1);
        // } else if(orientation == 90) {
        //     driver.getJardin()->changePosition($2, x + $1, y);
        // } else if(orientation == 180) {
        //     driver.getJardin()->changePosition($2, x, y + $1);
        // } else if(orientation == 270) {
        //     driver.getJardin()->changePosition($2, x - $1, y);
        // }
    } |

    rotate target {
        float newOrientation = driver.getJardin()->orientation($2);
        switch($1) {
            case directions::LEFT: {
                newOrientation -= 90;

                if(newOrientation < 0) {
                    newOrientation += 360;
                }

                break;
            }

            case directions::RIGHT: {
                newOrientation += 90;

                if(newOrientation > 360) {
                    newOrientation -= 360;
                }

                break;
            }
        }

        driver.getJardin()->changeOrientation($2, newOrientation);
    } |
    
    turtles {
        if(driver.getJardin()->nombreTortues() != 1) {
            std::cerr << "Non default number of turtles already set." << std::endl;
            YYERROR;
        } else {
            while(driver.getJardin()->nombreTortues() != $1) {
                driver.getJardin()->nouvelleTortue();

                std::cout << "Generated turtle. Now " << driver.getJardin()->nombreTortues() << std::endl;
            }
        }
    }
%%

void yy::Parser::error( const location_type &l, const std::string & err_msg) {
    std::cerr << "Erreur : " << l << ", " << err_msg << std::endl;
}
