#include "While.hh"

#include <iostream>

While::While(std::shared_ptr<Instruction> cond, InstructionList instructions): Instruction(0), _cond(cond), _instructions(instructions) {}

bool While::execute(Field garden) {
    while(_cond->execute(garden)) {
        for(auto const & i : _instructions) {
            if(!i->execute(garden)) {
                std::cerr << "Failed to run an instruction within a 'while' loop." << std::endl;
                return false;
            }
        }
    }

    return true;
}