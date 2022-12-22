#include "IfElse.hh"

IfElse::IfElse(std::shared_ptr<Instruction> cond, std::list<std::shared_ptr<Instruction>> const & ifTrue, std::list<std::shared_ptr<Instruction>> const & ifFalse): Instruction(0), _cond(cond), _instructionsTrue(ifTrue), _instructionsFalse(ifFalse) {}

bool IfElse::execute(JardinRendering* const & garden) {
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