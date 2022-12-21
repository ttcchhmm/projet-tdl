#pragma once

#include "Instruction.hh"

#include <string>

enum class ColorZone {
    SHELL,
    PATTERN
};

class Color: public Instruction {
    private:
        ColorZone _zone;
        std::string _colorHexa;

    public:
        Color(std::size_t _turtle, ColorZone const & zone, std::string const & colorHexa);
        Color(Color const &) = default;
        ~Color() override = default;

        bool execute(JardinRendering* const & garden) override;
};