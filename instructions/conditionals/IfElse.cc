#include "IfElse.hh"

IfElse::IfElse(std::shared_ptr<Instruction> cond, InstructionList const & ifTrue, InstructionList const & ifFalse): Instruction(0), _cond(cond), _instructionsTrue(ifTrue), _instructionsFalse(ifFalse) {}

bool IfElse::execute(Field garden) {
    if(_cond->execute(garden)) {
        for(auto const & i : _instructionsTrue) {
            if(!i->execute(garden)) {
                return false;
            }
        }
    } else {
        for(auto const & i : _instructionsFalse) {
            if(!i->execute(garden)) {
                return false;
            }
        }
    }

    return true;
}