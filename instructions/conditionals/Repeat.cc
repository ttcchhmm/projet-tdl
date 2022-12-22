#include "Repeat.hh"

#include <iostream>

Repeat::Repeat(unsigned int amount, InstructionList instructions): Instruction(0), _amount(amount), _instructions(instructions) {}

bool Repeat::execute(Field garden) {
    for(unsigned int i(0); i < _amount; i++) {
        for(auto const & i : _instructions) {
            if(!i->execute(garden)) {
                std::cerr << "Failed to run an instruction within a 'repeat' loop." << std::endl;
                return false;
            }
        }
    }

    return true;
}