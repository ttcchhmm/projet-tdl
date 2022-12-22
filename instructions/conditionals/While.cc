#include "While.hh"

While::While(std::shared_ptr<Instruction> cond, InstructionList instructions): Instruction(0), _cond(cond), _instructions(instructions) {}

bool While::execute(Field garden) {
    while(_cond->execute(garden)) {
        for(auto const & i : _instructions) {
            if(!i->execute(garden)) {
                return false;
            }
        }
    }

    return true;
}