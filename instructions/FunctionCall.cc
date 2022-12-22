#include "FunctionCall.hh"

FunctionCall::FunctionCall(std::shared_ptr<Function> function, std::shared_ptr<std::vector<double>> const & args): Instruction(0), _function(function), _args(args) {}

bool FunctionCall::execute(Field garden) {
    return _function->execute(garden);
}