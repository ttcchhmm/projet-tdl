#pragma once

#include "Instruction.hh"

/**
 * @brief An instruction that makes a turtle goes forward.
 */
class Forward : public Instruction<int> {
    public:
        unsigned int numberOfArguments() const override;
        bool execute(JardinRendering* const & garden, std::size_t const & target, std::vector<int> const & args) override;
};