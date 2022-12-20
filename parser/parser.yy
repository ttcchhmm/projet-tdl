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

    #include "../instructions/Forward.hh"
    #include "../instructions/Rotate.hh"
    #include "../instructions/Turtles.hh"
    #include "../instructions/FunctionCall.hh"
    #include "../instructions/conditionnals/Not.hh"
    #include "../instructions/conditionnals/If.hh"
    #include "../instructions/conditionnals/Repeat.hh"
    #include "../instructions/conditionnals/Empty.hh"
    #include "../instructions/conditionnals/Wall.hh"

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
%token                  FUNCTION

// --- TYPES --- //
%type <ExpressionPtr>   math

%type <int>                                                         move
%type <directions>                                                  rotate
%type <int>                                                         target
%type <std::size_t>                                                 turtles
%type <std::shared_ptr<Instruction>>                                instruction
%type <std::shared_ptr<Instruction>>                                branch
%type <std::shared_ptr<std::list<std::shared_ptr<Instruction>>>>    instructionList
%type <std::shared_ptr<Instruction>>                                condInstruc
%type <std::shared_ptr<Instruction>>                                conditionnal
%type <bool>                                                        not
%type <CheckDirection>                                              condDirection 

// --- PRECEDENCES --- //
%left                   PLUS        MINUS
%left                   MULTIPLY    DIVIDE
%precedence             NEGATIVE

%%

start:
    function NL {}
    start
    | NL {
        if(!driver.runMain()) {
            std::cout << "No main function was found." << std::endl;
            YYERROR;
        }

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
    FORWARD math times {
        $$ = $2->calculer(context);
    } |

    BACKWARD math times {
        $$ = -$2->calculer(context);
    } |
    
    FORWARD {
        $$ = 1;
    } |

    BACKWARD {
        $$ = -1;
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
        $$ = std::shared_ptr<Instruction>(new Forward($2, $1));
    } |

    rotate target {
        $$ = std::shared_ptr<Instruction>(new Rotate($2, $1));
    } |
    
    turtles {
        $$ = std::shared_ptr<Instruction>(new Turtles($1));
    } |

    IDENTIFIER {
        try {
            $$ = std::shared_ptr<Instruction>(new FunctionCall(driver.getFunction($1), {}));
        } catch (std::out_of_range const & e) {
            std::cerr << "Undefined function: " << $1 << std::endl;
            YYERROR;
        }
    } |

    branch {
        $$ = $1;
    }

condDirection:
    FRONT {
        $$ = CheckDirection::FRONT;
    } |

    BACK {
        $$ = CheckDirection::BACK;
    } |

    LEFT {
        $$ = CheckDirection::LEFT;
    } |

    RIGHT {
        $$ = CheckDirection::RIGHT;
    }

condInstruc:
    WALL condDirection target {
        $$ = std::shared_ptr<Instruction>(new Wall($3, $2));
    } |

    EMPTY condDirection target {
        $$ = std::shared_ptr<Instruction>(new Empty($3, $2));
    }

not:
    %empty {
        $$ = false;
    } |

    NOT {
        $$ = true;
    }

conditionnal:
    not condInstruc {
        if($1) {
            $$ = std::shared_ptr<Instruction>(new Not($2));
        } else {
            $$ = $2;
        }
    }

branch:
    IF conditionnal BRANCH_START comment NL instructionList END IF {
        $$ = std::make_shared<If>($2, *$6);
    } |

    REPEAT math BRANCH_START comment NL instructionList END REPEAT {
        $$ = std::make_shared<Repeat>($2->calculer(context), *$6);
    }

function:
    FUNCTION IDENTIFIER BRANCH_START comment NL instructionList END FUNCTION comment {
        std::cout << "Parsed function " << $2 << std::endl;

        if(!driver.addFunction($2, *$6)) {
            std::cerr << "Invalid function name. Maybe it's a redeclaration ?" << std::endl;
            YYERROR;
        }
    }

instructionList:
    %empty {
        $$ = std::make_shared<std::list<std::shared_ptr<Instruction>>>();
    } |

    instruction comment NL instructionList {
        $4->push_front($1);
        $$ = $4;
    }

comment:
    COMMENT | %empty {}

times:
    TIMES | %empty {}
%%

void yy::Parser::error( const location_type &l, const std::string & err_msg) {
    /* std::cerr << "Erreur : " << l << ", " << err_msg << std::endl; */
    std::cerr << "Error at " << l << " : " << err_msg << '.' << std::endl;
}
