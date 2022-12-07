#include "Function.hh"

Function::Function(std::string const & name): _name(name) {}

void Function::addInstruction(Instruction const & instruction) {
    _instructions.push_back(instruction);
}

void Function::execute(JardinRendering* const & garden) const {
    for(auto & instruction : _instructions) {
        instruction.execute(garden);
    }
}

std::string Function::getName() const {
    return _name;
} 