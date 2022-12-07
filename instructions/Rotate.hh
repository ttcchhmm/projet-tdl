#pragma once

#include "Instruction.hh"
#include "directions.hh"

/**
 * @brief An instruction that rotates a turtle.
 */
class Rotate : public Instruction {
    private:
        /**
         * @brief The direction used to rotate.
         */
        directions _dir;

    public:
        /**
         * @brief Construct a new Rotate instruction. 
         *
         * @param dir The direction used to rotate.
         */
        explicit Rotate(std::size_t turtle, directions dir);
        Rotate(Rotate const &) = default;
        ~Rotate() override = default;

        bool execute(JardinRendering* const & garden) override;
};