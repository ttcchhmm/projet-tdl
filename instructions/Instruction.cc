#include "Instruction.hh"

#include <iostream>

Instruction::Instruction(std::size_t turtle): _turtle(turtle) {}

bool Instruction::execute(JardinRendering* const & garden) {
    if(garden->getTortues().size() < _turtle) {
        std::cerr << "Invalid turtle ID. Got " << _turtle << " but there are " << garden->getTortues().size() << " turtle(s) on the field." << std::endl;
        return false;
    }

    return true;
}