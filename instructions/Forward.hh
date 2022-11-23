#pragma once

#include "Instruction.hh"

class Forward : public Instruction {
    public:
        unsigned int numberOfArguments() const override;
        bool execute(JardinRendering* garden, unsigned int target, std::vector<int> args) override;
};