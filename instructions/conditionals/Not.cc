#include "Not.hh"

Not::Not(std::shared_ptr<Instruction> cond): Instruction(0), _cond(cond) {}

bool Not::execute(JardinRendering* const & garden) {
    return !_cond->execute(garden);
}