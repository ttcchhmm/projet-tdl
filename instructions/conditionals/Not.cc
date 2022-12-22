#include "Not.hh"

Not::Not(std::shared_ptr<Instruction> cond): Instruction(0), _cond(cond) {}

bool Not::execute(Field garden) {
    return !_cond->execute(garden);
}