#include "If.hh"

#include <iostream>

If::If(std::shared_ptr<Instruction> cond, InstructionList const & instructions): Instruction(0), _cond(cond), _instructions(instructions) {}

bool If::execute(Field garden) {
    if(_cond->execute(garden)) {
        for(auto const & i : _instructions) {
            if(!i->execute(garden)) {
                std::cerr << "Failed to run instructions within an 'if' branch." << std::endl;
                return false;
            }
        }
    }

    return true;
}