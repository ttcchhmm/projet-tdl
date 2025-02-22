######################################################################
# Automatically generated by qmake (2.00a) Thu Sep 7 15:54:07 2006
######################################################################

QMAKE_CXXFLAGS += -std=c++17
TEMPLATE = app
TARGET +=
DEPENDPATH += $$PWD/build/expressions $$PWD/expressions
INCLUDEPATH += $$PWD/build/expressions $$PWD/expressions $$PWD/parser $$PWD/GUI $$PWD/instructions
LIBS += -L$$PWD/build/expressions/ -lexpressions
PRE_TARGETDEPS += $$PWD/build/expressions/libexpressions.a

QT += widgets 
# Input
HEADERS += parser/scanner.hh parser/driver.hh GUI/tortue.hh GUI/jardinHandler.hh GUI/jardinRendering.hh GUI/jardin.hh instructions/Instruction.hh instructions/Forward.hh instructions/Rotate.hh instructions/Turtles.hh instructions/Function.hh instructions/FunctionCall.hh instructions/conditionals/Empty.hh instructions/conditionals/If.hh instructions/conditionals/Not.hh instructions/conditionals/Wall.hh instructions/conditionals/Repeat.hh instructions/conditionals/While.hh instructions/conditionals/IfElse.hh instructions/Color.hh instructions/Garden.hh instructions/Jump.hh Utils.hh
#LEXSOURCES += parser/scanner.ll
#YACCSOURCES += parser/parser.yy
SOURCES += parser/main.cc parser/driver.cc GUI/tortue.cc GUI/jardinHandler.cc GUI/jardinRendering.cc GUI/jardin.cc instructions/Instruction.cc instructions/Forward.cc instructions/Rotate.cc instructions/Turtles.cc instructions/Function.cc instructions/FunctionCall.cc instructions/conditionals/Empty.cc instructions/conditionals/If.cc instructions/conditionals/Not.cc instructions/conditionals/Wall.cc instructions/conditionals/Repeat.cc instructions/conditionals/While.cc instructions/conditionals/IfElse.cc instructions/Color.cc instructions/Garden.cc instructions/Jump.cc


#app.depends = ./parser/parser.hh
# Flex/bison specifics

#QMAKE_LEX = flex
#QMAKE_YACC = bison

#QMAKE_YACCFLAGS = -o
#QMAKE_YACC_HEADER = 
#QMAKE_YACC_SOURCE =

FLEXSOURCES = parser/scanner.ll
BISONSOURCES = parser/parser.yy

rmlocation.commands = find . -name \"location.hh\" -exec rm {} \\;
rmstack.commands = find . -name \"stack.hh\" -exec rm {} \\;
rmposition.commands = find . -name \"position.hh\" -exec rm {} \\;
rmparser.commands = find . -name \"parser.hh\" -exec rm {} \\;

flex.commands = flex -oscanner.cc ${QMAKE_FILE_IN}
flex.input = FLEXSOURCES
flex.output = scanner.cc
flex.variable_out = SOURCES
flex.name = flex
QMAKE_EXTRA_COMPILERS += flex

bison.commands = bison -oparser.cc ${QMAKE_FILE_IN}
bison.input = BISONSOURCES
bison.output = parser.cc
bison.variable_out = SOURCES
bison.name = bison
QMAKE_EXTRA_COMPILERS += bison

bisonheader.commands = @true
bisonheader.input = BISONSOURCES
bisonheader.output = parser.hpp
bisonheader.variable_out = HEADERS
bisonheader.name = bison header
bisonheader.depends = parser.cc
QMAKE_EXTRA_COMPILERS += bisonheader

clean.depends =  rmlocation rmstack rmposition rmparser
distclean.depends = rmlocation rmstack rmposition rmparser
QMAKE_EXTRA_TARGETS += distclean clean rmlocation rmstack rmposition rmparser

flex.CONFIG += target_predeps
bison.CONFIG += target_predeps
bisonheader.CONFIG += target_predeps



