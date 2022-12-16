#pragma once

#include "Instruction.hh"

class Turtles: public Instruction {
    private:
        unsigned int _nbTurtles;

    public:
        /**
         * @brief Construct a new Turtles instance.
         * @param nbTurtles The number of turtles to spawn.
         */
        explicit Turtles(unsigned int nbTurtles);
        Turtles(Turtles const &) = default;
        ~Turtles() = default;

        bool execute(JardinRendering* const & garden) override;
};