#include "Repeat.hh"

Repeat::Repeat(unsigned int amount, std::list<std::shared_ptr<Instruction>> instructions): Instruction(0), _amount(amount), _instructions(instructions) {}

bool Repeat::execute(JardinRendering* const & garden) {
    for(unsigned int i(0); i < _amount; i++) {
        for(auto const & i : _instructions) {
            if(!i->execute(garden)) {
                return false;
            }
        }
    }

    return true;
}