#include "Function.hh"

#include <iostream>

void Function::addInstruction(std::shared_ptr<Instruction> const & instruction) {
    _instructions.push_back(instruction);
}

bool Function::execute(Field garden) const {
    for(auto & instruction : _instructions) {
        if(!instruction->execute(garden)) {
            std::cerr << "Failed to execute a function." << std::endl;
            return false;
        }
    }

    return true;
}