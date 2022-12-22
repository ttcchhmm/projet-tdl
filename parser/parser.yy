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
    #include "../instructions/Color.hh"
    #include "../instructions/Garden.hh"
    #include "../instructions/Jump.hh"
    #include "../instructions/conditionals/Not.hh"
    #include "../instructions/conditionals/If.hh"
    #include "../instructions/conditionals/IfElse.hh"
    #include "../instructions/conditionals/Repeat.hh"
    #include "../instructions/conditionals/While.hh"
    #include "../instructions/conditionals/Empty.hh"
    #include "../instructions/conditionals/Wall.hh"

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
%token                  PATTERN

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
%type <std::shared_ptr<Instruction>>                                conditional
%type <bool>                                                        not
%type <CheckDirection>                                              condDirection
%type <ColorZone>                                                   colorTarget

// --- PRECEDENCES --- //
%left                   PLUS        MINUS
%left                   MULTIPLY    DIVIDE
%precedence             NEGATIVE

%%

// Start of the grammar.
start:
    function NL {}
    start
    | NL {
        if(!driver.runMain()) {
            std::cerr << "An error occurred while running your program. This can happen for two reasons :\n\t1- No main function was found.\n\t2- An instruction threw an error." << std::endl;
            YYERROR;
        }

        YYACCEPT;
    }

// Represent a computed number.
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

// The target operator '@'.
target:
    TARGET {
        $$ = $1 - 1;
    } |

    %empty {
        $$ = 0;
    }

// The movement related instructions.
move:
    FORWARD math times {
        $$ = $2->calculer(context);
    } |

    FORWARD {
        $$ = 1;
    } |

    // Going backwards is just negatively going forward.

    BACKWARD math times {
        $$ = -$2->calculer(context);
    } |

    BACKWARD {
        $$ = -1;
    }

// The instruction related to adding new turtles to the field.
turtles:
    TURTLES math {
        $$ = $2->calculer(context);
    }

// The instruction related to rotating.
rotate:
    ROTATE LEFT {
        $$ = directions::LEFT;
    } |

    ROTATE RIGHT {
        $$ = directions::RIGHT;
    }

// Represent a zone for coloration.
colorTarget:
    %empty {
        $$ = ColorZone::SHELL;
    } |

    SHELL {
        $$ = ColorZone::SHELL;
    } |

    PATTERN {
        $$ = ColorZone::PATTERN;
    }

// Rule that includes every instructions.
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
    } |

    COLOR_CHANGE colorTarget COLOR target {
        $$ = std::make_shared<Color>($4, $2, $3);
    } |

    GARDEN STRING {
        $$ = std::make_shared<Garden>($2);
    } |

    JUMP target {
        $$ = std::make_shared<Jump>($2, 1);
    } |

    JUMP math target {
        $$ = std::make_shared<Jump>($3, $2->calculer(context));
    }

// Represent a direction in a conditional check.
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

// Represent the value of a conditional check.
condInstruc:
    WALL condDirection target {
        $$ = std::shared_ptr<Instruction>(new Wall($3, $2));
    } |

    EMPTY condDirection target {
        $$ = std::shared_ptr<Instruction>(new Empty($3, $2));
    }

// The negate operator.
not:
    %empty {
        $$ = false;
    } |

    NOT {
        $$ = true;
    }

// Represent a conditional.
conditional:
    not condInstruc {
        if($1) {
            $$ = std::shared_ptr<Instruction>(new Not($2));
        } else {
            $$ = $2;
        }
    }

// A sub-branch of a program.
branch:
    // If.
    IF conditional BRANCH_START endl instructionList END IF {
        $$ = std::make_shared<If>($2, *$5);
    } |

    // If/else.
    IF conditional BRANCH_START endl instructionList ELSE BRANCH_START endl instructionList END IF {
        $$ = std::make_shared<IfElse>($2, *$5, *$9);
    } |

    // Repeat.
    REPEAT math times BRANCH_START endl instructionList END REPEAT {
        $$ = std::make_shared<Repeat>($2->calculer(context), *$6);
    } |

    // While.
    WHILE conditional BRANCH_START endl instructionList END WHILE {
        $$ = std::make_shared<While>($2, *$5);
    }

// Represent a function.
function:
    FUNCTION IDENTIFIER BRANCH_START endl instructionList END FUNCTION comment {
        std::cout << "Parsed function " << $2 << std::endl;

        // Add the function to the Driver.
        if(!driver.addFunction($2, *$5)) {
            std::cerr << "Invalid function name. Maybe it's a redeclaration ?" << std::endl;
            YYERROR;
        }
    }

// Represent a list of instructions. It's the body of a function or a branch.
instructionList:
    // End of recursion.
    %empty {
        $$ = std::make_shared<std::list<std::shared_ptr<Instruction>>>();
    } |

    // Item in the list.
    instruction endl instructionList {
        $3->push_front($1);
        $$ = $3;
    }

// A space for a comment.
comment:
    COMMENT | %empty {}

// The optional repetition keyword.
times:
    TIMES | %empty {}

// The end of a line, with a space for a comment.
endl:
    comment NL {}

%%

void yy::Parser::error( const location_type &l, const std::string & err_msg) {
    std::cerr << "Error at " << l << " : " << err_msg << '.' << std::endl;
}
