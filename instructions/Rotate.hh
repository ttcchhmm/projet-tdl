#pragma once

#include "Instruction.hh"
#include "directions.hh"

/**
 * @brief An instruction that rotates a turtle.
 */
class Rotate : public Instruction<directions> {
    public:
        unsigned int numberOfArguments() const override;
        bool execute(JardinRendering* const & garden, std::size_t const & target, std::vector<directions> const & args) override;
};