#pragma once

#include "Instruction.hh"

#include <string>

class Garden: public Instruction {
    private:
        std::string _filename;

    public:
        Garden(std::string const & filename);
        Garden(Garden const &) = default;
        ~Garden() override = default;

        bool execute(JardinRendering* const & garden) override;
};