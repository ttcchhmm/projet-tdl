#include "Function.hh"

void Function::addInstruction(std::shared_ptr<Instruction> const & instruction) {
    _instructions.push_back(instruction);
}

bool Function::execute(Field garden) const {
    for(auto & instruction : _instructions) {
        if(!instruction->execute(garden)) {
            return false;
        }
    }

    return true;
}