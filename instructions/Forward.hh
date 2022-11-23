#pragma once

#include "Instruction.hh"

/**
 * @brief An instruction that makes a turtle goes forward.
 */
class Forward : public Instruction {
    public:
        unsigned int numberOfArguments() const override;
        bool execute(JardinRendering* garden, unsigned int target, std::vector<int> args) override;
};