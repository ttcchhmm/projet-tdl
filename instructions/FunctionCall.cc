#include "FunctionCall.hh"

FunctionCall::FunctionCall(std::shared_ptr<Function> function, std::vector<int> const & args): Instruction(0), _function(function), _args(args) {}

bool FunctionCall::execute(JardinRendering* const & garden) {
    return _function->execute(garden);
}