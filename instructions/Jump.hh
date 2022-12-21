#pragma once

#include "Instruction.hh"

class Jump: public Instruction {
    private:
        unsigned int _amount;

    public:
        Jump(std::size_t _turtle, unsigned int amount);
        Jump(Jump const &) = default;
        ~Jump() = default;

        bool execute(JardinRendering* const & garden) override;
};